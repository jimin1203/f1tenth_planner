#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

int main (int argc, char** argv) {
  string str_buf;
  fstream fs;

  fs.open("levine.csv", ios::in);

  while (!fs.eof()) {
    getline(fs, str_buf, ',');
    cout<<str_buf<<endl;
  }

  fs.close()

  return 0;

}