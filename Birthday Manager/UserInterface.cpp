#include "UserInterface.h"
#include "BirthdayEntries.h"
#include "stdafx.h"


void checkForValidDay(int &day, int month, int year) {
	int max_day = 0; // adjusted for each month
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		max_day = 31;
	}
	else if (month == 2) {
		max_day = 28; //common year
					  //leap year case
		if ((year % 4) == 0) {
			max_day = 29; //adds the leap day
			if ((year % 100 == 0) && (year % 400) != 0) { max_day = 28; }
		}
	}
	else { max_day = 30; }

	while (day > max_day || day < 1) {
		std::cout << "Hey, your day is invalid. Try again!\n>>";
		std::cin >> day;
	}
}

void checkForValidMonth(int &month) {
	while (month > 12 || month < 1) {
		std::cout << "Hey, your month is invalid. Try again!\n>>";
		std::cin >> month;
	}
}

void checkForValidYear(int &year, int month, int day) {
	std::chrono::system_clock Clock;
	auto now = Clock.now(); //gets current point in time
	std::time_t tt = std::chrono::system_clock::to_time_t(now); //conversion to C time datatype
	std::tm local_s = *localtime(&tt); //converts into a local time
									   //uses the current year as the max  and 1900 as the min (anybody born before 1900 is probably dead)
	while (year > (local_s.tm_year + 1900) || year < 1900) {
		std::cout << "Hey, your year is invalid. Try again!\n>>";
		std::cin >> year;
	}

	//checking to see if change in year is valid due to some years being leap years
	if (month == 2 && day == 29) {
		if (year % 4) {
			if ((year % 100 == 0) && (year % 400) != 0) {
				while (year > (local_s.tm_year + 1900) || year < 1900) {
					std::cout << "The year that you entered isn't a leap year,";
					std::cout << " which goes against having a birthday on the 29th of february. Try again!\n>>";
					std::cin >> year;
				}
			}
		}
	}
}

BirthdayManagerMenu::BirthdayManagerMenu() {}

void BirthdayManagerMenu::StartUp(){
	
	PrintGreeting();
	while (!ExitCondition) { 
		CreateInitialData(); //Will check after each action the user enacts
		SelectEvent( SelectOption() );
	}
}

bool BirthdayManagerMenu::CheckForExistingData() {
	
	std::ifstream f("Birthdays_Storage.txt");
	return f.good(); //returns true if no errors 
}

void BirthdayManagerMenu::CreateInitialData() {
	
	HasDataFile = CheckForExistingData();
	if (HasDataFile) { return; }
	else {
		std::cout << "\n It seems like you do not have a \"Birthdays_Storage.txt\" file." ;
		std::cout << "\n You will have to create one before continuing.\n\n";
		
		std::string f_name, l_name;
		int month, day, year;

		std::cout << "Enter the first and last name of the person of interest.\n";
		std::cin >> f_name >> l_name;

		std::cout << "Enter the birthday month.\n";
		std::cin >> month;
		std::cout << "Enter the birthday day.\n";
		std::cin >> day;
		std::cout << "Enter the birthday year.\n";
		std::cin >> year;

		checkForValidMonth(month);
		checkForValidYear(year,month,day);
		checkForValidDay(day,month,year);

		BirthdayEntry entry(f_name, l_name, month, day, year);
		entry.StoreEntry();

		HasDataFile = true;
		std::cout << "\n\n";
	}
}

void BirthdayManagerMenu::SelectEvent(int user_selection) {

	switch (user_selection) {
	case 1:
	{
			std::cout << "\nEntering: Birthday Viewing mode.\n\n";

			std::string f_name, l_name;

			std::cout << "Enter the first and last name of the person of interest.\n";
			std::cin >> f_name >> l_name;

			BirthdayEntry entry;
			entry.ViewSingleEntry(f_name, l_name);
			break;
	}
	case 2:
	{
		std::cout << "\nEntering: Add Birthday Entry mode.\n\n";

		std::string f_name, l_name;
		int month, day, year;

		std::cout << "Enter the first and last name of the person of interest.\n";
		std::cin >> f_name >> l_name;

		std::cout << "Enter the birthday month.\n";
		std::cin >> month;
		std::cout << "Enter the birthday day.\n";
		std::cin >> day;
		std::cout << "Enter the birthday year.\n";
		std::cin >> year;

		checkForValidMonth(month);
		checkForValidYear(year, month, day);
		checkForValidDay(day, month, year);

		BirthdayEntry entry(f_name,l_name,month,day,year);
		entry.StoreEntry();

		std::ifstream f("Birthdays_Storage.txt");
		if (isEmpty(f)) {
			f.close();
			std::remove("Birthdays_Storage.txt");
		}
		break;
	}

	case 3:
	{
		std::cout << "\nEntering: View All Birthday Entries mode.\n\n";
		
		BirthdayEntry entry;
		entry.ViewBirthdayList();
		break;
	}

	case 4:
	{
		std::cout << "\nEntering: Edit Birthday Entry mode.\n\n";

		std::string f_name, l_name;

		std::cout << "Enter the first and last name of the person of interest.\n";
		std::cin >> f_name >> l_name;

		BirthdayEntry entry;
		entry.EditEntry(f_name, l_name);
		break;
	}
	case 5:
	{
		std::string f_name, l_name;

		std::cout << "Which contact do you want to delete? Enter their first and last name.\n>>";
		std::cin >> f_name >> l_name;

		BirthdayEntry entry;
		entry.DeleteEntry(f_name, l_name);

		std::ifstream f("Birthdays_Storage.txt");

		if (isEmpty(f)) {
			f.close();
			std::remove("Birthdays_Storage.txt");
		}
		
		break;
	}
	case 6:
	{
		char isSure = 'n'; //default value
		std::cout << "Are you sure that you want to delete all of the birthday entries? Enter \'y\' if you are.\n>>" ;
		while (std::cin >> isSure) {}

		BirthdayEntry entry;
		if (isSure == 'y' || isSure == 'Y') { entry.DeleteAllBirthdayEntries(); }
		else { std::cout << "Okay. The information has not been deleted.\n"; }
		break;
	}
	case 7:
	{
		std::cout << "Exiting now. Goodbye!";
		ExitCondition = true;
		break;
	}
	}
}

void BirthdayManagerMenu::PrintGreeting() {
	std::cout << "Hello User, this is the Birthday Manager program.\n\n";
	std::cout << "In this program, you can view and edit existing birthdays.\n";
	std::cout << "In addition, you can store new birthdays.\n\n";

}

int BirthdayManagerMenu::SelectOption() {
	std::cout << "At this moment, you have the following options:\n";
	std::cout << "1. View a birthday entry.\n";
	std::cout << "2. Add a birthday entry\n";
	std::cout << "3. List all birthday entries.\n";
	std::cout << "4. Edit an existing birthday entry.\n";
	std::cout << "5. Delete a birthday entry\n";
	std::cout << "6. Delete all birthday entries\n";
	std::cout << "7. Exit?\n\n";
	
	int choice;
	std::cin >> choice;
	return choice;
}

