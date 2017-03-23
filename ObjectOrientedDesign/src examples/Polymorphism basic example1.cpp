#include <iostream> 
using namespace std; 
class Base { 
public:
  void dummy() {cout << "Base" << endl;} 
}; 
class Derived: public Base { 
public:
   void dummy(){cout << "derived" << endl;}
};

int main()
{
    Base b1;
    Base *bp;
    Derived d1;
    Derived *dp;
    
    b1.dummy();
    d1.dummy();
    
    bp = &b1;
    bp->dummy();
    
    bp = &d1;
    bp->dummy();
    
}