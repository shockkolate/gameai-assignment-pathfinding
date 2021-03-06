#include <boost/graph/graphviz.hpp>
#include <gameai/point2.hpp>
#include <gameai/astar.hpp>

struct edge_label_t { typedef boost::edge_property_tag kind; };

typedef boost::property<gameai::astar_pos_t, gameai::point2<int>> vertex_pos_p;
typedef boost::property<boost::vertex_name_t, boost::graph_traits<boost::adjacency_list<>>::vertices_size_type, vertex_pos_p> vertex_p;
typedef boost::property<boost::edge_weight_t, unsigned int> edge_p;
typedef boost::no_property graph_p;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, vertex_p, edge_p, graph_p> graph_t;

int main(int argc, char **argv) {
	std::ifstream in("assets/graph.dot");

	graph_t g;
	boost::dynamic_properties dp(boost::ignore_other_properties);
	dp.property("node_id", boost::get(boost::vertex_name,    g));
	dp.property("pos",     boost::get(gameai::astar_pos_t(), g));
	dp.property("label",   boost::get(boost::edge_weight,    g));

	boost::read_graphviz(in, g, dp);

	auto astar = gameai::make_astar<gameai::distance>(g);
	BOOST_REVERSE_FOREACH(auto v, astar.path(1, 61)) {
		auto n = boost::get(boost::vertex_name, g, v->vertex);
		std::cout << n << std::endl;
	}

	return 0;
}
