#include <iostream>

using namespace std;

class Foo {
public:
    // Redefine operator new for only this class.
    static void *operator new(size_t size) {
	// We can still call new to allocate chars--that will call
	// the global new operator.
	void *p = new char[size];
	cout << "new(" << size << ") returns " << p << '\n';
	return p;
    }

    // Redefine operator delete for only this class.
    static void operator delete(void *p, size_t size) {
	cout << "delete(" << p << ", " << size << ")\n";
	delete[] static_cast<char *>(p);
    }

    char zot[4000];
};

int main() {
    double *p = new double;
    Foo *q = new Foo;
    Foo *r = new Foo;
    delete p;
    delete q;
    delete r;
    return 0;
}
