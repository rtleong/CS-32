#include "Set.h"
#include <iostream>
using namespace std;


Set::Set() {
	head = nullptr;
	tail = nullptr;	//initialize all elements of Set to default values
	m_size = 0;
}

Set::~Set() {
	if (empty() == true) return; //no allocated items to deallocate
	if (empty() == false) {
		Node* p = head;
		while (p != nullptr) {	//until past last node, delete each Node
			Node* n = p->next;
			delete p;
			p = n;
		}
	}
	head = nullptr;	//make pointers null to be inaccessible and reset size
	tail = nullptr;
	m_size = 0;
}

Set::Set(const Set& other) {
	m_size = other.m_size;
	if (other.m_size == 0) { //if Set we want to copy is empty, just make a new empty Set.
		head = nullptr;
		tail = nullptr;
		return;
	}
	
	head = new Node;	//starts our linked list, sets prev to null and sets temp p to our new head
	head->prev = nullptr;
	Node* p = head;

	for (Node* i = other.head; i->next != nullptr; i = i->next){ //iterates through desired other node
		Node* n = new Node;										//and sett vals, next, and prev pointers
		p->nodeVal = i->nodeVal;
		p->next = n;
		n->prev = p;
		p = n;
	}
	p->nodeVal = other.tail->nodeVal; //handles last node copying and sets tail pointer
	p->next = nullptr;

	tail = p;
}
Set& Set::operator=(const Set& rhs) {
	if (this != &rhs) {	//as long as rhs and lhs are not equal
		Set temp(rhs);	//make temp Set of rhs
		swap(temp);	//swap "this->" and temp so rhs and lhs switch
	}
	return *this;
}

bool Set::empty() const {
	return (head==nullptr);
}

int Set::size() const {
	return m_size;
}

bool Set::insert(const ItemType& value) {
	if (contains(value)) return false;
	if (empty()) { //add to list if there are no values in list
		addtoEmpty(value);
		return true;
	}
	else if (head->nodeVal > value) {	//add to front if there are items present in the list
		addtoFront(value); //add to front if not empty, but still should be ordered first
		return true;
	}
	else if (value > tail->nodeVal){
		addtoRear(value); //add to rear if value is greater than all in Set
		return true;
	}
	else {
		addtoMiddle(value); //loop through and find where value > prev node and < next node if any
		return true;
	}
	return false; //return false if we do not insert for any reason.
}

bool Set::erase(const ItemType& value) {
	if (empty()) return false;
	if (head->nodeVal == value) {//if desired item is first in linked list, erase 1st item. 
		Node* killMe = head;
		head = killMe->next;
		delete killMe;
		m_size = m_size - 1;
		return true;
	}
	Node *p = head;
	while (p != nullptr) {
		if (p->next != nullptr && p->next->nodeVal == value) {	//stop right above the desired node to delete
			break;
		}
		p = p->next;
	}
	if (p != nullptr) {	
		Node* killMe = p->next;
		p->next = killMe->next;
		if (p->next == nullptr) { //not sure, should reset tail to new end of list
			tail = p;
		}
		delete killMe;
		m_size--;
		return true;
	}
	return false;

}


bool Set::contains(const ItemType& value) const {
	if (head == nullptr) return false;	//empy list return false
	if (head->nodeVal == value) return true; //checks first value in list 
	Node *p = head;
	while (p != nullptr) {
		if (p->nodeVal == value) {	//iterates until past list then returns true if value found
			return true;
		}
		p = p->next;
	}
	return false;	//otherwise return false
}

bool Set::get(int pos, ItemType& value) const {
	if (pos < 0 || pos >= m_size) return false; //if out of bounds position return false
	Node* p = head;
	for (int i = 0; i < pos; i++) { //loop until p points to position of value i want to copy
		p = p->next;
	}
	value = p->nodeVal; //copy the node value into our value reference
	return true;
}

void Set::swap(Set& other) {
	Node* p = other.head; //swap head pointers
	other.head = head;
	head = p;

	Node* n = other.tail;	//swap tail pointers
	other.tail = tail;
	tail = n;

	int temp = m_size;	//swap size values
	m_size = other.m_size;
	other.m_size = temp;
}

void unite(const Set& s1, const Set& s2, Set& result) {
	if (&s1 == &result) return;
	int tempsize = result.size();

	for (int i = 0; i < tempsize; i++) { //erasing any elements in the result set 
		ItemType temp;
		result.get(0, temp); //use 0 here because if we erase the first item, then the next item is get(0, x)
		result.erase(temp);

	}
	for (int k = 0; k < s1.size(); k++) { //insert into result all s1 values 
		ItemType temp;
		s1.get(k, temp);
		result.insert(temp);
	}
	for (int j = 0; j < s2.size(); j++) { //insert into result all unique s2 values
		ItemType temp;
		s2.get(j, temp);
		result.insert(temp); //insert checks for unique values already
	}
}

void butNot(const Set& s1, const Set& s2, Set& result) {
	Set u; //use a temporary set instead of deleting elements in result
	ItemType temp;

	for (int i = 0; i < s1.size(); i++) { //iterate through and get all values in s1 that are not contained in s2
		s1.get(i, temp);
		if (!(s2.contains(temp))) {
			u.insert(temp); //insert into temp set
		}
	}
	result = u; //make result set == to temporary set
}

void Set::addtoEmpty(const ItemType& value) {
	Node* p = new Node;
	p->nodeVal = value;
	p->next = nullptr; //sets pointers both = to nullptr
	p->prev = nullptr;
	head = p; //head and tail point at the SAME node because only one node
	tail = p;
	m_size++; //increment size
}

void Set::addtoFront(const ItemType& value) {
	Node* p = new Node;
	p->nodeVal = value; //sets up new node
	p->next = head;
	p->prev = nullptr; //if inserted in first spot, prev is nullptr
	head->prev = p;	// adjusts pointers, since we checked for empty, we can assume our head points at a value
	head = p;		//so accessing head prev should not prove erroneous
	m_size++; //increments size
}

void Set::addtoMiddle(const ItemType& value) {
	Node* p = head;
	while (p->next != nullptr) {
		if (p->nodeVal <= value && value <= p->next->nodeVal) { //iterate through and find node above target node
			break;
		}
		p = p->next;
	}
	if (p->next != nullptr) {	//reptitive check for last node just in case
		Node* n = new Node;
		n->nodeVal = value;	//sets up new node with correct value and pointers
		n->next = p->next;
		n->prev = p;
		Node* temp = p->next;	//creates temporary node so previous of current p is still accessible after
		p->next = n;			//changing p->next
		temp->prev = n;
		m_size++; //increment size if successful
	}
}

void Set::addtoRear(const ItemType& value) {
	Node* p = new Node;
	p->nodeVal = value; //sets up new node
	p->next = nullptr;
	p->prev = tail;
	tail->next = p; //updates the previous last value to point to our NEW last value
	tail = p;		//sets tail pointer to new last value
	m_size++;		//increment size
}
