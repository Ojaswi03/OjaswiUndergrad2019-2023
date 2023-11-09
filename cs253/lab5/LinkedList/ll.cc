#include "ll.h" 
#include <cstdlib>
#include <iostream>
using namespace std;
LinkedList::Link::Link(unsigned uiData, Link *pNext): m_uiData(uiData), m_pNext(pNext){}

LinkedList::LinkedList(): m_pHead(nullptr) {}


bool LinkedList::insert(unsigned uiData) {
    Link* new_link = new Link;		// Get a new node.

    *new_link = Link(uiData, m_pHead);      // Fill it with data.
    m_pHead = new_link;			// Put it at the head.

    return true;				// Indicate success.
}

bool LinkedList::remove(unsigned &pData) {
    if (!m_pHead)				// Empty list?
	return false;				// Indicate failure.

    Link *temp = m_pHead;			// Point to the first node.
    m_pHead = m_pHead->m_pNext;	                // Remove the first node.
    pData = temp->m_uiData;			// Obtain first node’s data.
    delete temp;                                // Managing leak
    return true;				// Indicate success.
}

void LinkedList::del(){
          while(m_pHead){
             remove(m_pHead->m_uiData);
          }
          cout << "done!" << "\n";
}

ostream& operator<<(ostream &os, const LinkedList &list){
     os << "data in the Listt: " << "\n";
     LinkedList temp;
     temp.m_pHead = list.m_pHead;

     while(temp.m_pHead){
        os << temp.m_pHead->m_uiData << "\n";
        temp.m_pHead = temp.m_pHead->m_pNext;
    }
    return os;
}

