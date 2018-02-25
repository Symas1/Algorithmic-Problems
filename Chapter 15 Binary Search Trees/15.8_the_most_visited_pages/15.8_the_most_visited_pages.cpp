// the most visited pages problem
#include <map>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <functional>
using namespace std;

vector<pair<int, char>> most_visited(ifstream& ifs, const int k)
{
	multimap<int, char>count_to_page{};
	unordered_map<char, multimap<int, char>::const_iterator>page_to_node{};
	string line{};
	while (getline(ifs, line))
	{
		istringstream stream{ line };
		string page{};
		while (getline(stream, page, ' '))
		{
			auto hash_iter = page_to_node.find(page[0]);
			if (hash_iter == page_to_node.end())
			{
				auto insert_iter = count_to_page.emplace(1, page[0]);
				page_to_node.emplace(page[0], insert_iter);
			}
			else
			{
				pair<int, char> new_elem = { hash_iter->second->first + 1,hash_iter->second->second };
				count_to_page.erase(hash_iter->second);
				auto insert_iter = count_to_page.emplace(new_elem);
				page_to_node[page[0]] = insert_iter;
			}
		}
	}
	vector<pair<int, char>>res{};
	for (auto iter = max_element(count_to_page.begin(), count_to_page.end()); res.size() != k; iter = prev(iter))
	{
		res.emplace_back(iter->first, iter->second);
	}
	return res;
} // time O(nlogk) n - pages, k - distinct pages; space O(k)

vector<pair<int, char>> variant1(ifstream& ifs, const int k)
{
	multimap<int, char, greater<>>count_to_page{};
	unordered_map<char, multimap<int, char>::const_iterator>page_to_node{};


	string page{};
	while (getline(ifs, page, ' '))
	{
		if (page[0] == '\n')continue;
		auto hash_iter = page_to_node.find(page[0]);
		if (hash_iter == page_to_node.end())
		{
			auto insert_iter = count_to_page.emplace(1, page[0]);
			page_to_node.emplace(page[0], insert_iter);
		}
		else
		{
			pair<int, char> new_elem = { hash_iter->second->first + 1,hash_iter->second->second };
			count_to_page.erase(hash_iter->second);
			auto insert_iter = count_to_page.emplace(new_elem);
			page_to_node[page[0]] = insert_iter;
		}
	}
	vector<pair<int, char>>res{};
	for (auto iter = count_to_page.begin(); res.size() != k; iter = next(iter))
	{
		res.emplace_back(iter->first, iter->second);
	}
	return res;
} // time O(nlogk) n - pages, k - distinct pages; space O(k)

void main()
{
	ifstream ifs{ "log.txt" };
	auto res = most_visited(ifs, 3);
	assert(res[0].first == 5 && res[0].second == 'c');
	assert(res[1].first == 4 && res[1].second == 'a');
	assert(res[2].first == 3 && res[2].second == 'd');

	ifs.clear();
	ifs.seekg(0, ios::beg);
	auto res1 = variant1(ifs, 3);

	assert(equal(res.begin(), res.end(), res1.begin(), res1.end()));
	system("pause");
}


