
#include <string>
#include <assert.h>
using namespace std;

bool interleaving(const string& a, const string& b, const string&c) {
	if (a.size() + b.size() != c.size()) {
		return false;
	}
	unsigned a_it = 0;
	unsigned b_it = 0;
	unsigned c_it = 0;
	for (; a_it < a.size() && b_it < b.size();) {
		if (c[c_it] == a[a_it]) {
			++a_it;
		}
		else if (c[c_it] == b[b_it]) {
			++b_it;
		}
		else {
			return false;
		}
		++c_it;
	}
	while (a_it < a.size()) {
		if (a[a_it++] != c[c_it++]) {
			return false;
		}
	}
	while (b_it < b.size()) {
		if (b[b_it++] != c[c_it++]) {
			return false;
		}
	}
	return true;
}

void main() {
	assert(interleaving("AB", "XY", "AXBY"));
	assert(!interleaving("AB", "XY", "ABBY"));
	system("pause");
}