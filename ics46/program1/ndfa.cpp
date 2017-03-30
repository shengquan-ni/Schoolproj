//Shengquan Ni 46564157
//Yangguang He 50947171
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ics46goody.hpp"
#include "array_queue.hpp"
#include "array_priority_queue.hpp"
#include "array_set.hpp"
#include "array_map.hpp"


typedef ics::ArraySet<std::string>                     States;
typedef ics::ArrayQueue<std::string>                   InputsQueue;
typedef ics::ArrayMap<std::string,States>              InputStatesMap;

typedef ics::ArrayMap<std::string,InputStatesMap>       NDFA;
typedef ics::pair<std::string,InputStatesMap>           NDFAEntry;

bool gt_NDFAEntry (const NDFAEntry& a, const NDFAEntry& b)
{return a.first<b.first;}

typedef ics::ArrayPriorityQueue<NDFAEntry,gt_NDFAEntry> NDFAPQ;

typedef ics::pair<std::string,States>                   Transitions;
typedef ics::ArrayQueue<Transitions>                    TransitionsQueue;


//Read an open file describing the non-deterministic finite automaton (each
//  line starts with a state name followed by pairs of transitions from that
//  state: (input followed by a new state, all separated by semicolons), and
//  return a Map whose keys are states and whose associated values are another
//  Map with each input in that state (keys) and the resulting set of states it
//  can lead to.
const NDFA read_ndfa(std::ifstream &file) {
    NDFA ndfa;
    std::string s;
    while(std::getline(file,s))
    {
        InputStatesMap ism;
        auto temp=ics::split(s,";");
        std::string s2=temp[0];
        temp.erase(temp.begin());
        for(int i=0;i<temp.size();i+=2)
            ism[temp[i]].insert(temp[i+1]);
        ndfa[s2]=ism;
    }
    return ndfa;
}


//Print a label and all the entries in the finite automaton Map, in
//  alphabetical order of the states: each line has a state, the text
//  "transitions:" and the Map of its transitions.
void print_ndfa(const NDFA& ndfa) {
    std::cout<<"The Non-Deterministic Finite Automaton Description"<<std::endl;
    for(auto i:ndfa)
        std::cout<<"  "<<i.first<<" transitions: "<<i.second<<std::endl;
    std::cout<<std::endl;
}


//Return a queue of the calculated transition pairs, based on the non-deterministic
//  finite automaton, initial state, and queue of inputs; each pair in the returned
//  queue is of the form: input, set of new states.
//The first pair contains "" as the input and the initial state.
//If any input i is illegal (does not lead to any state in the non-deterministic finite
//  automaton), ignore it.
TransitionsQueue process(const NDFA& ndfa, std::string state, const InputsQueue& inputs) {
    TransitionsQueue result;
    States reached;
    reached.insert(state);
    result.enqueue(ics::make_pair(std::string(""),reached));
    for(auto i:inputs)
    {
        States next_reached;
        for(auto j:reached)
            if(ndfa.has_key(j) && ndfa[j].has_key(i))
                next_reached.insert_all(ndfa[j][i]);
        reached=next_reached;
        result.enqueue(ics::make_pair(i,reached));
    }
    return result;
}


//Print a TransitionsQueue (the result of calling process) in a nice form.
//Print the Start state on the first line; then print each input and the
//  resulting new states indented on subsequent lines; on the last line, print
//  the Stop state.
void interpret(TransitionsQueue& tq) {  //or TransitionsQueue or TransitionsQueue&&
    std::cout<<"Start state = "<<tq.dequeue().second<<std::endl;
    Transitions i;
    while(tq.size())
    {
        i=tq.dequeue();
        std::cout << "  Input = " << i.first<<"; new possible states = "<<i.second<<std::endl;
    }
    std::cout<<"Stop state = "<<i.second<<"\n"<<std::endl;
}



//Prompt the user for a file, create a finite automaton Map, and print it.
//Prompt the user for a file containing any number of simulation descriptions
//  for the finite automaton to process, one description per line; each
//  description contains a start state followed by its inputs, all separated by
//  semicolons.
//Repeatedly read a description, print that description, put each input in a
//  Queue, process the Queue and print the results in a nice form.
int main() {
  try {
      std::ifstream fs;
      ics::safe_open(fs,"Enter some non-deterministic finite automaton file name","ndfaendin01.txt");
      const NDFA ndfa=read_ndfa(fs);
      print_ndfa(ndfa);
      std::ifstream fs2;
      ics::safe_open(fs2,"Enter some file name with start-state and inputs","ndfainputendin01.txt");
      std::string s;
      while(std::getline(fs2,s))
      {
          auto v=ics::split(s,";");
          std::string state=v[0];
          v.erase(v.begin());
          InputsQueue iq;
          iq.enqueue_all(v);
          auto result=process(ndfa,state,iq);
          interpret(result);
      }
  } catch (ics::IcsError& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
