#pragma once
#include <functional>

using namespace std;

using ScreenFunc = function<void()>;

extern stack<ScreenFunc> navigation;

void displayScreen(ScreenFunc currentScreen) {
	// Clear screen
	system("cls");

	// Push screen to the stack to be the latest one, and Display screen
	navigation.push(currentScreen);

	currentScreen();
}

bool canGoBack() {
	// Check if we can go back to previous screen
	return navigation.size() > 1;
}

void goBack() {
	if (canGoBack()) {
		// Pop the current screen
		navigation.pop();

		// Get the previous screen
		ScreenFunc previousScreen = navigation.top();

		// Clear screen
		system("cls");

		// Display the previous screen
		previousScreen();
	}
	else {
		cout << "!! ERROR: Cannot go back !!";
	}
}