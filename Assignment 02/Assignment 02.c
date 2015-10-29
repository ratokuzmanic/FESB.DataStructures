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

void PrintUserMenuChoices();
void PrintUserMenu(Node);

int main()
{
	Node _head = CreateHeadNode();

	PrintUserMenu(_head);

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
		_currentElement = GetNextElement(_currentElement);
		_nextElement = GetNextElement(_currentElement);
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

void PrintUserMenuChoices()
{
	int i;
	char* options[] = { 
		"Izlist liste",
		"Unos elementa na pocetak liste",
		"Unos elementa na kraj liste",
		"Pronalazak elementa po prezimenu",
		"Brisanje elementa po prezimenu",
		"Izlaz" };
	for (i = 0; i < 6; i++)
		printf("%d.\t%s\n", i + 1, options[i]);
}

void PrintUserMenu(Node _head)
{
	int userChoice, yearOfBirth;
	char firstName[NAMES_MAX_LENGTH], lastName[NAMES_MAX_LENGTH], searchQuery[NAMES_MAX_LENGTH];

	printf("\tMENI\n");
	PrintUserMenuChoices();

	printf("Odabir:\t");
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
			scanf("%s", searchQuery);
			PrintListElement(GetElementBySurname(_head, searchQuery));
			break;
		case 5:
			printf("Unesite prezime osobe koju zelite izbirsati: ");
			scanf("%s", searchQuery);
			DeleteElementBySurname(_head, searchQuery);
			break;
		case 6:
			return;
			break;
	}

	PrintUserMenu(_head);
}
