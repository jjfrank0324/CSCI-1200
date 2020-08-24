#include <iostream>
#include <list>
#include <vector>
#include <cassert>
using namespace std;


void print(const std::string &label, const std::list<std::string> &data) {
  std::cout << label;
  for (std::list<std::string>::const_iterator itr = data.begin();
       itr != data.end(); itr++) {
    std::cout << " " << *itr;
  }
  std::cout << std::endl;
}



void update(std::list<std::string> &data, std::vector<std::string> add, std::vector<std::string> remove){

  for (std::list<std::string>::iterator i = data.begin(); i!=data.end();i++){
    //  cout<<"enter?";
      for( unsigned int R = 0; R<remove.size();R++){
        if((*i).find(remove[R]) != std::string::npos){
        //  cout<<"endDELETING?";
          data.erase(i);
          i--;
        }
      }
      // for( unsigned int A = 0; A<add.size();A++){
      //   if(add[A]<*i){
      //     data.insert(i,add[A]);
      //   //  remove(add.begin(),add.end(),add[A]);
      //   }
      // }
  }

  for( std::vector<std::string>::iterator A = add.begin(); A!=add.end() && add.size()!=0;A++){
    for (std::list<std::string>::iterator i = data.begin() ; i!=data.end() && add.size()!=0;i++){
      if(*A<*i){
        //cout<<*i<<"<----i value is the following"<<endl;
        //cout<<*A<<"<----A value is the following"<<endl;;

        //cout<<"entered\n"<<*A<<"   "<<*i<<endl;
          //print ("Before Processing:",data);
         data.insert(i,*A);
         add.erase(A);
         //print ("Processing:",data);
        // cout<< add.size()<<"add size is"<<endl;
         i=data.end();
      }
    }
  }
if (add.size()>0){
  for(int i = 0; i<add.size();i++)
  {data.push_back(add[i]);}
}

 // for (std::list<std::string>::iterator i = data.begin(); i!=data.end();i++){
 //   for( std::vector<std::string>::iterator A = add.begin(); A!=add.end();A++){
 //     if(*A<*i && *A != *(i++)){
 //       data.insert(i,*A);
 //       add.erase(A);
 //
 //     }
 //   }
 // }




}





int main() {


  // Examples demonstrating STL string find:
  // catfish contains the substring fish
  assert (std::string("catfish").find(std::string("fish")) != std::string::npos);
  // fish contains the substring fish
  assert (std::string("fish").find(std::string("fish")) != std::string::npos);
  // fish does not contain the substring catfish
  assert (std::string("fish").find(std::string("catfish")) == std::string::npos);


  // A simple example:
  std::list<std::string> data;
  data.push_back("antelope");
  data.push_back("catfish");
  data.push_back("giraffe");
  data.push_back("llama");
  data.push_back("jellyfish");
  data.push_back("whale_shark");
  data.push_back("zebra");

  std::vector<std::string> add;
  add.push_back("tiger");
  add.push_back("llama");
  add.push_back("elephant");
  add.push_back("zzzzz");
  std::vector<std::string> remove;
  remove.push_back("fish");
  remove.push_back("bear");
  remove.push_back("whale");

  print ("before:",data);
  update(data,add,remove);
  print ("after: ",data);

  // at the end, data should contain: antelope elephant giraffe llama tiger zebra
  assert (data.size() == 7);

}
