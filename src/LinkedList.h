//
// Created by forouzan_a on 11/16/21.
//

#ifndef UNTITLED_LINKEDLIST_H
#define UNTITLED_LINKEDLIST_H

#include <iostream>
#include "LinkedListNode.h"
using namespace std;

class LinkedList {
    private:
	LinkedListNode *head;
	LinkedListNode *last;
	int sz;

    public:
	LinkedList() :head{nullptr}, last{nullptr}, sz{0} {}

	LinkedListNode *get_head() {return this->head;}
	LinkedListNode *get_last() {return this->last;}
	int get_size() {return this->sz;}

	void add_node(void *);
	void del_node(void *);
};


#endif //UNTITLED_LINKEDLIST_H
