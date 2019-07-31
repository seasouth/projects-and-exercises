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
    vector <string> boxes;
    void GenInstances();
};

typedef map <string, int>::iterator SIMit;

void BallsInBoxes::GenInstances()
{
  unsigned int index, i;
  SIMit bit, nextbit;
  stack <SIMit> st;

  st.push(balls.end());

  while (!st.empty()) {
    bit = st.top();
    st.pop();
    index = st.size();
    if (index == boxes.size()) { // Base case.
      cout << boxes[0];
      for (i = 1; i < boxes.size(); i++) cout << " " << boxes[i];
      cout << endl;

    } else {
      if (bit == balls.end()) { // If we're starting, set bit to the first color
        bit = balls.begin();
      } else {                  // Otherwise, undo the last enumeration
        bit->second++;
        bit++;
      }

      // Find the next color to enumerate
      while (bit != balls.end() && bit->second == 0) bit++;

      if (bit != balls.end()) {   // Enumerate the next color.
        boxes[index] = bit->first;
        bit->second--;
        st.push(bit);
        st.push(balls.end());
      }
    }
  }
}

int main()
{
  BallsInBoxes B;
  string s;
  int nb;

  nb = 0;
  while (cin >> s) { 
    B.balls[s]++; 
    nb++; 
  }
  B.boxes.resize(nb);
  
  clock_t begin = clock();
  B.GenInstances();
  clock_t end = clock();
  double elapsed = double(end - begin) / CLOCKS_PER_SEC;
  printf("%f\n", elapsed);
}
