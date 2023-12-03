#pragma once
#include "menu.h"
#include "user.h"
#include "course.h"
#include "fort.hpp"

using namespace std;

extern User loggedInUser;

void viewTeacherCourses();
void createStudentAttendance();
void createCourseExam();
void createStudentExamSubmission();
void deleteStudentAttendance();
void deleteStudentExamSubmission();

MenuOptions teacherMenu = {
	{"View Your Courses", viewTeacherCourses},
	{"Create Attendance", createStudentAttendance},
	{"Create Exam", createCourseExam},
	{"Create Exam Submission", createStudentExamSubmission},
	{"Delete Attendance", deleteStudentAttendance},
	{"Delete Exam Submission", deleteStudentExamSubmission}
};

/// pages
void TeacherScreen() {
	cout << "Welcome back, " << loggedInUser.name << "!" << endl;
	cout << "You are currently logged in as a teacher." << endl << endl;

	displayMenu(teacherMenu);
}

void viewTeacherCourses() {
	cout << "Viewing courses..." << endl;

	vector<Course> courses = getCoursesByTeacher(loggedInUser);

	for (int i = 0; i < courses.size(); i++) {
		printCourse(courses[i]);

		cout << "---------------------" << endl;
	}

	system("pause");

	goBack();
}

Course selectCourse() {
	// Choose course
	vector<Course> courses = getCoursesByTeacher(loggedInUser);

	if (courses.size() == 0) {
		cout << "You are not teaching any courses." << endl;
		system("pause");
		goBack();
	}

	fort::char_table table;
	table << fort::header << "ID" << "Name" << fort::endr;

	for (int i = 0; i < courses.size(); i++) {
		table << courses[i].id << courses[i].name << fort::endr;
	}

	cout << table.to_string() << endl;

	string courseId;

	while (true) {
		cout << "Enter Course ID or \"BACK\" to go back: ";
		cin >> courseId;

		if (courseId == "BACK") {
			goBack();
		}

		else {
			for (Course course : courses) {
				if (course.id == courseId) {
					return course;
					break;
				}
			}

			cout << "Invalid ID entered!" << endl << endl;
		}
	}
}

User selectStudent(Course course) {
	vector<User> students = getStudentsByCourse(course);
	
	fort::char_table table;
	table << fort::header << "ID" << "Name" << "# of Attendances" << fort::endr;
	
	for (int i = 0; i < students.size(); i++) {
		vector<Attendance> attendances = getAttendancesByCourseAndStudent(course, students[i]);

		table << students[i].id << students[i].name << attendances.size() << fort::endr;
	}

	cout << table.to_string() << endl;

	string studentId;

	while (true) {
		cout << "Enter Student ID or \"BACK\" to go back: ";
		cin >> studentId;

		if (studentId == "BACK") {
			goBack();
		}

		else {
			for (User student : students) {
				if (student.id == studentId) {
					return student;
					break;
				}
			}

			cout << "Invalid ID entered!" << endl << endl;
		}
	}
}

Exam chooseExam(Course course) {
	vector<Exam> exams = getExamsByCourse(course);

	fort::char_table table;
	table << fort::header << "Exam ID" << "Name" << "Maximum Score" << fort::endr;

	for (int i = 0; i < exams.size(); i++) {
		table << exams[i].id << exams[i].name << exams[i].maximumScore << fort::endr;
	}

	cout << table.to_string() << endl;

	string examId;

	while (true) {
		cout << "Enter Exam ID or \"BACK\" to go back: ";
		cin >> examId;

		if (examId == "BACK") {
			goBack();
		} else {
			for (Exam exam : exams) {
				if (exam.id == examId) {
					return exam;
					break;
				}
			}

			cout << "Invalid ID entered!" << endl << endl;
		}
	}
}

void createStudentAttendance() {
	Course course = selectCourse();

	while (true) {
		User student = selectStudent(course);

		createAttendance(course, student);

		cout << "Student attendance created! New count: " << getAttendancesByCourseAndStudent(course, student).size() << endl << endl;

		char choice;
		cout << "Do you want to add more attendance? (Y/N): ";
		cin >> choice;

		if (choice == 'N' || choice == 'n') {
			goBack();
		}
	}
}

void createCourseExam() {
	Course course = selectCourse();

	string examName;
	int maximumScore;
	cout << "Enter exam name: ";
	cin >> examName;
	cout << "Enter maximum score: ";
	cin >> maximumScore;

	createExam(course, examName, maximumScore);

	cout << "Exam created!" << endl << endl;

	system("pause");

	goBack();
}

void createStudentExamSubmission() {
	Course course = selectCourse();
	Exam exam = chooseExam(course);
	User student = selectStudent(course);

	int score;
	cout << "Enter score: ";
	cin >> score;

	createExamResult(exam, student, score);

	cout << "Exam submitted!" << endl << endl;

	system("pause");

	goBack();
}

void deleteStudentAttendance() {
	Course course = selectCourse();
	User student = selectStudent(course);
	vector<Attendance> attendances = getAttendancesByCourseAndStudent(course, student);

	fort::char_table table;
	table << fort::header << "Attendance ID" << fort::endr;

	for (int i = 0; i < attendances.size(); i++) {
		table << attendances[i].id  << fort::endr;
	}

	cout << table.to_string() << endl;

	string attendanceId;

	while (true) {
		cout << "Enter Attendance ID or \"BACK\" to go back: ";
		cin >> attendanceId;

		if (attendanceId == "BACK") {
			goBack();
		} else {
			for (Attendance attendance : attendances) {
				if (attendance.id == attendanceId) {
					removeAttendance(attendance);

					cout << "Attendance deleted!" << endl << endl;

					system("pause");

					goBack();
				}
			}

			cout << "Invalid ID entered!" << endl << endl;
		}
	}
}

void deleteStudentExamSubmission() {
	Course course = selectCourse();
	User student = selectStudent(course);

	vector<ExamResult> examResults = getExamResultsByCourseAndStudent(course, student);

	fort::char_table table;
	table << fort::header << "Exam Result ID" << "Exam Name" << "Maximum Score" << "Score" << fort::endr;

	for (int i = 0; i < examResults.size(); i++) {
		table << examResults[i].id << examResults[i].exam.name  << examResults[i].exam.maximumScore << examResults[i].score << fort::endr;
	}

	cout << table.to_string() << endl;

	string examResultId;

	while (true) {
		cout << "Enter Exam Result ID or \"BACK\" to go back: ";
		cin >> examResultId;

		if (examResultId == "BACK") {
			goBack();
		} else {
			for (ExamResult examResult : examResults) {
				if (examResult.id == examResultId) {
					removeExamResult(examResult);

					cout << "Exam result deleted!" << endl << endl;

					system("pause");

					goBack();
				}
			}

			cout << "Invalid ID entered!" << endl << endl;
		}
	}
}