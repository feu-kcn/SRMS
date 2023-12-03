#pragma once
#include "menu.h"
#include "user.h"
#include "fort.hpp"

using namespace std;

extern User loggedInUser;

void test() {
	cout << "Test";
}

void manageUsers();
void adminCreateUser();
void listAllTeacher();
void listAllStudent();
void updateName();
void deleteUser();

MenuOptions homepageMenu = {
	{"Manage Users", manageUsers},
	{"View Courses", test}
};

MenuOptions manageUsersMenu = {
	{"Create", adminCreateUser},
	{"List All Teacher", listAllTeacher},
	{"List All Student", listAllStudent},
	{"Update Name", test},
	{"Delete", test}
};

void adminHomepage() {
	cout << "Welcome back, " << loggedInUser.name << "!" << endl;
	cout << "You are currently logged in as an admin." << endl << endl;

	displayMenu(homepageMenu);
}

void manageUsers() {
	cout << "You are currently managing users." << endl << endl;

	displayMenu(manageUsersMenu);
}

void adminCreateUser() {
	string type = "";
	string name;
	string password;

	cout << "You are currently creating a user." << endl << endl;
	
	while (!(type == "teacher" || type == "student")) {
		cout << "Enter type (teacher/student): ";
		cin >> type;
	}

	cout << "Enter name: ";
	cin >> name;

	cout << "Enter password: ";
	cin >> password;

	userType userType = type == "teacher" ? teacher : student;

	User createdUser = createUser(name, password, userType);
	AddUser(createdUser);

	system("cls");

	if (userType == teacher) {
		cout << "Created teacher:" << endl;
	}
	else if (userType == student) {
		cout << "Created student:" << endl;
	}

	cout << "ID: " << createdUser.id << endl;
	cout << "Name: " << createdUser.name << endl;
	cout << "Password: " << createdUser.password << endl << endl;

	system("pause");

	goBack();
}

void listAllTeacher() {
	fort::char_table table;
	table << fort::header
		<< "ID" << "Name" << "Managed Courses" << fort::endr;

	for (User user : GetTeachers()) {
		table << user.id << user.name << "CCS0003L" << fort::endr;
	}

	std::cout << table.to_string() << std::endl;

	system("pause");

	goBack();
}

void listAllStudent() {
	fort::char_table table;
	table << fort::header
		<< "ID" << "Name" << "Enrolled Courses" << fort::endr;

	for (User user : GetStudents()) {
		table << user.id << user.name << "CCS0003L" << fort::endr;
	}

	std::cout << table.to_string() << std::endl;

	system("pause");

	goBack();
}
