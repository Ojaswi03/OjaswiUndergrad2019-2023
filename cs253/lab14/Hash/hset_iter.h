#ifndef HSET_ITER_H_INCLUDED
#define HSET_ITER_H_INCLUDED

#include <list>
#include <vector>
#include <iterator>	// for advance()

// Each hset_iter contains a reference to its associated hash,
// and an int indicating progress within the hash.

template <typename T>
class hset_iter {
  private:
    using table_t = typename std::vector<std::list<T>>;
    const table_t &parent;  // reference to the hash table we’re iterating over
    unsigned int num;		    // how far along we are.  0=first item
    unsigned int nu;            // How deep we are in the list 0 = First Item.

  public:
    hset_iter(table_t &table, unsigned int n , unsigned int li) : parent(table), num(n), nu(li) { }

    bool operator==(const hset_iter &rhs) const {
	return num == rhs.num;
    }

    bool operator!=(const hset_iter &rhs) const {
	return !(*this == rhs);
    }

    // Return a pointer to the num'th element,
    // where num==0 is the first element.

    T operator*() const {
	// unsigned int remaining = num;
	// int i;
    auto it = parent[num].begin();
    advance(it,nu); 
	return *it;
   
	// First, find the right list:
	// for (i=0; parent[i].size() <= remaining; i++)
	//     remaining -= parent[i].size();
	// // // Second, find the right slot within that list:
	// auto it = parent[i].begin();
	// advance(it,num);  // go forward that many steps
	// return *it;


    }

    // Pre-increment
    void operator++() {
        // num vecotr size : nu is each bucket size
        if (nu >= parent[num].size()-1){
            nu = 0;
            ++num ;
        }
        else{
            ++nu;
        }
    }
};

#endif /* HSET_ITER_H_INCLUDED */
