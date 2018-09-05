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

void BirthdayEntry::EditEntry(std::string desired_f_name, std::string desired_l_name) {
	
	std::string f_name, l_name, name_change;
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
			{
				std::cout << "Please, enter the new day.\n>>";
				std::cin >> day;

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

				break;
			}
			case 2:
				std::cout << "Please, enter the new month.\n>>";
				std::cin >> month;
					
				while (month > 12 || month < 1) {
					std::cout << "Hey, your month is invalid. Try again!\n>>";
					std::cin >> month;
				}
				break;

			case 3:
			{
				std::cout << "Please, enter the new year.\n>>";
				std::cin >> year;

				std::chrono::system_clock Clock;
				auto now = Clock.now(); //gets current point in time
				std::time_t tt = std::chrono::system_clock::to_time_t(now); //conversion to C time datatype
				std::tm local_tm = *localtime(&tt); //converts into a local time

				//uses the current year as the max  and 1900 as the min (anybody born before 1900 is probably dead)
				while (year > (local_tm.tm_year+1900) || year < 1900) {
					std::cout << "Hey, your year is invalid. Try again!\n>>";
					std::cin >> year;
				}

				//checking to see if change in year is valid due to some years being leap years
				if (month == 2 && day == 29) {
					if (year % 4) {
						if ((year % 100 == 0) && (year % 400) != 0) {
							while (year > (local_tm.tm_year + 1900) || year < 1900) {
								std::cout << "The year that you entered isn't a leap year,";
								std::cout << " which goes against having a birthday on the 29th of february. Try again!\n>>";
								std::cin >> year;
							}
						}
					}
				}

				break;
			}
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


