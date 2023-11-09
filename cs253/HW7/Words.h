#ifndef WORDS_H_INCLUDED
#define WORDS_H_INCLUDED

#include <string>
#include <ostream>
#include <iostream>
#include <vector>
#include <iterator>
#include <list>


class Words {

// public Constructors

	public:
		Words() = delete;
		Words (const std::string &);
		Words (const Words &);
		Words &operator=(const Words &);

		Words operator+(const Words &) const;
		Words &operator+=(const Words &);
		bool operator== (const Words &) const;
		bool operator!= (const Words &)const; 
		Words &operator--();
		Words operator--(int) ;  
		explicit operator bool() const;
		
				
		struct Shoo{
			std::string first;
			bool second;
		};

		Shoo operator[](int);

		void analyze(std::string);
		[[nodiscard]] size_t size () const ;
		[[nodiscard]] bool empty () ;
		bool get(size_t n, std::string &, bool &) const;
		std::string print() const;
		~Words();


	private:
		std::vector <std::string> words;
		std::vector <bool> es;      
};

std::ostream &operator<<(std::ostream &, const Words &);

#endif

