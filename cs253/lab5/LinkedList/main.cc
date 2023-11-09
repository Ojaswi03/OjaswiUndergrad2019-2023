#include <iostream>
#include "ll.h" 

using namespace std;

int main() {
    LinkedList list;
    unsigned int i;
    int option;

    for (bool done = false; !done; ) {
	cout << "Choose your operation:\n"
	     << "1. insert     2. remove    3. exit    4. print\n";

	cin >> option;

	switch (option) {
	    case 1:
		cout << "Enter the number to insert\n";
		cin >> i;
		list.insert(i);
		break;
	    case 2:
		if (list.remove(i))
		    cout << "removed " << i << '\n';
		else
		    cout << "No numbers in the list\n";
		break;
	    case 3:
                list.del();
                done = true;
		break;
            case 4:
                cout<< list << "\n";
                break;

 	}
    }

    return 0;
}

