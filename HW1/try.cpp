#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[])
{
    std::string order = argv[4];
    int Len = atoi(argv[3])+4;//
    std::string Head(Len, '-');
//Over here, take it all the inputs and save it somewhere

    ofstream OUT;
    OUT.open(argv[2]);
    OUT<<Head<<"\n";
  //print the headline of the program
  //take all the inputs and save them all into a vector array
    ifstream infile;
    std::string txt;
    std::string t1;
    infile.open(argv[1]);
    vector<std::string> words_L;
    while(infile>>t1)
{
    words_L.push_back(t1);
}

//this is the first part of the work. flush flush_left
//I write into the file line by Line
//I use for loops for the words array and check the proper conditions
if (order == "flush_left")
{
  int total_L = 4;
  std::string Line ;

  for (int i = 0; i<words_L.size();i++)
  {
    if ((4+Line.size()+words_L[i].size())<Len)
    {
      Line += (words_L[i]+' ');
      std::cout<<Line<<"|||||"<<words_L[i]<<std::endl;
    }
    else
    {
      //std::cout<<Line.size()<<"SIZE"<<std::;
      std::string Space (Len-4-Line.size(),' ');
      Line += Space;
      OUT<<"| "<<Line<<" |"<<"\n";
      Line=words_L[i]+' ';
    }
  }
  std::string Space (Len-4-Line.size(),' ');
  Line += Space;
  OUT<<"| "<<Line<<" |"<<"\n";
}
//  std::cout<<"L";

//This is similar to the flush_left except for several minor formating setting change
if (order == "flush_right")
{
  int total_L = 4;
  std::string Line ;

  for (int i = 0; i<words_L.size();i++)
  {
    if ((4+Line.size()+words_L[i].size())<Len)
    {
      Line += (words_L[i]+' ');
      std::cout<<Line<<"|||||"<<words_L[i]<<std::endl;
    }
    else
    {
      //std::cout<<Line.size()<<"SIZE"<<std::;
      std::string Space (Len-4-Line.size()+1,' ');
      Line = Space+Line;
      OUT<<"| "<<Line<<"|"<<"\n";
      Line=words_L[i]+' ';
    }
  }
  std::string Space (Len-4-Line.size()+1,' ');
  Line = Space+Line;
  OUT<<"| "<<Line<<"|"<<"\n";
  //  std::cout<<"R";
}


//this is the last and the hardeset part
//I use if statement to seperate the super-long words cases from the normal _Jv_RegisterClasses
if (order == "full_justify")
{ std::string Line;
  std::string new_word;
  vector<std::string> words;
  int sentence_L= 0;
  for (int i = 0; i<words_L.size();i++)
  { if(words_L[i].size()> Len-4)
    { new_word="";
      Line+="| ";
      for (int j =0;j<Len-4-1;j++)
      {
        Line+=words_L[i][j];
      }
      Line +="- |" ;
      OUT<<Line<<"\n";
      Line = "";
      for (int k=Len-4-1;k<words_L[i].size();k++)
      {
        new_word+=words_L[i][k];
      }
      words_L[i]=new_word;
      i-=1;
    }

    else{
    if ((4+  sentence_L+words_L[i].size())<Len)
    {
      words.push_back(words_L[i]);
      sentence_L += (words_L[i].size());
      //std::cout<<words_L[i]<<sentence_L<<std::endl;
    }
    else
    {
      //std::cout<<"vertorSIZE words size"<<words.size()<<std::endl;
      int Space_num = ((Len - 4 - sentence_L-words.size())/(words.size()-1));
      int Diff = Len-Space_num*(words.size()-1)-sentence_L;
      std::cout<<"Diff is"<<Diff<<words[0]<<std::endl;
      //std::cout<<Len<<'@'<<sentence_L<<'@'<<words.size()<<'@'<<std::endl;
      //std::cout<<"Here is Space"<<Space_num<<std::endl;
      for (int j = 0; j< words.size();j++)
      {if (Diff!=0)
        {words[j]+=' ';
        Diff-=1;}
        std::string Space(Space_num,' ');
        words[j]+= Space;
       }

      }

      for (int o = 0; o< words.size();o++)
      { Line += words[o];}
      std::cout<<"here is the line "<<Line<<std::endl;
      OUT<<"| "<<Line<<"|"<<"\n";
      words.clear();
      std::cout<<"vertorSIZE words size after "<<words.size()<<std::endl;
      words.push_back(words_L[i]);
      Line="";
      sentence_L = (words_L[i].size());
      int Space_num=0;
      }
    }
    for (int j = 0; j<words.size();j++)
    {Line += (words[j]+' ') ;}
    std::string Space (Len-4-Line.size(),' ');
  std::cout<<Line<<std::endl;
  OUT<<"| "<<Line<<" |"<<"\n";
  }




  OUT<<Head;
//std::cout<<Head<<std::endl;
infile.close();
OUT.close();
return 0;

}

//if (words.size()!=0)
// {  for (int j = 0; j<words.size();j++)
//         {Line += (words[j]+' ') ;}
//         std::string Space (Len-4-Line.size(),' ');
//         Line += Space;
//         std::cout<<Line<<std::endl;
//         OUT<<"| "<<Line<<" |"<<"\n";
//         words.clear();
//         Line="";}
