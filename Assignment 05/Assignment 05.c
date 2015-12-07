#include <stdio.h>
#include <malloc.h>

#define FILE_NAME_FIRST "prva_lista.txt"
#define FILE_NAME_SECOND "druga_lista.txt"

typedef struct Element {
	int Value;
	Element* Next;
};

typedef struct Element* Node;

int IsListEmpty(Node);
int IsLastElement(Node);
int IsOutOfRange(Node);
int IsListElement(Node, int);

Node CreateHeadNode();
Node CreateNode(int);
Node GetNextElement(Node);
Node GetLastElement(Node);

void InsertElement(Node, Node);
void AddElementToListStart(Node, Node);
void AddElementToListEnd(Node, Node);
void AddElementToListAscending(Node, Node);
void CopyAllUniqueElementsInOrder(Node, Node);
void DeleteAllElements(Node);

void Filter_AddUniqueElementsToList(Node, Node, Node, int);

Node UnionOfTwoLists(Node, Node);
Node IntersectionOfTwoLists(Node, Node);

void PrintListElement(Node);
void PrintAllListElements(Node);
void ReadListElementsFromFile(Node, char*);

void PrintUserMenu(Node, Node);

int main()
{
	Node _headOfFirst = CreateHeadNode();
	Node _headOfSecond = CreateHeadNode();

	ReadListElementsFromFile(_headOfFirst, FILE_NAME_FIRST);
	ReadListElementsFromFile(_headOfSecond, FILE_NAME_SECOND);

	PrintUserMenu(_headOfFirst, _headOfSecond);

	DeleteAllElements(_headOfFirst);
	DeleteAllElements(_headOfSecond);
	free(_headOfFirst);
	free(_headOfSecond);

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

int IsListElement(Node _head, int value)
{
	Node _currentElement = GetNextElement(_head);

	while (!IsOutOfRange(_currentElement))
	{
		if (_currentElement->Value == value)
			return 1;
		_currentElement = GetNextElement(_currentElement);
	}

	return 0;
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

void AddElementToListAscending(Node _head, Node _element)
{
	if (IsListEmpty(_head))
	{
		AddElementToListStart(_head, _element);
		return;
	}

	Node _currentElement = _head;
	while (!IsLastElement(_currentElement))
	{
		if (GetNextElement(_currentElement)->Value > _element->Value)
		{
			InsertElement(_currentElement, _element);
			return;
		}
		_currentElement = GetNextElement(_currentElement);
	}

	AddElementToListEnd(_head, _element);
}

void CopyAllUniqueElementsInOrder(Node _sourceHead, Node _destinationHead)
{
	Node _currentElement = GetNextElement(_sourceHead);

	while (!IsOutOfRange(_currentElement))
	{
		if(!IsListElement(_destinationHead, _currentElement->Value))
			AddElementToListAscending(_destinationHead, CreateNode(_currentElement->Value));
		_currentElement = GetNextElement(_currentElement);
	}
}

void DeleteAllElements(Node _head)
{
	Node _currentElement = GetNextElement(_head);
	Node _nextElement;

	while (!IsOutOfRange(_currentElement))
	{
		_nextElement = GetNextElement(_currentElement);
		free(_currentElement);
		_currentElement = _nextElement;
	}

	_head->Next = NULL;
}

void Filter_AddUniqueElementsToList(Node _sourceHead, Node _searchHead, Node _destinationHead, int filterValue)
{
	Node _currentElement = GetNextElement(_sourceHead);
	while (!IsOutOfRange(_currentElement))
	{
		if (IsListElement(_searchHead, _currentElement->Value) == filterValue)
			AddElementToListAscending(_destinationHead, CreateNode(_currentElement->Value));
		_currentElement = GetNextElement(_currentElement);
	}
}

Node UnionOfTwoLists(Node _headOfFirst, Node _headOfSecond)
{
	Node _headOfUnion = CreateHeadNode();

	CopyAllUniqueElementsInOrder(_headOfFirst, _headOfUnion);
	Filter_AddUniqueElementsToList(_headOfSecond, _headOfUnion, _headOfUnion, 0);

	return _headOfUnion;
}

Node IntersectionOfTwoLists(Node _headOfFirst, Node _headOfSecond)
{
	Node _headOfIntersection = CreateHeadNode();

	Filter_AddUniqueElementsToList(_headOfFirst, _headOfSecond, _headOfIntersection, 1);

	return _headOfIntersection;
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

void ReadListElementsFromFile(Node _head, char* fileName)
{
	FILE* listLog;
	int value;

	listLog = fopen(fileName, "r");
	if (listLog == NULL) return;

	while (!feof(listLog))
	{
		fscanf(listLog, "%d", &value);
		AddElementToListEnd(_head, CreateNode(value));
	}

	fclose(listLog);
}

void PrintUserMenu(Node _headOfFirst, Node _headOfSecond)
{
	Node _resultHead;
	int userChoice;

	printf("\tMENI\n1.\tUnija dviju lista\n2.\tPresjek dviju lista\nOdabir:\t");
	scanf("%d", &userChoice);

	if (userChoice == 1)
		_resultHead = UnionOfTwoLists(_headOfFirst, _headOfSecond);
	else if (userChoice == 2)
		_resultHead = IntersectionOfTwoLists(_headOfFirst, _headOfSecond);
	else
		return;

	printf("Rezultat operacije:\n");
	PrintAllListElements(_resultHead);

	DeleteAllElements(_resultHead);
	free(_resultHead);
}
