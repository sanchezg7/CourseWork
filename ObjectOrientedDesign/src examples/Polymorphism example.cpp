#include <iostream>
using namespace std;

class Polygon {
  protected:
    int width, height;
  public:
    void set_values (int a, int b)
      { 
          width=a; height=b; 
          cout << "Polygon set values" << endl;
      }
    int area()
    { 
        cout << "Polygon Area" << endl;
        return 0;
    }
};

class Rectangle: public Polygon {
  public:
    void set_values(int a, int b)
    {
        cout << "Rectangle Set Values" << endl;
    }
    int area()
      { return width*height; }
};

class Triangle: public Polygon {
  public:
  
    //will not actually set values, we will use polymorphism
    void set_values(int a, int b)
    {
        cout << "Triangle Set Values" << endl;
    }

    int area()
      { return width*height/2; }
};

int main () {
  Rectangle rect;
  Triangle trgl;
  Polygon * ppoly[2];
  ppoly[0] = &rect;
  ppoly[1] = &trgl;
  
  for (int i=0; i< 2; i++)
    {
        ppoly[i]->set_values (4,5);
        cout << ppoly[i] ->area() << endl;
    }

  cout << rect.area() << '\n';
  cout << trgl.area() << '\n';
  `
  return 0;
}