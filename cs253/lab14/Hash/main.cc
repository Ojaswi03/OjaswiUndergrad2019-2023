#include "hset.h"
#include <iostream>
#include <iomanip>			// for setw()
#include <time.h>			// for time() (duh)

using namespace std;

int main() {
    cout << setprecision(4);		// Display four significant digits

    hset<int> h;
    for (int j=0; j<20; j++)		// Put some numbers into the set
	h.insert(j*17 % 100);		// Each number is [0,100).
    h.dump();				// Let’s see what’s in there

    cout << "size=" << h.size() << ':';
    for (auto v : h)
	cout << ' ' << v;
    cout << '\n';

    hset<string> hs;
    for (auto s : {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta"})
	hs.insert(s);
    hs.dump();

    cout << "size=" << hs.size();
    for (auto v : hs)
	cout << ' ' << v;
    cout << '\n';

    hset<double> hv;
    hv.insert(1.1);
    hv.insert(1.2);
    hv.insert(1.3);
    hv.insert(1.4);
    hv.insert(1.5);
    hv.insert(1.6);
    hv.insert(1.7);
    hv.insert(1.8);
    hv.insert(1.9);
    hv.dump();

    cout << "size=" << hv.size();
    for (auto v : hv)
	cout << ' ' << v;
    cout << '\n';
    hv.empty();
}
