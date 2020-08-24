#include <iostream>
#include <vector>
#include <list>

using namespace std;

void reverse_vector(vector<int> &V){
  for(unsigned int i =0;i<(V.size()/2);i++){
    int inter = V[i];
    V[i]=V[V.size()-1-i];
    V[V.size()-1-i]=inter;

  }

}


void print_V (vector<int> V){
  cout<< "\n The vector have the following content"<<endl;
  for(unsigned int i = 0; i<V.size();i++)
  cout<<V[i]<<" || ";
  cout<<"\n the size of this vector is "<< V.size();
}

void reverse_list(list<int> &L){
  list<int>::iterator B = L.begin();
  list<int>::reverse_iterator E = L.rbegin();
  int count =0;
  while(count < (L.size()/2)){
    int inter = *B;
    *B=*E;
    *E=inter;
    B++;
    E++;
    count++;

  }
  // list<int>::iterator B = L.begin();
  // list<int>::iterator E = L.end();
  // int count =0;
  // while(count < (L.size()/2)){
  //   int inter = *B;
  //   *B=*E;
  //   *E=inter;
  //   B++;
  //   E--;
  //   count++;
  //   cout<<L.size()<<endl;
  // }
}

void print_L(list<int> L){
  cout<<"\n the list have the following content"<<endl;
  list<int>::iterator I = L.begin();
  while(I != L.end()){
    cout<<*I<<"  ||  ";
    I++;
    }
  cout<<"\n The size of this list is"<<L.size()<<endl;
}

int main(){
  vector <int> V1;
  V1.push_back(1);
  V1.push_back(2);
  V1.push_back(3);
  V1.push_back(4);
  V1.push_back(5);
  V1.push_back(6);
  V1.push_back(7);
  V1.push_back(8);
  V1.push_back(9);
  V1.push_back(10);
  V1.push_back(11);
  V1.push_back(12);
  V1.push_back(13);
  V1.push_back(14);
  print_V(V1);

  reverse_vector(V1);

  print_V(V1);

  list<int> a;
  for(unsigned int i =1;i<10;++i){
    a.push_back(i*i);
  }
  print_L(a);
  reverse_list(a);
  print_L(a);







  return 1;
}
