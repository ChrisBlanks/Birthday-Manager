#ifndef BIRTHDAY_ENTRIES
#define BIRTHDAY_ENTRIES
#include "stdafx.h"

class BirthdayEntry {
public:
	BirthdayEntry();
	BirthdayEntry(std::string f_name,std::string l_name); 
	BirthdayEntry(std::string f_name, std::string l_name, int month, int day, int year); 
	
	
	void StoreEntry();
	void ViewBirthdayList();
	void ViewSingleEntry(std::string desired_f_name, std::string desired_l_name);
	void DeleteEntry(std::string desired_f_name, std::string desired_l_name);
	void EditEntry(std::string desired_f_name,std::string desired_l_name);
	void DeleteAllBirthdayEntries();


private:
	int bday_month, bday_day, bday_year;
	std::string first_name, last_name;
	const std::string birthday_file = "Birthdays_Storage.txt";
	bool InData = false; 

	void SortEntries();
};

#endif
