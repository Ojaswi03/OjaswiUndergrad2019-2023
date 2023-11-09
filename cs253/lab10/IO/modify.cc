#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
	cerr << "usage: " << argv[0] << " infile outfile\n";
	return 1;
    }
    fstream in(argv[1]);
    if (!in) {
	cerr << argv[0] << ": can't open " << argv[1] << '\n';
	return 2;
    }

    size_t a = 0;
    for (string line; getline(in, line); ) {       
	    for (size_t pos=0; (pos=line.find("Trump", pos)) != line.npos; ){
	        line.replace(pos, 5, "Biden");
            in.seekp(a+pos);   
            in << "Biden";
            in.seekp(in.tellp());
        }
        a= in.tellg();
    }
    return 0;
}

// Note that line.npos ≡ string::npos.
// It’s a static constant, part of the string class.
// It’s a number that means “Sorry, I couldn’t find that.”
