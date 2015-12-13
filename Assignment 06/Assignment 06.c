#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define LOWER_LIMIT_ELEMENT_RANGE 10
#define UPPER_LIMIT_ELEMENT_RANGE 100

typedef struct Element {
	int Value;
	Element* Next;
};

typedef struct Element* Node;

enum ListTypes {
	Stack = 1,
	Queue = 2
};

int IsListEmpty(Node);
int IsLastElement(Node);
int IsOutOfRange(Node);

Node CreateHeadNode();
Node CreateNode(int);
Node GetNextElement(Node);
Node GetLastElement(Node);

void InsertElement(Node, Node);
void AddElementToListStart(Node, Node);
void AddElementToListEnd(Node, Node);
void DeleteFirstElementOfList(Node);
void DeleteAllElements(Node);

int GenerateRandomNumberInRange(int, int);
void Filter_ListTypeDependentPush(Node, int);

void Push(Node, int);
void Pop(Node);

void PrintListElement(Node);
void PrintAllListElements(Node);

void PrintOperationsMenu(Node, int);

int main()
{
	int userChoice;
	Node _head = CreateHeadNode();

	srand(time(NULL));

	printf("\tMENI\n1.\tStog\n2.\tRed\nOdabir:\t");
	scanf("%d", &userChoice);

	PrintOperationsMenu(_head, userChoice);

	printf("\tREZULTAT:\n");
	PrintAllListElements(_head);

	DeleteAllElements(_head);
	free(_head);

	return 0;
}

int IsListEmpty(Node _head)
{
	return _head->Next == NULL;
}

int IsLastElement(Node _element)
{
	return _element->Next == NULL;
}

int IsOutOfRange(Node _element)
{
	return _element == NULL;
}

Node CreateHeadNode()
{
	Node _newHead = (Node)malloc(sizeof(Element));
	if (IsOutOfRange(_newHead)) return NULL;

	_newHead->Next = NULL;
	return _newHead;
}

Node CreateNode(int value)
{
	Node _newNode = (Node)malloc(sizeof(Element));
	if (IsOutOfRange(_newNode)) return NULL;

	_newNode->Value = value;
	_newNode->Next = NULL;

	return _newNode;
}

Node GetNextElement(Node _element)
{
	return _element->Next;
}

Node GetLastElement(Node _head)
{
	Node _lastElement = _head;

	while (!IsLastElement(_lastElement))
		_lastElement = GetNextElement(_lastElement);

	return _lastElement;
}

void InsertElement(Node _previous, Node _next)
{
	_next->Next = GetNextElement(_previous);
	_previous->Next = _next;
}

void AddElementToListStart(Node _head, Node _element)
{
	InsertElement(_head, _element);
}

void AddElementToListEnd(Node _head, Node _element)
{
	InsertElement(GetLastElement(_head), _element);
}

void DeleteFirstElementOfList(Node _head)
{
	Node _firstElement = GetNextElement(_head);

	_head->Next = GetNextElement(_firstElement);

	free(_firstElement);
}

void DeleteAllElements(Node _head)
{
	while (!IsListEmpty(_head))
		DeleteFirstElementOfList(_head);
}

int GenerateRandomNumberInRange(int lowerLimit, int upperLimit)
{
	return rand()%(upperLimit - lowerLimit + 1) + lowerLimit;
}

void Filter_ListTypeDependentPush(Node _head, int filterValue)
{
	if (filterValue == ListTypes::Stack)
		AddElementToListStart(_head, CreateNode(
			GenerateRandomNumberInRange(LOWER_LIMIT_ELEMENT_RANGE, UPPER_LIMIT_ELEMENT_RANGE)
		));

	if (filterValue == ListTypes::Queue)
		AddElementToListEnd(_head, CreateNode(
			GenerateRandomNumberInRange(LOWER_LIMIT_ELEMENT_RANGE, UPPER_LIMIT_ELEMENT_RANGE)
		));
}

void Push(Node _head, int listType)
{
	Filter_ListTypeDependentPush(_head, listType);
}

void Pop(Node _head)
{
	if (!IsListEmpty(_head))
		DeleteFirstElementOfList(_head);
}

void PrintListElement(Node _element)
{
	printf("%d\n", _element->Value);
}

void PrintAllListElements(Node _head)
{
	if (IsListEmpty(_head))
	{
		printf("Lista je prazna.\n");
		return;
	}

	Node _currentElement = GetNextElement(_head);
	while (!IsOutOfRange(_currentElement))
	{
		PrintListElement(_currentElement);
		_currentElement = GetNextElement(_currentElement);
	}
}

void PrintOperationsMenu(Node _head, int listType)
{
	int userChoice;

	printf("\tOperacija\n1.\tPush\n2.\tPop\nOdabir:\t");
	scanf("%d", &userChoice);

	if (userChoice == 1)
		Push(_head, listType);
	else if (userChoice == 2)
		Pop(_head);
	else
		return;

	PrintOperationsMenu(_head, listType);
}
