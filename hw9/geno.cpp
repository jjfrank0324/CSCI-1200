#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;
#include "hash_int.h"

//this is the hash function that we use in lab
// it help us eventually distubute the key
unsigned int hasher(std::string const& key) {
  //  This implementation comes from
  //  http://www.partow.net/programming/hashfunctions/
  unsigned int hash = 1315423911;
  for(unsigned int i = 0; i < key.length(); i++)
    hash ^= ((hash << 5) + key[i] + (hash >> 2));
  return hash;

}

  // to make my origram looks more clearly, I do all the input things
  //at the begining of the main function, all the things and command
  // will be store in to several vector
  //after taht, we will retreive back all the things and do
  // the finding things

int main(int argc, char** argv)
{

//1st part of the program: read in all the inputs
  string text;
  cin>>text;
  cin>>text;
  string filename = text;

  //that's the defalut cofficient, size , and kmer size
  // if any of them is giver, the value will be updated
  int size = 100;
  float occ = 0.5;
  int kmer = 0;


  //read unitl query occur
  while(text != "query")
  {
    if(text == "table_size")
      cin>>size;
    if(text == "kmer")
      cin>>kmer;
    if(text == "occupancy")
      cin>>occ;
    cin>>text;
  }

//use two container to store the query info
// one for error, one for the gene we want to find
//flag is an variable to determine where we are when we are
//doing the reading
  vector<int> Err;
  vector<string> gene;
  int flag = 1;
  while(cin>>text && text != "quit")
  {
    if(flag == 0)
      {
        flag++;
        continue;
      }
    if(flag == 1)
      {
        int temp = atoi( text.c_str() );
        Err.push_back(temp);
        flag++;
        continue;
      }
    if(flag == 2)
    {
      gene.push_back(text);
      flag = 0;
      continue;
    }
  }

//open the gene txt file and store it into a string called long_gene
  ifstream infile;
  infile.open(filename.c_str());

  string long_gene = "";
  while(infile>>text)
  long_gene += text;


//using my own class which is called hash_int,
// which is the hash table for the int
    hash_int table(size);

//after that, we will turn the long gene into many substring, then store
// it into the table we create
//the staring index of the kmer is the thing we use to store in
    for(unsigned int i=0; i<long_gene.size()-kmer;i++)
    {
      string temp =  long_gene.substr(i, kmer);
      table.insert(hasher(temp),i, occ, long_gene, kmer );
    }

// start retreive the data over here
    for(unsigned int i =0; i<gene.size(); i++)
    {
      cout<<"Query: "<<gene[i]<<endl;
      string seed = gene[i].substr(0,kmer);
      // find all the possible possition and store it into the table
      vector<int> result = table.find(hasher(seed), long_gene, kmer, seed);

//bool is the flag that help us determine whether we
//successfully find the data or not
      bool match = false;
      for(unsigned int k=0; k< result.size(); k++)
      {
        int mismatch = 0;
        string possible = long_gene.substr(result[k], gene[i].size());
        // over herem we go though the list to find how many dismatch

          for(unsigned int l = 0; l< gene[i].size(); l++)
          {
            if(possible[l] != gene[i][l])
              mismatch ++;
          }
  // if the dismatch is within the range, we will print it out,
  // this means that it's a valid fragment of gene
          if(mismatch <= Err[i])
          {
            cout<<result[k]<<" "<<mismatch<<" "
            <<long_gene.substr(result[k], gene[i].size())<<endl;
            //the match flagalso need to be set as true
            //this means at least one match is find
            match =true;
          }


      }
//if find nothing, print No match
    if(match == false)
    cout<<"No Match"<<endl;

    }



}
