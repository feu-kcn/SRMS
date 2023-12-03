#pragma once
#include "menu.h"
#include "user.h"
#include "fort.hpp"
#include "course.h"

using namespace std;

extern User loggedInUser;


void manageUsers();
void viewCourses();
void adminCreateUser();
void listAllTeacher();
void listAllStudent();
void updateUser();
void deleteUser();

// Options
MenuOptions homepageMenu = {
	{"Manage Users", manageUsers},
	{"View Courses", viewCourses}
};


MenuOptions manageUsersMenu = {
	{"Create", adminCreateUser},
	{"List All Teacher", listAllTeacher},
	{"List All Student", listAllStudent},
	{"Update", updateUser},
	{"Delete", deleteUser }
};

// helpers
void listAllTeacher() {
	displayTeachers();

	system("pause");

	goBack();
}

void listAllStudent() {
	displayStudents();

	system("pause");

	goBack();
}

User chooseUser() {
	displayUserTable();

	string id;
	while (true) {
		cout << "Enter ID or \"B\" to go back: ";
		cin >> id;

		if (id == "B") {
			goBack();
		}
		else {
			for (User user : users) {
				if (user.id == id) {
					return user;
					break;
				}
			}

			cout << "Invalid ID entered!" << endl << endl;
		}
	}
}

// Screens/Pages
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

void updateUser() {
	cout << "You are currently updating a user." << endl << endl;

	User selectedUser = chooseUser();

	string name;
	string password = "";

	cout << "Enter new name (enter \"KEEP\") if you want to keep previous): ";
	cin >> name;

	cout << "Enter new password (enter \"KEEP\" if you want to keep previous): ";
	cin >> password;

	if (password == "KEEP") {
		password = selectedUser.password;
	}

	if (name == "KEEP") {
		name = selectedUser.name;
	}

	selectedUser.name = name;
	selectedUser.password = password;

	UpdateUser(selectedUser);

	system("cls");

	displayUserTable();

	system("pause");

	goBack();
}

void deleteUser() {
	cout << "You are currently deleting a user." << endl << endl;

	User selectedUser = chooseUser();

	DeleteUser(selectedUser);

	system("cls");

	displayUserTable();

	system("pause");

	goBack();
}

void viewCourses() {
	cout << "You are currently viewing courses." << endl << endl;

	for (int i = 0; i < courses.size(); i++) {
		printCourse(courses[i]);
		cout << "-----------------------------------" << endl;	
	}

	system("pause");

	goBack();
}