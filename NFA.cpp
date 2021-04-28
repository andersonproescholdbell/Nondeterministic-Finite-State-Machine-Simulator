#include <iostream>
#include <vector>
#include <map>
#include "NFA.h"
using namespace std;

NFA::NFA() {
  currentStates.push_back(0);
}

NFA::~NFA() {

}

void NFA::addState(int num, bool start, bool accepting) {
  if (start) {
    currentStates[0] = num;
  }
  states.insert(pair<int, bool>(num, accepting));
}

void NFA::addTransition(int start, int end, char c) {
  if (transitions.find(start) == transitions.end()) {
    vector<int> v;
    v.push_back(end);
    map<char, vector<int>> m;
    m.insert(pair<char, vector<int>>(c, v));
    transitions.insert(pair<int, map<char, vector<int>>>(start, m));
  } else {
    if (transitions.find(start)->second.find(c) == transitions.find(start)->second.end()) {
      vector<int> v;
      v.push_back(end);
      transitions.find(start)->second.insert(pair<char, vector<int>>(c, v));
    } else {
      transitions.find(start)->second.find(c)->second.push_back(end);
    }   
  }
}

vector<pair<int, bool>> NFA::transition(char c) {
  vector<pair<int, bool>> v;
  int startSize = currentStates.size();
  for (int i = 0; i < startSize; i++) {
    if (transitions.find(currentStates[i]) != transitions.end()) {
      map<char, vector<int>> m = transitions.find(currentStates[i])->second;
      if (m.find(c) != m.end()) {
	vector<int> ends = m.find(c)->second;
	for (int j = 0; j < ends.size(); j++) {
	  currentStates.push_back(ends[j]);
	  v.push_back(pair<int, bool>(ends[j], states.find(ends[j])->second));
	}
      }
    }
  }

  currentStates.erase(currentStates.begin(), currentStates.begin()+startSize);

  return v;
}

bool NFA::end() {
  for (int i = 0; i < currentStates.size(); i++) {
    if (states.find(currentStates[i])->second) {
      return true;
    }
  }
  return false;
}
