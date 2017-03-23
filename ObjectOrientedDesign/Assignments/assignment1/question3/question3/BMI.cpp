//question3 BMI Indicator
#include <iostream>
using namespace std;

int main()
{
	int weight, height; //measured in pounds and inches
	double bmi;

	cout << "Enter your weight in pounds and height in inches: " << endl;
	cin >> weight >> height;

	bmi = double (weight * 703) / (height*height);

	cout << "Your BMI is: " << bmi << endl << "BMI VALUES" << endl
		<< "Underweight : less than 18.5" << endl
		<< "Normal: \t between 18.5 and 24.9" << endl
		<< "Overweight: between 25 and 29.9" << endl
		<< "Obese: \t 30 or greater " << endl;

	return 0;
}