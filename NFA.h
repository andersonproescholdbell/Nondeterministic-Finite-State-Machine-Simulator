#ifndef NFA_H
#define NFA_H

#include <vector>
#include <map>
using namespace std;

class NFA {
 public:
  NFA();
  ~NFA();
  void addState(int num, bool start, bool accepting);
  void addTransition(int start, int end, char c);
  vector<pair<int, bool>> transition(char c);
  bool end();
 private:
  vector<int> currentStates;
  map<int, bool> states;
  map<int, map<char, vector<int>>> transitions;
};

#endif
