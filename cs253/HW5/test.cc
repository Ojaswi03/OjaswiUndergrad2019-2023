#include "Words.h"
#include "Words.h"      // I meant to do that.
#include <iostream>
#include <cassert>
 
using namespace std;
 
int main() {
    Words a("");
    assert(a.size() == 0);
    assert(a.empty());
    assert(!a);
    a.analyze("Applejack Pinkie\\ Pie");
    assert(a.size() == 2);
    assert(a);
    auto p = a[0];
    assert(p.first == "Applejack" && !p.second);
    p = a[1];
    assert(p.first == "Pinkie Pie" && p.second);
 
 
    assert(a == Words("\v\\Applejack\nPinkie\\ Pie \f\t\r"));
    assert(a != Words("Applejack Pinkie\\ Pie vjfnwb"));
    assert(!(a != Words("Applejack Pinkie\\ Pie")));
    assert(!(a == Words("Applejack Pinkie\\ Pie 1660")));
 
    const Words b(" Fluttershy "), c(" Rarity "), d(b+c);
    assert(b.size() == 1);
    assert(c.size() == 1);
    assert(d.size() == 2);
 
    Words e(a += d);
    assert(a == e);
    assert(e.size() == 4);
    assert(e[0].first == "Applejack");
    assert(e[1].first == "Pinkie Pie");
    assert(e[2].first == "Fluttershy");
    assert(e[3].first == "Rarity");
    assert(!e[0].second);
    assert( e[1].second);
    assert(!e[2].second);
    assert(!e[3].second);
 
    while (e) {
        cout << "size=" << e.size() << " ";
        cout << e-- << '\n';
    }
 
    cout << "Done.\n";
 
    return 0;
}