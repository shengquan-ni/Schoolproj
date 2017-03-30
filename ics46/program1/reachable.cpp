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
//typedef ics::ArraySet<std::string>          NodeSet;
//typedef ics::pair<std::string,NodeSet>      GraphEntry;
//
//bool graph_entry_gt (const GraphEntry& a, const GraphEntry& b)
//{return a.first<b.first;}
//
//typedef ics::ArrayPriorityQueue<GraphEntry,graph_entry_gt> GraphPQ;
//typedef ics::ArrayMap<std::string,NodeSet>  Graph;
//
//
////Read an open file of edges (node names separated by semicolons, with an
////  edge going from the first node name to the second node name) and return a
////  Graph (Map) of each node name associated with the Set of all node names to
////  which there is an edge from the key node name.
//Graph read_graph(std::ifstream &file) {
//	  Graph graph;
//    std::string s;
//    while(std::getline(file,s))
//   {
//        auto t=ics::split(s, ";");
//        graph[t[0]].insert(t[1]);
//    }
//    return graph;
//}
//
//
////Print a label and all the entries in the Graph in alphabetical order
////  (by source node).
////Use a "->" to separate the source node name from the Set of destination
////  node names to which it has an edge.
//void print_graph(const Graph& graph) {
//    std::cout<<"\nGraph: source node -> set[destination nodes]"<<std::endl;
//    GraphPQ gpq;
//    gpq.enqueue_all(graph);
//    for(auto i=gpq.begin();i!=gpq.end();i++)
//        std::cout<<"  "<<(*i).first<<" -> "<<(*i).second<<std::endl;
//    std::cout<<std::endl;
//}
//
//
////Return the Set of node names reaching in the Graph starting at the
////  specified (start) node.
////Use a local Set and a Queue to respectively store the reachable nodes and
////  the nodes that are being explored.
//NodeSet reachable(const Graph& graph, std::string start) {
//    NodeSet result;
//    ics::ArrayQueue<std::string> explore;
//    result.insert(start);
//    explore.enqueue_all(graph[start]);
//    while(explore.size())
//    {
//        auto temp=explore.dequeue();
//        result.insert(temp);
//        if(graph.has_key(temp))
//        {
//            auto extend_nodes=graph[temp];
//            extend_nodes.erase_all(result);
//            explore.enqueue_all(extend_nodes);
//        }
//    }
//    return result;
//}
//
//
//
//
//
////Prompt the user for a file, create a graph from its edges, print the graph,
////  and then repeatedly (until the user enters "quit") prompt the user for a
////  starting node name and then either print an error (if that the node name
////  is not a source node in the graph) or print the Set of node names
////  reachable from it by using the edges in the Graph.
//int main() {
//  try {
//      std::ifstream fs;
//      ics::safe_open(fs,"Enter some graph file name","graph1.txt");
//      auto g=read_graph(fs);
//      print_graph(g);
//      for(;;)
//      {
//          auto s=ics::prompt_string("Enter some starting node name (else quit)");
//          if(s=="quit")break;
//          else if(g.has_key(s))std::cout<<"From "<<s<< " the reachable nodes are "<<reachable(g,s)<<std::endl;
//          else std::cout<<s<<" is not a source node name in the graph"<<std::endl;
//      }
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//
//  return 0;
//}
