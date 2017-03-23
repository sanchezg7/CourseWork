#include <iostream>
using namespace std;

int main(){

	int num1, num2, num3;
	double average;
	int sum, product, small, large;

	cout << "Input three different integers: " << endl;
	cin >> num1 >> num2 >> num3;

	sum = num1 + num2 + num3;
	average = (double)(num1 + num2 + num3) / 3;
	product = num1 * num2 * num3;

	//assume num1 is already the biggest and the smallest integer
	small = num1;
	large = num1;

	if (num2>num3)
	{
		large = num2;
	}
	if (num3>num2 && num3>num1)
	{
		large = num3;
	}
	if (num2<num1)
	{
		small = num2;
	}
	if (num3<num2 && num3<num1)
	{
		small = num3;
	}


	cout << "Sum is: " << sum << endl << "Average is: " << average << endl << "Product is: " << product << endl << "Smallest is: " << small << endl << "Largest: " << large << endl;
	
	return 0;

}