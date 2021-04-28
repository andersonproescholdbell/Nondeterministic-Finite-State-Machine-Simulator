#include <iostream>
#include <vector>
#include <unistd.h>
#include "NFA.h"
using namespace std;

int main(int argc, char* argv[]) {
  // create DFA here

  NFA nfa = NFA();

  // example from "Nondeterministic Finite Automata" week 7 video, ACCEPT if second from last character is a 1
  nfa.addState(0, true, false);
  nfa.addState(1, false, false);
  nfa.addState(2, false, true);
  nfa.addTransition(0, 0, '0');
  nfa.addTransition(0, 0, '1');
  nfa.addTransition(0, 1, '1');
  nfa.addTransition(1, 2, '0');
  nfa.addTransition(1, 2, '1');

  // set delay
  cout << "Give a delay in ms: ";
  unsigned int delay;
  cin >> delay;
  
  // give NFA chars here
  cout << "Give a string for the NFA to process: ";
  string s;
  cin >> s;

  for (int i = 0; i < s.length(); i++) {
    cout << "After processing " << s.substr(0, i+1) << " NFA is now in state(s) ";
    vector<pair<int, bool>> v = nfa.transition(s[i]);
    for (int i = 0; i < v.size(); i++) {
      cout << v[i].first << " ";
    }
    cout << "which ";
    for (int i = 0; i < v.size(); i++) {
      if (v[i].second) {
	cout << "ACCEPT ";
      } else {
	cout << "REJECT ";
      }
    }
    cout << endl;
    usleep(delay * 1000);
  }

  bool accepted = nfa.end();
  if (accepted) {
    cout << "The NFA ended in an ACCEPT state";
  } else {
    cout << "The NFA ended in a REJECT state";
  }
  cout << " on input " << s << endl;

  return 0;
}
