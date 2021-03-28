#include "ElectionDate.h"
#include <iostream>
using namespace std;

namespace elections
{
	ElectionDate::ElectionDate(int day, int month, int year)
	{
		if (month < 1 || month>12)
			throw "THERE IS NO SUCH MONTH. PLEASE RE ENTER DATE";

		if (day < 1 || day>31)
			throw "THERE IS NO SUCH DAY. PLEASE RE ENTER DATE";

		else if ((month == 2) && (day > 28))
		{
			throw "THERE ARE EXACTLY 28 DAYS IN FEBURARY, PLEASE RE-ENTER DATE";
		}

		if (year < 2021)
		{
			throw "AN ELECTION CANNOT EXIST IN THE PAST. PLEASE RE-ENTER DATE";
		}

		_day = day;
		_month = month;
		_year = year;
	}

}