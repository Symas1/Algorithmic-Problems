// implement an ISBN cache
#include <utility>
#include <list>
#include <assert.h>
#include <iostream>
#include <unordered_map>
using namespace std;

template <size_t capacity>
class Isbn_with_cache
{
public:
	int search(int isbn)
	{
		auto iter = data_.find(isbn);
		if (iter == data_.end())return -1;
		move_to_front(iter);
		return iter->second.second;
	}

	void insert(int isbn, int price)
	{
		auto iter = data_.find(isbn);
		if (iter != data_.end())
		{
			move_to_front(iter);
		}
		else
		{
			if (data_.size() == capacity)
			{
				data_.erase(cache_.back());
				cache_.pop_back();
			}
			cache_.emplace_front(isbn);
			data_[isbn] = make_pair( cache_.begin(),price );
		}
	}

	void remove(int isbn)
	{
		auto iter = data_.find(isbn);
		if (iter == data_.end())return;
		cache_.erase(iter->second.first);
		data_.erase(iter);
	}

private:
	using Table = unordered_map<int, pair<list<int>::iterator, int>>;
	void move_to_front(const Table::iterator& iter)
	{
		cache_.erase(iter->second.first);
		cache_.emplace_front(iter->first);
		iter->second.first = cache_.begin();
	}
	Table data_;
	list<int> cache_;
}; // time O(1)

int main(int argc,char* argv[])
{
	Isbn_with_cache<2> a{};

	// search
	{
		a.insert(1, 100);
		assert(a.search(1) == 100);
		assert(a.search(2) == -1);
	}

	// test insert moves to front and capacity constraints
	{
		a.insert(2, 200); // 2 1
		assert(a.search(2) == 200);
		a.insert(1, 200); // 1 2
		a.insert(3, 300); // 3 1
		assert(a.search(1) == 100);
		assert(a.search(3) == 300);
		assert(a.search(2) == -1);
	}

	// test search moves to front
	{
		a.search(1); // 1 3
		a.insert(2,200); // 2 1
		assert(a.search(1) == 100);
		assert(a.search(3) == -1);
		assert(a.search(2) == 200);
	}

	// test remove
	{
		a.remove(2);
		a.remove(1);
		assert(a.search(1) == -1);
		assert(a.search(3) == -1);
		assert(a.search(2) == -1);
	}
	system("pause");
	return 0;
}