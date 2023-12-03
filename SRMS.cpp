// SRMS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <functional>
#include <stack>
#include <unordered_map>
#include "user.h"
#include "navigation.h"
#include "menu.h"

using namespace std;

vector<User> users = {};
User loggedInUser;
stack<ScreenFunc> navigation;
using Option = pair<std::string, std::function<void()>>;

void test() {
	cout << "Test";
}

void createUsers() {
	cout << "Creating users";

	vector<Option> menuOptions = {
		{"Delete", test},
		{"List All", test},
		{"Update", test}
	};

	displayMenu(menuOptions);
}

void viewCourses() {
	cout << "Viewing courses";
}	

void homepage() {
	cout << "Homepage";

	vector<Option> menuOptions = {
		{"Create Users", createUsers},
		{"View Courses", viewCourses}
	};

	displayMenu(menuOptions);
}



int main()
{
	// initialize();
	// loggedInUser = login();
	// cout << "Logged in user: " << loggedInUser.name;

	// displayScreen(homepage);

	displayScreen(homepage);
	
	

	return 0;

}
