#pragma once
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace elections
{
	class CountyList;
	class CitizenList;
	class Party;
	class ElectionDate;
	class County;
	class Citizen;
	//--------------------------------------------------------------------------------------------------------------------------------------
	class Election
	{
	protected:
		ElectionDate* _date;
		list<County*> _countylst;
		list<Citizen*> _citizenlst;
		list<Party*> _partylst;
		bool isSimple = false;
		int* _partyCounter;
		int* _countyCounter;
		int* _citizenCounter;

	public:
		Election(list<County*>* lst, list<Citizen*>* Clst, list<Party*>* Plst, int* partycounter, int* countycounter, int* citizencounter, ElectionDate* date);
		~Election();
		virtual void save(ostream& out) const;
		virtual void load(istream& in);
		ElectionDate* getDate() { return _date; };
		list<County*> getCountyLst() { return _countylst; };
		list<Party*> getPartyLst() { return _partylst; };
		list<Citizen*> getCitizenLst() { return _citizenlst; };
		int getPartycounter() const { return *_partyCounter; };
		int getCitizencounter() const { return *_citizenCounter; };
		int getCountycounter() const { return *_countyCounter; };
	};
	//------------------------------------------------------------------------------------------------------------------------------------------
	class SimpleElection : public  Election
	{
	private:

	public:
		SimpleElection(list<County*> *county, list<Citizen*>* Clst, list<Party*>* Plst, int* partycounter, int* countycounter, int* citizencounter, ElectionDate* date);
		~SimpleElection();
		virtual void save(ostream& out) const;
		virtual void load(istream& in);

	};

}