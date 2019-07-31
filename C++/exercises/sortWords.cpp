#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Read words from cin into the given vector of strings.
void readWords( vector< string > &words )
{
  string word;
  while ( cin >> word ) {
      words.push_back(word);
  }
}

// Use the index operator ( you know, [] ) to print out the list
// of words in reverse.
void printBackward( const vector< string > &words )
{
  cout << "-- Backward --" << endl;
  for (int i = words.size() - 1; i >= 0; i--) {
      cout << words[i] << endl;
  }
}

// Use iteratros to print the list forward.
void printForward( const vector< string > &words )
{
  cout << "-- Forward --" << endl;
  for (auto it = words.begin(); it != words.end(); it++) {
      cout << *it << endl;
  }
}

int main()
{
  // You can make a vector of strings.  Why not.
  vector< string > words;

  // Read a list of words.
  readWords( words );

  // Use a template algorithm to sort them.
  sort(words.begin(), words.end());
  

  // Print the list backward.
  printBackward( words );

  // Then print it again, forward this time.
  printForward( words );
}
