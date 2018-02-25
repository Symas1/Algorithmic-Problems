#include <random>
#include <iostream>
#include <assert.h>
using namespace std;

int ran_one_zero()
{
	mt19937 mt((random_device())());
	uniform_int_distribution<int> dist(0, 1);
	return dist(mt);
}

int generate_random(int low, int up)
{
	int diff = up - low, res;
	do {
		res = 0;
		for (int i = 0; (1 << i) < diff;++i)
		{
			res = (res << 1) | ran_one_zero();
		}
	} while (res > diff);
	return res+low;		
} // O(lg(up-low+1))

void main()
{
	mt19937 mt((random_device())());
	uniform_int_distribution<int> dist( 0,1 );
	for (int i = 0; i < 10000; ++i)
	{
		int l = 1;
		int u = 6;
		int res = generate_random(l, u);
		assert((res >= l) && (res <= u));
	}
	system("pause");
}