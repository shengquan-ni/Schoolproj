////Shengquan Ni 46564157
////Yangguang He 50947171
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include <limits>                    //Biggest int: std::numeric_limits<int>::max()
//#include "ics46goody.hpp"
//#include "array_queue.hpp"
//#include "array_priority_queue.hpp"
//#include "array_set.hpp"
//#include "array_map.hpp"
//
//
//typedef ics::ArrayQueue<std::string>              CandidateQueue;
//typedef ics::ArraySet<std::string>                CandidateSet;
//typedef ics::ArrayMap<std::string,int>            CandidateTally;
//
//typedef ics::ArrayMap<std::string,CandidateQueue> Preferences;
//typedef ics::pair<std::string,CandidateQueue>     PreferencesEntry;
//typedef ics::ArrayPriorityQueue<PreferencesEntry> PreferencesEntryPQ; //Must supply gt at construction
//
//typedef ics::pair<std::string,int>                TallyEntry;
//typedef ics::ArrayPriorityQueue<TallyEntry>       TallyEntryPQ;
//
//
//
////Read an open file stating voter preferences (each line is (a) a voter
////  followed by (b) all the candidates the voter would vote for, in
////  preference order (from most to least preferred candidate, separated
////  by semicolons), and return a Map of preferences: a Map whose keys are
////  voter names and whose values are a queue of candidate preferences.
//Preferences read_voter_preferences(std::ifstream &file) {
//    Preferences p;
//    std::string s;
//    while(std::getline(file,s))
//    {
//        auto i=ics::split(s,";");
//        auto k=i[0];
//        i.erase(i.begin());
//        p[k].enqueue_all(i);
//    }
//    return p;
//}
//
//
////Print a label and all the entries in the preferences Map, in alphabetical
////  order according to the voter.
////Use a "->" to separate the voter name from the Queue of candidates.
//void print_voter_preferences(const Preferences& preferences) {
//    std::cout<<"\nVoter name -> queue[Preferences]"<<std::endl;
//    PreferencesEntryPQ ppq(preferences,[](const PreferencesEntry &a,const PreferencesEntry &b){return a.first<b.first;});
//    for(auto i:ppq)
//        std::cout<<" "<<i.first<<" -> "<<i.second<<std::endl;
//    std::cout<<std::endl;
//
//}
//
//
////Print the message followed by all the entries in the CandidateTally, in
////  the order specified by has_higher_priority: i is printed before j, if
////  has_higher_priority(i,j) returns true: sometimes alphabetically by candidate,
////  other times by decreasing votes for the candidate.
////Use a "->" to separate the candidat name from the number of votes they
////  received.
//void print_tally(std::string message, const CandidateTally& tally, bool (*has_higher_priority)(const TallyEntry& i,const TallyEntry& j)) {
//    std::cout<<message<<std::endl;
//    TallyEntryPQ tpq(has_higher_priority);
//    tpq.enqueue_all(tally);
//    for(auto i:tpq)
//    {
//        std::cout<<" "<<i.first<<" -> "<<i.second<<std::endl;
//    }
//    std::cout<<std::endl;
//}
//
//
////Return the CandidateTally: a Map of candidates (as keys) and the number of
////  votes they received, based on the unchanging Preferences (read from the
////  file) and the candidates who are currently still in the election (which changes).
////Every possible candidate should appear as a key in the resulting tally.
////Each voter should tally one vote: for their highest-ranked candidate who is
////  still in the the election.
//CandidateTally evaluate_ballot(const Preferences& preferences, const CandidateSet& candidates) {
//    CandidateTally ct;
//    for(auto i:preferences)
//        for(auto j:i.second)
//            if(candidates.contains(j))
//            {
//                ct[j]++;
//                break;
//            }
//    return ct;
//}
//
//
////Return the Set of candidates who are still in the election, based on the
////  tally of votes: compute the minimum number of votes and return a Set of
////  all candidates receiving more than that minimum; if all candidates
////  receive the same number of votes (that would be the minimum), the empty
////  Set is returned.
//CandidateSet remaining_candidates(const CandidateTally& tally) {
//    TallyEntryPQ tpq(tally,[](const TallyEntry& i,const TallyEntry& j){return i.second<j.second;});
//    int m=(*tpq.begin()).second;
//    CandidateSet cs;
//    for(auto i:tpq) {
//        if(i.second!=m)
//        cs.insert(i.first);
//    }
//    return cs;
//}
//
//
////Prompt the user for a file, create a voter preference Map, and print it.
////Determine the Set of all the candidates in the election, from this Map.
////Repeatedly evaluate the ballot based on the candidates (still) in the
////  election, printing the vote count (tally) two ways: with the candidates
////  (a) shown alphabetically increasing and (b) shown with the vote count
////  decreasing (candidates with equal vote counts are shown alphabetically
////  increasing); from this tally, compute which candidates remain in the
////  election: all candidates receiving more than the minimum number of votes;
////  continue this process until there are less than 2 candidates.
////Print the final result: there may 1 candidate left (the winner) or 0 left
////   (no winner).
//int main() {
//  try {
//      std::ifstream fs;
//      ics::safe_open(fs,"Enter some voter preferences file name","votepref1.txt");
//      auto p=read_voter_preferences(fs);
//      print_voter_preferences(p);
//      int count=0;
//      CandidateSet c;
//      c.insert_all((*p.begin()).second);
//      while(c.size()>1)
//      {
//          auto temp=evaluate_ballot(p,c);
//          count++;
//          std::stringstream ss;
//          ss<<"Vote count on ballot #"<<count<<": candidates (alphabetically ordered) with remaining candidates = ";
//          ss<<c;
//          std::string msg=ss.str();
//          print_tally(msg,temp,[](const TallyEntry& i,const TallyEntry& j){return i.first<j.first;});
//          msg.replace(msg.find("alphabetically"),14,"numerically");
//          print_tally(msg,temp,[](const TallyEntry& i,const TallyEntry& j){return i.second<j.second;});
//          c=remaining_candidates(temp);
//      }
//      if(c.size()==1)
//          std::cout<<"Winner is "<<(*c.begin())<<std::endl;
//      else
//          std::cout<<"Not any unique winner: election is a tie among all the candidates remaining on the last ballot"<<std::endl;
//
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//  return 0;
//}
