#ifndef SET_H
#define SET_H

#include <string>
using ItemType = std::string;;

class Set
{
private:
    struct Node {
        ItemType nodeVal;
        Node* next;
        Node* prev;
    };
public:
    Set();
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    //added destructor, copy constructor, and assignment operator
    ~Set();
    Set(const Set& other);
    Set& operator= (const Set & rhs);
private:
    Node* head;
    Node* tail;
    int m_size = 0;
    void addtoEmpty(const ItemType& value);
    void addtoFront(const ItemType& value);
    void addtoMiddle(const ItemType& value);
    void addtoRear(const ItemType& value);
};

void unite(const Set& s1, const Set& s2, Set& result);
void butNot(const Set& s1, const Set& s2, Set& result);


#endif
