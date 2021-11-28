//
// Created by forouzan_a on 11/16/21.
//

#ifndef UNTITLED_LINKEDLISTNODE_H
#define UNTITLED_LINKEDLISTNODE_H


class LinkedListNode {
    private:
	LinkedListNode *priv;
	LinkedListNode *next;
	void *data;

    public:
	LinkedListNode(LinkedListNode *p, LinkedListNode *n, void *d)
		:priv{p}, next{n}, data{d} {}
	LinkedListNode *getPrev() {return ((this == nullptr) ? nullptr : this->priv);}
    LinkedListNode *getNext() {return ((this == nullptr) ? nullptr : this->next);}
	void *getData() {return this->data;}

	void setPrev(LinkedListNode *p) {this->priv = p;}
	void setNext(LinkedListNode *n) {this->next = n;}
	void setData(void *d) {this->data = d;}
};


#endif //UNTITLED_LINKEDLISTNODE_H
