//define the class for Gradebook the interface is in the header file Header.h
#include <iostream>
#include "Gradebook.h"
using namespace std;
	
	//constructor
	GradeBook::GradeBook(string course, string instructor)
	{
		setCourse(course);
		setInstructor(instructor);
	}
	//set instructor name
	void GradeBook::setInstructor(string name)
	{
		instructorName = name;
	}
	//get instructer name
	string GradeBook::getInstructor() const
	{
		return instructorName;
	}
	//set different course name
	void GradeBook::setCourse(string name)
	{
		courseName = name;
	}
	//get name of course
	string GradeBook::getCourse() const
	{
		return courseName;
	}

	void GradeBook::displayMessage() const
	{
		cout << "Welcome to the grade book for \n" << getCourse() << "!"
			<< endl << "This course is presented by: " << getInstructor() << endl;
	}
