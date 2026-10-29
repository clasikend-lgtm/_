#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    float x, y, S, R, C;

    cin >> x >> y;

    R = pow((1 / sin(x / y)), -1);
    S = pow(exp(1.0), -3 * x) + cbrt(y);

    cout << endl << R << " " << S << endl;

    C = max(R, S);

    cout << C << endl;

    system("pause");

    return 0;
}