#include <iostream>
#include <cstdlib>
#include <algorithm>	    // for min(), max()

using namespace std;

class Foo {
  public:
    static void *operator new(size_t size) {
	void *p = new char[size];
	if (!min_addr)
	    min_addr = max_addr = p;
	min_addr = min(min_addr, p);
	max_addr = max(max_addr, p);
	cout << "new(" << size << ") returns " << p << '\n';
	return p;
    }

    static void operator delete(void *p, size_t size) {
	cout << "delete(" << p << ", " << size << ")\n";
	if (!p)			    // It's ok to delete a null pointer.
	    return;

	if (!min_addr) {
	    cerr << "ERROR: attempt to delete a Foo, "
		 << "but no Foo was ever allocated.\n";
	    exit(1);
	}
	else if (p < min_addr || p > max_addr) {
	    cerr << "ERROR: attempt to delete a Foo, "
		 << "but " << p << " is out of range.\n";
	    exit(1);
	}
	// The alignof operator returns the alignment requirement of a type.
	// For example, alignof(int) == 4.
	else if (long(p) & ((1<<alignof(Foo))-1)) {
	    // Verify our rash assumption:
	    static_assert(sizeof(long) == sizeof(p),
			  "assume long and void * are the same size");
	    cerr << "ERROR: attempt to delete a Foo, "
		 << "but " << p << " has bad alignment.\n";
	    exit(1);
	}

	delete[] static_cast<char *>(p);
    }

    static void *min_addr, *max_addr;
    char zot[4000];
};

void *Foo::min_addr, *Foo::max_addr;

int main() {
    double *p = new double;
    Foo *q = new Foo;
    int z;
    Foo *r = reinterpret_cast<Foo *>(&z);
    delete p;		// fine
    delete q;		// fine
    delete r;		// bad: this is a stack address
    return 0;
}
