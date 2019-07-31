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

int main()
{
  vector <string> people;
  string s;
  int i, j;

  while (cin >> s) people.push_back(s);
  if (people.size() > 30) {
    cerr << "Sorry, not generating more than 2^30 teams\n";
    exit(1);
  }

  for (i = 1; i < (1 << people.size()); i++) {
    for (j = 0; j < people.size(); j++) {
      printf("%c", (i & (1 << j)) ? '1' : '0');
    }
    for (j = 0; j < people.size(); j++) {
      if (i & (1 << j)) printf(" %s", people[j].c_str());
    }
    printf("\n");
  }
  exit(0);
}

  
