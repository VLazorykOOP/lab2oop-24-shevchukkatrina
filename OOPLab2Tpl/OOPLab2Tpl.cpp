#include <iostream>
using namespace std;

static int Task1() {
    int a, b, c, d, x, y;

    cout << "Enter integers a and b:";
    cin >> a >> b;
    cout << "Enter integers c and d:";
    cin >> c >> d;

    x = ((((b << 4) + b) + ((a << 11) + (a << 9) + (a << 8) + (a << 7) + (a << 6) + (a << 2))) >> 5) - ((c << 6) + (c << 5) + (c << 4) + (c << 3)) + ((d << 7) - d);

    y = (17 * b + 3012 * a) / 32 - c * 120 + d * 127;

    cout << " x=" << x << " a=" << a << " b=" << b << " c=" << c << " d=" << d << " y=" << y << endl;
    return 0;
}

int main()
{
    Task1();
}
