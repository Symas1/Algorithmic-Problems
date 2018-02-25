// add credits
#include <unordered_map>
#include <map>
#include <vector>
#include <assert.h>
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <unordered_set>
using namespace std;

class Client_credit_info
{
public:
	void insert(int credit, string name)
	{
		remove(name);
		client_to_credit_.emplace(name, credit - offset_);
		credit_to_clients_[credit - offset_].emplace(name);
	}

	bool remove(const string& name)
	{
		auto hash_iter = client_to_credit_.find(name);
		if (hash_iter != client_to_credit_.end())
		{
			credit_to_clients_[hash_iter->second].erase(name);
			if (credit_to_clients_[hash_iter->second].empty())
			{
				credit_to_clients_.erase(hash_iter->second);
			}
			client_to_credit_.erase(hash_iter);
			return true;
		}
		return false;
	}

	int lookup(const string& name)
	{
		auto iter = client_to_credit_.find(name);
		if (iter != client_to_credit_.end())return iter->second + offset_;
		else return -1;
	}

	void add_all(const int off)
	{
		offset_ += off;
	}

	string Max()const
	{
		auto iter = credit_to_clients_.crbegin();
		if (iter != credit_to_clients_.crend())
		{
			return *iter->second.begin();
		}
		else return{};
	}


private:
	int offset_{ 0 };
	unordered_map<string, int>client_to_credit_{};
	map<int, unordered_set<string>>credit_to_clients_{};
}; // insert,remove O(logn); max,lookup,add_all O(1)

int main(int argc, char* argv[]) {
	Client_credit_info a{};
	assert(a.Max() == "");
	assert(!a.remove("foo"));
	a.insert(10,"foo");
	a.insert(1,"foo");
	a.insert(2,"bar");
	a.add_all(5);
	a.insert(3,"widget");
	a.add_all(5);
	a.insert(4,"dothis");
	assert(11 == a.lookup("foo"));
	assert(12 == a.lookup("bar"));
	assert(8 == a.lookup("widget"));
	assert(4 == a.lookup("dothis"));
	assert(a.remove("foo"));
	assert(-1 == a.lookup("foo"));
	assert(a.Max().compare("bar") == 0);
	a.insert(13,"xyz");
	assert(a.Max().compare("xyz") == 0);
	a.insert(15,"dd");
	assert(a.Max().compare("dd") == 0);
	system("pause");
	return 0;
}