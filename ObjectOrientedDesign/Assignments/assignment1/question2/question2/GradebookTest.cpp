#include <iostream>
#include <cstdlib>
#include "Gradebook.h"

using namespace std;

int main ()
{
	int input = 1;
	string nameI, nameC;
	GradeBook class1("Programming", "Dr. Sun");

	class1.displayMessage();

	while (input != 0)
	{
		switch (input)
		{
			case 1:
				cout << "Enter instructor name: " << endl;
				cin >> nameI;
				class1.setInstructor(nameI);
				goto menu;
			case 2:
				cout << "Instructor name: " << class1.getInstructor() << endl;
				goto menu;
			case 3:
				cout << "Enter course name: " << endl;
				cin >> nameC;
				class1.setCourse(nameC);
				goto menu;
			case 4:
				cout << "Course name: " << class1.getCourse() << endl;
				goto menu;
			default:
			menu :
				cout << endl;
					cout << "Enter a choice 1-4 or 0 to terminate the program.\n"
					<< "Choice 1: change instructor name\n"
					<< "Choice 2: get instructor name\n"
					<< "Choice 3: change course name\n"
					<< "Choice 4: get course name\n"
					<< "Enter 0 to exit" << endl;
					cin >> input;
					system("CLS");
				break;
		}
	}

	

	return 0;

}