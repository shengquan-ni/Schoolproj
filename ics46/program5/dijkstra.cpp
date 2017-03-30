#include <string>
#include <iostream>
#include <fstream>
#include "ics46goody.hpp"
#include "array_queue.hpp"
#include "array_graph.hpp"
#include "dijkstra.hpp"



std::string get_node_in_graph(const ics::DistGraph& g, std::string prompt, bool allow_QUIT) {
  std::string node;
  for(;;) {
    node = ics::prompt_string(prompt + " (must be in graph" + (allow_QUIT ? " or QUIT" : "") + ")");
    if ( (allow_QUIT && node == "QUIT") || g.has_node(node) )
      break;
  }
  return node;
}


int main() {
  try {
	  ics::DistGraph g;
	  std::ifstream fs;
      ics::safe_open(fs,"Enter graph file name","flightcost.txt");
	  g.load(fs,";");
	  std::cout<<g;
	  std::string s=get_node_in_graph(g,"Enter start node",false);
	  auto cm=ics::extended_dijkstra(g,s);
	  std::cout<<cm<<std::endl;
	  while((s=get_node_in_graph(g,"Enter start node",true))!="QUIT")
		  std::cout<<"Cost is "<<cm[s].cost<<"; path is "<<ics::recover_path(cm,s)<<std::endl;
  } catch (ics::IcsError& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
