#include <string>
#include <iostream>

#include "LinkedList.h"
#include "LinkedListNode.h"
#include "err.h"

using namespace std;

enum class Operation {
    SUM,
    SUB,
    DIV,
    MUL,
    NOUN
};

/* ooo: operand1 operation operand2 */
struct ooo {
    float operand1, operand2;
    Operation operation;
};

enum Operation ParseOperation(char op) {
	switch (op) {
		case '+':
			return Operation::SUM;
		case '-':
			return Operation::SUB;
		case '/':
			return Operation::DIV;
		case '*':
			return Operation::MUL;
		default:
			return Operation::NOUN;
	}
}

int ValidateInput(string &inputLine)
{
	int index = 0;

	if (!isdigit(inputLine[index++]))
		return INPUT_ERROR;
	while (isdigit(inputLine[index]))
		index++;

	while (inputLine[index] != '\0') {
		if (ParseOperation(inputLine[index++]) == Operation::NOUN)
			return INPUT_ERROR;

		if (!isdigit(inputLine[index++]))
			return INPUT_ERROR;
		while (isdigit(inputLine[index]))
			index++;
	}

	return RET_SUCCESS;
}

int ParsedInput(string &input, LinkedList *list) {
	unsigned long parserPosition = 0;
	char *parser, operation;

	if (input == "exit")
		return EXIT;
	if (ValidateInput(input) != RET_SUCCESS)
		return INPUT_ERROR;

	while (parserPosition != -1) {
		auto *o = (struct ooo *) malloc(sizeof(struct ooo));
		parser = &input[parserPosition];

		int ret = sscanf(parser, "%f%c%f", &o->operand1, &operation, &o->operand2);
		o->operation = ParseOperation(operation);
		if (ret != 3) {
			free(o);
			break;
		}

		list->add_node(o);
		parserPosition = input.find(operation, parserPosition) + 1;
	};

	return RET_SUCCESS;
}

float Calc(struct ooo *o) {
	switch (o->operation) {
		case Operation::SUM:
			return o->operand1 + o->operand2;
		case Operation::SUB:
			return o->operand1 - o->operand2;
		case Operation::DIV:
			return o->operand1 / o->operand2;
		case Operation::MUL:
			return o->operand1 * o->operand2;
	}
}

void UpdateLRNode(LinkedListNode *node, float value) {
	if (node->getPrev() != nullptr)
		((struct ooo *) node->getPrev()->getData())->operand2 = value;

	if (node->getNext() != nullptr)
		((struct ooo *) node->getNext()->getData())->operand1 = value;
}

float CalcList(LinkedList *list) {
	float result;

	/* First iteration for MUL & DIV calculate, second for SUM and SUB. */
	for (int iterationNum = 0; iterationNum < 2; ++iterationNum) {
		for (LinkedListNode *node = list->get_head(), *nnode = node->getNext();
		     node != nullptr; node = nnode, nnode = nnode->getNext()) {
			auto o = (struct ooo *) node->getData();

			if (iterationNum == 0) {
				if (o->operation == Operation::MUL || (o->operation == Operation::DIV))
					result = Calc(o);
				else
					continue;
			}

			if (iterationNum == 1) {
				if (o->operation == Operation::SUM || (o->operation == Operation::SUB))
					result = Calc(o);
				else
					continue;
			}

			UpdateLRNode(node, result);
			list->del_node(o);
		}
	}

	return result;
}

int main() {
	string inputStr;
	auto inputList = new LinkedList;
	int ret;

	while (true) {
		cout << "> ";
		cin >> inputStr;

		ret = ParsedInput(inputStr, inputList);
		switch (ret) {
			case RET_SUCCESS:
				break;
			case INPUT_ERROR:
				cout << "Invalid input" << endl;
				continue;
			case EXIT:
				return 0;
			default:
				cout << "Unknown error!" << endl;
		}
		std::cout << ((inputList->get_size() == 0) ? stof(inputStr,nullptr) :
		CalcList(inputList)) << std::endl;
	}
}