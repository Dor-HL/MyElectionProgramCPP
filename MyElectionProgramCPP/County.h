#pragma once
#include <iostream>
#include <list>
using namespace std;

namespace elections
{

	class CitizenList;
	class CountyList;
	class Citizen;

	class County
	{
	protected:
		string _countyName;
		int _logicSize;
		static int _countyID;
		int realcountyID;
		int _numOfElectors;
	    list<Citizen*> _countyCitizens;
		bool isDevided = false;

	public:
		County(const string name, int electors);//ctor
		County(const County& source);//cpy ctor
		virtual ~County();//dtor
		void operator=(const County& source)=delete;
		void addCitizenToCounty(Citizen* newCitizen, list<County*> county);
		list<Citizen*>* getCitizens();
		string getName();
		int getLogicSize() { return _logicSize; };
		int getID();
		int getNumElectors();
		virtual void printType() const { cout << "\n The county is a united county"; };
		bool getIsDevided() { return isDevided; };
		virtual void calculateRes(int NumElectors, int partycounter, float* copyVotesArray, int* DelegateArr, float delegateAvg, int* sumOfDelegates);
		void resetStaticID() { _countyID = _countyID--; }; 
		friend ostream& operator<<(ostream& os, const County& c)
		{
			c.printType();//virtual to distinguish between devided and united as instructed 
			os << "\n The county's name is: " << c._countyName << "\n the ID number is: " << c.realcountyID << "\n the number of delegates is: "<<c._numOfElectors << endl;

			return os;
			
		}
		void setStaticID() { _countyID--; };
		
	};
	
	class devidedCounty : public County
	{
	private:
	public:
		devidedCounty(string name, int electors) :County(name, electors) { isDevided = true; };
		~devidedCounty() {};
		virtual void printType() const { cout << "\n The county is a devided county"; };
		virtual void calculateRes(int NumElectors, int partycounter, float* copyVotesArray, int* DelegateArr, float delegateAvg, int* sumOfDelegates);
	};
}