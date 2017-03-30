//// Submitter: yangguah(Yangguang, He)
//// Partner  : shengqun(Shengquan, Ni)
//// We certify that we worked cooperatively on this programming
////   assignment, according to the rules for pair programming
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include <limits>                           //I used std::numeric_limits<int>::max()
//#include "ics46goody.hpp"
//#include "array_queue.hpp"
//#include "array_priority_queue.hpp"
//#include "array_set.hpp"
//#include "array_map.hpp"
//
//
//typedef ics::ArrayQueue<std::string>         WordQueue;
//typedef ics::ArraySet<std::string>           FollowSet;
//typedef ics::pair<WordQueue,FollowSet>       CorpusEntry;
//typedef ics::ArrayPriorityQueue<CorpusEntry> CorpusPQ;     //Convenient to supply gt at construction
//typedef ics::ArrayMap<WordQueue,FollowSet>   Corpus;
//
//
////Return a random word in the words set (use in produce_text)
//std::string random_in_set(const FollowSet& words) {
//  int index = ics::rand_range(1, words.size());
//  int i = 0;
//  for (const std::string& s : words)
//    if (++i == index)
//      return s;
//  return "?";
//}
//
//
////Read an open file of lines of words (separated by spaces) and return a
////  Corpus (Map) of each sequence (Queue) of os (Order-Statistic) words
////  associated with the Set of all words that follow them somewhere in the
////  file.
//Corpus read_corpus(int os, std::ifstream &file) {
//    Corpus result;
//    std::string s((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
//    for(;;)
//    {
//        unsigned long pos=s.find('\n');
//        if (pos!=std::string::npos)
//            s.replace(pos,1," ");
//        else
//            break;
//    }
//    auto v=ics::split(s," ");
//    for(int i=0;i<v.size()-os;++i)
//    {
//        WordQueue wq;
//        for(int j=0;j<os;++j)
//            wq.enqueue(v[i+j]);
//        result[wq].insert(v[i+os]);
//    }
//    return result;
//}
//
//
////Print "Corpus" and all entries in the Corpus, in lexical alphabetical order
////  (with the minimum and maximum set sizes at the end).
////Use a "can be followed by any of" to separate the key word from the Set of words
////  that can follow it.
//
////One queue is lexically greater than another, if its first value is smaller; or if
////  its first value is the same and its second value is smaller; or if its first
////  and second values are the same and its third value is smaller...
////If any of its values is greater than the corresponding value in the other queue,
////  the first queue is not greater.
////Note that the queues sizes are the same: each stores Order-Statistic words
////Important: Use iterators for examining the queue values: DO NOT CALL DEQUEUE.
//
//bool queue_gt(const CorpusEntry& a, const CorpusEntry& b) {
//    auto i1=a.first.begin();
//    auto i2=b.first.begin();
//    while(i1!=a.first.end())
//    {
//        if(*i1!=*i2)
//            return *i1<*i2;
//        else
//        {
//            i1++;
//            i2++;
//        }
//    }
//    return true;
//}
//
//void print_corpus(const Corpus& corpus) {
//    std::cout<<"\nCorpus had "<<corpus.size()<<" Entries"<<std::endl;
//    int max=0,min=std::numeric_limits<int>::max();
//    CorpusPQ cpq(corpus,queue_gt);
//    for(auto i:cpq)
//    {
//        if(i.second.size()>max)max=i.second.size();
//        if(i.second.size()<min)min=i.second.size();
//        std::cout<<"  "<<i.first<<" -> "<<i.second<<std::endl;
//    }
//    std::cout<<"Corpus had "<<corpus.size()<<" Entries"<<std::endl;
//    std::cout<<"max/min = "<<max<<"/"<<min<<"\n"<<std::endl;
//}
//
//
////Return a Queue of words, starting with those in start and including count more
////  randomly selected words using corpus to decide which word comes next.
////If there is no word that follows the previous ones, put "None" into the queue
////  and return immediately this list (whose size is <= start.size() + count).
//WordQueue produce_text(const Corpus& corpus, const WordQueue& start, int count) {
//    WordQueue wq(start),result(start);
//    int now=0;
//    while(corpus.has_key(wq))
//    {
//        auto s=random_in_set(corpus[wq]);
//        wq.dequeue();
//        wq.enqueue(s);
//        result.enqueue(s);
//        now++;
//        if(now==count)
//            return result;
//    }
//    result.enqueue("None");
//    return result;
//}
//
//
//
////Prompt the user for (a) the order statistic and (b) the file storing the text.
////Read the text as a Corpus and print it appropriately.
////Prompt the user for order statistic words from the text.
////Prompt the user for number of random words to generate
////Call the above functions to solve the problem, and print the appropriate information
//int main() {
//  try {
//      int os=ics::prompt_int("Enter some order statistic",2);
//      std::ifstream fs;
//      ics::safe_open(fs,"Enter some file name to process","wginput1.txt");
//      auto c=read_corpus(os,fs);
//      print_corpus(c);
//      std::cout<<"Enter "<<os<<" words for starting"<<std::endl;
//      WordQueue wq;
//      for(int i=1;i<=os;++i)
//      {
//          std::stringstream ss;
//          ss<<"Enter word "<<i;
//          auto s=ics::prompt_string(ss.str());
//          wq.enqueue(s);
//      }
//      int count=ics::prompt_int("Enter # of words to generate");
//      std::cout<<"Random text = "<<produce_text(c,wq,count)<<std::endl;
//
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//
//  return 0;
//}
