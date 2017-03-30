#include <iostream>
#include <sstream>
#include "ics46goody.hpp"
#include "gtest/gtest.h"
#include "array_set.hpp"
#include "array_map.hpp"
#include "q1solution.hpp"

class Quiz1 : public ::testing::Test {
protected:
    virtual void SetUp()    {}
    virtual void TearDown() {}
};


TEST_F(Quiz1, swap) {
  typedef ics::ArraySet<std::string> string_set;
  ics::ArrayMap<std::string,string_set> names_set (
      {
       ics::pair<std::string,string_set>("Boy", string_set({"Mary","Betty","Mimsi"})),
       ics::pair<std::string,string_set>("Girl",string_set({"Peter","Joey","Joe","Carl"}))
      }
  );

  swap(names_set, std::string("Boy"), std::string("Girl"));

  ASSERT_EQ(string_set({"Peter","Joey","Joe","Carl"}), names_set["Boy"]);
  ASSERT_EQ(string_set({"Mary","Betty","Mimsi"}),      names_set["Girl"]);
}


TEST_F(Quiz1, values_set_to_queue) {
  typedef ics::ArrayQueue<std::string> string_queue;
  typedef ics::ArraySet<std::string>   string_set;
  ics::ArrayMap<std::string,string_set> names_set (
      {
       ics::pair<std::string,string_set>("Girl", string_set({"Mary","Betty","Mimsi"})),
       ics::pair<std::string,string_set>("Boy",  string_set({"Peter","Joey","Joe","Carl"}))
      }
  );

  ics::ArrayMap<std::string,string_queue> names_queue;
  values_set_to_queue(names_set, names_queue);
  ASSERT_EQ(string_set({"Peter","Joey","Joe","Carl"}), string_set(names_queue["Boy"]));
  ASSERT_EQ(string_set({"Mary","Betty","Mimsi"}),      string_set(names_set["Girl"]));

}


TEST_F(Quiz1, sort_descending) {
  typedef std::string                 name;
  typedef ics::ArrayQueue<int>        descendants;
  typedef ics::pair<name,descendants> nd_entry;
  typedef ics::ArrayQueue<int>        int_queue;

  ics::ArrayMap<name,descendants> family(
    {
      nd_entry("David",int_queue({6,4,8})),
      nd_entry("Muriel",int_queue({3,5})),
      nd_entry("Barbara",int_queue({5,3})),
      nd_entry("Chester",int_queue({6,6,6})),
      nd_entry("Ingrid",int_queue({4,4,4,2,4}))
    }
  );
  ASSERT_EQ(ics::ArrayQueue<std::string>({"Barbara","Muriel","Chester","David","Ingrid"}), sort_descendants(family));


  family = ics::ArrayMap<name,descendants>(
    {
      nd_entry("Allen",int_queue({6,4,8})),
      nd_entry("Dody",int_queue({3,5})),
      nd_entry("Emile",int_queue({5,3})),
      nd_entry("Harold",int_queue({6,6,6})),
      nd_entry("Louis",int_queue({4,4,4,2,4}))
    }
  );
  ASSERT_EQ(ics::ArrayQueue<std::string>({"Dody","Emile","Allen","Harold","Louis"}), sort_descendants(family));
}


TEST_F(Quiz1, sort_generations) {
  typedef std::string                 name;
  typedef ics::ArrayQueue<int>        descendants;
  typedef ics::pair<name,descendants> nd_entry;
  typedef ics::ArrayQueue<int>        int_queue;

  ics::ArrayMap<name,descendants> family(
    {
      nd_entry("David",int_queue({6,5,8})),
      nd_entry("Muriel",int_queue({3,5})),
      nd_entry("Barbara",int_queue({5,3})),
      nd_entry("Chester",int_queue({6,6,6})),
      nd_entry("Ingrid",int_queue({4,4,4,2,4}))
    }
  );

  ics::ArrayQueue<nd_entry> answer(
    {
      nd_entry("Ingrid",int_queue({4,4,4,2,4})),
      nd_entry("David",int_queue({6,5,8})),
      nd_entry("Chester",int_queue({6,6,6})),
      nd_entry("Barbara",int_queue({5,3})),
      nd_entry("Muriel",int_queue({3,5}))
    }
  );
  ASSERT_EQ(answer,sort_generations(family));


  family = ics::ArrayMap<name,descendants>(
    {
      nd_entry("Allen",int_queue({12})),
      nd_entry("Dody",int_queue({15})),
      nd_entry("Emile",int_queue({8})),
      nd_entry("Harold",int_queue({6,6,6})),
      nd_entry("Louis",int_queue({4,4,4,2,4})),
      nd_entry("Robert",int_queue({6,12}))
    }
  );

  answer = ics::ArrayQueue<nd_entry>(
    {
      nd_entry("Louis",int_queue({4,4,4,2,4})),
      nd_entry("Harold",int_queue({6,6,6})),
      nd_entry("Robert",int_queue({6,12})),
      nd_entry("Dody",int_queue({15})),
      nd_entry("Allen",int_queue({12})),
      nd_entry("Emile",int_queue({8}))
    }
  );
  ASSERT_EQ(answer,sort_generations(family));
}


TEST_F(Quiz1, big_family) {
  typedef std::string                 name;
  typedef ics::ArrayQueue<int>        descendants;
  typedef ics::pair<name,descendants> nd_entry;
  typedef ics::ArrayQueue<int>        int_queue;

  ics::ArrayMap<name,descendants> family(
    {
    nd_entry("David",int_queue({6,5,8})),
    nd_entry("Muriel",int_queue({3,5})),
    nd_entry("Barbara",int_queue({5,3})),
    nd_entry("Chester",int_queue({6,6,6})),
    nd_entry("Ingrid",int_queue({4,4,4,2,4}))
    }
  );
  ASSERT_EQ(ics::ArraySet<std::string>({"David","Chester","Ingrid"}),big_family(family));

  family = ics::ArrayMap<name,descendants>(
    {
    nd_entry("Allen",int_queue({12})),
    nd_entry("Dody",int_queue({15})),
    nd_entry("Emile",int_queue({8})),
    nd_entry("Harold",int_queue({6,6,6})),
    nd_entry("Louis",int_queue({4,4,4,2,4})),
    nd_entry("Robert",int_queue({6,12}))
    }
  );
  ASSERT_EQ(ics::ArraySet<std::string>({"Allen","Dody","Harold","Louis","Robert"}),big_family(family));
}


TEST_F(Quiz1, big_word_map) {
  typedef ics::ArraySet<char>                 char_set;
  typedef ics::ArrayMap<std::string,char_set> map;
  typedef ics::pair<std::string,char_set>     entry;

  ASSERT_EQ(map({
                  entry({"that",    char_set({'t','h','a','t'})}),
                  entry({"question",char_set({'q','u','e','s','t','i','o','n'})})
                 }
                ), big_word_map("To be or not to be that is the question"));

  ASSERT_EQ(map({
                  entry({"When",   char_set({'W','h','e','n'})}),
                  entry({"course", char_set({'c','o','u','r','s','e'})}),
                  entry({"human",  char_set({'h','u','m','a','n'})}),
                  entry({"events", char_set({'e','v','n','t','s'})})
                 }
                ), big_word_map("When in the course of human events"));
}


TEST_F(Quiz1, near) {
  typedef ics::ArraySet<char>             char_set;
  typedef ics::ArrayMap<char,char_set>    map;
  typedef ics::pair<char,char_set> entry;


  ASSERT_EQ(map({
                   entry({'r', char_set({'r',})}),
                   entry({'a', char_set({'a'})}),
                   entry({'d', char_set({'d'})})
                 }
                ), near("radar",0));

  ASSERT_EQ(map({
                   entry({'r', char_set({'r','a'})}),
                   entry({'a', char_set({'r','a','d'})}),
                   entry({'d', char_set({'a','d'})})
                 }
                ), near("radar",1));

  ASSERT_EQ(map({
                   entry({'r', char_set({'r','a','d'})}),
                   entry({'a', char_set({'r','a','d'})}),
                   entry({'d', char_set({'r','a','d'})})
                 }
                ), near("radar",2));

  ASSERT_EQ(map({
                   entry({'r', char_set({'r','a','d'})}),
                   entry({'a', char_set({'r','a','d'})}),
                   entry({'d', char_set({'r','a','d'})})
                 }
                ), near("radar",3));


  ASSERT_EQ(map({
                   entry({'w', char_set({'w','h'})}),
                   entry({'h', char_set({'w','h','i','s'})}),
                   entry({'i', char_set({'h','i','p'})}),
                   entry({'p', char_set({'i','p','l'})}),
                   entry({'l', char_set({'p','l','a'})}),
                   entry({'a', char_set({'l','a','s'})}),
                   entry({'s', char_set({'a','s','h'})})
                 }
                ), near("whiplash",1));


  ASSERT_EQ(map({
                   entry({'w', char_set({'w','h','i'})}),
                   entry({'h', char_set({'w','h','i','p','a','s'})}),
                   entry({'i', char_set({'w','h','i','p','l'})}),
                   entry({'p', char_set({'h','i','p','l','a'})}),
                   entry({'l', char_set({'i','p','l','a','s'})}),
                   entry({'a', char_set({'p','l','a','s','h'})}),
                   entry({'s', char_set({'l','a','s','h'})})
                 }
                ), near("whiplash",2));

  ASSERT_EQ(map({
                   entry({'w', char_set({'w','h','i','p'})}),
                   entry({'h', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'i', char_set({'w','h','i','p','l','a'})}),
                   entry({'p', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'l', char_set({'h','i','p','l','a','s'})}),
                   entry({'a', char_set({'i','p','l','a','s','h'})}),
                   entry({'s', char_set({'p','l','a','s','h'})})
                 }
                ), near("whiplash",3));

  ASSERT_EQ(map({
                   entry({'w', char_set({'w','h','i','p','l'})}),
                   entry({'h', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'i', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'p', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'l', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'a', char_set({'h','i','p','l','a','s'})}),
                   entry({'s', char_set({'i','p','l','a','s','h'})})
                 }
                ), near("whiplash",4));

  ASSERT_EQ(map({
                   entry({'w', char_set({'w','h','i','p','l','a'})}),
                   entry({'h', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'i', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'p', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'l', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'a', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'s', char_set({'h','i','p','l','a','s'})})
                 }
                ), near("whiplash",5));

  ASSERT_EQ(map({
                   entry({'w', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'h', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'i', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'p', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'l', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'a', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'s', char_set({'w','h','i','p','l','a','s'})})
                 }
                ), near("whiplash",6));

  ASSERT_EQ(map({
                   entry({'w', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'h', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'i', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'p', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'l', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'a', char_set({'w','h','i','p','l','a','s'})}),
                   entry({'s', char_set({'w','h','i','p','l','a','s'})})
                 }
                ), near("whiplash",7));

}


TEST_F(Quiz1, alt_map) {
  typedef ics::pair<std::string,std::string> string_pair;
  typedef ics::pair<string_pair,int>         cc_int;

  typedef ics::pair<std::string,int>         c_int;
  typedef ics::pair<std::string,ics::ArrayMap<std::string,int>>       c_c_int;

  ics::ArrayMap<string_pair,int> calls (
      {
         cc_int(string_pair("a","b"),3),
         cc_int(string_pair("b","c"),2),
         cc_int(string_pair("a","c"),5)
      }
  );

  ics::ArrayMap<std::string,ics::ArrayMap<std::string,int>> answer (
      {
         c_c_int("a",ics::ArrayMap<std::string,int>({c_int("b",3),c_int("c",5)})),
         c_c_int("b",ics::ArrayMap<std::string,int>({c_int("c",2)}))
      }
  );
  ASSERT_EQ(answer,alt_map(calls));


  calls = ics::ArrayMap<string_pair,int>(
      {
         cc_int(string_pair("a","b"),3),
         cc_int(string_pair("b","c"),2),
         cc_int(string_pair("a","c"),5),
         cc_int(string_pair("a","d"),2),
         cc_int(string_pair("d","a"),3),
         cc_int(string_pair("c","d"),4),
         cc_int(string_pair("d","b"),5)
      }
  );

   answer = ics::ArrayMap<std::string,ics::ArrayMap<std::string,int>> (
      {
         c_c_int("a",ics::ArrayMap<std::string,int>({c_int("b",3),c_int("c",5),c_int("d",2)})),
         c_c_int("b",ics::ArrayMap<std::string,int>({c_int("c",2)})),
         c_c_int("c",ics::ArrayMap<std::string,int>({c_int("d",4)})),
         c_c_int("d",ics::ArrayMap<std::string,int>({c_int("a",3),c_int("b",5)}))
      }
  );
  ASSERT_EQ(answer,alt_map(calls));
}


//map[a->map[b->3,c->5,d->2],b->map[c->2],d->map[a->3,b->5],c->map[d->4]]

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
