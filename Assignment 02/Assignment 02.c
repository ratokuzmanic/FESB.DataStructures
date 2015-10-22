#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define NAMES_MAX_LENGTH 50

typedef struct Person {
    char FirstName[NAMES_MAX_LENGTH];
    char LastName[NAMES_MAX_LENGTH];
    int YearOfBirth;
    Person* Next;
};

typedef struct Person* Node;

int IsListEmpty(Node);
int IsLastElement(Node);
int IsOutOfRange(Node);

Node CreateHeadNode();
Node CreateNode(char*, char*, int);
Node GetNextElement(Node);
Node GetLastElement(Node);
Node GetElementBySurname(Node, char*);

void InsertElement(Node, Node);
void AddElementToListStart(Node, Node);
void AddElementToListEnd(Node, Node);
void DeleteElementBySurname(Node, char*);
void DeleteAllElements(Node);

void PrintListElement(Node);
void PrintAllListElements(Node);
void UserMenu(Node);

int main()
{
	Node _head = CreateHeadNode();

	UserMenu(_head);

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
	Node _newHead = (Node)malloc(sizeof(Person));
	_newHead->Next = NULL;
	return _newHead;
}

Node CreateNode(char* firstName, char* lastName, int yearOfBirth)
{
	Node _newNode = (Node)malloc(sizeof(Person));

	strcpy(_newNode->FirstName, firstName);
	strcpy(_newNode->LastName, lastName);
	_newNode->YearOfBirth = yearOfBirth;
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

Node GetElementBySurname(Node _head, char* searchQuery)
{
	Node _currentElement = GetNextElement(_head);

	while (!IsOutOfRange(_currentElement))
	{
		if (strcmp(_currentElement->LastName, searchQuery) == 0)
			return _currentElement;
		_currentElement = GetNextElement(_currentElement);
	}		

	return NULL;
}

void InsertElement(Node _previous, Node _next)
{
	_next->Next = _previous->Next;
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

void DeleteElementBySurname(Node _head, char* searchQuery)
{
	Node _currentElement = _head;
	Node _nextElement = GetNextElement(_head);

	while (!IsOutOfRange(_nextElement))
	{
		if (strcmp(_nextElement->LastName, searchQuery) == 0)
		{
			_currentElement->Next = GetNextElement(_nextElement);
			free(_nextElement);
			break;
		}
		_nextElement = GetNextElement(_currentElement);
	}
}

void DeleteAllElements(Node _head)
{
	Node _currentElement = _head->Next;
	Node _nextElement;

	while (!IsOutOfRange(_currentElement))
	{
		_nextElement = _currentElement->Next;
		free(_currentElement);
		_currentElement = _nextElement;
	}

	_head->Next = NULL;
}

void PrintListElement(Node _element)
{
	printf("%s \t %s \t %d\n", _element->FirstName, _element->LastName, _element->YearOfBirth);
}

void PrintAllListElements(Node _head)
{
	if (IsListEmpty(_head))
	{
		printf("Lista je prazna.\n");
		return;
	}

	Node _currentElement = _head->Next;

	while (!IsOutOfRange(_currentElement))
	{ 
		PrintListElement(_currentElement);
		_currentElement = GetNextElement(_currentElement);
	}
}

void UserMenu(Node _head)
{
	int userChoice, yearOfBirth;
	char firstName[NAMES_MAX_LENGTH], lastName[NAMES_MAX_LENGTH];

	printf("\n---MENI---\nIzaberite zeljenu radnju:\n1.\tIzlist liste\n2.\tUnos elementa na pocetak liste\n"
		"3.\tUnos elementa na kraj liste\n4.\tPretrazivanje elementa po prezimenu\n5.\tBrisanje elementa po prezimenu\n"
		"6.\tIzlaz\nUnos:\t");
	scanf("%d", &userChoice);

	switch (userChoice)
	{
		case 1: 
			PrintAllListElements(_head);
			break;
		case 2:
			printf("Unesite element u formatu <ime prezime godina_rodenja>: ");
			scanf("%s %s %d", firstName, lastName, &yearOfBirth);
			AddElementToListStart(_head, CreateNode(firstName, lastName, yearOfBirth));
			break;
		case 3:
			printf("Unesite element u formatu <ime prezime godina_rodenja>: ");
			scanf("%s %s %d", firstName, lastName, &yearOfBirth);
			AddElementToListEnd(_head, CreateNode(firstName, lastName, yearOfBirth));
			break;
		case 4:
			printf("Unesite prezime po kojem ce se pretrazivati: ");
			scanf("%s", lastName);
			PrintListElement(GetElementBySurname(_head, lastName));
			break;
		case 5:
			printf("Unesite prezime osobe koju zelite izbirsati: ");
			scanf("%s", lastName);
			DeleteElementBySurname(_head, lastName);
			break;
		case 6:
			return;
			break;
	}

	UserMenu(_head);
}
