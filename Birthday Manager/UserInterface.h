#ifndef USERINTERFACE
#define USERINTERFACE

class BirthdayManagerMenu {
public:
	BirthdayManagerMenu();
	
	void StartUp();
	void PrintGreeting();
	bool CheckForExistingData();
	void CreateInitialData();
	int SelectOption();
	void SelectEvent(int user_selection);
	bool isEmpty(std::ifstream &data_file) { return data_file.peek() == std::ifstream::traits_type::eof(); }

private:
	bool ExitCondition = false;
	bool HasDataFile;
};



#endif
