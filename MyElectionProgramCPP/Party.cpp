#define _CRT_SECURE_NO_WARNINGS

#include "Citizen.h"
#include "DynamicArray.h"
#include <string.h>
#include <iostream>
#include "Party.h"


using namespace std;

namespace elections
{

	int Party::_partyID = 0;


	Party::Party(const string name, int leaderid, int countycounter)//ctor
		:_leaderID(leaderid)
	{
		if (countycounter <= 0)
		{
			throw "NUMBER OF COUNTYS NEEDS TO BE BIGGER THAN 0";
		}
		_logicSize = name.length();	
		_partyName = name;
		Party::_partyID++;
		realPartyID = _partyID;
		DynamicArray<list<Citizen*>>* temp;
		try
		{
			temp = new DynamicArray<list<Citizen*>>;
			temp->setSize(countycounter);
		}
		catch (bad_alloc& ex)
		{
			cout << "bad allocation: " << ex.what() << endl;
			exit(3);
		}
		this->CandidatesList = *temp;
	}
	//----------------------------------------------------------------------------------------------------------------------------------


	Party::Party(const Party& source)//cpy ctor
	{
		_logicSize = source._logicSize;
		_partyName.clear();
		_partyName= source._partyName;
		_partyID = source._partyID;
		realPartyID = source.realPartyID;
		_leaderID = source._leaderID;
		CandidatesList = source.CandidatesList;
	}
	//----------------------------------------------------------------------------------------------------------------------------------


	Party& Party::operator=(const Party& source)
	{
		this->_logicSize = source._logicSize;
		_partyName.clear();
		this->_partyName=source._partyName;
		this->_partyID = source._partyID;
		this->realPartyID = source.realPartyID;
		this->CandidatesList = source.CandidatesList;
		return *this;

	}
	//----------------------------------------------------------------------------------------------------------------------------------

	Party::~Party()//dtor
	{
		for (int i = 0; i < CandidatesList.size(); i++)
		{
			CandidatesList[i].clear();
		}
	}
	//----------------------------------------------------------------------------------------------------------------------------------


	void Party::PrintCandidateList(Party* p)//this func prints the candidate lst
	{
		cout << "\n";
		cout << " The party candidates list is: " << endl;
		list<Citizen*>::const_iterator citizenit;
		for (int i = 0; i < p->CandidatesList.size(); i++)
		{
			
				cout << " The List for county: " << i + 1 << endl;
				for (citizenit = p->CandidatesList[i].begin(); citizenit != p->CandidatesList[i].end(); citizenit++)
				{
					cout << " " << (*citizenit)->getName() << endl;;

				}
		}
	}
	//----------------------------------------------------------------------------------------------------------------------------------

	int Party:: HowManyDelgates()
	{
		int counter = 0;
		int size = CandidatesList.size();
		list<Citizen*>::const_iterator it;
		for (int i = 0; i < size; i++)
		{
			for(it=CandidatesList[i].begin(); it!=CandidatesList[i].end();it++)
			{
				counter++;
			}
		}
		return counter;
	}

}