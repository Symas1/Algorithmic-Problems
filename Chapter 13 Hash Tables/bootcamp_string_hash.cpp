// string hash function
#include <string>
#include <random>
#include <iostream>
using namespace std;

string generate_string(int size)
{
	mt19937 mt{ random_device{}() };
	string result(size, '\n');
	for (int i = 0; i < size; ++i)
	{
		char new_char = uniform_int_distribution<int>{ 0,25 }(mt);
		new_char += uniform_int_distribution<int>{0, 1}(mt) ? 'A' : 'a';
		result[i] = new_char;
	}
	return result;
}

int string_hash(const string& str, int modulus)
{
	const int base = 997;
	int result = 0;
	for (const char& c : str)
	{
		result = (result*base + c) % modulus;
	}
	return result;
} // time O(m) m - string size; space O(1)

int main(int argc, char* argv[])
{
	string str;
	if (argc == 2)
	{
		str = argv[1];
	}
	else
	{
		mt19937 mt{ random_device{}() };
		str = generate_string(uniform_int_distribution<>{1, 20}(mt));
	}
	cout << "string= " << str << endl;
	cout << "hash= " << string_hash(str, 1 << 16) << endl;
	system("pause");
	return 0;
}
