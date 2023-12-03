#pragma once
#include "menu.h"
#include "user.h"
#include "navigation.h"
#include "fort.hpp"

extern User loggedInUser;

using namespace std;


void ViewCoursesSummary();

void ViewExamSubmissions();

MenuOptions studentMenu = {
	{ "View Courses", ViewCoursesSummary },
	{ "View Exam Submissions", ViewExamSubmissions },
};

void Studenthomepage() {
	cout << "Welcome to FEU Student Portal Homepage!! " << loggedInUser.name << endl;

	displayMenu(studentMenu);
}

void ViewCoursesSummary() {
	fort::char_table table;
	table << fort::header
		<< "Course ID"
		<< "Course Name"
		<< "Attendances"
		<< "Grades"
		<< "Remarks"
		<< fort::endr;

	vector<Course> courses = getCoursesByStudent(loggedInUser);

	for (Course course : courses) {
		vector<Attendance> attendances = getAttendancesByCourseAndStudent(course, loggedInUser);
		float grade = getExamScoreByCourseAndStudent(course, loggedInUser);
		string remarks = "";
		int minimumAttendance = course.maximumAttendance * 0.7;

		if (attendances.size() < minimumAttendance) {
			remarks = "FA";
		}
		else if (grade < 70) {
			remarks = "F";
		}
		else {
			remarks = "Passed";
		}

		table
			<< course.id
			<< course.name
			<< attendances.size()
			<< grade
			<< remarks
			<< fort::endr;
	}
	
	std::cout << table.to_string() << std::endl;

	system("pause");

	goBack();
}

void ViewExamSubmissions() {
	fort::char_table table;
	table << fort::header
		<< "Course ID"
		<< "Course Name"
		<< "Exam ID"
		<< "Exam Name"
		<< "Maximum Score"
		<< "Passing Score"
		<< "Submission Score"
		<< "Remarks"
		<< fort::endr;

	vector<Course> courses = getCoursesByStudent(loggedInUser);

	for (Course course : courses) {
		vector<ExamResult> examResults = getExamResultsByCourseAndStudent(course, loggedInUser);

		for (ExamResult result : examResults) {
			string remarks = "";
			int passingScore = (result.exam.maximumScore * 0.7);

			if (result.score < passingScore) {
				remarks = "F";
			}
			else {
				remarks = "Passed";
			}

			table
				<< course.id
				<< course.name
				<< result.exam.id
				<< result.exam.name
				<< result.exam.maximumScore
				<< passingScore
				<< result.score
				<< remarks
				<< fort::endr;
		}
		
	}

	std::cout << table.to_string() << std::endl;

	system("pause");

	goBack();
}