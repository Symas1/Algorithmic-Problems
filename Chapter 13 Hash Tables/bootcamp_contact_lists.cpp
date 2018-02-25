// contact lists
#include <unordered_set>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Contact {
	bool operator==(const Contact& that)const
	{
		return unordered_set<string>{data.begin(), data.end()} ==
			unordered_set<string>{that.data.begin(), that.data.end()};
	}
	vector<string> data;
};

struct Hash_contact
{
	size_t operator()(const Contact& contact)const
	{
		size_t hash_code = 0;
		for (const string& str : unordered_set<string>{ contact.data.begin(), contact.data.end() })
		{
			hash_code ^= hash<string>()(str);
		}
		return hash_code;
	}
};

vector<Contact> merge_contacts(const vector<Contact>&arr)
{
	unordered_set<Contact, Hash_contact>unique_contacts{ arr.begin(), arr.end() };
	return{ unique_contacts.begin(),unique_contacts.end() };
} // time O(n) n - number of strings

int main(int argc, char* argv[])
{
	vector<Contact>arr{ {{"a","b","c"}},{{"b","a","c"}},{{"a","b","d"}} };
	arr = merge_contacts(arr);
	assert(arr.size() == 2);
	system("pause");
	return 0;
}