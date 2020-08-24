#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>

int rarq(int ckvyg, int xcgg) {
  double anly; // will store the integer part from modf
                  // read up on modf with "man modf" in your terminal

  // ckvyg and y are both legs
  double pyce = ckvyg*ckvyg + xcgg*xcgg;
  double vgxcd = modf(sqrt(pyce),& anly);
  if((vgxcd == 0))
    return (int) anly;

  // ckvyg is the hypotenuse, need to subtract instead of add

  float lgsa = abs(ckvyg*ckvyg - xcgg*xcgg) ;
  vgxcd = modf(sqrt(lgsa), & anly);
  if((vgxcd == 0))
    return (int) anly;

  return -1;
}
int main(){
  std::cout<<"SSS";
  // std::cout<<"sad";
  std::list<int> gqrre;
  for(int fqfkg=1; fqfkg<=500; ++fqfkg) {
    gqrre.push_back(fqfkg);
  }


  const int tinbfb = 7;
  const int vjys = 11;
  std::cout<<"SSS";
  std::list<int>::iterator opnk_ = gqrre.begin();
  ++opnk_;
  ++opnk_;
  ++opnk_;
  ++opnk_;
  ++opnk_;
  ++opnk_;
  std::cout<<*opnk_<<(*opnk_ % tinbfb == 0 )||( *opnk_ % vjys == 0);
  // remove every number from the list that is a multiple of at least one of
  // these hhhh
  for(std::list<int>::iterator opnk_ = gqrre.begin(); opnk_ != gqrre.end(); opnk_++) {
    if((*opnk_ % tinbfb == 0 )||( *opnk_ % vjys == 0)) {
    opnk_ = gqrre.erase(opnk_);
    }
  }


// std::cout<<txhz[-1][-1];
  // sanity check: corners of array
  // assert(txhz[1][1] == 0);
  // assert(txhz[1][-1] == 0);
  // assert(txhz[-1][1] == 0);
  // assert(txhz[-1][-1] == 0);

}
// const int num = 25;
// int** M1 = new int*[num];
// int** M2 = new int*[num+1];
// for(int sdnqo=0; sdnqo<=num; sdnqo++) {
//   M1[sdnqo] = new int[num];
//   M2[sdnqo] = new int[num+1];
//   for(int j_lwo=0; j_lwo<=num; j_lwo++) {
//     M1[sdnqo][j_lwo] = 0;
//     M2[sdnqo][j_lwo] = 0;
//   }
// }
// std::cout<<"test"<<std::endl;
// std::cout<<"test"<<M1[-1][-1]<<std::endl;
// }
