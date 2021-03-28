#pragma once
#include <iostream>
#include <string>
#include <list>
#include "County.h"
using namespace std;

namespace elections
{
	class County;

	class Citizen
	{
		friend class County;
		friend class App;
		private:
		string _name;
		int _logicSize;
		int _id;
		int _yearOfBirth;
		int voted=-1;//check if someone voted already
		int isDelegate = -1;
		County* _myCounty;

		public:
		Citizen(int id,int yearOfBirth, const string name,County* county);//ctor
		Citizen(const Citizen& source);//copy ctor
		~Citizen() {  };//dtor
		const Citizen& operator=(const Citizen& source);
		const string getName() const { return _name; };
		int getID() const { return _id; };
		int getYearOfBirth()const { return _yearOfBirth; };
		int getCountyID() const{ return _myCounty->getID(); };
		int getLogicSize()const { return _logicSize; };
		int getvoted()const { return voted; };
		int getIsDelegate() const {if(this==nullptr) return 0; else return  isDelegate; };
		void setDelegate() { isDelegate = 1; };
		void setVoted(int partyid) { voted = partyid; };
		bool isNineDigit(int id);
		friend ostream& operator<<(ostream& os, const Citizen& c)//printing operator
		{
			os << "\n The citizen's name is: " << c.getName() << "\n the ID number is: " << c.getID() << "\n the year of birth is: " << c.getYearOfBirth() << " \n The county ID is: " << c.getCountyID() << endl;
			return os;
		}
		
	};

}