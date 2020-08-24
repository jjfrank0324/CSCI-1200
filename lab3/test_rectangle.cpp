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
#include "Rectangle.h"

int main(){
  Point2D a(1,2);
  Point2D b(10,30);
  Point2D Q(5,35);
  Point2D P(5,25);
  Point2D e(10,50);

  Rectangle AF(a,b);
  Rectangle AE(a,e);
  cout<<AF.is_point_within(Q)<<endl;
  cout<<AF.is_point_within(P)<<endl;
  AF.add_point(Q);
  AE.add_point(P);
  AF.add_point(P);
  AF.add_point(b);
  std::vector<Point2D> QQQ=points_in_both(AE,AF);
  cout<<"Size is"<<QQQ.size()<<endl;
  for(int i=0;i<QQQ.size();i++)
  {cout<<"x is: "<<QQQ[i].x()<<"y is"<<QQQ[i].y()<<endl;}
  print_rectangle(AF);
// float Q=2.2;
// float P=10.10;
// Point2D a（Q,Q);
// // Point2D b（3,3);
// // Point2D c（4,3);
// // Point2D d（5,3);
// // Point2D e（6,3);
// Point2D f（P,P);
// Rectangle AF(a,f);
// // AF.add_point(b);
// print_rectangle(AF);











}
