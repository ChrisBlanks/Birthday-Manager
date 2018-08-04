#ifndef USERINTERFACE
#define USERINTERFACE

class BirthdayManagerMenu {
public:
	BirthdayManagerMenu();
	
	void StartUp();
	void PrintGreeting();
	int SelectOption();
	void SelectEvent(int user_selection);

private:
	bool ExitCondition = false;
};

#endif
