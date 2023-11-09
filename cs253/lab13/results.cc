#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;
int helper(int n){
        return ++n;
 }

int main() {
    vector<short> pi = {3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4};
    string alpha="abcdefghijklmnopqrstuvwxyz", digits="0123456789";
    char cbuf[100] = { };	// contains 100 '\0' chars
    list<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    short powers[] = {1,2,4,8,16,32,64};
    int ibuf[100];		// contains unknown values

    cout << "Exercise 0\n";
    copy(alpha.begin(), alpha.end(), cbuf);
    cout << cbuf << '\n';

    cout << "Exercise 1\n";
    reverse(alpha.begin(),alpha.end());
    cout << alpha <<'\n';

    cout << "Exercise 2\n";
    
    transform(begin(primes), end(primes), ibuf, helper);
    for (size_t i = 0; i < primes.size(); ++i) {
       cout << ibuf[i] << ' ';
    }
    cout << '\n'; 
    
    cout << "Exercise 3\n";

    auto a = any_of(begin(primes), end(primes),[] (int z) {return z % 2 == 0;});
    auto b = any_of(begin(primes), end(primes),[] (int x) {return x % 42 == 0;});
    if (a){
        cout << "div 2\n";
    }
    if (b){
        cout << "div 42\n";
    }
    cout << "Exercise 4\n";
    auto r = find(begin(primes), end(primes), 13);
    advance(r , 1);
    cout << *r << '\n';
    
    
    cout << "Exercise 5\n";
    auto c = count(begin(pi), end(pi), 3);
    cout << c << '\n';

    cout << "Exercise 6\n";
    auto d = count_if(begin(pi), end(pi), [] (int i) { return i < 5;});
    cout << d << '\n';
    
    cout << "Exercise 7\n";
    
    auto e = max_element(begin(pi), end(pi));
    cout << *e << '\n';
    
    cout << "Exercise 8\n";
    sort(begin(pi), end(pi));
    for (size_t i = 0; i < pi.size(); ++i){
        cout << pi[i]<< ' ';
    }
    cout << '\n';
    
    cout << "Exercise 9\n";

    auto lower = lower_bound(begin(pi), end(pi), 7);
    cout << lower - begin(pi) << '\n';
    
    cout << "Exercise 10\n";
    auto g = set_intersection(begin(pi), end(pi), begin(powers), end(powers), begin(ibuf));
    for (auto i  = &ibuf[0] ; i != g; ++i){      
        cout << *i << ' ';
    }    
    cout << '\n';
}

