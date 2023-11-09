#ifndef WORDS_H_INCLUDED
#define WORDS_H_INCLUDED

#include <string>
#include <ostream>
#include <iostream>
#include <vector>


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

#endif
