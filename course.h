#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "user.h"
#include "fort.hpp"

using namespace std;

/// <summary>
///  Classes
/// </summary>
class Course {
public:
	string id;
	string name;
	User teacher;

	int maximumAttendance;

	bool operator==(const Course& other) const {
		return id == other.id;
	}
};


class Attendance {
public:
	string id;
	Course course;
	User student;

	bool operator==(const Attendance& other) const {
		return id == other.id;
	}
};

class Exam {
public:
	string id;
	Course course;
	string name;
	int maximumScore;

	bool operator==(const Exam& other) const {
		return id == other.id;
	}
};

class ExamResult {
public:
	string id;
	Exam exam;
	User student;
	int score;

	bool operator==(const ExamResult& other) const {
		return id == other.id;
	}
};

class Enrollment {
public:
	string id;
	Course course;
	User student;

	bool operator==(const Enrollment& other) const {
		return id == other.id;
	}
};

/// <summary>
/// Global variables, from SRMS.cpp
/// </summary>

extern vector<Course> courses;
extern vector<Attendance> attendances;
extern vector<Exam> exams;
extern vector<ExamResult> examResults;
extern vector<Enrollment> enrollments;

/// ******
/// Course Module
/// ******

Course createCourse(string name, User teacher, int maximumAttendance) {
	Course course;
	course.id = "CS" + to_string(courses.size() + 1);

	course.name = name;
	course.teacher = teacher;
	course.maximumAttendance = maximumAttendance;

	courses.push_back(course);

	return course;
}

// Get all students in a course
vector<User> getStudentsByCourse(Course course) {
	vector<User> studentsByCourse = {};

	for (Enrollment enrollment : enrollments) {
		if (enrollment.course == course) {
			studentsByCourse.push_back(enrollment.student);
		}
	}

	return studentsByCourse;
}

/// ******
/// Enrollment Module
/// ******

// Add a student to a course
void enrollStudentToCourse(User student, Course course) {
	Enrollment enrollment;
	enrollment.id = "EN" + to_string(enrollments.size() + 1);
	enrollment.course = course;
	enrollment.student = student;

	enrollments.push_back(enrollment);
}

void unenrollStudentToCourse(User student, Course course) {
	// Find the enrollment data first
	Enrollment enrollment;
	for (Enrollment e : enrollments) {
		if (e.course == course && e.student == student) {
			enrollment = e;
			break;
		}
	}

	// Remove the enrollment data
	enrollments.erase(remove(enrollments.begin(), enrollments.end(), enrollment), enrollments.end());
}

/// ******
/// Attendances Module
/// ******

// Create an attendance for a student in a course
Attendance createAttendance(Course course, User student) {
	Attendance attendance;
	attendance.id = "AT" + to_string(attendances.size() + 1);
	attendance.course = course;
	attendance.student = student;

	attendances.push_back(attendance);

	return attendance;
}

// Remove an attendance for a student in a course
void removeAttendance(Attendance attendance) {
	attendances.erase(remove(attendances.begin(), attendances.end(), attendance), attendances.end());
}

// Get all attendances for a course from a student
vector<Attendance> getAttendancesByCourseAndStudent(Course course, User student) {
	vector<Attendance> attendancesByCourseAndStudent = {};

	for (Attendance attendance : attendances) {
		if (attendance.course == course && attendance.student == student) {
			attendancesByCourseAndStudent.push_back(attendance);
		}
	}

	return attendancesByCourseAndStudent;
}

/// ******
/// Exam Module
/// ******

// Create an exam for a course
Exam createExam(Course course, string name, int maximumScore) {
	Exam exam;
	exam.id = "EX" + to_string(exams.size() + 1);
	exam.course = course;
	exam.name = name;
	exam.maximumScore = maximumScore;

	exams.push_back(exam);

	return exam;
}

// Remove an exam for a course
void removeExam(Exam exam) {
	exams.erase(remove(exams.begin(), exams.end(), exam), exams.end());
}

/// ******
/// Exam Results Module
/// ******

// Create an exam result for a student in an exam
ExamResult createExamResult(Exam exam, User student, int score) {
	ExamResult examResult;
	examResult.id = "ER" + to_string(examResults.size() + 1);
	examResult.exam = exam;
	examResult.student = student;
	examResult.score = score;

	examResults.push_back(examResult);

	return examResult;
}

// Remove an exam result for a student in an exam
void removeExamResult(ExamResult examResult) {
	examResults.erase(remove(examResults.begin(), examResults.end(), examResult), examResults.end());
}

// Get all exams for a course
vector<Exam> getExamsByCourse(Course course) {
	vector<Exam> examsByCourse = {};

	for (Exam exam : exams) {
		if (exam.course == course) {
			examsByCourse.push_back(exam);
		}
	}

	return examsByCourse;
}

// Get all exam results for a course from a student
vector<ExamResult> getExamResultsByCourseAndStudent(Course course, User student) {
	vector<ExamResult> examResultsByCourseAndStudent = {};

	for (ExamResult examResult : examResults) {
		if (examResult.exam.course == course && examResult.student == student) {
			examResultsByCourseAndStudent.push_back(examResult);
		}
	}

	return examResultsByCourseAndStudent;
}

// Sum all exam results and divide over exam's maximum score
float getExamScoreByCourseAndStudent(Course course, User student) {
	float totalScore = 0;
	float totalMaximumScore = 0;

	for (ExamResult examResult : examResults) {
		if (examResult.exam.course == course && examResult.student == student) {
			totalScore += examResult.score;
			totalMaximumScore += examResult.exam.maximumScore;
		}
	}

	if (totalScore == 0 && totalMaximumScore == 0) {
		// Return -1 for debugging if the user does not have any
		// exam results yet
		return -1;
	}
		 
	return (totalScore / totalMaximumScore) * 100;
}

// Get all courses by teacher
vector<Course> getCoursesByTeacher(User teacher) {
	vector<Course> coursesByTeacher = {};

	for (Course course : courses) {
		if (course.teacher == teacher) {
			coursesByTeacher.push_back(course);
		}
	}

	return coursesByTeacher;
}

/// <summary>
/// Show summary of course
/// </summary>
void printCourse(Course course) {
	cout << "Course ID: " << course.id << endl;
	cout << "Course Name: " << course.name << endl;
	cout << "Course Teacher: " << course.teacher.name << endl;
	cout << "Max Attendance Set: " << course.maximumAttendance << endl;
	cout << "Course Students: " << endl;

	vector<User> students = getStudentsByCourse(course);

	fort::char_table table;
	table << fort::header
		<< "ID" << "Name" << "# of Attendances" << "Exam Grades" << "Remarks" << fort::endr;

	for (User user : students) {
		vector<Attendance> attendances = getAttendancesByCourseAndStudent(course, user);
		float grade = getExamScoreByCourseAndStudent(course, user);
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
			<< user.id
			<< user.name
			<< attendances.size()
			<< to_string(grade) + "%"
			<< remarks
			<< fort::endr;
	}

	std::cout << table.to_string() << std::endl;
}