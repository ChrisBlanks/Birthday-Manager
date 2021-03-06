#include "BirthdayEntries.h"
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

	SortEntries();
	RemoveDuplicates();
}

void BirthdayEntry::EditEntry(std::string target_f_name, std::string target_l_name) {
	
	std::string f_name = "", l_name = "";
	std::string temp1, temp2, name_change;
	std::string delimiter = " ";

	int choice, month, day, year;
	
	std::ofstream overwrite_file("temp_name.txt"); //used to rewrite the old file contents with the new change
	std::ifstream file_store;

	file_store.open(birthday_file);
	if (file_store.is_open() == false) {
		std::fstream file(birthday_file,std::ios::out);
		file.close();
		file_store.open(birthday_file);
	}

	while (file_store >> f_name >> l_name >> month >> day >> year) {
		
		if (f_name == target_f_name && l_name == target_l_name) {
			InData = true;
			std::cout << "\nHere's the current birthday entry:\n" << f_name << " " << l_name<< " " << month << "/" << day << "/" << year;
			std::cout << "\n\nEnter one of the following numbers that corresponds to what you want to change.";
			std::cout << "\nOptions:\n1. day \n2. month \n3. year \n4. first name \n5. last name\n\n>>";

			while (1) {
				std::getline(std::cin, temp2);
				std::stringstream input_stream(temp2);
				if (input_stream >> choice) { break; }
				else { std::cout << "Invalid choice. Try again.\n>>"; }
			}

			switch (choice) {
			case 1:
			{
				std::cout << "Please, enter the new day.\n>>";
				while (1) {
					std::string input = "";
					std::getline(std::cin, input);
					std::stringstream input_stream(input);
					if (input_stream >> day) { break; }
					else { std::cout << "Invalid input. Try again.\n>>"; }
				}
				checkForValidDay(day, month, year);
				break;
			}
			case 2:
				std::cout << "Please, enter the new month.\n>>";
				while (1) {
					std::string input = "";
					std::getline(std::cin, input);
					std::stringstream input_stream(input);
					if (input_stream >> month) { break; }
					else { std::cout << "Invalid input. Try again.\n>>"; }
				}
				checkForValidMonth(month);
				break;

			case 3:
			{
				std::cout << "Please, enter the new year.\n>>";
				while (1) {
					std::string input = "";
					std::getline(std::cin, input);
					std::stringstream input_stream(input);
					if (input_stream >> year) { break; }
					else { std::cout << "Invalid input. Try again.\n>>"; }
				}
				checkForValidYear(year, month, day);
				break;
			}
			case 4:
				std::cout << "Please, enter the new first name.\n>>";
				while (1) {
					std::getline(std::cin, temp1);
					f_name = temp1.substr(0, temp1.find(delimiter));
					if ( !(f_name.empty()) ) { break; }
					else { std::cout << "Invalid input. Try again.\n>>"; }
				}
				break;

			case 5:
				std::cout << "Please, enter the new last name.\n>>";
				while (1) {
					std::getline(std::cin, temp1);
					l_name = temp1.substr(0, temp1.find(delimiter));
					if (!(l_name.empty())) { break; }
					else { std::cout << "Invalid input. Try again.\n>>"; }
				}
				break;
			default:
				std::cout << "No option was selected, so going back to main menu.\n";
			}
			
		}
		
		overwrite_file << f_name << " " << l_name << " " << month << " " << day << " " << year << std::endl; //transfers changes to new file
	}
	if (!InData) { std::cout << "No contacts with that name.\n\n" ; }
	overwrite_file.close();
	file_store.close();

	std::remove(birthday_file.c_str());
	std::rename("temp_name.txt", birthday_file.c_str()); //renames overwrite file to original birthday file name
	SortEntries(); //sorts entries because there's no guarantee that everything will be alphabetical order
	RemoveDuplicates();
}


void BirthdayEntry::ViewSingleEntry(std::string desired_f_name, std::string desired_l_name) {
	std::string f_name, l_name;
	int month, day, year;
	
	std::ifstream file_store(birthday_file);
	while (file_store >> f_name >> l_name >> month >> day >> year) {
		if (f_name == desired_f_name && l_name == desired_l_name) {
			InData = true;
			std::cout << std::endl << f_name << " " << l_name <<" " << month << "/" << day << "/" << year << "\n\n";
			break;
		}
	
	}
	if (!InData) { std::cout << "No contacts with that name.\n\n"; }
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
	
	std::ofstream overwrite_file("temp_name.txt"); //used to rewrite the old file contents with the new change
	std::ifstream file_store;
	file_store.open(birthday_file);

	while (file_store >> f_name >> l_name >> month >> day >> year) {
		if (f_name == desired_f_name && l_name == desired_l_name) {
			InData = true;
			std::cout << "Found " << desired_f_name << " " << desired_l_name << ".\n Entry is now removed.\n" ;
		}
		else { overwrite_file << f_name << " " << l_name << " " << month  << " " << day << " " << year <<std::endl;}
	}
	
	if (!InData) { std::cout << "No contacts with that name.\n\n"; }

	overwrite_file.close();
	file_store.close();

	std::remove(birthday_file.c_str());
	std::rename("temp_name.txt", birthday_file.c_str());
}


void BirthdayEntry::SortEntries() {

	std::string f_name, l_name, line,search_first, search_second;
	int month, day, year;

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

	file_store.clear();
	file_store.seekg(0, std::ios::beg); //resets the stream to point at the beginning of the file again

	for (itr = names.begin(); itr != names.end();itr++) {
		search_first = itr->first;
		search_second = itr->second;

		while (getline(file_store, line)) {
			if (line.find(search_first) != std::string::npos && line.find(search_first) != std::string::npos) {
				overwrite_file << line<< std::endl;
			}
		}
		file_store.clear();
		file_store.seekg(0, std::ios::beg);
	}
	
	overwrite_file.close();
	file_store.close();
	
	std::remove(birthday_file.c_str());
	std::rename("temp_name.txt", birthday_file.c_str());
}


void BirthdayEntry::RemoveDuplicates() {

	std::string f_name, l_name,temp1;
	int month, day, year;

	std::set<std::string> name_set;
	std::ifstream original(birthday_file);
	std::ofstream new_file("temp.txt");

	//Set data structure gets rid of duplicates
	while (original >> f_name >> l_name >> month >> day >> year) {
		name_set.insert(f_name + " " + l_name + " " + std::to_string(month) + " " + std::to_string(day) + " " + std::to_string(year) + "\n");
	}

	for (auto const &str : name_set) { new_file << str; }

	original.close();
	new_file.close();
	std::remove(birthday_file.c_str());
	std::rename("temp.txt", birthday_file.c_str());
}


void BirthdayEntry::DeleteAllBirthdayEntries() {
	std::remove(birthday_file.c_str());
}


