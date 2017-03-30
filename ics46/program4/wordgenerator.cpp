//// Submitter: Shengqun(Ni, Shengquan)
//// Partner  : changchs(Shen, Changchuan)
//// We certify that we worked cooperatively on this programming
////   assignment, according to the rules for pair programming
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include <limits>                           //I used std::numeric_limits<int>::max()
//#include "ics46goody.hpp"
//#include "stopwatch.hpp"
//#include "array_queue.hpp"
//#include "array_priority_queue.hpp"
//#include "array_set.hpp"
//#include "array_map.hpp"
//#include "heap_priority_queue.hpp"
//#include "hash_map.hpp"
//#include "hash_set.hpp"
//
//
//typedef ics::ArrayQueue<std::string>         WordQueue;
//int str_hash(const std::string& s)
//{
//    std::hash<std::string> hashfunc;
//    return hashfunc(s);
//}
//typedef ics::HashSet<std::string,str_hash>           FollowSet;
//typedef ics::pair<WordQueue,FollowSet>       CorpusEntry;
//
//
//
//int queue_hash(const WordQueue& a) {
//    std::hash<std::string> s;
//    return s(a.str());
//}
//
//bool queue_lt(const WordQueue& a, const WordQueue& b) {
//    for (WordQueue::Iterator ac = a.begin(), bc= b.begin(); ac != a.end(); ++ac,++bc)
//        if      (*ac < *bc) return true;
//        else if (*ac > *bc) return false;
//    return false;
//}
//
//bool CorpusEntry_gt(const CorpusEntry& a, const CorpusEntry& b) {
//    return queue_lt(a.first,b.first); // reverse of lt for queues
//}
//typedef ics::HeapPriorityQueue<CorpusEntry,CorpusEntry_gt> CorpusPQ;
//typedef ics::HashMap<WordQueue,FollowSet,queue_hash>   Corpus;
//
//
//ics::Stopwatch s_read; //started/stopped in main
//ics::Stopwatch s_sort; //started/stopped in print_corpus
//
//
////One queue is lexically greater than another, if its first value is smaller; or if
////  its first value is the same and its second value is smaller; or if its first
////  and second values are the same and its third value is smaller...
////If any of its values is greater than the corresponding value in the other queue,
////  the first queue is not greater.
////Note that the queues sizes are the same: each stores Order-Statistic words
////Important: Use iterators for examining the queue values: DO NOT CALL DEQUEUE.
//
//
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
//  Corpus corpus;
//  WordQueue word_queue;
//  std::string line;
//  while (getline(file,line)) {
//    std::vector<std::string> line_sp = ics::split(line," ");
//    for (const std::string& word : line_sp) {
//      if (word_queue.size() == os) {
//        corpus[word_queue].insert(word);
//        word_queue.dequeue();
//      }
//      word_queue.enqueue(word);
//    }
//  }
//  file.close();
//
//  return corpus;
//}
//
//
////Print "Corpus" and all entries in the Corpus, in lexical alphabetical order
////  (with the minimum and maximum set sizes at the end).
////Use a "can be followed by any of" to separate the key word from the Set of words
////  that can follow it.
//
//void print_corpus(const Corpus& corpus) {
//  std::cout << "\nCorpus of " << corpus.size() << " entries" << std::endl;
//  CorpusPQ words_sorted(corpus, CorpusEntry_gt);
//  s_sort.stop();
//  int min = std::numeric_limits<int>::max(), max = 0;
//  for (const CorpusEntry& kv : words_sorted) {
//    std::cout << "  " << kv.first << " can be followed by any of " << kv.second << std::endl;
//    if (kv.second.size() < min) min = kv.second.size();
//    if (kv.second.size() > max) max = kv.second.size();
//  }
//  std::cout << "Corpus of " << corpus.size() << " entries" << std::endl;
//  std::cout << "min/max = " << min << "/" << max << std::endl;
//}
//
//
////Return a Queue of words, starting with those in start and including count more
////  randomly selected words using corpus to decide which word comes next.
////If there is no word that follows the previous ones, put "None" into the queue
////  and return immediately this list (whose size is <= start.size() + count).
//WordQueue produce_text(const Corpus& corpus, const WordQueue& start, int count) {
//  WordQueue result (start), keys(start);
//  for (int i=0; i<count; ++i) {
//    if (!corpus.has_key(keys)) {
//      result.enqueue("None");
//      return result;
//    }
//    std::string r = random_in_set(corpus[keys]);
//    result.enqueue(r);
//    keys.dequeue();
//    keys.enqueue(r);
//  }
//
//  return result;
//}
//
//
//
////Prompt the user for (a) the order statistic and (b) the file storing the text.
////Read the text as a Corpus and print it appropriately.
////Prompt the user for order statistic words from the text.
////Prompt the user for number of random words to generate
////Call the functions above to solve the problem, and print the appropriate information
//int main() {
//  try {
//    int os  = ics::prompt_int("Enter order statistic",2);
//    std::ifstream corpus_file;
//    ics::safe_open(corpus_file,"Enter file name to process","wghuck.txt");
//
//    s_read.start();
//    Corpus corpus = read_corpus(os,corpus_file);
//    s_read.stop();
//    std::cout << "read_corpus time = " << s_read.read() << std::endl;
//    s_sort.start();
//    print_corpus(corpus);
//    std::cout << "read_corpus time                   = " << s_read.read() << std::endl;
//    std::cout << "print_corpus (sort not print) time = " << s_sort.read() << std::endl;
//
//    std::cout << "\nEnter " << os << " words to start with" << std::endl;
//    WordQueue start;
//    for (int i=1; i<=os; ++i) {
//      std::ostringstream prompt;
//      prompt << "Enter word " << i;
//      start.enqueue(ics::prompt_string(prompt.str()));
//    }
//    int how_many  = ics::prompt_int ("Enter # of words to generate");
//    std::cout << "Random text = " << produce_text(corpus,start,how_many);
//
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//
//  return 0;
//}
//
//
//
////Fill in the running times (printed by the program)
////for each of the following implementation choices
//
////Array Implementations for Queue and Set; HeapPriorityQueue and HashMap
////  read_corpus time                   = 1.39
////  print_corpus (sort not print) time = 0.313
//
////Array Implementations for Queue; HeapPriorityQueue, HashMap, and HashSet
////  read_corpus time                   = 1.5
////  print_corpus (sort not print) time = 0.406
//
////Briefly explain (in a comment below) what is interesting
////about the times above (and explain why it occurs).
//// After we used HashSet, the time increased. This is because the most of the entries only contain 1 word, the constants of HashSet's operations are bigger than ArraySet's.
