#pragma once
#include <assert.h>
#include <string.h>
#include <iostream>
#include "Citizen.h"
#include "County.h"
#include "ElectionDate.h"
#include "Election.h"
#include "Party.h"
#include <string.h>
#include "DynamicArray.h"
#include <string>
#include <list>

using namespace std;

namespace elections
{
	class CountyList; 

	class App
	{
		friend class County;
	private:
	public:
		App() {};//empty ctor
		~App() {};//empty dtor
		App(const App& source)=delete;//cpy ctor. no data so there's no need for a cpy ctor
		void operator=(const App& source) = delete;
		//display functions
		void display();
		void DisplayElectionOptions();
		void DisplayResByParty(int partycounter, int* copyDelegateArr, list<Party*> PLst, int* DelegateArr, list<Citizen*> Clst, int* votesArray, int* cwinner, County* curr,int countedvotes);
		void DisplayElectionRes(list<Party*> PLst, list<Citizen*> Clst, list<County*> countyLst, int countycounter, int partycounter, bool isSimpleElection, ElectionDate* date);
		//lists realeted functions(adds to lists/searches in list)
		void AddToCandidateList(Citizen* newCitizen, int county, list<County*> countylist, list<Party*>& partylist, int partyID);
		void createNewCounty(string countyname, int numOfDelegates,list<County*> &countyLst, int type);
		void addNewCitizen(string citizenname, int citizenid, int yearofbirth, int citizencounty, list<Citizen*>& Clst, list<County*> countyLst);
		void createNewParty(string partyName,int leaderid,list<Party*>& partylist,int countycounter);
		void addDelegateToPartyByCounty(Citizen* temp, int partyid, int countyid, list<Party*>& partylist, list<County*> countylist);
		void AddCounty(County* newCounty, list<County*>& countylist);
		Party* findParty(int k, list<Party*> partylist);
		County* getData(int i, list<County*> countylist) const;//finds a county by id (i) and returns it
		Citizen* getCitizen(int i, list<Citizen*> citizenlist) const;//finds citizen via id
		void AddCitizen(Citizen* newCitizen, list<Citizen*>& citizenlist);
		//printing functions
		void printAllCitizens(list<Citizen*> citizenlist);
		void printAllCounties(list<County*> countylist, bool isSimpleElection);
		void printAllParties(list<Citizen*> citizenlist, list<Party*> partylist);//the list of all citizens
		//other
		void resizeAllDynArrays(list<Party*>& partylist,int countycounter, list<County*> countylist);
		void runElections(ElectionDate* date, int electionType, Election* election, bool isLoaded);
		//switch functions
		void AddCountyCase(bool isSimpleElection, list<County*>& countylist, list<Party*>& partylist, int* countycounter);
		void AddCitizenCase(int elecyear,int countycounter, list<Citizen*>& citizenlist, bool isSimpleElection, int* citizencounter, list<County*>& countylist);
		void addPartyCase(int citizencounter, list<Citizen*>& citizenlist, list<Party*>& partylist, int countycounter, int* partycounter);
		void addDelegateToPartyCase(int partycounter, list<Citizen*>& citizenlist, bool isSimpleElection, int countycounter, list<Party*>& partylist, list<County*>& countylist);
		void voteCase(int citizencounter, int partycounter, list<County*>& countylist, list<Citizen*>& citizenlist);
		void saveElectionCase(list<Citizen*> citizenlist, list<Party*> partylist, list<County*> countylist, int countycounter, int partycounter, int citizencounter, int electionType, ElectionDate date);
		void loadElectionCase(bool* isSimpleElection, list<Citizen*>* citizenlist, list<Party*>* partylist, list<County*>* countylist, int* countycounter, int* partycounter, int* citizencounter, int* electionType, ElectionDate& date);
		bool isNineDigit(int id);
	};

}