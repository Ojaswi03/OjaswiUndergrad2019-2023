#include <iostream>

using namespace std;

class Foo {
  public:
    double datum;
};

int main() {
    cout << "sizeof(double) = " << sizeof(double) << '\n'
	 << "sizeof(Foo) = " << sizeof(Foo) << '\n';
    Foo *p = new Foo;
    Foo *q = new Foo;
    Foo *z;
    for (size_t i = 0; i < 10000000; ++i){
      z = new Foo;

    }
    cout << "p=" << p << '\n'
	 << "q=" << q << '\n'
   << "z= " << z << '\n';
    delete p;
    delete q;
    return 0;
}
