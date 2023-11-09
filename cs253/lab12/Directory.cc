#include "Directory.h"
#include <iostream>
#include<string>
using namespace std;

// The directory iterator pre-fetches the name.  That is, readdir()
// is called when you first create the iterator, and upon ++.
//
// An end() iterator is designated by a null pointer for its DIR *.
// When readdir() fails, we set our pointer to null.

DirectoryIterator::DirectoryIterator(DIR *dp_arg , const string &mat) : dp(dp_arg), ma(mat){ // fix3
    ++*this;				// get that first entry
}

// Get the next entry in the directory (that we like) and
// put it in the member variable name.

bool DirectoryIterator::wanted(string &a){    // fix2

    
    if (ma == ""){  // fix3
        if (a!= "." && a != ".."){
            return true;
        }
        else{
            return false;
        }
    }
    else {
        return !(a.find(ma)==string::npos) && (a!= "." && a != "..");
    }
    
}

DirectoryIterator &DirectoryIterator::operator++() {	// pre-increment
    while (auto p = readdir(dp)) {	// Read a directory entry.
	name = p->d_name;		// C-string ⇒ C++ string
    if (wanted(name)){
        return *this;     // fix2
    }
    /*
	if (name == ".")		// Stupid entry for current directory?
	    continue;			// Nobody wants that.
	if (name == "..")		// Stupid entry for parent directory?
	    continue;			// Nobody wants that.
	return *this;			// Everything else, I like!
    */
    }
    dp = nullptr;			// readdir failed; don’t try again.
    return *this;
}

string DirectoryIterator::operator*() const {
    return name;			// Fetched in a previous ++.
}

bool DirectoryIterator::operator!=(const DirectoryIterator &rhs) const {
    return dp != rhs.dp;
}


//////////////// Directory methods

Directory::Directory(const char dirname[], string const &mat) : dp(opendir(dirname)), ma(mat) { // fix3

    if (!dp){                           // fix1
        throw runtime_error("The file is not in the list of files");
    }
}
   

Directory::~Directory() {
    if (dp)				// Only if opendir() succeeded:
	closedir(dp);			//   should we close it.
}

Directory::iterator Directory::begin() const {
    return iterator(dp,ma);
}

Directory::iterator Directory::end() const {
    return iterator();
}
