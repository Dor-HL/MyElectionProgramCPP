#pragma once
#include "DynamicArray.h"
#include <string>

namespace elections
{	
	
	class CitizenList;
	class CountyList;
	
	class Party
	{
		friend class App;
		friend class CitizenList;
		friend class Citizen;
	private:
		string _partyName;
		int _logicSize;
		static int _partyID;
		int realPartyID;
		int _leaderID;
		DynamicArray<list<Citizen*>> CandidatesList;
		

	public:
		Party(const string name,int leaderid,int countycounter);
		Party(const Party& source);//cpy ctor
		Party& operator=(const Party& source);//operator hasama
		~Party();
		const string getName() const{ return _partyName;};
		int getID() const{ return realPartyID; };
		int getLogicSize() const { return _logicSize; };
		int getLeaderID()const { return _leaderID; };
		int getPartyID()const { return _partyID; };
		void PrintCandidateList(Party* p);
		int HowManyDelgates();
		DynamicArray<list<Citizen*>>&  getArray()  { return CandidatesList; };
		void resetStaticID() { _partyID = _partyID--; };
		friend ostream& operator<<(ostream& os, const Party& c)
		{
			os << "\n The party's name is: " << c._partyName << "\n ID number is: " << c.realPartyID << "\n The leader ID is " << c._leaderID << endl;
			
			return os;
		}
		void setStaticID() { _partyID--; };

		
	};
}