#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//this is an hash table class
// we use vector of int to store data
// linear probing is used to avoid collision( with space of 2)

class hash_int
{
  public:
    //defalut constructor
    hash_int(unsigned int asize);

    //finding function, return all the match index
    vector<int> find(unsigned int hash_value, const string& long_gene,int kmer, const string& word);

    //resize function, resize hash table
    void resize(const string& long_gene,const int& kmer);

    //insert hashfunctions, using hash functionto find the index
    //and insert it into the hash table
    void insert(unsigned int hash_value, int value, float fraction,
                const string& long_gene,int kmer);

    //help function to help us visualize the std::vector<int> v;
    void print(std::ostream & ostr);

    //asseeor, return the size
    int get_size(){ return size_;}

    //hash function, return the hash value
    unsigned int hashing(std::string const& key) ;

    //helper function, help us retreive the word
    string get_word(const string& long_gene, unsigned int index, int kmer);

  private:
    //the size of the list
    int size_;
    //the hash table
    std::vector< int > m_table;
    //the number of data within the table
    int data_;

};

//defalut constructor
hash_int::hash_int(unsigned int asize)
{
  size_ = asize;
  data_ = 0;
  //if nothing has been putted in yet, the value will be -1
  std::vector< int> table(asize, -1);
  m_table = table;
}

//find function: return all the match index
vector<int> hash_int::find(unsigned int hash_value, const string& long_gene, int kmer, const string& word)
{
  vector<int> result;

  //start searching until it hit an empty space
  unsigned int index = hash_value % size_;
  //the space will be two due to the way we insert it
  for(;m_table[index] != (-1); index+=2 )
  {
    index = index % size_;
    string word2 = long_gene.substr(m_table[index] , kmer );

    //if match put it into the vector
    if(word == word2)
    {
    result.push_back(m_table[index]);
    }
  }
  return result;
}




//helper function, help us visualize the hash table
void  hash_int::print(std::ostream & ostr)
{
  for (unsigned int i=0; i<m_table.size(); ++i) {
    ostr << i << ": ";
      ostr << ' ' << m_table[i];
    ostr << std::endl;
  }
}

//insert data into the table
//since the data is too squeeze
// we will use space of two in linear probing
//this can make it run faster
void hash_int::insert(unsigned int hash_value, int value, float fraction,
                      const string& long_gene, int kmer)
{
  //to see weather we need to resize it or not
  if(data_ >= fraction * size_)
    this->resize(long_gene, kmer);

//calculation the index
// in collision happended, it will go to next two space
//it will kepp going untion the in find some completly empty spce
// value = -1 ,means empty
  unsigned int index = hash_value % size_;
  while(m_table[index] != -1)
  {
    index += 2;
    index = index % size_;
  }
  m_table[index] = value;
  data_++;

}


//resize function
void hash_int::resize(const string& long_gene, const int& kmer)
{
  //creat an new table with double of its origin size
  int new_size = size_*2;
  hash_int set2(new_size);

  //insert every elements in the old table into the new
  // bigger table
  for(unsigned int i =0; i < m_table.size(); i++)
    {
      if(m_table[i] != -1)
      {
        string word = long_gene.substr(m_table[i], kmer );
        set2.insert(hashing(word), m_table[i],1, long_gene, kmer);
      }
    }

  //marking the increment of the size
  size_ = set2.size_;
  m_table = set2.m_table;
}


// the hash function
unsigned int hash_int::hashing(std::string const& key)
{
  //  This implementation comes from
  //  http://www.partow.net/programming/hashfunctions/
  unsigned int hash = 1315423911;
  for(unsigned int i = 0; i < key.length(); i++)
    hash ^= ((hash << 5) + key[i] + (hash >> 2));
  return hash;


  //bad version Checkpoint1
  // return key.size();
}

string hash_int::get_word(const string& long_gene, unsigned int index, int kmer)
{
  return long_gene.substr(index , kmer );
}
