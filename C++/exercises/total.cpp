#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream input("numbers.txt");
    int val;
    int total = 0;
    while (input >> val) {
        total += val;
    }
    cout << "Total: " << total << endl;
}
