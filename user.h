#pragma once
#include <string>
#include <stack>
#include <algorithm>
#include "fort.hpp"

using namespace std;

// Define user types available in our application
enum userType { admin, student, teacher };

// Define User class that handles User logic
class User {
public:
	string id;
	string name;
	string password;
	userType type;

	bool operator==(const User& other) const {
		return id == other.id && type == other.type;
	}

	bool isStudent() const {
		return type == student;
	}

	bool isAdmin() const {
		return type == admin;
	}

	bool isTeacher() const {
		return type == teacher;
	}
};

// Fetch global variable from entry file (SRMS.cpp)
extern vector<User> users;
extern User loggedInUser;

// Function to get the number of users based on a type
// For example: This is used when you want to get how many
// teachers do you have, or how many students, or how many
// admins
int countUsersByType(userType type) {
	return count_if(users.begin(), users.end(), [type](const User& user) {
		switch (type) {
		case student:
			return user.isStudent();
		case admin:
			return user.isAdmin();
		case teacher:
			return user.isTeacher();
		default:
			return false;
		}
		});
}

// Logic to create user
User createUser(string name, string password, userType type) {
	User user;

	user.name = name;
	user.type = type;
	user.password = password;

	int lastId = countUsersByType(type);
	int newId = lastId + 1;
	
	// Add a prefix to the user id based on the type
	string pad = "";
	switch (type)
	{
	case admin:
		pad = "admin_";
		break;
	case student:
		pad = "student_";
		break;
	case teacher:
		pad = "teacher_";
		break;
	default:
		break;
	}
	user.id = pad + to_string(newId);

	return user;
}

// Method to add user
void AddUser(User user) {
	users.push_back(user);
}

// Method to delete user
void DeleteUser(User user) {
	users.erase(remove(users.begin(), users.end(), user), users.end());
}

// Method to update user
void UpdateUser(User user) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i] == user) {
			users[i] = user;
		}
	}
}

// Method for fetching User(s) with type of teacher
vector<User> GetTeachers() {
	vector<User> teachers = {};

	for (User user : users) {
		if (user.isTeacher()) {
			teachers.push_back(user);
		}
	}

	return teachers;
}

// Method for fetching User(s) with type of student
vector<User> GetStudents() {
	vector<User> students = {};

	for (User user : users) {
		if (user.isStudent()) {
			students.push_back(user);
		}
	}

	return students;
}

User login() {
	User user;
	string id, password;

	// Keep asking for credentials until correct one is entered
	while (true)
	{
		// Ask for user credentials
		cout << "Enter ID: ";
		cin >> id;
		cout << "Enter Password: ";
		cin >> password;

		for (User user : users) {
			if (user.id == id && user.password == password) {
				// Clear console screen
				system("cls");
				return user;
			}
		}

		cout << "Invalid ID or Password entered!" << endl << endl;
	}
}

void displayUserTable() {
	fort::char_table table;
	table << fort::header
		<< "ID" << "Name" << "Password" << fort::endr;

	for (User user : users) {
		table << user.id << user.name << user.password << fort::endr;
	}

	std::cout << table.to_string() << std::endl;
}

// Get User based on id
User getUserById(string id) {
	for (User user : users) {
		if (user.id == id) {
			return user;
			break;
		}
	}
}

void logout() {
	system("cls");

	loggedInUser = login();
}