#ifndef ARRAY_GRAPH_HPP_
#define ARRAY_GRAPH_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"
#include "pair.hpp"
#include "heap_priority_queue.hpp"
#include "array_set.hpp"
#include "array_map.hpp"


namespace ics {


template<class T>
class ArrayGraph {
  //Forward declaration: used in templated typedefs below
  private:
    class LocalInfo;

  public:
    //Typedefs
    typedef std::string                         NodeName;
    typedef ics::pair<NodeName, NodeName>       Edge;
    typedef ics::pair<NodeName, LocalInfo>      NodeLocalEntry;
    typedef ics::ArrayMap<NodeName, LocalInfo>  NodeMap;
    typedef ics::ArrayMap<Edge, T>              EdgeMap;
    typedef ics::pair<NodeName, LocalInfo>      NodeMapEntry;
    typedef ics::pair<Edge, T>                  EdgeMapEntry;
    typedef ics::ArraySet<NodeName>             NodeSet;
    typedef ics::ArraySet<Edge>                 EdgeSet;

    static bool LocalInfo_gt(const NodeLocalEntry& a, const NodeLocalEntry& b)
    {return a.first < b.first;}


    //Destructor/Constructors
    ~ArrayGraph();
    ArrayGraph();
    ArrayGraph(const ArrayGraph<T>& g);

    //Queries
    bool empty      ()                                     const;
    int  node_count ()                                     const;
    int  edge_count ()                                     const;
    bool has_node  (std::string node_name)                 const;
    bool has_edge  (NodeName origin, NodeName destination) const;
    T    edge_value(NodeName origin, NodeName destination) const;
    int  in_degree (NodeName node_name)                    const;
    int  out_degree(NodeName node_name)                    const;
    int  degree    (NodeName node_name)                    const;

    const NodeMap& all_nodes()                   const;
    const EdgeMap& all_edges()                   const;
    const NodeSet& out_nodes(NodeName node_name) const;
    const NodeSet& in_nodes (NodeName node_name) const;
    const EdgeSet& out_edges(NodeName node_name) const;
    const EdgeSet& in_edges (NodeName node_name) const;

    //Commands
    void add_node   (NodeName node_name);
    void add_edge   (NodeName origin, NodeName destination, T value);
    void remove_node(NodeName node_name);
    void remove_edge(NodeName origin, NodeName destination);
    void clear      ();
    void load       (std::ifstream& in_file,  std::string separator = ";");
    void store      (std::ofstream& out_file, std::string separator = ";");

    //Operators
    ArrayGraph<T>& operator = (const ArrayGraph<T>& rhs);
    bool operator == (const ArrayGraph<T>& rhs) const;
    bool operator != (const ArrayGraph<T>& rhs) const;

    template<class T2>
    friend std::ostream& operator<<(std::ostream& outs, const ArrayGraph<T2>& g);


  private:
    //All methods and operators relating to LocalInfo are defined below, followed by
    //  a friend function for << onto output streams for LocalInfo
    class LocalInfo {
      public:
        LocalInfo() {}
        LocalInfo(ArrayGraph<T>* g) : from_graph(g) {}
        void connect(ArrayGraph<T>* g) {from_graph = g;}
        bool operator == (const LocalInfo& rhs) const {
          //No need to check in_nodes and _out_nodes: redundant information there
          return this->in_edges == rhs.in_edges && this->out_edges == rhs.out_edges;
        }
        bool operator != (const LocalInfo& rhs) const {
          return !(*this == rhs);
        }

        //LocalInfor instance variables
        //The LocalInfo class is private to code #including this file, but public
        //  instance variables allows ArrayGraph them directly
        //from_graph should point to the ArrayGraph of the LocalInfo it is in, so
        //  LocalInfo methods can access its edge_value map (see <<)
        ArrayGraph<T>* from_graph = nullptr;
        NodeSet       out_nodes;
        NodeSet       in_nodes;
        EdgeSet       out_edges;
        EdgeSet       in_edges;
    };


    friend std::ostream& operator<<(std::ostream& outs, const LocalInfo& li) {
      outs << "LocalInfo[" << std::endl << "         out_nodes = " << li.out_nodes << std::endl;
      outs << "         out_edges = set[";
      int printed = 0;
      for (Edge e : li.out_edges)
        outs << (printed++ == 0 ? "" : ",") << "->" << e.second << "(" << li.from_graph->edge_values[e] << ")";
      outs << "]" << std::endl;

      outs << "         in_nodes  = " << li.in_nodes << std::endl;
      outs << "         in_edges  = set[";
      printed = 0;
      for (Edge e : li.in_edges)
        outs << (printed++ == 0 ? "" : ",") << e.first << "(" << li.from_graph->edge_values[e] << ")" << "->" ;

      outs << "]]";
      return outs;
    }

    //ArrayGraph<T> class two local instance variables
    NodeMap node_values;
    EdgeMap edge_values;
};




////////////////////////////////////////////////////////////////////////////////
//
//ArrayGraph: the class and its related definitions

//Destructor/Constructors

template<class T>
ArrayGraph<T>::~ArrayGraph ()
{}


template<class T>
ArrayGraph<T>::ArrayGraph ()
{}


//Copy all nodes and edges from g
template<class T>
ArrayGraph<T>::ArrayGraph (const ArrayGraph& g) {
        *this=g;
}


////////////////////////////////////////////////////////////////////////////////
//
//Queries

//Returns whether a graph is empty
template<class T>
bool ArrayGraph<T>::empty() const {
        return node_values.empty();
}


//Returns the number of nodes in a graph
template<class T>
int ArrayGraph<T>::node_count() const {
        return node_values.size();
}


//Returns the number of edges in a graph
template<class T>
int ArrayGraph<T>::edge_count() const {
        return edge_values.size();
}


//Returns whether or not node_name is in the graph
template<class T>
bool ArrayGraph<T>::has_node(NodeName node_name) const {
        return node_values.has_key(node_name);
}

//Returns whether or not the edge is in the graph
template<class T>
bool ArrayGraph<T>::has_edge(NodeName origin, NodeName destination) const {
        return edge_values.has_key(ics::make_pair(origin,destination));
}


//Returns the value of the edge in the graph; if the edge is not in the graph,
//  throw a GraphError exception with appropriate descriptive text
template<class T>
T ArrayGraph<T>::edge_value(NodeName origin, NodeName destination) const {
        if(has_edge(origin,destination))
            return edge_values[ics::make_pair(origin,destination)];
        throw GraphError("There is no edge from "+origin+" to "+destination+".");
}


//Returns the in-degree of node_name; if that node is not in the graph,
//  throw a GraphError exception with appropriate descriptive text
template<class T>
int ArrayGraph<T>::in_degree(NodeName node_name) const {
        if(has_node(node_name))
            return node_values[node_name].in_nodes.size();
        throw GraphError("There is no node called "+node_name+".");
}


//Returns the out-degree of node_name; if that node is not in the graph,
//  throw a GraphError exception with appropriate descriptive text
template<class T>
int ArrayGraph<T>::out_degree(NodeName node_name) const {
        if(has_node(node_name))
            return node_values[node_name].out_nodes.size();
        throw GraphError("There is no node called "+node_name+".");
}


//Returns the degree of node_name; if that node is not in the graph,
//  throw a GraphError exception with appropriate descriptive text.
template<class T>
int ArrayGraph<T>::degree(NodeName node_name) const {
        if(has_node(node_name))
        {
            auto& t=node_values[node_name];
            return t.out_nodes.size()+t.in_nodes.size();
        }
        throw GraphError("There is no node called "+node_name+".");
}


//Returns a reference to the all_nodes map;
//  the user should not mutate its data structure: call Graph commands instead
template<class T>
auto ArrayGraph<T>::all_nodes () const -> const NodeMap& {
        return node_values;
}


//Returns a reference to the all_edges map;
//  the user should not mutate its data structure: call Graph commands instead
template<class T>
auto ArrayGraph<T>::all_edges () const -> const EdgeMap& {
        return edge_values;
}

//Returns a reference to the out_nodes set in the LocalInfo for node_name;
//  the user should not mutate its data structure: call Graph commands instead;
//  if that node is not in the graph, throw a GraphError exception with
//  appropriate  descriptive text
template<class T>
auto ArrayGraph<T>::out_nodes(NodeName node_name) const -> const NodeSet& {
        if(has_node(node_name))
            return node_values[node_name].out_nodes;
        throw GraphError("There is no node called "+node_name+".");
}


//Returns a reference to the in_nodes set in the LocalInfo for node_name;
//  the user should not mutate its data structure: call Graph commands instead;
//  if that node is not in the graph, throw a GraphError exception with
//  appropriate descriptive text
template<class T>
auto ArrayGraph<T>::in_nodes(NodeName node_name) const -> const NodeSet& {
        if(has_node(node_name))
            return node_values[node_name].in_nodes;
        throw GraphError("There is no node called "+node_name+".");
}


//Returns a reference to the out_edges set in the LocalInfo for node_name;
//  the user should not mutate its data structure: call Graph commands instead;
//  if that node is not in the graph, throw a GraphError exception with
//  appropriate descriptive text
template<class T>
auto ArrayGraph<T>::out_edges(NodeName node_name) const -> const EdgeSet& {
        if(has_node(node_name))
            return node_values[node_name].out_edges;
        throw GraphError("There is no node called "+node_name+".");
}


//Returns a reference to the in_edges set in the LocalInfo for node_name;
//  the user should not mutate its data structure: call Graph commands instead;
//  if that node is not in the graph, throw a GraphError exception with
//  appropriate descriptive text
template<class T>
auto ArrayGraph<T>::in_edges(NodeName node_name) const -> const EdgeSet& {
        if(has_node(node_name))
            return node_values[node_name].in_edges;
        throw GraphError("There is no node called "+node_name+".");
}


////////////////////////////////////////////////////////////////////////////////
//
//Commands

//Add node_name to the graph if it is not already there.
//Ensure that its associated LocalInfo has a from_graph refers to this graph.
template<class T>
void ArrayGraph<T>::add_node (NodeName node_name) {
        if(has_node(node_name))
            return;
        node_values[node_name]=LocalInfo(this);
}


//Add an edge from origin node to destination node, with value
//Add these node names and update edge_values and the LocalInfos of each node
template<class T>
void ArrayGraph<T>::add_edge (NodeName origin, NodeName destination, T value) {
        if(has_edge(origin,destination))
            throw GraphError("The edge is already in the graph.");
        add_node(origin);
        add_node(destination);
        auto edge=ics::make_pair(origin,destination);
        node_values[origin].out_nodes.insert(destination);
        node_values[origin].out_edges.insert(edge);
        node_values[destination].in_nodes.insert(origin);
        node_values[destination].in_edges.insert(edge);
        edge_values[edge]=value;
}


//Remove all uses of node_name from the graph: update node_values, edge_values,
//  and all the LocalInfo in which it appears as an origin or destination node
//If the node_name is not in the graph, do nothing
//Hint: you cannot iterate over a sets that you are changing:, so you might have
// to copy a set and then iterate over it while removing values from the original set
template<class T>
void ArrayGraph<T>::remove_node (NodeName node_name){
        if(has_node(node_name))
        {
            auto tempset=node_values[node_name].in_edges;
            tempset.insert_all(node_values[node_name].out_edges);
            for(auto i:tempset)
                remove_edge(i.first,i.second);
            node_values.erase(node_name);
        }
}


//Remove all uses of this edge from the graph: update edge_values and all the
//  LocalInfo in which its origin and destination node appears
//If the edge is not in the graph, do nothing
//Hint: Simpler than remove_node: write and test this one first
template<class T>
void ArrayGraph<T>::remove_edge (NodeName origin, NodeName destination) {
        if(has_edge(origin,destination))
        {
            auto edge=ics::make_pair(origin,destination);
            node_values[origin].out_nodes.erase(destination);
            node_values[origin].out_edges.erase(edge);
            node_values[destination].in_nodes.erase(origin);
            node_values[destination].in_edges.erase(edge);
            edge_values.erase(edge);
        }
}


//Clear the graph of all nodes and edges
template<class T>
void ArrayGraph<T>::clear() {
        node_values.clear();
        edge_values.clear();
}


//Load the nodes and edges for a graph from a text file whose form is
// (a) a node name (one per line)
// followed by
// (b) an origin node, destination node, and value (one triple per line,
//       with the values separated by separator, on any number of lines)
// Adds these nodes/edges to those currently in the graph
//Hint: use ics::split and istringstream (the extraction dual of ostreamstring)
template<class T>
void ArrayGraph<T>::load (std::ifstream& in_file, std::string separator) {
        std::string s;
        while(std::getline(in_file,s))
        {
            auto t=ics::split(s, separator);
            if(t.size()==1)
                add_node(t[0]);
            else
            {
                std::istringstream iss(t[2]);
                T v;
                iss>>v;
                add_edge(t[0],t[1],v);
            }
        }
}


//Store the nodes and edges in a graph into a text file whose form is specified
//  above for the load method; files written by store should be readable by load
//Hint: this is the easier of the two methods: write and test it first
template<class T>
void ArrayGraph<T>::store(std::ofstream& out_file, std::string separator) {
        for(auto i:node_values)
            out_file<<i.first+"\n";
        for(auto i:edge_values)
        {
            out_file << i.first.first + separator + i.first.second + separator << i.second << "\n";
        }
}


////////////////////////////////////////////////////////////////////////////////
//
//Operators

//Copy the specified graph into this and return the newly copied graph
//Hint: each copied LocalInfo object should reset from_graph to the this new graph
template<class T>
ArrayGraph<T>& ArrayGraph<T>::operator = (const ArrayGraph<T>& rhs){
        node_values=rhs.node_values;
        for(auto i:node_values)
            i.second.from_graph=this;
        edge_values=rhs.edge_values;
        return *this;
}


//Return whether two graphs are the same nodes and same edges
//Avoid checking == on LocalInfo (edge_map has equivalent information;
//  just check that node names are the same in each
template<class T>
bool ArrayGraph<T>::operator == (const ArrayGraph<T>& rhs) const{
        if(node_count()!=rhs.node_count())
            return false;
        if(edge_count()!=rhs.edge_count())
            return false;
        for(auto i:node_values)
            if(!rhs.has_node(i.first))return false;
        for(auto i:edge_values)
            if(!rhs.has_edge(i.first.first,i.first.second) || rhs.edge_values[i.first]!=i.second)return false;
        return true;
}


//Return whether two graphs are different
template<class T>
bool ArrayGraph<T>::operator != (const ArrayGraph<T>& rhs) const{
        return !(*this == rhs);
}


template<class T>
std::ostream& operator<<(std::ostream& outs, const ArrayGraph<T>& g) {
    outs<<"graph[\n";
    for(auto i:g.node_values)
    {
        outs<<"  "+i.first+" -> LocalInfo[\n";
        outs<<"         out nodes = "<<i.second.out_nodes<<"\n";
        outs<<"         out_edges = set[";
        auto iter=i.second.out_edges.begin();
        outs<<"->"+iter->second+"("<<g.edge_values[*iter]<<")";
        while(++iter!=i.second.out_edges.end())
            outs<<",->"+iter->second+"("<<g.edge_values[*iter]<<")";
        outs<<"]\n         in_nodes  = "<<i.second.in_nodes<<"\n";
        outs<<"         in_edges  = set[";
        iter=i.second.in_edges.begin();
        outs<<iter->first+"("<<g.edge_values[*iter]<<")->";
        while(++iter!=i.second.in_edges.end())
            outs<<","+iter->first+"("<<g.edge_values[*iter]<<")->";
        outs<<"]]\n";
    }
    outs<<"]\n";
    return outs;
}


}

#endif /* ARRAY_GRAPH_HPP_ */
