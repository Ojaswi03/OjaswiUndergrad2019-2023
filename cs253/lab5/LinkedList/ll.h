
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <iostream>
using namespace std;
class LinkedList {
  public:
    LinkedList();
    bool insert(unsigned uiData);
    bool remove(unsigned &pData);
    friend ostream& operator<< (ostream &os, const LinkedList &list);
    void del();
  private:
    struct Link {
        Link() = default;
        unsigned m_uiData;
        Link *m_pNext;
        Link(unsigned int uiData, Link *pNext);
    } *m_pHead;
};

#endif /* LINKED_LIST_H */ 
