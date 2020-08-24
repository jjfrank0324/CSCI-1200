#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include "BPlusTree.h"
void RealTreeTestNoPrint(std::ofstream& outfile);
int main(int argc, char* argv[]){
  if (argc!=2){
		std::cerr << "Correct usage is " << argv[0] << " [output file]" << std::endl;
		return -1;
	}
	std::ofstream outfile(argv[1]);
	if(!outfile){
		std::cerr << "Failed to open " << argv[1] << " for writing." << std::endl;
		return -1;
	}

  	RealTreeTestNoPrint(outfile);
}

void RealTreeTestNoPrint(std::ofstream& outfile)
{

  BPlusTree<int> b1(3);
	BPlusTree<int> b2(3);
  b2.insert(6);
    b2.insert(5);
      b2.insert(4);
      b2.insert(3);
            b2.insert(2);
                        b2.insert(1);
                        b2.insert(3);
                        b2.insert(19);
                        b2.insert(29);
                        b2.insert(39);
                        b2.insert(49);
                        b2.insert(94);
                        b2.insert(33);
                        b2.insert(16);
                        b2.insert(43);
                        b2.insert(23);
                        b2.insert(53);
         b2.print_BFS_pretty(outfile);
	// for(int i=1; i<=6; i++){
	// 	std::cout<<i<<"OVERhere"<<i<<std::endl;;
	// 	b1.insert(i);
	// 	b2.insert(7-i);
	// }
  // b1.print_BFS(outfile);
  // b2.print_BFS(outfile);
  // if(b1.find(1)->contains(1));
  //   std::cout<<"YESSSSSSSSSSSS"<<std::endl;
  //  b1.insert(4);
}
