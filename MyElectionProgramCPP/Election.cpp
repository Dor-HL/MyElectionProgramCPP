#define _CRT_SECURE_NO_WARNINGS
#include "Election.h"
#include "Party.h"
#include "ElectionDate.h"
#include <string>
#include "App.h"



namespace elections
{

	Election::Election(list<County*> *lst, list<Citizen*> *Clst, list<Party*> *Plst, int* partycounter, int* countycounter, int* citizencounter,ElectionDate* date)
		:_partyCounter(partycounter),_countyCounter(countycounter),_citizenCounter(citizencounter)
	{
		_date = date;
		_countylst = *lst;
		_citizenlst = *Clst;
		_partylst = *Plst;
	}
	//----------------------------------------------------------------------------------------------------------------------------------
	Election::~Election()
	{
		_date->~ElectionDate();
	}
	//-------------------------------------------------------------------------------------------------------------------------------------
	void Election::save(ostream& out) const
	{
	//now we will write the day
		out.write(rcastcc(&isSimple), sizeof(isSimple));
		int forDate = _date->getDay();
		out.write(rcastcc(&forDate), sizeof(forDate));
		forDate = _date->getMonth();
		out.write(rcastcc(&forDate), sizeof(forDate));
		forDate = _date->getYear();
		out.write(rcastcc(&forDate), sizeof(forDate));
		list<County*>::const_iterator countyit;
		out.write(rcastcc(_countyCounter), sizeof(int));

		for (countyit = _countylst.begin(); countyit != _countylst.end(); countyit++)//this loop writes into the file all the countys data
		{
				int temp = (*countyit)->getLogicSize();
				out.write(rcastcc(&temp), sizeof(int));//writes logic size to file
				out.write(rcastcc((*countyit)->getName().c_str()), temp*sizeof(char));//temp=logicSize
				temp = (*countyit)->getNumElectors();
				out.write(rcastcc(&temp), sizeof(int));
				bool tempB = (*countyit)->getIsDevided();
				out.write(rcastcc(&tempB), sizeof(bool));
		}

			out.write(rcastcc(_citizenCounter), sizeof(int));
			list<Citizen*>::const_iterator citizenit;

			if (_citizenCounter != 0)
			{
				for (citizenit = _citizenlst.begin(); citizenit != _citizenlst.end(); citizenit++)//this loop writes into the file all the countys data//this loop writes into the file all the citizens data
				{
					int temp = (*citizenit)->getLogicSize();
					out.write(rcastcc(&temp), sizeof(int));
					out.write(rcastcc((*citizenit)->getName().c_str()),temp);
					temp = (*citizenit)->getID();
					out.write(rcastcc(&temp), sizeof(int));
					temp = (*citizenit)->getYearOfBirth();
					out.write(rcastcc(&temp), sizeof(int));
					temp = (*citizenit)->getCountyID();
					out.write(rcastcc(&temp), sizeof(int));
					temp = (*citizenit)->getvoted();
					out.write(rcastcc(&temp), sizeof(int));
					temp = (*citizenit)->getIsDelegate();
					out.write(rcastcc(&temp), sizeof(int));
				}
			}
			out.write(rcastcc(_partyCounter), sizeof(int));

			if (_partyCounter != 0)
			{
				list<Party*>::const_iterator partyit;
				for(partyit=_partylst.begin();partyit!=_partylst.end();partyit++)
				{
					int tmp = (*partyit)->getLogicSize();
					out.write(rcastcc(&tmp), sizeof(int));//saves party's name logical size
					out.write(rcastcc((*partyit)->getName().c_str()), tmp);//saves party's name
					tmp = (*partyit)->getLeaderID();
					out.write(rcastcc(&tmp), sizeof(int));//saves leader's id
					int i = 0;
					int HowMantDelegates = (*partyit)->HowManyDelgates();
					out.write(rcastcc(&HowMantDelegates), sizeof(HowMantDelegates));//writes to file num of delegates
					while (i < *_countyCounter)
					{
						for (citizenit = (*partyit)->getArray()[i].begin(); citizenit != (*partyit)->getArray()[i].end(); citizenit++)//runs on delegets arr of party and saves delegate id and county
						{
							tmp = (*citizenit)->getID();
							out.write(rcastcc(&tmp), sizeof(int));//delegate ID
							tmp = i + 1;
							out.write(rcastcc(&tmp), sizeof(int));//the county the delegateis delegate of
						}
						i++;
					}
				}
			}
		
	}
	//-------------------------------------------------------------------------------------------------------------------------------------
	void Election::load(istream& in)
	{
		App a;
		while (!in.eof())
		{
			if (!in.good())
			{
				cout << "Error reading" << endl;
				exit(-1);
			}
			
			//now we will read the date from the file
			int dayt=0, montht=0, yeart = 0;
			in.read(rcastc(&dayt), sizeof(dayt));
			in.read(rcastc(&montht), sizeof(montht));
			in.read(rcastc(&yeart), sizeof(yeart));
			_date->setDate(dayt, montht, yeart);

			int tempNum = 0;
			in.read(rcastc(&tempNum), sizeof(tempNum));//reads how many countys are in the file
			*_countyCounter = tempNum;
			//we will use the next variables to send read and send data to county ctor
			int i = 0;
			int logiSize = 0;
			int countyIDt = 0;
			int numElectorst = 0;
			bool isDevidedt = false;
			while (i < *_countyCounter)//reads all countys data from file
			{
				in.read(rcastc(&logiSize), sizeof(int));//read logic size of county's name
				char* countyName;
				try
				{
					countyName = new char[logiSize + 1];//+1 for /0
				}
				catch (bad_alloc& ex)
				{
					cout << "bad allocation: " << ex.what() << endl;
					exit(3);
				}
				in.read(rcastc(countyName), logiSize);//read county's name
				countyName[logiSize] = '\0';
				string countyNameTemp;
			    countyNameTemp = (string)countyName;
				in.read(rcastc(&numElectorst), sizeof(numElectorst));//reads county's num of electors
				in.read(rcastc(&isDevidedt), sizeof(isDevidedt));//reads if county is devided or not

				if (isDevidedt == true)//if county is devided
				{
					County* c;
					try
					{
						c = new devidedCounty(countyNameTemp, numElectorst);
					}
					catch (bad_alloc& ex)
					{
						cout << "bad allocation: " << ex.what() << endl;
						exit(3);
					}
					a.AddCounty(c, _countylst);//add to county lst
				}
				else
				{
					County* c;
					try
					{
						c = new County(countyName, numElectorst);//if county is united
					}
					catch (bad_alloc& ex)
					{
						cout << "bad allocation: " << ex.what() << endl;
						exit(3);
					}
					a.AddCounty(c, _countylst);//add to county lst
				}

				i++;

			}
			

	   //now we will read the citizens from the file 
	   //variables to use
			int citizenID = 0;
			int birthYear = 0;
			int votedt = 0;
			int isDelegateT = 0;

			in.read(rcastc(&tempNum), sizeof(tempNum));//reads how many citizens we have to read
			*_citizenCounter = tempNum;
			i = 0;
			while (i < *_citizenCounter)//reads all the citizens from the file
			{
				in.read(rcastc(&logiSize), sizeof(logiSize));
				char* citizenName;
				try
				{
					citizenName = new char[logiSize + 1];
				}
				catch (bad_alloc& ex)
				{
					cout << "bad allocation: " << ex.what() << endl;
					exit(3);
				}
				in.read(rcastc(citizenName), logiSize);
				citizenName[logiSize] = '\0';
				string citizenNameTemp = (string)citizenName;
				in.read(rcastc(&citizenID), sizeof(citizenID));
				in.read(rcastc(&birthYear), sizeof(birthYear));
				in.read(rcastc(&countyIDt), sizeof(countyIDt));
				in.read(rcastc(&votedt), sizeof(votedt));
				in.read(rcastc(&isDelegateT), sizeof(isDelegateT));

				Citizen* tempCitizen;
				try
				{
					tempCitizen = new Citizen(citizenID, birthYear, citizenNameTemp, a.getData(countyIDt, _countylst));//this already finds the citizen's county and sets the pointer
				}
				catch (bad_alloc& ex)
				{
					cout << "bad allocation: " << ex.what() << endl;
					exit(3);
				}
				tempCitizen->setVoted(votedt);
				if (isDelegateT != -1)//-1 automatically when citizen is created
				{
					tempCitizen->setDelegate();
				}
				a.AddCitizen(tempCitizen,_citizenlst);//adds citizen to citizen lst
				a.getData(countyIDt,_countylst)->addCitizenToCounty(tempCitizen,_countylst);
				list<Citizen*>* tmplst = a.getData(countyIDt, _countylst)->getCitizens();
				a.getCitizen(citizenID, *tmplst)->setVoted(votedt);
				i++;
			}

			//now we will read all partys from the file
			in.read(rcastc(&tempNum), sizeof(tempNum));
			*_partyCounter = tempNum;
			i = 0;
			int delegateNum = 0;
			while (i < *_partyCounter)
			{
				in.read(rcastc(&logiSize), sizeof(logiSize));
				char* partyName;
				try
				{
					partyName = new char[logiSize + 1];
				}
				catch (bad_alloc& ex)
				{
					cout << "bad allocation: " << ex.what() << endl;
					exit(3);
				}
				in.read(rcastc(partyName), logiSize);
				partyName[logiSize] = '\0';
				string partyNameTemp = (string)partyName;
				in.read(rcastc(&citizenID), sizeof(citizenID));//gets leader id from file
				in.read(rcastc(&delegateNum), sizeof(delegateNum));
				Party* p;
				try
				{
					p = new Party(partyNameTemp, citizenID, *_countyCounter);//creates the party
				}
				catch (bad_alloc& ex)
				{
					cout << "bad allocation: " << ex.what() << endl;
					exit(3);
				}
				_partylst.push_back(p);//adds party to party lst
				int j = 0;
				while (j < delegateNum)//this loop enters the delegates of the party into the delegate arr
				{
					int delegateid = 0;
					int delegateCounty = 0;
					in.read(rcastc(&delegateid), sizeof(delegateid));
					in.read(rcastc(&delegateCounty), sizeof(delegateCounty));//reads the curr delgate county (the county he is a delegate in)
					Citizen* currD = a.getCitizen(delegateid,_citizenlst);
					Citizen* newc;
					try
					{
						newc = new Citizen(currD->getID(), currD->getYearOfBirth(), currD->getName(), a.getData(currD->getCountyID(), _countylst));
					}
					catch (bad_alloc& ex)
					{
						cout << "bad allocation: " << ex.what() << endl;
						exit(3);
					}
					p->getArray()[delegateCounty - 1].push_back(newc);//adds delegate to dynamic array
					j++;//next delegate
				}
				i++;
			}
			return;
		}
	
	
	}

	
	

	//-----------------------------------------------------------------------------------------------------------------------------------
	SimpleElection::SimpleElection(list<County*> *county, list<Citizen*>* Clst, list<Party*>* Plst, int* partycounter, int* countycounter, int* citizencounter, ElectionDate* date)
		:Election(county, Clst, Plst, partycounter, countycounter, citizencounter, date)
	{
		isSimple = true;
	}
	//-------------------------------------------------------------------------------------------------------------------------------------
	SimpleElection::~SimpleElection(){}
	//-------------------------------------------------------------------------------------------------------------------------------------
	 void SimpleElection::save(ostream& out) const
	{
		 out.write(rcastcc(&isSimple), sizeof(isSimple));
		 int forDate = _date->getDay();
		 out.write(rcastcc(&forDate), sizeof(forDate));
		 forDate = _date->getMonth();
		 out.write(rcastcc(&forDate), sizeof(forDate));
		 forDate = _date->getYear();
		 out.write(rcastcc(&forDate), sizeof(forDate));
		 list<County*>::const_iterator countyit;
		 countyit = _countylst.begin();//sets iterator to begining
		//there is only one county in a simple election 
		int temp = (*countyit)->getLogicSize();
		out.write(rcastcc(&temp), sizeof(int));//writes logic size to file
		out.write(rcastcc((*countyit)->getName().c_str()), temp * sizeof(char));//temp=logicSize
		temp = (*countyit)->getNumElectors();
		out.write(rcastcc(&temp), sizeof(int));
		list<Citizen*>::const_iterator citizenit;
		 
		 out.write(rcastcc(_citizenCounter), sizeof(int));
		 if (_citizenCounter != 0)
		 {
			 for (citizenit = _citizenlst.begin(); citizenit != _citizenlst.end(); citizenit++)//this loop writes into the file all the countys data//this loop writes into the file all the citizens data
			 {
				 int temp = (*citizenit)->getLogicSize();
				 out.write(rcastcc(&temp), sizeof(int));
				 out.write(rcastcc((*citizenit)->getName().c_str()), temp);
				 temp = (*citizenit)->getID();
				 out.write(rcastcc(&temp), sizeof(int));
				 temp = (*citizenit)->getYearOfBirth();
				 out.write(rcastcc(&temp), sizeof(int));
				 temp = (*citizenit)->getvoted();
				 out.write(rcastcc(&temp), sizeof(int));
				 temp = (*citizenit)->getIsDelegate();
				 out.write(rcastcc(&temp), sizeof(int));
			 }
		 }
		 out.write(rcastcc(_partyCounter), sizeof(int));

		 if (_partyCounter != 0)
		 {
			 list<Party*>::const_iterator partyit;
			 for(partyit=_partylst.begin();partyit!=_partylst.end();partyit++)
			 {
				 int tmp = (*partyit)->getLogicSize();
				 out.write(rcastcc(&tmp), sizeof(int));//saves party's name logical size
				 out.write(rcastcc((*partyit)->getName().c_str()), tmp);//saves party's name
				 tmp = (*partyit)->getLeaderID();
				 out.write(rcastcc(&tmp), sizeof(int));//saves leader's id
				 int HowMantDelegates = (*partyit)->HowManyDelgates();
				 out.write(rcastcc(&HowMantDelegates), sizeof(HowMantDelegates));//writes to file num of delegates
				
					 for (int i = 0; i < *_countyCounter; i++)
					 {
						 for (citizenit = (*partyit)->getArray()[i].begin(); citizenit != (*partyit)->getArray()[i].end(); citizenit++)
						 {
							 tmp = (*citizenit)->getID();
							 out.write(rcastcc(&tmp), sizeof(int));//delegate ID
						 }
					 }
			 }
		 }

		 
	}
	 //-------------------------------------------------------------------------------------------------------------------------------------
	 void SimpleElection::load(istream& in)
	 {
		 App a;
		 while (!in.eof())
		 {
			 if (!in.good())
			 {
				 cout << "Error reading" << endl;
				 exit(-1);
			 }

			 //now we will read the date from the file
			 int dayt = 0, montht = 0, yeart = 0;
			 in.read(rcastc(&dayt), sizeof(dayt));
			 in.read(rcastc(&montht), sizeof(montht));
			 in.read(rcastc(&yeart), sizeof(yeart));
			 _date->setDate(dayt, montht, yeart);

			 int tempNum = 0;
		
			 *_countyCounter = 1;//in a simpleElection there is only 1 county 
			 //we will use the next variables to send read and send data to county ctor

			 int logiSize = 0;
			 int numElectorst = 0;
			
				 in.read(rcastc(&logiSize), sizeof(int));//read logic size of county's name
				 char* countyName;
				 try
				 {
					 countyName = new char[logiSize + 1];//+1 for /0
				 }
				 catch (bad_alloc& ex)
				 {
					 cout << "bad allocation: " << ex.what() << endl;
					 exit(3);
				 }
				 in.read(rcastc(countyName), logiSize);//read county's name. size of countyName or size of logicSize?
				 countyName[logiSize] = '\0';
				 in.read(rcastc(&numElectorst), sizeof(numElectorst));//reads county's num of electors
				 County* c;
				 try
				 {
					 c = new devidedCounty(countyName, numElectorst);
				 }
				 catch (bad_alloc& ex)
				 {
					 cout << "bad allocation: " << ex.what() << endl;
					 exit(3);
				 }
				a.AddCounty(c,_countylst);//add to county lst
		

		//now we will read the citizens from the file 
		//variables to use
			 int citizenID = 0;
			 int birthYear = 0;
			 int votedt = 0;
			 int isDelegateT = 0;

			 in.read(rcastc(&tempNum), sizeof(tempNum));//reads how many citizens we have to read
			 *_citizenCounter = tempNum;
			int i = 0;
			 while (i < *_citizenCounter)//reads all the citizens from the file
			 {
				 in.read(rcastc(&logiSize), sizeof(logiSize));
				 char* citizenName;
				 try
				 {
					 citizenName = new char[logiSize + 1];
				 }
				 catch (bad_alloc& ex)
				 {
					 cout << "bad allocation: " << ex.what() << endl;
					 exit(3);
				 }
				 in.read(rcastc(citizenName), logiSize);
				 citizenName[logiSize] = '\0';
				 in.read(rcastc(&citizenID), sizeof(citizenID));
				 in.read(rcastc(&birthYear), sizeof(birthYear));
				 in.read(rcastc(&votedt), sizeof(votedt));
				 in.read(rcastc(&isDelegateT), sizeof(isDelegateT));

				 Citizen* tempCitizen;
				 try
				 {
					 tempCitizen = new Citizen(citizenID, birthYear, citizenName, a.getData(1, _countylst));//this already finds the citizen's county and sets the pointer
				 }
				 catch (bad_alloc& ex)
				 {
					 cout << "bad allocation: " << ex.what() << endl;
					 exit(3);
				 }
				 tempCitizen->setVoted(votedt);
				 if (isDelegateT != -1)//-1 automatically when citizen is created
				 {
					 tempCitizen->setDelegate();
				 }
				a.AddCitizen(tempCitizen,_citizenlst);//adds citizen to citizen lst
				 a.getData(1,_countylst)->addCitizenToCounty(tempCitizen, _countylst);
				 list<Citizen*>* tmplst = a.getData(1, _countylst)->getCitizens();
				 a.getCitizen(citizenID, *tmplst)->setVoted(votedt);
				 i++;
			 }

			 //now we will read all partys from the file
			 in.read(rcastc(&tempNum), sizeof(tempNum));
			 *_partyCounter = tempNum;
			 i = 0;
			 int delegateNum = 0;
			 while (i < *_partyCounter)
			 {
				 in.read(rcastc(&logiSize), sizeof(logiSize));
				 char* partyName;
				 try
				 {
					 partyName = new char[logiSize + 1];
				 }
				 catch (bad_alloc& ex)
				 {
					 cout << "bad allocation: " << ex.what() << endl;
					 exit(3);
				 }
				 in.read(rcastc(partyName), logiSize);
				 partyName[logiSize] = '\0';
				 in.read(rcastc(&citizenID), sizeof(citizenID));//gets leader id from file
				 in.read(rcastc(&delegateNum), sizeof(delegateNum));
				 Party* p;
				 try
				 {
					 p = new Party(partyName, citizenID, *_countyCounter);//creates the party
				 }
				 catch (bad_alloc& ex)
				 {
					 cout << "bad allocation: " << ex.what() << endl;
					 exit(3);
				 }
				 _partylst.push_back(p);//adds party to party lst
				 int j = 0;
				 while (j < delegateNum)//this loop enters the delegates of the party into the delegate arr
				 {
					 int delegateid = 0;
					 in.read(rcastc(&delegateid), sizeof(delegateid));
					 Citizen* currD = a.getCitizen(delegateid,_citizenlst);
					 Citizen* newc;
					 try
					 {
						 newc = new Citizen(currD->getID(), currD->getYearOfBirth(), currD->getName(), a.getData(currD->getCountyID(), _countylst));
					 }
					 catch (bad_alloc& ex)
					 {
						 cout << "bad allocation: " << ex.what() << endl;
						 exit(3);
					 }
					 p->getArray()[0].push_back(newc);//adds delegate to dynamic array
					 j++;//next delegate
				 }
				 i++;
			 }
			 return;
		 }
		

	 }
}


