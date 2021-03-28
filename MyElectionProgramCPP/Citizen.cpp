#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include <string.h>
#include "County.h" 
#include "App.h"
using namespace std;

namespace elections
{
	Citizen::Citizen(int id, int yearOfBirth, const string name,County* county)
		:_id(id), _yearOfBirth(yearOfBirth), _logicSize(name.length()), voted(-1), isDelegate(-1)
	{
		if (!isNineDigit(id))
		{
			throw "ID len should be 9 digits exactly!";
		}

		if (id < 0)
		{
			throw "ID cannot be a negative number!";
		}

		if (yearOfBirth <= 0)
		{
			throw  "YEAR NEEDS TO BE GREATER THEN 0. PLWASE ENTER A VALID YEAR!";
		}

		_myCounty = county;
		int size = _logicSize + 1;
		_name = name;//uses string copy ctor
	}
	//---------------------------------------------------------------------------------------------------------------------------------
	bool Citizen::isNineDigit(int id)
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

	Citizen::Citizen(const Citizen& source) //copy ctor
	{
		int size =(source._logicSize)+1;
		this->_name.clear();
		this->_name = source._name;
		_logicSize = source._logicSize;
		_id = source._id;
		_yearOfBirth = source._yearOfBirth;
		voted = source.voted;
		isDelegate = source.isDelegate;
		_myCounty = source._myCounty;
	}
	//----------------------------------------------------------------------------------------------------------------------------------

	const Citizen& Citizen:: operator=(const Citizen& source)//operator hasama
	{
		this->_logicSize = source._logicSize;
		this->_name.clear();//empty's the string
		this->_name.resize(this->_logicSize + 1);
		this->_name = source._name;
		this->_id = source._id;
		this->_yearOfBirth = source._yearOfBirth;
		this->voted = source.voted;
		this->isDelegate = source.isDelegate;
		this->_myCounty = source._myCounty;
		return *this;
	}




	 


}