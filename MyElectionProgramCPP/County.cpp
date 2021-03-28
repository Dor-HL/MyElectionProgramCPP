#define _CRT_SECURE_NO_WARNINGS
#include "County.h"
#include <string.h>
#include <iostream>
#include "Citizen.h"
#include "App.h"

using namespace std;

namespace elections
{
	int County::_countyID = 0;

	County::County(const string name, int electors)
		:_numOfElectors(electors)
	{
		if (electors <= 0)
			throw "ERROR DELEGATES CAANOT BE A NEGATIVE NUMBER OR 0";
		_logicSize = name.length();
		_countyName = name;
		County::_countyID++;
		realcountyID = _countyID;
		this->_countyCitizens.clear();
	}
	//----------------------------------------------------------------------------------------------------------------------------------

	County::County(const County& source)//cpy ctor
	{
		int size = (source._logicSize) + 1;
		_countyName.clear();
		_countyName = source._countyName;
		_logicSize = source._logicSize;
		_countyID = source._countyID;
		realcountyID = source.realcountyID;
		_numOfElectors = source._numOfElectors;
		_countyCitizens = source._countyCitizens;

	}
	//----------------------------------------------------------------------------------------------------------------------------------

	County::~County()
	{
		//Citizen list dtor is called automatically , was not dynamically allocted
	}
	//----------------------------------------------------------------------------------------------------------------------------------
	void County::addCitizenToCounty(Citizen* newCitizen, list<County*> countylist)
	{
		App a;
		Citizen* newc;
		try
		{
			 newc = new Citizen(newCitizen->getID(), newCitizen->getYearOfBirth(), newCitizen->getName(), a.getData(newCitizen->getCountyID(), countylist));
		}
		catch (bad_alloc& ex)
		{
			cout << "bad allocation: " << ex.what() << endl;
			exit(3);
		}
		_countyCitizens.push_back(newc);
	};
	//----------------------------------------------------------------------------------------------------------------------------------


	string County::getName()
	{
		return _countyName;

	}
	//----------------------------------------------------------------------------------------------------------------------------------

	int County::getID()
	{
		return realcountyID;
	}
	//----------------------------------------------------------------------------------------------------------------------------------

	int County::getNumElectors()
	{

		return _numOfElectors;

	}
	//----------------------------------------------------------------------------------------------------------------------------------


	list<Citizen*>* County::getCitizens()
	{

		return &_countyCitizens;
	}
	//----------------------------------------------------------------------------------------------------------------------------------

	void devidedCounty::calculateRes(int NumElectors, int partycounter, float* copyVotesArray, int* DelegateArr, float delegateAvg, int* sumOfDelegates)

	{
		for (int k = 0; k < NumElectors; k++)//divides electors on a system based on remainder
		{
			int maxvotes = 1;
			for (int r = 1; r < partycounter + 1; r++)
			{
				if (copyVotesArray[r] > copyVotesArray[maxvotes])
					maxvotes = r;
			}
			*(copyVotesArray + maxvotes) -= (float)delegateAvg;
			DelegateArr[maxvotes - 1]++;
			sumOfDelegates[maxvotes - 1]++;
		}//end for
	}
	//----------------------------------------------------------------------------------------------------------------------------------

	void County::calculateRes(int NumElectors, int partycounter, float* copyVotesArray, int* DelegateArr, float delegateAvg, int* sumOfDelegates)
	{
		int winner=1;
		for (int i = 1; i < partycounter + 1; i++)//looks for the winner
		{
			if (copyVotesArray[i] > copyVotesArray[winner])
				winner = i;
		}

		for (int k = 0; k <NumElectors; k++)//divides electors on a system based on remainder
		{
			int maxvotes = 1;
			for (int r = 1; r < partycounter + 1; r++)
			{
				if (copyVotesArray[r] > copyVotesArray[maxvotes])
					maxvotes = r;
			}
			*(copyVotesArray + maxvotes) -= (float)delegateAvg;
			DelegateArr[maxvotes - 1]++;
		}//end for

		sumOfDelegates[winner-1]+=NumElectors;
	}



}