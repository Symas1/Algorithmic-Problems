//// compute the diameter of a tree
//#include <memory>
//#include <iostream>
//#include <assert.h>
//#include <algorithm>
//#include <vector>
//#include <array>
//#include <map>
//#include <functional>
//
//#include "variant.h"
//
//using namespace std;
//
//struct Tree_node {
//	struct Edge{
//		unique_ptr<Tree_node> root;
//		double length;
//	};
//	vector<Edge>edges;
//};
//
//struct Height_and_diameter {
//	double height, diameter;
//};
//
//Height_and_diameter diameter2_helper(const unique_ptr<Tree_node>&node);
//double diameter2(const unique_ptr<Tree_node>&root)
//{
//	return root ? diameter2_helper(root).diameter : 0.0;
//}
//Height_and_diameter diameter2_helper(const unique_ptr<Tree_node>&node)
//{
//	double diameter = numeric_limits<double>::lowest();
//	array<double, 2> max_heights{ {0.0,0.0} };
//	for (const auto& e : node->edges)
//	{
//		auto d_and_h = diameter2_helper(e.root);
//		if (d_and_h.height + e.length > max_heights[0]) {
//			max_heights = { d_and_h.height + e.length,max_heights[0] };
//		}
//		else if (d_and_h.height + e.length > max_heights[1]) {
//			max_heights[1] = d_and_h.height + e.length;
//		}
//		diameter = max(diameter, d_and_h.diameter);
//	}
//	return{ max_heights[0],max(diameter,max_heights[0] + max_heights[1]) };
//} // time O(n) n - nodes; space O(h) h - height;
//
//void test_main();
//
//void main()
//{
//	test_main();
//	system("pause");
//}
//
//void test_main() {
//	unique_ptr<Tree_node> r = nullptr;
//	assert(0.0 == diameter2(r));
//	r = make_unique<Tree_node>(Tree_node());
//	r->edges.emplace_back(
//		Tree_node::Edge{ make_unique<Tree_node>(Tree_node()), 10 });
//	r->edges[0].root->edges.emplace_back(
//		Tree_node::Edge{ make_unique<Tree_node>(Tree_node()), 50 });
//	r->edges.emplace_back(
//		Tree_node::Edge{ make_unique<Tree_node>(Tree_node()), 20 });
//	assert(80 == diameter2(r));
//	cout << diameter2(r) << endl;
//	r->edges[0].root->edges.emplace_back(
//		Tree_node::Edge{ make_unique<Tree_node>(Tree_node()), 100 });
//	assert(150 == diameter2(r));
//	cout << diameter2(r) << endl;
//}