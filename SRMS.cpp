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

// Classes
#include "user.h"
#include "course.h"

// Helpers
#include "navigation.h"
#include "menu.h"

// Pages
#include "admin.h"
#include "teacher.h"

using namespace std;

vector<User> users = {};
vector<Course> courses = {};
vector<Attendance> attendances = {};
vector<Exam> exams = {};
vector<ExamResult> examResults = {};
vector<Enrollment> enrollments = {};

User loggedInUser;
stack<ScreenFunc> navigation;

void homepage() {
	switch (loggedInUser.type)
	{
		case admin:
			adminHomepage();
			break;
		case teacher:
			TeacherScreen();
			break;
		case student:
			// studentHomepage();
			break;
		default:
			break;
	}
}

void initialize() {
	// Create dummy user accounts for testing
	User adminUser = createUser("Admin", "admin", admin);
	User teacherUser = createUser("Teacher", "teacher", teacher);
	User studentUser1 = createUser("Student 1", "student", student);
	User studentUser2 = createUser("Student 2", "student", student);
	User studentUser3 = createUser("Student 3", "student", student);

	users.push_back(adminUser);
	users.push_back(teacherUser);
	users.push_back(studentUser1);
	users.push_back(studentUser2);
	users.push_back(studentUser3);

	Course course = createCourse("Programming", teacherUser, 10);
	createAttendance(course, studentUser1);
	createAttendance(course, studentUser1);
	createAttendance(course, studentUser1);
	createAttendance(course, studentUser1);
	createAttendance(course, studentUser1);
	createAttendance(course, studentUser1);
	createAttendance(course, studentUser1);
	enrollStudentToCourse(studentUser1, course);

	Exam midterm = createExam(course, "Midterm", 50);
	ExamResult midtermResult = createExamResult(midterm, studentUser1, 40);

	// createAttendance(course, studentUser1);
}


int main()
{
	initialize();
	// loggedInUser = login();
	loggedInUser = users[1];
	cout << "Logged in user: " << loggedInUser.name;

	displayScreen(homepage);
	
	return 0;

}