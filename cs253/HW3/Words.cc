#include "Words.h"
#include <string>
#include <vector>
#include <iostream>
#include <ostream>

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
