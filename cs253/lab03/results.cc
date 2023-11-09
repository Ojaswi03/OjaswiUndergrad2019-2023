#include <vector>
#include <string>
#include <set>
#include <iterator>
#include <fstream>
#include <iostream>
using namespace std;
int main (){

        vector<int> v;
        int num;
        string line , st;
        multiset<char> ms;
        set <char> s;

        while (cin >> num){
              if (num != 0){
                 v.push_back(num);
              }
              else
                  break;
        }

        cout << "Output of the vector line: \n";
        for (auto z  = v.begin(); z != v.end() ; z++){
            cout << *z << "\n";
        }
        cout << "\n";

        string fname = "/etc/resolv.conf";
        ifstream in(fname);
        st = "";

        for(line; getline(in , line);) {
           st += line + "\n";
        }
        cout << "string: size=" << st.size() << " " << st << "\n";

        for (auto a: st){
            ms.insert(a);
        }


        for (auto b: ms){
            s.insert(b);
        }

        cout << "set: size=" << s.size();
        for (auto i  = s.begin(); i != s.end(); i++) {
            cout << *i ;
        }
        cout << "\n";
        cout << "multiset: size=" << ms.size() ;
        for (auto j = ms.begin(); j != ms.end(); j++) {
            cout << *j ;
        }
        cout << "\n";

         // Question 7 :
         //
         // string: It is a collection of characters and also one of the STL containers it stores the chracter in the orde 
         //         in which they are placed into to variable and duplicate characters are allowed as well.
         //         Therefore, it's size is very similar to the multiset with the difference of one being unsorted and other
         //         being sorted respectively.
         //
         // set: It is a STL container which doesn't store duplicate values and arranges them in sorted order. For that
         //      reason the size of set is less or equal to multiset and string.
         //
         // multiset: It is also a STL container which stores all characters even if they are repeated and then arranges
         //           them in  sorted order. Therefore, their size tends to be almost the sasme size as the original 
         //           string.

}
