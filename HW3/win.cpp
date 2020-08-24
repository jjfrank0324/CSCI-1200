#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;

int main(int argc, char const *argv[]) {
  double** data = new double [3][3];
  for(unsigned int i =0; i<3; i++)
    {for(unsigned int j =0;j<3;j++)
        data[i][j]=3;
    }
  return 0;
}
