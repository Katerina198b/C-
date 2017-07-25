#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
using namespace boost;

int main() {
  
	typedef adjacency_list<vecS,
						 vecS,
						 undirectedS,
						 property<vertex_index_t, int>
						 > graph;


	int count_of_edjes, count_of_vertices;
	int start_point, next_point;
	std::cin >> count_of_vertices  >> count_of_edjes ;
	graph g(count_of_vertices);
		for (int i = 0; i  < count_of_edjes; i++) {
		std::cin >> start_point >> next_point;
		add_edge(start_point, next_point, g);
	}

	if (boyer_myrvold_planarity_test(g))
	std::cout << "YES" ;
	else
	std::cout << "NO";

	return 0;
}
