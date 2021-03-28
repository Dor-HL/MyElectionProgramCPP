#define _CRT_SECURE_NO_WARNINGS
#include "App.h"
#include <iostream>
using namespace std;
#define MAX 100
#define CURR_YEAR 2021

using namespace elections;
template<class S>
bool comp(S a, S b)
{
	if (a <= b)//if a is smaller than b or equal to b return false
	{
		return false;
	}
	else
		return true;
}

template<>
bool comp(list<Citizen*> a, list<Citizen*> b)
{
	if (a.size() <= b.size())//if a is shorter than b or equal to b return false
	{
		return false;
	}
	else
		return true;
}

int main()
{
	App app;
	int input = -2;
	int day = 0;
	int month = 0;
	int year = 0;
	int electionType = -7;
	int endProgram = 1;
	enum elections
	{
		NewElectionRound = 1, LoadExistingRound, ExitProgram
	};

	app.DisplayElectionOptions();
	cin >> input;
	while (input < 1 || input>3)
	{
		cout << "invalid input. Please enter a number between 1-3" << endl;
		app.DisplayElectionOptions();
		cin >> input;
	}
	while (endProgram)
	{
		switch (input)//switch case
		{
		case NewElectionRound:
		{
			//NOTE: VALIDATION CHECK IS IN THE CTOR AND IN THE FUNCTIONS/MAIN AS INSTRUCTED BY THE PROFFESOR IN THE FORUM! ENTER FULL DATE TO SEE ERROR 
			cout << "please enter the election's month" << endl;
		    cin >> month;
			while (month < 1 || month>12)
			{
				cout<< "THERE IS NO SUCH MONTH. PLEASE RE ENTER DATE"<<endl;
				cin >> month;

			}


			cout << "please enter the election's day" << endl;
		    cin >> day;
			while (day < 1 || day>31 || ((month == 2) && (day > 28)))
			{
				if (day < 1 || day>31)
					cout << "THERE IS NO SUCH DAY. PLEASE RE ENTER DATE" << endl;

				else
					cout << "THERE ARE EXACTLY 28 DAYS IN FEBURARY, PLEASE RE-ENTER DATE" << endl;

				cin >> day;
			}

			
			cout << "please enter the election's year" << endl;
			cin >> year;
			while (year < 2021)
			{
				cout << "AN ELECTION CANNOT EXIST IN THE PAST. PLEASE RE ENTER YEAR" << endl;
				cin >> year;
			}

			ElectionDate* date;
			try
			{
				date=new ElectionDate(day, month, year);
			}

			catch (const char* statement)
			{
				cout << statement << endl;
				break;
			}
			cout << "Please choose an election type" << endl;
			cout << "Press 1 for a normal election round" << endl;
			cout << "Press 2 for a simple election round" << endl;
			cin >> electionType;
			while (electionType != 1 && electionType != 2)
			{
				cout << "Please enter a valid choice" << endl;
				cin >> electionType;
			}
			app.runElections(date, electionType, nullptr, false);
			endProgram = 0;
			break;
		}
		case LoadExistingRound:
		{
			list<County*> countySource;
			list<Party*> partySource;
			list<Citizen*> citizenSource;
			int partyCounterS = 0;
			int countyCounterS = 0;
			int citizenCounterS = 0;
			ElectionDate* dateSource;

			try
			{
			   dateSource =new ElectionDate(1, 1, CURR_YEAR);
			}

			catch (const char* statement)
			{
				cout << statement << endl;
				break;
			}
			char* fileName;
			try
			{
				fileName = new char[100]();
			}
			catch (bad_alloc& ex)
			{
				cout << "bad allocation: " << ex.what() << endl;
				exit(3);
			}
			cout << " please enter the file's name " << endl;
			cin >> fileName;
			ifstream infile(fileName, ios::binary);
			if (!infile)
			{
				cout << "ERROR WITH INFILE!!" << endl;
				exit(-1);
			}
			bool readIntoSimple;
			infile.read(rcastc(&readIntoSimple), sizeof(readIntoSimple));
			electionType = readIntoSimple + 1;
			Election* loadData;
			if (electionType == 1)
			{
				try
				{
					loadData = new Election(&countySource, &citizenSource, &partySource, &partyCounterS, &countyCounterS, &citizenCounterS, dateSource);
				}
				catch (bad_alloc& ex)
				{
					cout << "bad allocation: " << ex.what() << endl;
					exit(3);
				}
				loadData->load(infile);
			}
			else
			{
				try
				{
					loadData = new SimpleElection(&countySource, &citizenSource, &partySource, &partyCounterS, &countyCounterS, &citizenCounterS, dateSource);
				}
				catch (bad_alloc& ex)
				{
					cout << "bad allocation: " << ex.what() << endl;
					exit(3);
				}
				loadData->load(infile);
			}
			

			app.runElections(loadData->getDate(), electionType, loadData, true);
			endProgram = 0;
			break;
		}
		case ExitProgram:
		{
			return 1;
			break;
		}

		}//end of switch

	}

}


