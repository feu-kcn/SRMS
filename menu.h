#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include "navigation.h"

using namespace std;

using Option = pair<string, function<void()>>;

typedef vector<Option> MenuOptions;

void exitApp() {
	exit(0);
}

// Displays the menu, and ask for choice
void displayMenu(MenuOptions menuOptions) {
	if (canGoBack()) {
		menuOptions.push_back({ "Back", goBack });
	}
	else {
		// If we cannot go back, it means that we are at the main menu
		// So we can add the logout option

		menuOptions.push_back({ "Logout", logout });
	}
	
	// Add exit option
	menuOptions.push_back({ "Exit", exitApp });

	cout << endl << endl;

	// Print options vertically with index
	for (int i = 0; i < menuOptions.size(); ++i) {
		cout << "[" << i + 1 << "]" << " " << menuOptions[i].first << "\n";
	}

	// Print new lines
	cout << endl << endl;

	// Ask for choice until valid choice is entered
	int choice;
	while (true) {
		cout << "Enter choice: ";
		cin >> choice;
		
		// Get the number of options available
		int size = menuOptions.size();

		if (choice > 0 && choice <= size) {
			int choiceIndex = choice - 1;

			// Check if selected option is exit or back
			// If it's exit or back, run the function
			// If it's not, wrap the function in displayScreen
			// So that we can keep track of the navigation

			// We do not need to track the back option or exit
			// Doing so, causes bugs :(
			if (choiceIndex == size - 1 || choiceIndex == size - 2) {
				menuOptions[choiceIndex].second();
			} else {
				displayScreen(menuOptions[choiceIndex].second);
			}
			
			break;
		}
		else {
			cout << "Invalid choice entered!" << endl;
		}
	}
}