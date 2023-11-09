#include <iostream>
#include <cstdlib>

using namespace std;

// Redefine the global operator new.  It gets memory by calling the old
// C function malloc().  At this level, that’s good enough, since we’re
// just allocating raw memory.  Constructors and destructors get called
// at higher levels.

void *operator new(size_t size) {
    void *p = malloc(size);
    cout << "new(" << size << ") returns " << p << '\n';
    return p;
}

// Redefine the global operator delete.  Since we redefined global new
// to call malloc(), we deallocate the memory in old C style by
// calling free().

void operator delete(void *p, size_t size) {
    cout << "delete(" << p << ", " << size << ")\n";
    free(p);
}

// The size_t argument for global delete is a C++14 feature.
// I’m not sure when this version (without a size) gets invoked,
// but the compiler insists that I write it.  Fine--here!

void operator delete(void *p) {
    cout << "delete(" << p << ")\n";
    free(p);
}

class Foo {
    char zot[4000];
};

int main() {
    double *p = new double;
    Foo *q = new Foo;
    cout << "p=" << p << '\n'
	 << "q=" << q << '\n';
    delete p;
    delete q;
    return 0;
}
