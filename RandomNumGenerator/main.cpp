#include <bits/stdc++.h>
using namespace std;

int Random(int Xo, int m, int a, int c)
{
    cout << Xo << " ";
    return ((Xo * a) + c) % m;
}

int main()
{
    int Xo = 2432;  // Initial value
    int m = 134456; // mod
    int a = 8121;   // Multiply
    int c = 28411;  // add

    for (int i = 0; i < 10; i++)
    {
        Xo = Random(Xo, m, a, c);
    }

    return 0;
}