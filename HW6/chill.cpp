
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <algorithm>
using namespace std;
string int_to_str(int a)
{
  stringstream ss;
  ss << a;
  string str = ss.str();
  return str;

}

int main ()
{
  int a = 10;
  string test = " Lol, we got an A";
  string adder =  int_to_str(a);
  test = test+adder;
  cout<<test;
}
