#include "BirthdayEntries.h"
#include <filesystem>
#include "stdafx.h"


//This constructor is meant for general operations in the BirthdayEntry class
BirthdayEntry::BirthdayEntry() {}

//This constructor is meant to be used for editing or deleting entries
BirthdayEntry::BirthdayEntry(std::string f_name, std::string l_name): first_name(f_name), last_name(l_name) {}

//This constructor is meant to be used for adding new entries
BirthdayEntry::BirthdayEntry(std::string f_name, std::string l_name, int month, int day, int year):
		first_name(f_name),last_name(l_name) , bday_month(month), bday_day(day), bday_year(year){}




void BirthdayEntry::StoreEntry() {

	std::ofstream file_store;
	file_store.open(birthday_file,std::ofstream::app);
	file_store << this->first_name << " " << this->last_name << " " << this->bday_month << " " 
		<< this->bday_day << " " << this->bday_year << std::endl;
	file_store.close();

	//SortEntries(); //sorts entries because there's no guarantee that everything will be alphabetical order
}

void BirthdayEntry::EditEntry(std::string desired_f_name, std::string desired_l_name) {
	
	std::string f_name, l_name, name_change;
	int choice, month, day, year;
	bool InData = false;

	std::ofstream overwrite_file("temp_name.txt"); //used to rewrite the old file contents with the new change
	std::ifstream file_store;

	file_store.open(birthday_file);
	if (file_store.is_open() == false) {
		std::fstream file(birthday_file,std::ios::out);
		file.close();
		file_store.open(birthday_file);
	}

	while (file_store >> f_name >> l_name >> month >> day >> year) {
		
		if (f_name == desired_f_name && l_name == desired_l_name) {
			InData = true;
			std::cout << "\nHere's the current birthday entry:\n" << f_name << " " << l_name<< " " << month << "/" << day << "/" << year;
			std::cout << "\n\nEnter one of the following numbers that corresponds to what you want to change.";
			std::cout << "\nOptions:\n1. day \n2. month \n3. year \n4. first name \n5. last name\n\n>>";

			while (!(std::cin >> choice)) {
				std::cout << "\n Not a valid choice. Try again\n>>";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			switch (choice) {
			case 1:
				std::cout << "Please, enter the new day.\n>>";
				std::cin >> day;
				break;

			case 2:
				std::cout << "Please, enter the new month.\n>>";
				std::cin >> month;
				break;

			case 3:
				std::cout << "Please, enter the new year.\n>>";
				std::cin >> year;
				break;

			case 4:
				std::cout << "Please, enter the new first name.\n>>";
				std::cin >> f_name;
				break;

			case 5:
				std::cout << "Please, enter the new last name.\n>>";
				std::cin >> l_name;
				break;
			}
			
		}
		
		overwrite_file << f_name << " " << l_name << " " << month << " " << day << " " << year << std::endl; //transfers changes to new file
	}
	if (!InData) { std::cout << "No contacts with that name.\n" ; }
	overwrite_file.close();
	file_store.close();

	std::remove(birthday_file.c_str());
	if (std::rename("temp_name.txt", birthday_file.c_str()) == 1) { std::cout << "Error in renaming file."; }; //renames overwrite file to original birthday file name
	//SortEntries(); //sorts entries because there's no guarantee that everything will be alphabetical order
}


void BirthdayEntry::ViewSingleEntry(std::string desired_f_name, std::string desired_l_name) {
	std::string f_name, l_name;
	int month, day, year;
	bool InData = false;
	std::ifstream file_store(birthday_file);
	while (file_store >> f_name >> l_name >> month >> day >> year) {
		if (f_name == desired_f_name && l_name == desired_l_name) {
			InData = true;
			std::cout << std::endl << f_name << " " << l_name <<" " << month << "/" << day << "/" << year << "\n\n";
			break;
		}
	
	}
	if (!InData) { std::cout << "No contacts with that name.\n"; }
}


void BirthdayEntry::ViewBirthdayList() {

	std::string f_name, l_name;
	int month, day, year;

	std::ifstream birthday_list(birthday_file);

	while (birthday_list >> f_name >> l_name >> month >> day >> year) {
		std::cout << f_name << " " << l_name << " " << month << "/" << day << "/" << year << "\n\n";
	}

	birthday_list.close();
}

void BirthdayEntry::DeleteEntry(std::string desired_f_name, std::string desired_l_name) {
	std::string f_name, l_name;
	int month, day, year;
	bool InData = false;

	std::ofstream overwrite_file("temp_name.txt"); //used to rewrite the old file contents with the new change

	std::ifstream file_store;
	file_store.open(birthday_file);

	while (file_store >> f_name >> l_name >> month >> day >> year) {
		if (f_name == desired_f_name && l_name == desired_l_name) {
			InData = true;
			std::cout << "Found " << desired_f_name << " " << desired_l_name << ".\n Entry is now removed.\n" ;
		}
		else {
			overwrite_file << f_name << " " << l_name << " " << month  << " " << day << " " << year <<std::endl;
		}
	}
	
	if (!InData) { std::cout << "No contacts with that name.\n"; }

	overwrite_file.close();
	file_store.close();

	std::remove(birthday_file.c_str());
	if (std::rename("temp_name.txt", birthday_file.c_str()) == 1) { std::cout << "Error in renaming file."; }; //renames overwrite file to original birthday file name
}


//Not working
void BirthdayEntry::SortEntries() {

	std::string f_name, l_name, line,search_first, search_second;
	int month, day, year;
	int count = 0;

	std::vector<std::pair<std::string, std::string>> names;
	std::pair<std::string, std::string> name;
	std::vector<std::pair<std::string, std::string>>::iterator itr;

	std::ifstream file_store;
	file_store.open(birthday_file);
	std::ofstream overwrite_file("temp_name.txt"); 
	
	while (file_store >> f_name >> l_name >> month >> day >> year) {
		name = std::make_pair(f_name,l_name);
		names.push_back(name);
	}

	std::sort(names.begin(),names.end());
	
	for (itr = names.begin(); itr != names.end();itr++) {
		search_first = names.at(count).first;
		search_second = names.at(count).second;

		while (getline(file_store, line)) {
			if (line.find(search_first) != std::string::npos && line.find(search_first) != std::string::npos) {
				overwrite_file << line;
			}
		}
		count++;
	}
	
	std::remove(birthday_file.c_str());
	std::rename("temp_name.txt", birthday_file.c_str());
	file_store.close();
	overwrite_file.close();
}

void BirthdayEntry::DeleteAllBirthdayEntries() {
	std::remove(birthday_file.c_str());
}


