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

#include "admin.h"

using namespace std;

vector<User> users = {};
User loggedInUser;
stack<ScreenFunc> navigation;
using Option = pair<std::string, std::function<void()>>;

void homepage() {
	switch (loggedInUser.type)
	{
		case admin:
			adminHomepage();
			break;
		case teacher:
			// teacherHomepage();
			break;
		case student:
			// studentHomepage();
			break;
		default:
			break;
	}
}

int main()
{
	initialize();
	// loggedInUser = login();
	// loggedInUser = users[0];
	cout << "Logged in user: " << loggedInUser.name;

	displayScreen(homepage);
	
	return 0;

}
