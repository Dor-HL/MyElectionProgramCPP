#define _CRT_SECURE_NO_WARNINGS
#include "App.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include "Party.h"
using namespace std;
#define MAX 100

namespace elections
{
	void App:: AddCounty(County* newCounty, list<County*>& countylist)
	{
		countylist.push_back(newCounty);
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Citizen* App::getCitizen(int i, list<Citizen*> citizenlist) const//finds citizen via id
	{
			list<Citizen*>::const_iterator it;

			if (citizenlist.empty() == true)//if lst is empty
				return nullptr;

			for (it = citizenlist.begin(); it !=citizenlist.end(); it++)
			{
				if ((*it)->getID() == i)
					return *it;

			}
				return nullptr;
		
	}
	//-----------------------------------------------------------------------------------------------------
	void App::AddToCandidateList(Citizen* newCitizen, int county, list<County*> countylist, list<Party*> &partylist, int partyID)//this func adds a citizen to the candidate lst
	{
		int c = county;
		Citizen* newc;
		County* tempc = getData(newCitizen->getCountyID(), countylist);
		try
		{
			newc = new Citizen(newCitizen->getID(), newCitizen->getYearOfBirth(), newCitizen->getName(), tempc);
		}
		catch(bad_alloc& ex)
		{
			cout <<"bad allocation: " <<ex.what() << endl;
			exit(3);
		}
		Party* temp = findParty(partyID, partylist);
		temp->CandidatesList[c - 1].push_back(newc);
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

	void App::printAllCounties(list<County*> countylist,bool isSimpleElection)
	{
		if (isSimpleElection == true)
		{
			throw "ERROR THERE ARE NO COUNTIES IN A SIMPLE ELECTION";
		}
		if (countylist.empty())
		{
			throw "ERROR THERE ARE NO COUNTIES YET";
		}
		list<County*>::const_iterator it;
		for (it = countylist.begin(); it != countylist.end(); it++)
		{
			cout << *(*it) << endl;
		}
		return;
	}
	//------------------------------------------------------------------------------------------------------
	void App::AddCitizen(Citizen* newCitizen, list<Citizen*>& citizenlist)
	{
		citizenlist.push_back(newCitizen);
	}

	//--------------------------------------------------------------------------------------------------------------------------
	void App::createNewCounty(string countyname, int numOfDelegates, list<County*>& countyLst, int type)
	{
		County* c;
		if (type == 1)
		{
			try
			{
				c = new County(countyname, numOfDelegates);
			}
			 catch (bad_alloc& ex)
			 {
				 cout << "bad allocation: " << ex.what() << endl;
				 exit(3);
			 }
			countyLst.push_back(c);
		}
		else
		{
			try
			{
				c = new devidedCounty(countyname, numOfDelegates);
			}
			catch (bad_alloc& ex)
			{
				cout << "bad allocation: " << ex.what() << endl;
				exit(3);
			}
			countyLst.push_back(c);
		}
	}
	//----------------------------------------------------------------------------------------------------------------------------------
	void App::printAllCitizens(list<Citizen*> citizenlist)
	{
		if (citizenlist.empty())
		{
			throw "EROR! NO CITIZENTS FOUND. PLEASE ENTER A CITIZEN FIRST!";
		}
		list<Citizen*>::const_iterator it;
		for (it = citizenlist.begin(); it != citizenlist.end(); it++)
		{

			cout << *(*it) << endl;

		}

		return;
	}

	//----------------------------------------------------------------------------------------------------------------------

	void App::addNewCitizen(string citizenname, int citizenid, int yearofbirth, int citizencounty, list<Citizen*>& Clst, list<County*> countyLst)
	{
		Citizen* c;
		County* tempc = getData(citizencounty, countyLst);
		try
		{
			c = new Citizen(citizenid, yearofbirth, citizenname, tempc);
		}
		catch (bad_alloc& ex)
		{
			cout << "bad allocation: " << ex.what() << endl;
			exit(3);
		}
		catch (const char* statement)
		{
			throw statement;
		}
		AddCitizen(c,Clst);
		list<County*>::iterator it;
		for (it = countyLst.begin();  it != countyLst.end(); it++)
		{
			if ((*it)->getID() == citizencounty)
			{
				(*it)->addCitizenToCounty(c, countyLst);
				return;
			}

		}
		
	}	
	//----------------------------------------------------------------------------------------------------------------------------------
	County* App::getData(int i, list<County*> countylist) const
	{
		list<County*>::const_iterator it;

		if (countylist.empty() == true)//if lst is empty
			return nullptr;

		for (it = countylist.begin(); it != countylist.end(); it++)
		{
			if ((*it)->getID() == i)
				return *it;

		}

		return nullptr;
	}
	//--------------------------------------------------------------------------------------------------------------
	void App::createNewParty(string partyName, int leaderid, list<Party*>& partylist,int countycounter)
	{
		Party* p;
		try
		{
			p = new Party(partyName, leaderid, countycounter);
		}
		catch (bad_alloc& ex)
		{
			cout << "bad allocation: " << ex.what() << endl;
			exit(3);
		}
		partylist.push_back(p);
	}
	//--------------------------------------------------------------------------------------------------------------------------------
	void App::AddCountyCase(bool isSimpleElection,list<County*>& countylist,list<Party*>& partylist, int* countycounter )
	{
		string countyname;
		int numOfDelegates = 0;
		int countyType = 0;
		
			if (isSimpleElection == true)//if this is a simple election there is only one single county that is backend handled
			{
				throw "ERROR Type <There are no added counties in a simple election>";
			}
		cout << "Please enter the county name(one word, no spaces)" << endl;
		cin >> countyname;
		cout << "Please enter the num of delegates in said county" << endl;
		cin >> numOfDelegates;
		
		while (numOfDelegates <= 0)
		{
			cout << "NUMBER OF DELEGATES HAVE TO BE BIGGER THAN 0! PLEASE ENTER A VALID NUMBER" << endl;
			cin >> numOfDelegates;		
		}
			
		cout << "Please enter the county's type" << endl;
		cout << "press 1 for united county" << endl;
		cout << "press 2 for devided county" << endl;
		cin >> countyType;

		while (countyType != 1 && countyType != 2)
		{
			cout<<"INVALUD TYPE.PLEASE ENTER A VALID OPTION"<<endl;
			cin >> countyType;	
			
		}
		try
		{
			createNewCounty(countyname, numOfDelegates, countylist, countyType);
		}
		catch (const char* statement)
		{
			cout << statement << endl;
			return;
		}
		(*countycounter)++;

		if (partylist.empty() == false)
		{
			resizeAllDynArrays(partylist, *countycounter, countylist);//this checks the sizes of the dyn arrays in each party and resizes them if counties get too big
		}
		return;
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
	bool App::isNineDigit(int id)
	{
		int count = 0;
		while (id != 0)
		{
			id = id / 10;
			count++;
		}
		if (count == 9)
			return true;
		else
			return false;

	}
	//----------------------------------------------------------------------------------------------------------------------------------
	void App::AddCitizenCase(int elecyear,int countycounter, list<Citizen*>& citizenlist, bool isSimpleElection,int* citizencounter, list<County*>& countylist )
	{
		string citizenname;
		int citizenid;
		int yearofbirth;
		int citizencounty;

		if (countycounter == 0)
		{
			throw "EROR!, No countys found! please enter a county before entering a citizen!";
		}

		else
		{
			cout << "Please enter the citizen's name (one word, no spaces)" << endl;
			cin >> citizenname;
			cout << "Please enter the citizen's id" << endl;
			cin >> citizenid;
	
			//NOTE: VALIDATION CHECK IS BOTH IN APP AND  IN THE CTOR AS INSTRUCTED BY THE PROFESSOR IN THE FORUM! ENTER FULL CITIZEN TO SEE ERROR


			while ((!isNineDigit(citizenid)) || (getCitizen(citizenid, citizenlist) != nullptr)|| citizenid<=0)
			{

				if (!isNineDigit(citizenid))
				{
					cout << "ID LENGTH SHOULD BE EXACTLY 9-PLEASE RE-ENTER A VALID ID"<<endl;
				}
				
				else if ((getCitizen(citizenid, citizenlist) != nullptr))
				{
					cout << "THIS ID ALREADY EXISTS, PLEASE RE ENTER A VALID ID" << endl;
				}
				else
				{
					cout << "ID NUMBER CANNOT BE NEGATIVE" << endl;
				}
				
				cin >> citizenid;

			}
						

			cout << "Please enter year of birth" << endl;
			cin >> yearofbirth;
			while (yearofbirth <= 0)
			{
				cout << "YEAR NEEDS TO BE GREATER THEN 0. PLEASE ENTER A VALID YEAR!" << endl;
				cin >> yearofbirth;
			}

			if (elecyear-yearofbirth<18)//if citizen is younger then 18
			{
				throw "ERROR! YOU ARE NOT 18 YET, PLEASE COME BACK WHEN YOU ARE OLDER!";
			}

			if (isSimpleElection == false)
			{
				cout << "Please enter county id" << endl;
				cin >> citizencounty;
				while (countycounter < citizencounty || citizencounty <= 0)
				{
						
					cout<<"ERROR! County does not exist Please enter a valid county id"<<endl;
					cin >> citizencounty;	
				}
			}
			else
			{
				citizencounty = 1;
			}
		
			try
			{
				addNewCitizen(citizenname, citizenid, yearofbirth, citizencounty, citizenlist, countylist);
			}
			catch (const char* statement)
			{
				cout << statement << endl;
				return;
			}
			(*citizencounter)++;
		}
		return;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------------
	void App:: loadElectionCase(bool* isSimpleElection, list<Citizen*>* citizenlist, list<Party*>* partylist, list<County*>* countylist, int* countycounter, int* partycounter, int* citizencounter, int* electionType, ElectionDate& date)
	{
		//first we will empty all existing lists and data 
		list<County*>::const_iterator countyit;
		list<Party*>::const_iterator partyit;

		for (countyit = countylist->begin(); countyit != countylist->end(); countyit++)//this for loop initializes the static int back to 0 (this int represents the county's id)
		{
			(*countyit)->setStaticID();
		}
		for (partyit = partylist->begin(); partyit != partylist->end(); partyit++)//this for loop initializes the static int back to 0 (this int represents the party's id)
		{
			(*partyit)->setStaticID();
		}
		countylist->clear();
		citizenlist->clear();
		partylist->clear();
		*countycounter = 0;
		*citizencounter = 0;
		*partycounter = 0;
		date.setDate(0, 0, 0);
		char* fileName;
		try
		{
			fileName = new char[MAX]();
		}
		catch (bad_alloc& ex)
		{
			cout << "bad allocation: " << ex.what() << endl;
			exit(3);
		}
		cout << " please enter the file's name " << endl;
		cin >> fileName;
		ifstream infile(fileName, ios::binary);
		if (!infile)
		{
			cout << "ERROR with infile" << endl;
			exit(-1);
		}
		bool readIntoSimple;
		infile.read(rcastc(&readIntoSimple), sizeof(readIntoSimple));
		*electionType = readIntoSimple + 1;
		Election* loadData;
		if (*electionType == 1)
		{
			*isSimpleElection = false;
			try
			{
				loadData = new Election(countylist, citizenlist, partylist, partycounter, countycounter, citizencounter, &date);
			}
			catch (bad_alloc& ex)
			{
				cout << "bad allocation: " << ex.what() << endl;
				exit(3);
			}
		}

		else
		{
			*isSimpleElection = true;
			try
			{
				loadData = new SimpleElection(countylist, citizenlist, partylist, partycounter, countycounter, citizencounter, &date);
			}
			catch (bad_alloc& ex)
			{
				cout << "bad allocation: " << ex.what() << endl;
				exit(3);
			}
		}
		loadData->load(infile);//polymorphism
		*countylist = loadData->getCountyLst();
		*citizenlist = loadData->getCitizenLst();
		*partylist = loadData->getPartyLst();
		return;
	}
	
	//--------------------------------------------------------------------------------------------------------------------------------------------------
	void App::voteCase(int citizencounter, int partycounter,list<County*>& countylist,list<Citizen*>& citizenlist )
	{
		int citizenid = 0;
		int partyid;
		Citizen* temp = nullptr;
		if (citizencounter == 0 || partycounter == 0)
		{
			throw "EROR! NO CITIZEN FOUND OR NO PARTY FOUND. PLEASE ENTER MISSING OBJECT FIRST!";
		}
		else
		{
			cout << "Please enter an id" << endl;
			cin >> citizenid;
			temp = getCitizen(citizenid, citizenlist);

			if (temp == nullptr)
			{
				throw "CITIZEN NOT FOUND. PLEASE ENTER A VALID ID";
			}
			int cID = temp->getCountyID();
			if (temp->getvoted() != -1)
			{
				throw "YOU ALREADY VOTED! YOU CANNOT VOTE AGAIN";
			}
			else
			{
				cout << "Please enter a party id you want to vote for- please remember you can only vote once, do so wisely :)" << endl;
				cin >> partyid;
				while (partyid > partycounter || partyid <= 0)
				{
					cout << "THIS PARTY DOES NOT EXIST, PLEASE ENTER A VALID PARTY ID" << endl;
					cin >> partyid;
				}
				temp->setVoted(partyid);

				list<Citizen*>* tmplst = getData(cID, countylist)->getCitizens();
				getCitizen(citizenid, *tmplst)->setVoted(partyid);
			}
			return;
		}
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------
	void App::addPartyCase(int citizencounter,list<Citizen*>& citizenlist,list<Party*>& partylist, int countycounter, int* partycounter)
	{
		string partyName;
		int leaderid;
		Citizen* temp;

		if (citizencounter == 0)
		{
			throw "EROR! NO CITIZENS FOUND! PLEASE CREATE A CITIZEN FIRST!";
		
		}
		else
		{
			cout << "Please enter the party name(one word, no spaces)" << endl;
			cin >> partyName;
			cout << "Please enter the leader's id" << endl;
			cin >> leaderid;
			temp = getCitizen(leaderid, citizenlist);
			if (temp == nullptr)
			{
				throw "ERROR! LEADER DOES NOT EXIST WITHIN CITIZEN LIST";
			}
			else if(temp->getIsDelegate() != -1)
			{
				throw "EROR! THIS CITIZEN IS ALREADY A DELEGATE OR PARTY LEADER. CANNOT BE CHOSEN AGAIN!";
			}
				
			temp->setDelegate();
			try
			{
				createNewParty(partyName, leaderid, partylist, countycounter);
			}
			catch (const char* statement)
			{
				cout << statement << endl;
				return;
			}
			(*partycounter)++;
		}
		return;
	}
	//-------------------------------------------------------------------------------------------------------------------------------------
	void App::addDelegateToPartyCase(int partycounter,list<Citizen*>& citizenlist,bool isSimpleElection, int countycounter, list<Party*>& partylist, list<County*>& countylist )
	{
		int citizenid = 0;
		Citizen* temp = nullptr;
		int partyid;
		int countyid;
		if (partycounter == 0)
		{
			throw "EROR! NO PARTY FOUND! PLEASE ENTER A PARTY FIRST!";
		}
		else
		{
			cout << "please enter a citizen's id" << endl;
			cin >> citizenid;
			temp = getCitizen(citizenid, citizenlist);


			if (temp->getIsDelegate() != -1)
			{
				if (temp->getIsDelegate() == 0)//if citizen does not exist
				{
					throw "EROR! CITIZEN ID DOES NO EXIST.";
				}
				else//if citizen already delegate
				{
					throw "THIS CITIZEN IS ALREADY A DELEGATE/LEADER.";
				}

			}

			cout << "Please enter party id" << endl;
			cin >> partyid;

			while (partyid > partycounter || partyid <= 0)
			{
				cout << "PARTY ID DOES NOT EXIST. PLEASE ENTER A VALID PARTY ID" << endl;
			    cin >> partyid;
			}

			if (isSimpleElection == false)
			{
				cout << "Please enter county id" << endl;
				cin >> countyid;
				while (countyid > countycounter || countycounter == 0||countyid<=0)
				{
				  cout<<"COUNTY ID DOES NOT EXIST. PLEASE ENTER A VALID COUNTY ID!"<<endl;
				  cin >> countyid;
				}
			}
			else
			{
				countyid = 1;
			}
			addDelegateToPartyByCounty(temp, partyid, countyid, partylist, countylist);
			temp->setDelegate();
			return;
		}
	}
	//------------------------------------------------------------------------------------------------------------------------------------
	void App::saveElectionCase(list<Citizen*> citizenlist, list<Party*> partylist, list<County*> countylist, int countycounter, int partycounter, int citizencounter,int electionType, ElectionDate date)
	{
		char* fileName;
		try
		{
			fileName = new char[MAX]();
		}
		catch (bad_alloc& ex)
		{
			cout << "bad allocation: " << ex.what() << endl;
			exit(3);
		}
		cout << " please enter the file's name " << endl;
		cin >> fileName;
		ofstream outfile(fileName, ios::binary);
		Election* saveData;
		if (!outfile)
		{
			cout << "ERROR with outfile" << endl;
			exit(-1);
		}

		if (electionType == 1)
		{
			try
			{
				saveData = new Election(&countylist, &citizenlist, &partylist, &partycounter, &countycounter, &citizencounter, &date);
			}
			catch (bad_alloc& ex)
			{
				cout << "bad allocation: " << ex.what() << endl;
				exit(3);
			}
		}
		else
		{
			try
			{
				saveData = new SimpleElection(&countylist, &citizenlist, &partylist, &partycounter, &countycounter, &citizencounter, &date);
			}
			catch (bad_alloc& ex)
			{
				cout << "bad allocation: " << ex.what() << endl;
				exit(3);
			}
		}
		saveData->save(outfile);//polymorphism


		outfile.close();
		return;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------
	void App::addDelegateToPartyByCounty(Citizen* temp, int partyid, int countyid, list<Party*>& partylist, list<County*> countylist)
	{
		list<Party*>::const_iterator it;
		for (it = partylist.begin(); it != partylist.end(); it++)
		{
			if ((*it)->getID() == partyid)
			{
				AddToCandidateList(temp, countyid, countylist,partylist, partyid);
			}
		}
	
	}
	//----------------------------------------------------------------------------------------------------------------------------------


	void App::resizeAllDynArrays(list<Party*>& partylist,int countycounter, list<County*> countylist)
	{
		list<Party*>::const_iterator partyit;
		for(partyit=partylist.begin();partyit!=partylist.end();partyit++)
		{
			if ((*partyit)->getArray().capacity()<=countycounter)
			{
				(*partyit)->getArray().resize();
			}
		
			(*partyit)->getArray().setSize(countycounter);
		}
	}
	//----------------------------------------------------------------------------------------------------------------------------------

	void App::display()
	{
		cout << "Please enter the number corresponding with the following list" << endl;
		cout << "Press 1 to add a county" << endl;
		cout << "Press 2 to add a citizen" << endl;
		cout << "Press 3 to add a party" << endl;
		cout << "Press 4 to add a citizen as a party delegate" << endl;
		cout << "Press 5 to display all counties" << endl;
		cout << "Press 6 to display all citizens" << endl;
		cout << "Press 7 to display all parties" << endl;
		cout << "Press 8 to enter a vote" << endl;
		cout << "Press 9 to display the election's results" << endl;
		cout << "Press 10 to Exit the application" << endl;
		cout << "Press 11 to save current election round" << endl;
		cout << "Press 12 to load existing election round" << endl;

	}
	//----------------------------------------------------------------------------------------------------------------------------------

	void App::DisplayElectionOptions()
	{
		cout << "Please enter the number corresponding with the following list" << endl;
		cout << "Press 1 to make a new election round" << endl;
		cout << "Press 2 to load existing round" << endl;
		cout << "Press 3 to exit the program" << endl;
	}
	//----------------------------------------------------------------------------------------------------------------------------------
	Party* App::findParty(int k, list<Party*> partylist)
	{
		list<Party*>::const_iterator it;
		for (it = partylist.begin(); it != partylist.end(); it++)
		{
			if ((*it)->getID() == k)
				return *it;
		}
	
		return nullptr;
	}
	//---------------------------------------------------------------------------------------------------------------------------------------
	void App:: printAllParties(list<Citizen*> citizenlist, list<Party*> partylist)//the list of all citizens
	{
		App a;
		if (partylist.empty())
		{
			throw "EROR! NO PARTYS FOUND. PLEASE ADD A PARTY FIRST!";
		}
		list<Party*>::const_iterator partyit;
		for (partyit = partylist.begin(); partyit != partylist.end(); partyit++)
		{
			cout << (**partyit)<< "The leader's name is: " << getCitizen((*partyit)->getLeaderID(), citizenlist)->getName() << endl;
			(*partyit)->PrintCandidateList(*partyit);


		}
	}
	//---------------------------------------------------------------------------------------------------------------------------------
	void App::DisplayResByParty(int partycounter, int* copyDelegateArr,list<Party*> PLst, int* DelegateArr,list<Citizen*> Clst,int* votesArray,int* cwinner, County* curr, int countedvotes)
	{
		for (int k = 1; k < partycounter + 1; k++)//prints the precentage of votes each party got and how many votes
		{
			int maxDelegates = -1;
			int maxIndex = 0;
			for (int j = 0; j < partycounter; j++)
			{
				if (copyDelegateArr[j] >= maxDelegates)
				{
					if (copyDelegateArr[j] != maxDelegates)
					{
						maxDelegates = copyDelegateArr[j];
						maxIndex = j;
					}
				}

			}
			copyDelegateArr[maxIndex] = -2;
			Party* currp = findParty((maxIndex + 1),PLst);//locates the party via party id
			if (DelegateArr[maxIndex] != 0)
			{
				cout << "The party leader's name is " << getCitizen(currp->getLeaderID(),Clst)->getName() << endl;
				cout << currp->getName() << "Party ID " << maxIndex + 1 << " has received " << votesArray[maxIndex + 1] << " votes " << endl;
				if (countedvotes == 0)
				{
					cout << "The Party got " << 0 << "% " << "of all votes in the county" << endl;//this calc is correct
				}

				else
				{
					cout << "The Party got " << (((float)votesArray[maxIndex + 1] * 100) / (float)countedvotes) << "% " << "of all votes in the county" << endl;//this calc is correct
				}
				if (curr->getIsDevided() == true)//if devided county
				{
					cout <<"The party got " << DelegateArr[maxIndex] << " delagets in this county " << endl;//if  normal print numElectors
				}
				else//if united county
				{
					if (currp->getID() == *cwinner)
					{
						cout << "The party got " << curr->getNumElectors() << " delagets in this county " << endl;
					}
					else
						cout << "The party got " << 0 << " delagets in this county " << endl;
				}
				cout << "\n";

				cout << "The chosen delegates from this party are: " << endl;
				list<Citizen*>::const_iterator citizenit;
				int p = 0;
				while (p < DelegateArr[maxIndex])
				{
					if (currp->getArray()[curr->getID() - 1].begin() == currp->getArray()[curr->getID() - 1].end())
					{
						cout << "\n";
						throw "ERROR,NOT ENOUGH DELEGATES IN THE PARTY ";
					}
					for (citizenit = currp->getArray()[curr->getID() - 1].begin(); citizenit != currp->getArray()[curr->getID() - 1].end(); citizenit++)
					{
						cout << (*citizenit)->getName() << endl;
						p++;
						if (p >= DelegateArr[maxIndex])
						{
							break;
						}
					}
				}
				cout << "\n";
			}
		}
	}
	//----------------------------------------------------------------------------------------------------------------------------------

	void App:: DisplayElectionRes(list<Party*> PLst, list<Citizen*> Clst, list<County*> countyLst, int countycounter, int partycounter, bool isSimpleElection,ElectionDate * date)
	{
		if (countyLst.empty())
		{
			throw "ERROR THERE ARE NO COUNTIES YET";
		}
		if (Clst.empty())
		{
			throw "ERROR THERE ARE NO CITIZENS YET";
		}
		if (PLst.empty())
		{
			throw "ERROR THERE ARE NO PARTIES YET";
		}
		App a;
		int TheWinner = 0;
		int partyCounterwithOne = partycounter + 1;
		int* sumOfDelegates;
		int* sumOfVotes;
		try
		{
			sumOfDelegates = new int[partycounter]();//hold the num of delegates for each party (arr[i-1]==num of delagates in i party)
		}
		catch (bad_alloc& ex)
		{
			cout << "bad allocation: " << ex.what() << endl;
			exit(3);
		}
		try
		{
			sumOfVotes = new int[partyCounterwithOne]();//same but with votes, arr[0] holds num of citizens who didnt vote. 
		}
		catch (bad_alloc& ex)
		{
			cout << "bad allocation: " << ex.what() << endl;
			exit(3);
		}
		
		list<County*>::const_iterator countyit;
		list<Citizen*>::const_iterator citizenit;

		cout << *date << endl;//calls for printing operator of date
		for (countyit = countyLst.begin(); countyit != countyLst.end(); countyit++)//for loop that runs on all county's
		{
			int* votesArray;
			try
			{
				votesArray = new int[partycounter + 1]();
			}
			catch (bad_alloc& ex)
			{
				cout << "bad allocation: " << ex.what() << endl;
				exit(3);
			}
			if (isSimpleElection == false)
			{
				cout << "The county's name is: " << (*countyit)->getName() << endl;

				if ((*countyit)->getIsDevided() == true)
					cout << "this county is a devided county" << endl;
				else
					cout << "this county is a united county" << endl;

				cout << "The number of delegates in this county is: " << (*countyit)->getNumElectors() << endl;
				cout << "\n";
			}

			for(citizenit=(*countyit)->getCitizens()->begin();citizenit!= (*countyit)->getCitizens()->end();citizenit++)//runs on citizen's list inside county. counts citizens votes and puts it into votes arr (votesarr[i] is number of votes for party id i)
			{
				int vote =(*citizenit)->getvoted();
				if (vote == -1)
				{
					votesArray[0]++;//saves the numbers of people who didn't vote
					sumOfVotes[0]++;
				}
				else
				{
					votesArray[vote]++;
					sumOfVotes[vote]++;
				}
			}
			int allvotes = 0;
			int cwinner = 1;
			int didntvote = votesArray[0];
			for (int k = 0; k < partycounter + 1; k++)//finds the winning party of the county
			{
				if ((*(votesArray + cwinner) < *(votesArray + k)) && (k > 0))
					cwinner = k;

				allvotes += votesArray[k];
			}
			float precentage;
			if (allvotes == 0)
			{
				precentage = 0;
			}

			else
			{
				precentage = (float)(100 - (((float)didntvote * 100) / (float)allvotes));
			}
			if (isSimpleElection == false)
			{
				cout << "now we will present the county's result!" << endl;
				cout << "\n";
				
				if ((*countyit)->getIsDevided() == false)
				{
					cout << "The winner who got most votes in this county is: " << getCitizen(findParty(cwinner,PLst)->getLeaderID(),Clst)->getName() << endl;
				}
				cout << "The voting precentage in this county is: " << precentage << "% " << endl;
				cout << "\n";
			}
			else//if is simple
			{
				cout << "now we will present the results!" << endl;
				cout << "\n";
				if (isSimpleElection == false)
				{
					cout << "The winner is: " << getCitizen(findParty(cwinner,PLst)->getLeaderID(),Clst)->getName() << endl;
				}
				cout << "The voting precentages are: " << precentage << "% " << endl;
				cout << "\n";
			}
			int delegateNum = 0;
			int countedvotes = allvotes - didntvote;
			float delegateAvg = (float)(((countedvotes) / (float)((*countyit)->getNumElectors())));
			int* DelegateArr;
			try 
			{
				DelegateArr = new int[partycounter]();
			}
			catch (bad_alloc& ex)
			{
				cout << "bad allocation: " << ex.what() << endl;
				exit(3);
			}
			float* copyVotesArray;
			try 
			{
				copyVotesArray = new float[partycounter + 1];
			}
			catch (bad_alloc& ex)
			{
				cout << "bad allocation: " << ex.what() << endl;
				exit(3);
			}
			for (int h = 0; h < partycounter + 1; h++)
			{
				copyVotesArray[h] = (float)votesArray[h];
			}

			(*countyit)->calculateRes((*countyit)->getNumElectors(), partycounter, copyVotesArray, DelegateArr, delegateAvg, sumOfDelegates);//polymorphism , it will go to the right function based on the type of county

			cout << "Now we will present the list of elected delegates and voting precentage per party " << endl;
			cout << "this will not include partys who got 0 delegates, as instructed in the pdf file" << endl;
			cout << "\n";

			int* copyDelegateArr;
			try
			{
				copyDelegateArr = new int[partycounter]();
			}
			catch (bad_alloc& ex)
			{
				cout << "bad allocation: " << ex.what() << endl;
				exit(3);
			}
			for (int j = 0; j < partycounter; j++)
			{
				copyDelegateArr[j] = DelegateArr[j];
			}
			try
			{
				a.DisplayResByParty(partycounter, copyDelegateArr, PLst, DelegateArr, Clst, votesArray, &cwinner, *countyit, countedvotes);
			}
			catch (const char* statement)
			{
				cout << statement << endl;
				return;
			}
			delete[]copyVotesArray;//realeses data that was allocated
			delete[]DelegateArr;
			delete[]votesArray;
			delete[]copyDelegateArr;
		
			//for loop, countyit advances by itself (countyit++)
		}//end of while that goes through each county
	
		cout << "\n";
		cout << "Now the resulst will be shown! " << endl;
		cout << "\n";
		Party* z;
		int* copySumOfDelegates;
		try
		{
			copySumOfDelegates = new int[partycounter]();
		}
		catch (bad_alloc& ex)
		{
			cout << "bad allocation: " << ex.what() << endl;
			exit(3);
		}
		for (int i = 0; i < partycounter; i++)//copys data to copy arr
		{
			copySumOfDelegates[i] = sumOfDelegates[i];
		}

		if (isSimpleElection == false)
		{
			for (int k = 1; k < partycounter + 1; k++)
			{
				int maxDelegates = -1;
				int maxIndex = 0;
				for (int j = 0; j < partycounter; j++)
				{
					if (copySumOfDelegates[j] >= maxDelegates)
					{
						if (copySumOfDelegates[j] != maxDelegates)
						{
							maxDelegates = copySumOfDelegates[j];
							maxIndex = j;
						}
					}

				}
				copySumOfDelegates[maxIndex] = -2;
				z = findParty((maxIndex + 1),PLst);//locates the party via party id
				cout << " \nThe party name  is: " << z->getName() << endl;
				cout << "Party leader is :" << getCitizen(z->getLeaderID(),Clst)->getName() << endl;
				cout << "The total number of votes the party got is: " << *(sumOfVotes+maxIndex+1) << endl;
				cout << "The total number of delegates the party has won " << sumOfDelegates[maxIndex] << endl;
			}
		}

		for (int k = 0; k < partycounter; k++)
		{
			if (sumOfDelegates[k] > sumOfDelegates[TheWinner])
			{
				TheWinner = k;
			}
		}
		cout << "\n";
		cout << "THE WINNIG PARTY IS: " << findParty((TheWinner + 1),PLst)->getName() << endl;
		cout << "THE NEW PRESIDENT IS " << getCitizen(findParty((TheWinner + 1),PLst)->getLeaderID(),Clst)->getName() << endl;

		delete[]sumOfDelegates;
		delete[]sumOfVotes;
		
	}
	//----------------------------------------------------------------------------------------------------------------------------------
	void App::runElections(ElectionDate* date, int electionType, Election* election, bool isLoaded)
	{
		//variables
		list<County*> countylist;
		list<Citizen*> citizenlist;
		list<Party*> partylist;
		Citizen* temp = nullptr;
		int input = -2;
		bool isSimpleElection = false;
		int partycounter = 0;
		int citizencounter = 0;
		int numOfDelegates = 0;
		int countycounter = 0;
		bool EndProgrem = 0;
		int countyType = 0;
		string smp;
		County* simple;

		if (isLoaded == true)
		{
			countylist = (election->getCountyLst());
			partylist = election->getPartyLst();
			citizenlist = election->getCitizenLst();
			partycounter = election->getPartycounter();
			countycounter = election->getCountycounter();
			citizencounter = election->getCitizencounter();	
			if (electionType == 2)
				isSimpleElection = true;
		}
		
		if (electionType == 2 && isLoaded==false)
		{
			isSimpleElection = true;
			smp.clear();
			smp = "simple";
			cout << "Please enter the number of delegates that can be chosen" << endl;
			cin >> numOfDelegates;

			//THERE IS A CHECK FOR DELEGATE NUM BOTH IN CTOR AND IN THE FUNCTION AS INSTRUCTED BY THE PROFFESOR IN THE FORUM

			while (true)
			{
				try
				{
					simple = new devidedCounty(smp, numOfDelegates);
					if (numOfDelegates > 0)
						break;//to end the while loop 
				}
		
				catch (bad_alloc& ex)
				{
					cout << "bad allocation: " << ex.what() << endl;
					exit(3);
				}
				catch (const char* statement)
				{
					cout << statement << "PLEASE RE-ENTER A VALID NUMBER" << endl;
					cin >> numOfDelegates;
				}
			}
			countycounter++;
			AddCounty(simple, countylist);
			
		}
	
		enum options
		{
			AddCounty = 1, AddCitizen, AddParty, AddDelegateToParty, DisplayCounties, DisplayCitizens, DisplayParties, Vote, DisplayResults, Exit, saveElection, loadElection
		};

		cout << "Hello,welocme to our voting system, are you ready to vote?" << endl;
		while (EndProgrem == 0)//keeps the loop until "10" is pressed (exit)-we wanted to use exit() but it shuts down without calling dtors
		{
			cout << "\n";//displays all options to the screen
			display();
			cin >> input;
			while (input < 1 || input >12)
			{
				cout << "ERROR, PLEASE CHOOSE A VALID OPTION" << endl;
				display();
				cin >> input;
			}

			switch (input)
			{
				case AddCounty://add a county
				{
					try
					{
						AddCountyCase(isSimpleElection, countylist, partylist, &countycounter);
					}
					catch (const char* statement)
					{
						cout << statement << endl;
						break;
					}
					break;
				}

				case AddCitizen://add a citizen
				{
					try
					{
						AddCitizenCase(date->getYear(), countycounter, citizenlist, isSimpleElection, &citizencounter, countylist);
					}
					catch (const char* statement)
					{
						cout << statement << endl;
						break;
					}
					break;
				
				}

				case AddParty://add party
				{
					try
					{
						addPartyCase(citizencounter, citizenlist, partylist, countycounter, &partycounter);
					}
					catch (const char* statement)
					{
						cout << statement << endl;
						break;
					}
					break;
				
				}

				case AddDelegateToParty://add citizen to delagate lst
				{
					try
					{
						addDelegateToPartyCase(partycounter, citizenlist, isSimpleElection, countycounter, partylist, countylist);
					}
					catch (const char* statement)
					{
						cout << statement << endl;
						break;
					}
					break;
				
				}

				case DisplayCounties://display counties
				{
				
					try
					{
						printAllCounties(countylist, isSimpleElection);
					}
					catch (const char* statement)
					{
						cout << statement << endl;
						break;
					}
						break;
					
				}

				case DisplayCitizens://display citizens
				{
					try
					{
						printAllCitizens(citizenlist);
					}
					catch (const char* statement)
					{
						cout << statement << endl;
						break;
					}
						break;
				}

				case DisplayParties://display partys
				{
					try
					{
						printAllParties(citizenlist, partylist);
					}
					catch(const char* statement)
					{
						cout << statement << endl;
						break;
					}
					break;
				}

				case Vote: //add vote
				{
					try
					{
						voteCase(citizencounter, partycounter, countylist, citizenlist);
					}
					catch (const char* statement)
					{
						cout << statement << endl;
						break;
					}
					break;
				}

				case DisplayResults://display election results
				{
					try
					{
						DisplayElectionRes(partylist, citizenlist, countylist, countycounter, partycounter, isSimpleElection, date);
					}
					catch (const char* statement)
					{
						cout << statement << endl;
						break;
					}
					break;
				
				}

				case Exit:
				{
					cout << "Thank you for using our election programm, we'll see you in the next elections! (:" << endl;
					EndProgrem = 1;
					break;
				}
			
				case saveElection:
				{
					saveElectionCase(citizenlist, partylist, countylist, countycounter, partycounter, citizencounter, electionType, *date);
					break;
				}

				case loadElection:
				{
					loadElectionCase(&isSimpleElection, &citizenlist, &partylist, &countylist, &countycounter, &partycounter, &citizencounter, &electionType, *date);;
					break;
				}

			}

		}

	}
}
