#include <iostream>
using namespace std;

int main() {
    string input;
    string word = "";
    int count = 0;
    string longestWord ="";
    while (getline(cin , input)){
        int flag = 0;
        for (size_t i = 0; i < input.size(); i++){
           if (isspace(input[i])){
               if (!word.empty()){
                  cout << "Word is \"" << word  << "\"\n";
                  if (longestWord.size() < word.size()) {
                      longestWord = word;
                  }
                  word = "";
                  count++;
                  flag = 0;
               }
               flag = 0;
           }
           else if (input[i] !='(' && input[i] != ')') {
               flag = 1;
               word.push_back(input[i]);
           }
           else {
               if (!word.empty()){
                   cout << "Word is \"" << word << "\" \n";
                   count++;
               }
               cout << "Word is \"" << input[i] << "\"\n";
               if ( longestWord.size() < word.size()) {
                  longestWord = word;
               }
               count++;
               word ="";
               flag = 0;
           }
           if ( longestWord.size() < word.size()) {
              longestWord = word;
           }
        }
        if (flag == 1){
           cout << "word is \"" << word <<  "\"\n";
           word ="";
           count++;
        }
    }
    cout << "Words: " << count << "\n";
    cout << "Word range: 1-" << longestWord.size() << "\n";
    return 0;
}

