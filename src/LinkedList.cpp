//
// Created by forouzan_a on 11/16/21.
//

#include "LinkedList.h"


void LinkedList::add_node(void *data)
{
	if (this->sz == 0) {
		auto node = new LinkedListNode(nullptr, nullptr, data);
		this->head = this->last = node;
		this->sz++;
	} else {
		auto node = new LinkedListNode(this->last, nullptr, data);
		node--->getPrev()->setNext(node);
		this->last = node;
		this->sz++;
	}
}

void LinkedList::del_node(void *data)
{
	if (!data && this->sz == 0)
		return;

	for (LinkedListNode *node = this->head;
	     node != nullptr; node = node->getNext()) {
		if (node->getData() == data) {
			if (node != this->head && node != this->last) {
				node->getPrev()->setNext(node->getNext());
				node->getNext()->setPrev(node->getPrev());
			}
			if (node == this->head) {
				this->head = node->getNext();
				if (node->getNext() != nullptr)
					node->getNext()->setPrev(nullptr);
			}
			if (node == this->last) {
				this->last = node->getPrev();
				if (node->getPrev() != nullptr)
					node->getPrev()->setNext(nullptr);
			}

			delete(node);
			this->sz--;
		}
	}
}