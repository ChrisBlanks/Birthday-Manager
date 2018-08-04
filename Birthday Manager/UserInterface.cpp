#include "UserInterface.h"
#include "BirthdayEntries.h"
#include "stdafx.h"

BirthdayManagerMenu::BirthdayManagerMenu() {}


void BirthdayManagerMenu::StartUp(){
	
	PrintGreeting();
	while (!ExitCondition) { SelectEvent( SelectOption() ); }
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

		BirthdayEntry entry(f_name,l_name,month,day,year);
		entry.StoreEntry();
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
		break;
	}
	case 6:
	{
		int isSure;
		std::cout << "Are you sure that you want to delete all of the birthday entries? Enter 1 if you are.\n>>" ;
		std::cin >> isSure;
		if (std::cin.fail() or !std::cin) { abort(); }

		BirthdayEntry entry;
		if (isSure == 1) { entry.DeleteAllBirthdayEntries(); }
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