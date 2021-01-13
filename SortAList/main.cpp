#include <bits/stdc++.h>
using namespace std;

struct Hack
{
    string name;
    int year;
    int month;
    int day;
};

bool compare(Hack a, Hack b)
{
    if (a.year != b.year)
        return a.year < b.year;

    if (a.month != b.month)
        return a.month < b.month;

    if (a.day != b.day)
        return a.day < b.day;

    return a.name < b.name;
}

int main()
{
    int n;
    cout << "How many hacks? ";
    cin >> n;

    Hack arr[n];

    cout << "Enter details of Hacks" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "Hack " << i + 1 << " name: ";
        cin >> arr[i].name;
        cout << "Hack " << i + 1 << " date (YYYY MM DD): ";
        cin >> arr[i].year >> arr[i].month >> arr[i].day;
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (compare(arr[i], arr[j]))
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    cout << "List of Hacks in chronological order (lexographic if same date)" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << arr[i].name << "      ";
        cout << arr[i].year << " ";
        if (arr[i].month / 10 == 0)
        {
            cout << "0";
        }
        cout << arr[i].month << " ";
        if (arr[i].day / 10 == 0)
        {
            cout << "0";
        }
        cout << arr[i].day << endl;
    }

    return 0;
}