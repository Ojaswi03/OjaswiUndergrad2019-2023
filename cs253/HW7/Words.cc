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


Words Words:: operator+(const Words &a) const{
	Words z = *this;
	z+=a;
	return z;


}	
Words & Words::operator+=(const Words &b){
	for (size_t i =0; i< b.size(); ++i){
		words.push_back(b.words[i]);
		es.push_back(b.es[i]);
	}	
	return *this;

}
bool Words::operator== (const Words &c) const { 
	for (size_t i =0; i < c.words.size(); i++){
		if (c.words.size() == words.size()){
			if (c.words[i] != words[i]){
				return false;
			}
		}
		else {
			return false;
		}
	}
	return true;
}
bool Words::operator!= (const Words &d) const{
	return !(*this == d);	
}
// pre decrement
Words & Words::operator--(){   // --Words()
	for (size_t i = 0; i < words.size(); ++i){ 

		if (words[i].size() == 0){
			words.erase(words.begin() + i);
			es.erase(es.begin() + i);
			--i;
		}
		else {
			words[i] = words[i].substr(0 , words[i].size()-1); // hello
		}
	} 
	return *this;

}
//post decrement
Words Words::operator--(int) {
	const auto save = *this;
	--*this;
	return save;

}
Words:: operator bool() const{
	return (words.size() >0);
}

Words::Shoo Words:: operator[](int e){
	Shoo t;
	t.first = words[e];
	t.second = es[e];
	return t;
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


