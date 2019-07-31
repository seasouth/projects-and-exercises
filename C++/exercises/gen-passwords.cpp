#include <string>
#include <iostream>
using namespace std;

main()
{
  string password;
  int i, j, k;

  password.resize(3);
  
  for (i = 0; i < 26*26*26; i++) {
    j = i;
    for (k = 0; k < 3; k++) {
      password[k] = 'a' + (j%26);
      j /= 26;
    }
    cout << password << endl;
  }
}
