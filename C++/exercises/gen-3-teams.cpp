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
    vector <string> people;
    vector <string> team;
    void GenTeams(int index, int npeople);
};

void People::GenTeams(int index, int npeople)
{
  int i;

  /* Base case -- if there are no more people to add, 
     print out the team and return */

  if (npeople == 0) {
    cout << team[0];
    for (i = 1; i < team.size(); i++) cout << " " << team[i];
    cout << endl;
    return;
  }

  /* This is a second base case -- if there are fewer people left to add
     than there are places left on the team, then it's impossible to finish,
     so simply return.  Ask yourself why this is better than testing whether
     index is equal to people.size(), and returning if so. */

  if (npeople > people.size() - index) return;

  /* Now, put the person in people[index] onto the team, and call GenTeams()
     recursively.  Afterwards, take the person off of the team. */

  team.push_back(people[index]);
  GenTeams(index+1, npeople-1);
  team.pop_back();

  /* Finally, call GenTeams() recursively without putting
     people[index] on the team. */

  GenTeams(index+1, npeople);
}

int main()
{
  People P;
  string s;
  int i, j;

  while (cin >> s) P.people.push_back(s);
  
  P.GenTeams(0, 3);
}
