#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class People {
  public:
    int print;
    vector <string> people;
    void GenPermutations(int index);
};

void People::GenPermutations(int index)
{
  int i;
  string tmp;

  if (index == people.size()) {
    if (print) {
      cout << people[0];
      for (i = 1; i < people.size(); i++) cout << " " << people[i];
      cout << endl;
    }
    return;
  }

  for (i = index; i < people.size(); i++) {

    tmp = people[i];         /* Swap people[index] with people[i] */
    people[i] = people[index];
    people[index] = tmp;

    GenPermutations(index+1);  

    tmp = people[i];          /* Swap back */
    people[i] = people[index];
    people[index] = tmp;
  }
}

int main(int argc, char **argv)
{
  People P;
  string s;
  int i, j;

  P.print = 1;
  if (argc == 2) {
    s = argv[1];
    if (s == "No" || s == "no") P.print = 0;
  }

  while (cin >> s) P.people.push_back(s);
  
  P.GenPermutations(0);
}
