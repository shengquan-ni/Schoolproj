////Shengquan Ni 46564157
////Yangguang He 50947171
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include "ics46goody.hpp"
//#include "array_queue.hpp"
//#include "array_priority_queue.hpp"
//#include "array_set.hpp"
//#include "array_map.hpp"
//
//
//typedef ics::ArrayQueue<std::string>                InputsQueue;
//typedef ics::ArrayMap<std::string,std::string>      InputStateMap;
//
//typedef ics::ArrayMap<std::string,InputStateMap>    FA;
//typedef ics::pair<std::string,InputStateMap>        FAEntry;
//
//bool gt_FAEntry (const FAEntry& a, const FAEntry& b)
//{return a.first<b.first;}
//
//typedef ics::ArrayPriorityQueue<FAEntry,gt_FAEntry> FAPQ;
//
//typedef ics::pair<std::string,std::string>          Transition;
//typedef ics::ArrayQueue<Transition>                 TransitionQueue;
//
//
////Read an open file describing the finite automaton (each line starts with
////  a state name followed by pairs of transitions from that state: (input
////  followed by new state, all separated by semicolons), and return a Map
////  whose keys are states and whose associated values are another Map with
////  each input in that state (keys) and the resulting state it leads to.
//const FA read_fa(std::ifstream &file) {
//    FA f;
//    std::string s;
//    while(std::getline(file,s))
//    {
//        auto t=ics::split(s,";");
//        for(int i=1;i<t.size();i+=2)
//            f[t[0]].put(t[i],t[i+1]);
//    }
//    return f;
//
//}
//
//
////Print a label and all the entries in the finite automaton Map, in
////  alphabetical order of the states: each line has a state, the text
////  "transitions:" and the Map of its transitions.
//void print_fa(const FA& fa) {
//    std::cout<<"\nThe Finite Automaton Description"<<std::endl;
//    for(auto i:fa)
//        std::cout<<"\t"<<i.first<<" transitions: "<<i.second<<std::endl;
//    std::cout<<std::endl;
//}
//
//
////Return a queue of the calculated transition pairs, based on the finite
////  automaton, initial state, and queue of inputs; each pair in the returned
////  queue is of the form: input, new state.
////The first pair contains "" as the input and the initial state.
////If any input i is illegal (does not lead to a state in the finite
////  automaton), then the last pair in the returned queue is i,"None".
//TransitionQueue process(const FA& fa, std::string state, const InputsQueue& inputs) {
//    TransitionQueue result;
//    result.enqueue(ics::make_pair(std::string(""),state));
//    for(auto i:inputs)
//        if (fa[state].has_key(i))
//        {
//            state = fa[state][i];
//            result.enqueue(ics::make_pair(i,state));
//        }
//        else
//        {
//            result.enqueue(ics::make_pair(i,std::string("None")));
//            break;
//        }
//    return result;
//}
//
//
////Print a TransitionQueue (the result of calling the process function above)
//// in a nice form.
////Print the Start state on the first line; then print each input and the
////  resulting new state (or "illegal input: terminated", if the state is
////  "None") indented on subsequent lines; on the last line, print the Stop
////  state (which may be "None").
//void interpret(TransitionQueue& tq) {  //or TransitionQueue or TransitionQueue&&
//    std::cout<<"Start state = "<<tq.dequeue().second<<std::endl;
//    Transition i;
//    while(tq.size())
//    {
//        i=tq.dequeue();
//        std::cout << "  Input = " << i.first<<"; ";
//        if(i.second!="None")
//            std::cout << "new state = " << i.second << std::endl;
//        else
//            std::cout << "illegal input: simulation terminated" << std::endl;
//    }
//    std::cout<<"Stop state = "<<i.second<<"\n"<<std::endl;
//
//}
//
//
//
////Prompt the user for a file, create a finite automaton Map, and print it.
////Prompt the user for a file containing any number of simulation descriptions
////  for the finite automaton to process, one description per line; each
////  description contains a start state followed by its inputs, all separated by
////  semicolons.
////Repeatedly read a description, print that description, put each input in a
////  Queue, process the Queue and print the results in a nice form.
//int main() {
//  try {
//      std::ifstream fs;
//      ics::safe_open(fs,"Enter some finite automaton file name","faparity.txt");
//      auto f=read_fa(fs);
//      print_fa(f);
//      std::ifstream fs2;
//      ics::safe_open(fs2,"Enter some file name with start-state and inputs","fainputparity.txt");
//      std::string s;
//      while(std::getline(fs2,s))
//      {
//          std::cout<<"Starting up a new simulation with description: "<<s<<std::endl;
//          auto v=ics::split(s,";");
//          std::string state=v[0];
//          v.erase(v.begin());
//          InputsQueue iq;
//          iq.enqueue_all(v);
//          auto result=process(f,state,iq);
//          interpret(result);
//      }
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//
//  return 0;
//}
