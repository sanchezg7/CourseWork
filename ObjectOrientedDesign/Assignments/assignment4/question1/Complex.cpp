//Complex class member-function definitions.    
#include  <iostream>    
#include <iomanip>
#include"Complex.h"  

// Complex class definition    
using namespace  std;     
//Constructor  
Complex::Complex(double realPart, double imaginaryPart) : real(realPart ), imaginary(imaginaryPart)    
{}

//addition operator    
Complex Complex::operator+(const Complex &operand2) const  
{  
	return  Complex(real + operand2.real,    imaginary + operand2.imaginary);    
}

// subtraction operator    
Complex Complex::operator-(const Complex &operand2) const    
{   
	return  Complex( real - operand2.real,   imaginary - operand2.imaginary );    
}

Complex Complex::operator*(Complex &operand2)
{
	//assume (x+yi)(u+vi) then multiplication is (xu - yv) + (xv + yu)i
	return Complex(((real*operand2.real) - (imaginary*operand2.imaginary)), ((real*operand2.imaginary) + (imaginary * operand2.real)));
}

bool Complex::operator==(const Complex &operand2) const
{
	if((real == operand2.real) && (imaginary == operand2.imaginary))
	{
		return true;
	}
	else {
		return false;
	}
}

bool Complex::operator!=(const Complex &operand2) const
{
	if ((real == operand2.real) && (imaginary == operand2.imaginary))
	{
		return false;
	}
	else {
		return true;
	}
}

/* display a Complex object in the form: (a, b)    
void  Complex::print() const   
{   
	cout << '(' << real << ", " << imaginary <<  ')';
}
*/

ostream &operator<< (ostream &output, const Complex &number)
{
	output << number.real << "+" << number.imaginary << "i";

	return output;
}

istream &operator>> (istream &input, Complex &number)
{
	cout << "Input the real portion of the number" << endl;
	input >> number.real;
	cout << "Input the imaginary portion of the number" << endl;
	input >> number.imaginary;

	return input;
}


