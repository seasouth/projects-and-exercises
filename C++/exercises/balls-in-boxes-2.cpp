#include <string>
#include <vector>
#include <stack>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class BallsInBoxes {
  public:
    map <string,int> balls;
    vector <string> colors;
    vector <int> nballs;
    vector <string> boxes;
    void GenInstances();
};

void BallsInBoxes::GenInstances()
{
  stack <int> Stack;
  int index, color, i;

  Stack.push(-1);

  while (!Stack.empty()) {
    color = Stack.top();
    Stack.pop();
    index = Stack.size();

    // Base case -- if we're at the end of boxes, print it out and "return"

    if (index == boxes.size()) {
      cout << boxes[0];
      for (i = 1; i < boxes.size(); i++) cout << " " << boxes[i];
      cout << endl;
    } else {

      if (color != -1) {  // We have just finished enumerating with "color"
        nballs[color]++;  
      }

      // Find the next color to enumerate.  
      // Note how this works when color started at -1.

      for (color++; color < nballs.size() && nballs[color] == 0; color++) ;
    
      // If we still have a color to enumerate, put it into boxes, push
      // the color onto the stack, and push -1 on the stack to enumerate the next index.

      if (color < nballs.size()) {
        boxes[index] = colors[color];
        nballs[color]--;
        Stack.push(color);
        Stack.push(-1);
      }
    }
  }
}

int main()
{
  BallsInBoxes B;
  map <string, int>::iterator bit;
  string s;
  int nb;

  while (cin >> s) B.balls[s]++; 

  nb = 0;
  for (bit = B.balls.begin(); bit != B.balls.end(); bit++) {
    B.colors.push_back(bit->first);
    B.nballs.push_back(bit->second);
    nb += bit->second;
  }

  B.boxes.resize(nb);
  
  B.GenInstances();
}
