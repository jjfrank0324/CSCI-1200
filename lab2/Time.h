class Time {
public:
  Time();
  Time(int ahour, int aminute, int asecond);
// ACCESSORS
  int gethour() const;
  int getminute() const;
  int getsecond() const;
  // MODIFIERS
  void sethour(int hour);
  void setminute(int minute);
  void setsecond(int second);

  void printAmPm() const;



private: // REPRESENTATION (member variables)
  int hour;
  int minute;
  int second;
};


bool IsEarlierThan (const Time& t1, const Time& t2);
