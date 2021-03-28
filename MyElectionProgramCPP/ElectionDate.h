#pragma once
#include <iostream>
using namespace std;

namespace elections
{
	class ElectionDate
	{
	private:
		int _day;
		int _month;
		int _year;


	public:
		ElectionDate(int day, int month, int year);
		ElectionDate(const ElectionDate& source) { _day = source._day; _month = source._month; _year = source._year; };//cpy ctor
		~ElectionDate() {};//default dtor
		void operator=(const ElectionDate& source)=delete;
		int getDay() const { return _day; };
		int getMonth() const { return _month; };
		int getYear() const { return _year; };
		void setDate(int day, int month, int year) { _day = day, _month = month, _year = year; };
		friend ostream & operator<<(ostream& os, const ElectionDate& c)//printing operator
		{
			os << "The election date is " << c.getDay() << "\\ " << c.getMonth()<< "\\ " << c.getYear() << endl;

			return os;
		}
	};
}