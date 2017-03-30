//#include <string>
//#include <iostream>
//#include <fstream>
//#include "array_set.hpp"
//#include "array_map.hpp"
//#include "q1solution.hpp"
//
//
////////////
////
//// Do not edit this file
////
////////////
//
//int main() {
//  try{
//    //Testing swap
//    typedef ics::ArraySet<std::string> string_set;
//
//    std::cout << std::endl << "Testing swap" << std::endl;
//    ics::ArrayMap<std::string,string_set> names_set (
//        {
//         ics::pair<std::string,string_set>("Boy", string_set({"Mary","Betty","Mimsi"})),
//         ics::pair<std::string,string_set>("Girl",string_set({"Peter","Joey","Joe","Carl"}))
//        }
//    );
//    std::cout << "Original Map = " << names_set << std::endl;
//    //Oops, got the names backwards; let's swap values mapped to/from "Boy" and "Girl"
//    swap(names_set, std::string("Boy"), std::string("Girl"));
//    std::cout << "Swapped  Map = " << names_set << std::endl;
//
//
//    //Testing values_set_to_queue
//    typedef ics::ArrayQueue<std::string> string_queue;
//
//    std::cout << std::endl << "Testing values_set_to_queue" << std::endl;
//    std::cout << "Original Map = " << names_set << std::endl;
//    ics::ArrayMap<std::string,string_queue> names_queue;
//    values_set_to_queue(names_set, names_queue);
//    std::cout << "New Map = " << names_queue << std::endl;
//
//
//    //Testing sort_descendants
//    typedef std::string                 name;
//    typedef ics::ArrayQueue<int>        descendants;
//    typedef ics::pair<name,descendants> nd_entry;
//    typedef ics::ArrayQueue<int>        int_queue;
//
//    std::cout << std::endl << "Testing sort_descendants" << std::endl;
//    ics::ArrayMap<name,descendants> family(
//      {
//        nd_entry("David",int_queue({6,4,8})),
//        nd_entry("Muriel",int_queue({3,5})),
//        nd_entry("Barbara",int_queue({5,3})),
//        nd_entry("Chester",int_queue({6,6,6})),
//        nd_entry("Ingrid",int_queue({4,4,4,2,4}))
//      }
//    );
//    std::cout << sort_descendants(family) << std::endl;
//
//
//    family = ics::ArrayMap<name,descendants>(
//      {
//        nd_entry("Allen",int_queue({6,4,8})),
//        nd_entry("Dody",int_queue({3,5})),
//        nd_entry("Emile",int_queue({5,3})),
//        nd_entry("Harold",int_queue({6,6,6})),
//        nd_entry("Louis",int_queue({4,4,4,2,4}))
//      }
//    );
//    std::cout << sort_descendants(family) << std::endl;
//
//
//    //Testing sort_generations
//    std::cout << std::endl << "Testing sort_generations" << std::endl;
//    family = ics::ArrayMap<name,descendants>(
//      {
//      nd_entry("David",int_queue({6,5,8})),
//      nd_entry("Muriel",int_queue({3,5})),
//      nd_entry("Barbara",int_queue({5,3})),
//      nd_entry("Chester",int_queue({6,6,6})),
//      nd_entry("Ingrid",int_queue({4,4,4,2,4}))
//      }
//    );
//    std::cout << sort_generations(family) << std::endl;
//
//    family = ics::ArrayMap<name,descendants>(
//      {
//      nd_entry("Allen",int_queue({12})),
//      nd_entry("Dody",int_queue({15})),
//      nd_entry("Emile",int_queue({8})),
//      nd_entry("Harold",int_queue({6,6,6})),
//      nd_entry("Louis",int_queue({4,4,4,2,4})),
//      nd_entry("Robert",int_queue({6,12}))
//      }
//    );
//    std::cout << sort_generations(family) << std::endl;
//
//
//    //Testing big_family
//    std::cout << std::endl << "Testing big_family" << std::endl;
//    family = ics::ArrayMap<name,descendants>(
//      {
//      nd_entry("David",int_queue({6,5,8})),
//      nd_entry("Muriel",int_queue({3,5})),
//      nd_entry("Barbara",int_queue({5,3})),
//      nd_entry("Chester",int_queue({6,6,6})),
//      nd_entry("Ingrid",int_queue({4,4,4,2,4}))
//      }
//    );
//    std::cout << big_family(family) << std::endl;
//
//    family = ics::ArrayMap<name,descendants>(
//      {
//      nd_entry("Allen",int_queue({12})),
//      nd_entry("Dody",int_queue({15})),
//      nd_entry("Emile",int_queue({8})),
//      nd_entry("Harold",int_queue({6,6,6})),
//      nd_entry("Louis",int_queue({4,4,4,2,4})),
//      nd_entry("Robert",int_queue({6,12}))
//      }
//    );
//    std::cout << big_family(family) << std::endl;
//
//
//    //Testing big_word_map
//    std::cout << std::endl << "Testing big_word_map" << std::endl;
//    std::cout << big_word_map("To be or not to be that is the question") << std::endl;
//    std::cout << big_word_map("When in the course of human events") << std::endl;
//
//
//    //Testing near
//    std::cout << std::endl << "Testing near" << std::endl;
//    std::cout << near("radar",1) << std::endl;
//    std::cout << near("radar",2) << std::endl;
//    std::cout << near("radar",3) << std::endl;
//    std::cout << near("whiplash",1) << std::endl;
//    std::cout << near("whiplash",2) << std::endl;
//    std::cout << near("whiplash",3) << std::endl;
//    std::cout << near("whiplash",4) << std::endl;
//    std::cout << near("whiplash",5) << std::endl;
//    std::cout << near("whiplash",6) << std::endl;
//    std::cout << near("whiplash",7) << std::endl;
//
//
//    //Testing alt_map
//    typedef ics::pair<std::string,std::string> string_pair;
//    typedef ics::pair<string_pair,int>        cc_int;
//    std::cout << std::endl << "Testing alt_map" << std::endl;
//
//    ics::ArrayMap<string_pair,int> calls (
//        {
//           cc_int(string_pair("a","b"),3),
//           cc_int(string_pair("b","c"),2),
//           cc_int(string_pair("a","c"),5)
//        }
//    );
//    std::cout << alt_map(calls) << std::endl;
//
//
//    calls = ics::ArrayMap<string_pair,int>(
//        {
//           cc_int(string_pair("a","b"),3),
//           cc_int(string_pair("b","c"),2),
//           cc_int(string_pair("a","c"),5),
//           cc_int(string_pair("a","d"),2),
//           cc_int(string_pair("d","a"),3),
//           cc_int(string_pair("c","d"),4),
//           cc_int(string_pair("d","b"),5),
//        }
//    );
//    std::cout << alt_map(calls) << std::endl;
//
//} catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;}
//  return 0;
//}
//
//
//
///*
//Here is the output that the driver should produce:
//
//Testing swap
//Original Map = map[Boy->set[Mary,Betty,Mimsi],Girl->set[Peter,Joey,Joe,Carl]]
//Swapped  Map = map[Boy->set[Peter,Joey,Joe,Carl],Girl->set[Mary,Betty,Mimsi]]
//
//Testing values_set_to_queue
//Original Map = map[Boy->set[Peter,Joey,Joe,Carl],Girl->set[Mary,Betty,Mimsi]]
//New Map = map[Boy->queue[Peter,Joey,Joe,Carl]:rear,Girl->queue[Mary,Betty,Mimsi]:rear]
//
//Testing sort_descendants
//queue[Barbara,Muriel,Chester,David,Ingrid]:rear
//queue[Dody,Emile,Allen,Harold,Louis]:rear
//
//Testing sort_generations
//queue[pair[Ingrid,queue[4,4,4,2,4]:rear],pair[David,queue[6,5,8]:rear],pair[Chester,queue[6,6,6]:rear],pair[Barbara,queue[5,3]:rear],pair[Muriel,queue[3,5]:rear]]:rear
//queue[pair[Louis,queue[4,4,4,2,4]:rear],pair[Harold,queue[6,6,6]:rear],pair[Robert,queue[6,12]:rear],pair[Dody,queue[15]:rear],pair[Allen,queue[12]:rear],pair[Emile,queue[8]:rear]]:rear
//
//Testing big_family
//set[David,Chester,Ingrid]
//set[Allen,Dody,Harold,Louis,Robert]
//
//Testing big_word_map
//map[that->set[t,h,a],question->set[q,u,e,s,t,i,o,n]]
//map[When->set[W,h,e,n],course->set[c,o,u,r,s,e],human->set[h,u,m,a,n],events->set[e,v,n,t,s]]
//
//Testing near
//map[r->set[r,a],a->set[r,a,d],d->set[a,d]]
//map[r->set[r,a,d],a->set[r,a,d],d->set[r,a,d]]
//map[r->set[r,a,d],a->set[r,a,d],d->set[r,a,d]]
//map[w->set[w,h],h->set[w,h,i,s],i->set[h,i,p],p->set[i,p,l],l->set[p,l,a],a->set[l,a,s],s->set[a,s,h]]
//map[w->set[w,h,i],h->set[w,h,i,p,a,s],i->set[w,h,i,p,l],p->set[h,i,p,l,a],l->set[i,p,l,a,s],a->set[p,l,a,s,h],s->set[l,a,s,h]]
//map[w->set[w,h,i,p],h->set[w,h,i,p,l,a,s],i->set[w,h,i,p,l,a],p->set[w,h,i,p,l,a,s],l->set[h,i,p,l,a,s],a->set[i,p,l,a,s,h],s->set[p,l,a,s,h]]
//map[w->set[w,h,i,p,l],h->set[w,h,i,p,l,a,s],i->set[w,h,i,p,l,a,s],p->set[w,h,i,p,l,a,s],l->set[w,h,i,p,l,a,s],a->set[h,i,p,l,a,s],s->set[i,p,l,a,s,h]]
//map[w->set[w,h,i,p,l,a],h->set[w,h,i,p,l,a,s],i->set[w,h,i,p,l,a,s],p->set[w,h,i,p,l,a,s],l->set[w,h,i,p,l,a,s],a->set[w,h,i,p,l,a,s],s->set[h,i,p,l,a,s]]
//map[w->set[w,h,i,p,l,a,s],h->set[w,h,i,p,l,a,s],i->set[w,h,i,p,l,a,s],p->set[w,h,i,p,l,a,s],l->set[w,h,i,p,l,a,s],a->set[w,h,i,p,l,a,s],s->set[w,h,i,p,l,a,s]]
//map[w->set[w,h,i,p,l,a,s],h->set[w,h,i,p,l,a,s],i->set[w,h,i,p,l,a,s],p->set[w,h,i,p,l,a,s],l->set[w,h,i,p,l,a,s],a->set[w,h,i,p,l,a,s],s->set[w,h,i,p,l,a,s]]
//
//Testing alt_map
//map[a->map[b->3,c->5],b->map[c->2]]
//map[a->map[b->3,c->5,d->2],b->map[c->2],d->map[a->3,b->5],c->map[d->4]]
//*/