#include <iostream>
#include <cstdlib>		// for malloc(), free()
#include <cstring>		// for memset()

using namespace std;

void *operator new(size_t size) {
    void *p = malloc(size);
    cout << "new(" << size << ") returns " << p << '\n';
    return memset(p, 'q', size);	// Fill memory with the letter 'q'
}

void operator delete(void *p, size_t size) {
    cout << "delete(" << p << ", " << size << ")\n";
    if (p)				// It’s ok to delete a null pointer.
	memset(p, '!', size);		// Fill memory with exclamation points
    free(p);
}

void operator delete(void *p) {
    cout << "delete(" << p << ")\n";
    // Can’t scrub this memory--don’t know how big it is!
    free(p);
}

int main() {
    int *pi = new int;
    cout << "Our int is: " << *pi << '\n';
    auto pd = new double;
    cout << "Our double is: " << *pd << '\n';
    delete pi;
    delete pd;
    return 0;
}
