// partitioning and sorting array with many repeated entries
#include <vector>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <random>
#include <unordered_set>
using namespace std;

struct Student {
	Student(int age_, string name_) :age{ age_ },name{name_} {};
	string name{};
	int age;
};

void part(vector<Student>&arr)
{
	unordered_map<int, unsigned>ages{};
	for (const auto& x : arr)
	{
		++ages[x.age];
	}
	unordered_map<int, size_t>indexes{};
	int free_index = 0;
	for (const auto&x : ages)
	{
		indexes.emplace(x.first,free_index);
		free_index += x.second;
	}
	while (!indexes.empty())
	{
		auto from = indexes.begin();
		auto to = indexes.find(arr[from->second].age);
		swap(arr[from->second], arr[to->second]);
		--ages[to->first];
		if (ages[to->first] > 0)
		{
			++to->second;
		}
		else
			indexes.erase(to);
	}
} // time O(n); space O(c) c - distinct elements

string gen_name(int size)
{
	mt19937 mt{ random_device{}() };
	string str(size,{} );
	for (int i = 0; i < size; ++i)
	{
		str[i] = uniform_int_distribution<>{ 'a','c' }(mt);
	}
	return str;
}

void print(const vector<Student>&arr)
{
	for (const auto&x : arr)
	{
		cout << x.name << '\t' << x.age << endl;
	}
}

void check(const vector<Student>&arr)
{
	unordered_set<int>used{};
	used.emplace(arr.front().age);
	for (int i = 1; i < arr.size();++i)
	{
		if (arr[i].age == arr[i - 1].age)continue;
		else
		{
			assert(!used.count(arr[i].age));
			used.emplace(arr[i].age);
		}
	}
}

void small_test();

void main()
{
	small_test();
	mt19937 mt{ random_device{}() };
	for (int times = 0; times < 10; ++times)
	{
		vector<Student>arr{};
		for (int i = 0; i < 100; ++i)
			arr.emplace_back(uniform_int_distribution<>{17, 22}(mt), gen_name(3));
		part(arr);
		check(arr);
	}
	system("pause");
}

void small_test()
{
	vector<Student>arr{ { 14,"Greg" },{ 12,"John" },{ 11,"Andy" },{ 13,"Jim" },{ 12,"Phil" },{ 13,"Bob" },{ 13,"Chip" },{ 14,"Tim" } };
	part(arr);
	check(arr);
}