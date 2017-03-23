#include <iostream>
#include <cmath>

using namespace std;

int gcd (int, int);

int main ()
{
    cout << "int gcd of 12 and 8" << gcd(12, 8)
    << "\n\nint gcd of 3 and 4" << gcd (3,4);

    return 0;

}

int gcd ( int a, int b)
{
    int aa = abs(a);
        int bb = abs(b);
        if (aa == 0)
        {
            return bb;
        }
        if (bb == 0)
        {
            return aa;
        }
        return gcd(bb, aa%bb);
}
