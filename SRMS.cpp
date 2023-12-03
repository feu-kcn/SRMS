// SRMS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <stack>

// Classes
#include "user.h"
#include "course.h"

// Helpers
#include "navigation.h"
#include "menu.h"

// Pages
#include "admin.h"
#include "teacher.h"
#include "student.h"

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
			Studenthomepage();
			break;
		default:
			break;
	}
}

void initialize() {
	// Create dummy user accounts for testing
	User adminUser = createUser("Admin", "admin", admin);
	User teacherUser = createUser("Teacher", "teacher", teacher);

	User studentUser1 = createUser("Student 1", "student1", student);
	users.push_back(studentUser1);

	User studentUser2 = createUser("Student 2", "student2", student);
	users.push_back(studentUser2);

	User studentUser3 = createUser("Student 3", "student3", student);
	users.push_back(studentUser3);

	users.push_back(adminUser);
	users.push_back(teacherUser);

	Course course = createCourse("Programming", teacherUser, 10);
	enrollStudentToCourse(studentUser1, course);
	createAttendance(course, studentUser1);
	createAttendance(course, studentUser1);
	createAttendance(course, studentUser1);
	createAttendance(course, studentUser1);
	createAttendance(course, studentUser1);
	createAttendance(course, studentUser1);
	createAttendance(course, studentUser1);
	createAttendance(course, studentUser1);

	Exam midterm = createExam(course, "Midterm", 50);
	ExamResult midtermResult = createExamResult(midterm, studentUser1, 40);
}

void mainLogin() {
	system("cls");

	loggedInUser = login();

	displayScreen(homepage);
}


int main()
{
	initialize();

	mainLogin();
	
	return 0;

}