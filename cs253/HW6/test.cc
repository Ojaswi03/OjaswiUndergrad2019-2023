
#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <fstream>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

class Words {

// public Constructors

	public:
		Words() = delete;
		Words (const std::string &);
		Words (const Words &);
		Words &operator=(const Words &);

		~Words();


		void analyze(std::string);
		[[nodiscard]] size_t size () const ;
		[[nodiscard]] bool empty () ;
		bool get(size_t n, std::string &, bool &) const;
		std::string print() const;


	private:
		std::vector <std::string> words;
		std::vector <bool> es;

};

std::ostream &operator<<(std::ostream &, const Words &);

using namespace std;

Words::Words (const string &input) : words(), es() {
	analyze(input);
}

Words::Words (const Words &copy) : words(copy.words) , es(copy.es) {}


void Words::analyze(string ana){
	size_t counter =0;
	words.clear();
	es.clear();
	string wordformed = "";
	for (size_t i =0; i < ana.size() ; i++) {
		if (ana[i]=='\\'){
			wordformed.push_back(ana[++i]);
			if (es.size() == words.size())
				es.push_back(true);
		}
		else if (ana[i]==' ' || ana[i]=='\n' || ana[i]=='\t' || ana[i]=='\f' || ana[i]=='\v' || ana[i] =='\r'){
			if (counter<i){
				if (es.size() == words.size())
					es.push_back(false);
				words.push_back(wordformed);
				wordformed = "";
			}
			counter = i+1;
		}
		else if (ana[i]=='(' || ana[i] == ')'){
			if (wordformed.empty()){
				wordformed.push_back(ana[i]);
				if (es.size() == words.size())
					es.push_back(false);
				words.push_back(wordformed);
			}
			else {
				if (es.size() == words.size())
						es.push_back(false);

					words.push_back(wordformed);
					wordformed="";
					wordformed.push_back(ana[i]);
					if (es.size() == words.size())
						es.push_back(false);
					words.push_back(wordformed);

				}
			counter = i+1;
			wordformed= "";
		}
		else {
			wordformed.push_back(ana[i]);

		}
	}
	if (!wordformed.empty()){
		if (es.size() == words.size())
			es.push_back(false);
		words.push_back(wordformed);
	}

}

size_t Words::size() const {
	return words.size();
}

bool Words::empty() {
	return words.empty();
}
bool Words::get (size_t i, string &s, bool &b) const{
	if (i > words.size()-1){
		return false;
	}
	s = words[i];
	b =es[i];
	return true;
}


ostream &operator<<(std::ostream &os , const Words &w){
	return os <<w.print();
}

string Words::print() const {
	string sentence = "";
	for (size_t i=0; i< words.size(); i++){
		if (i!= words.size()-1){
			sentence+= words[i] + ",";
		}
		else {
			sentence += words[i];
		}
	}
	return sentence;
}

Words &Words::operator=(const Words &w) = default;

Words::~Words() = default;

int main(int argc, char *argv[]){
	int flags, opt , nsecs , tfnd; 
	vector <string> st;
	string input ,word ;
	flags = 0;
	nsecs = 0;
	tfnd = 0;
	while ((opt = getopt(argc, argv, "nt:")) != -1){
		switch (opt){
			case 'v':
				
				st.push_back()


		}
	}
}