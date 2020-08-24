class Person{
public:
  Person();
  Person(std::string afname, std::string alname, std::vector<int> ascores, int atotal_score);
// ACCESSORS
  std::string getfname() const;
  std::string getlname() const;
  std::string getname() const;
  std::vector<int> getscores() const;
  int gettotal_scores() const;
  void set_totalscores(int total);



private: // REPRESENTATION (member variables)
  std::string fname; // stand for first_name
  std::string lname; // stand for last_name
  std::vector<int> scores;
  int total_score;
};

bool lower_score(const Person& p1, const Person& p2);
bool lower_name(const Person& p1, const Person& p2);
