#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>                    //Biggest int: std::numeric_limits<int>::max()
#include "array_queue.hpp"
#include "array_stack.hpp"
#include "array_map.hpp"
#include "heap_priority_queue.hpp"
#include "hash_graph.hpp"


namespace ics {


class Info {
  public:
    Info() { }

    Info(std::string a_node) : node(a_node) { }

    bool operator==(const Info &rhs) const { return cost == rhs.cost && from == rhs.from; }

    bool operator!=(const Info &rhs) const { return !(*this == rhs); }

    friend std::ostream &operator<<(std::ostream &outs, const Info &i) {
      outs << "Info[" << i.node << "," << i.cost << "," << i.from << "]";
      return outs;
    }

    //Public instance variable definitions
    std::string node = "?";
    int cost = std::numeric_limits<int>::max();
    std::string from = "?";
  };


  bool gt_info(const Info &a, const Info &b) { return a.cost < b.cost; }

  typedef ics::HashGraph<int>                  DistGraph;
  typedef ics::HeapPriorityQueue<Info, gt_info> CostPQ;
  typedef ics::ArrayMap<std::string, Info>       CostMap;
  typedef ics::pair<std::string, Info>          CostMapEntry;


//Return the final_map as specified in the lecture-note description of
//  extended Dijkstra algorithm
  CostMap extended_dijkstra(const DistGraph &g, std::string start_node) {
		CostMap answer_map;
		CostMap info_map;
		for(auto i:g.all_nodes())
			info_map[i.first]=Info(i.first);
		info_map[start_node].cost=0;
		CostPQ info_pq;
		for(auto i:info_map)
			info_pq.enqueue(i.second);
		while(!info_map.empty())
		{
			Info temp;
			do
			{
				temp = info_pq.dequeue();
			}while(answer_map.has_key(temp.node));
			if (temp.cost == std::numeric_limits<int>::max())break;
			answer_map.put(temp.node,info_map.erase(temp.node));
			info_pq.clear();
			for(auto i:g.out_nodes(temp.node))
			{
				if(!answer_map.has_key(i))
				{
					auto sum=temp.cost+g.edge_value(temp.node,i);
					if(info_map[i].cost==std::numeric_limits<int>::max() || info_map[i].cost>sum)
					{
						info_map[i].cost=sum;
						info_map[i].from=temp.node;
					}
				}
				info_pq.enqueue(info_map[i]);
			}
		}
		return answer_map;
  }


//Return a queue whose front is the start node (implicit in answer_map) and whose
//  rear is the end node
  ArrayQueue <std::string> recover_path(const CostMap &answer_map, std::string end_node) {
		ArrayStack<std::string> stack;
		ArrayQueue<std::string> answer;
		stack.push(end_node);
		while(answer_map[end_node].from!="?")
			stack.push(end_node=answer_map[end_node].from);
		while(!stack.empty())
			answer.enqueue(stack.pop());
		return answer;
  }


}

#endif /* DIJKSTRA_HPP_ */
