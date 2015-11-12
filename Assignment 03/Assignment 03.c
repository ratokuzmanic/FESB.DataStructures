#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define NAMES_MAX_LENGTH 50
#define BUFFER_MAX_SIZE 150
#define FILE_NAME "lista.txt"

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
int IsInAlphabetOrder(char*, char*);
int IsLastNameIdentical(char*, char*);
int IsEmptyRow(char*);

Node CreateHeadNode();
Node CreateNode(char*, char*, int);
Node GetNextElement(Node);
Node GetPreviousElement(Node, char*);
Node GetLastElement(Node);
Node GetElementBySurname(Node, char*);

void InsertElement(Node, Node);
void AddElementToListStart(Node, Node);
void AddElementToListEnd(Node, Node);
void DeleteElementBySurname(Node, char*);
void DeleteAllElements(Node);

void SwapElementWithNextOne(Node, Node);
void SortList(Node);

void PrintListElement(Node);
void PrintAllListElements(Node);
void SaveListElementsToFile(Node, char*);
void ReadListElementsFromFile(Node, char*);

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

int IsInAlphabetOrder(char* first, char* second)
{
	return strcmp(first, second) < 0;
}

int IsLastNameIdentical(char* firstName, char* secondName)
{
	return strcmp(firstName, secondName) == 0;
}

int IsEmptyRow(char* content)
{
	return strlen(content) == 0 || strcmp(content, "\n") == 0;
}

Node CreateHeadNode()
{
	Node _newHead = (Node)malloc(sizeof(Person));
	if (IsOutOfRange(_newHead)) return NULL;

	_newHead->Next = NULL;
	return _newHead;
}

Node CreateNode(char* firstName, char* lastName, int yearOfBirth)
{
	Node _newNode = (Node)malloc(sizeof(Person));
	if (IsOutOfRange(_newNode)) return NULL;

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

Node GetPreviousElement(Node _head, char* searchQuery)
{
	Node _currentElement = GetNextElement(_head);

	while (!IsLastElement(_currentElement))
	{
		if (IsLastNameIdentical(GetNextElement(_currentElement)->LastName, searchQuery))
			return _currentElement;
		_currentElement = GetNextElement(_currentElement);
	}

	return _head;
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
		if (IsLastNameIdentical(_currentElement->LastName, searchQuery))
			return _currentElement;
		_currentElement = GetNextElement(_currentElement);
	}

	return NULL;
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

void DeleteElementBySurname(Node _head, char* searchQuery)
{
	Node _currentElement = _head;
	Node _nextElement = GetNextElement(_head);

	while (!IsOutOfRange(_nextElement))
	{
		if (IsLastNameIdentical(_nextElement->LastName, searchQuery))
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

void SwapElementWithNextOne(Node _head, Node _element)
{
	Node _previousElement = GetPreviousElement(_head, _element->LastName);
	Node _nextElement = GetNextElement(_element);

	_previousElement->Next = _nextElement;
	_element->Next = GetNextElement(_nextElement);
	_nextElement->Next = _element;

	_element = _nextElement;
}

void SortList(Node _head)
{
	Node _endElement = NULL;
	Node _currentElement;

	while (GetNextElement(_head) != _endElement)
	{
		_currentElement = GetNextElement(_head);
		while (GetNextElement(_currentElement) != _endElement)
		{
			if (!IsInAlphabetOrder(_currentElement->LastName, GetNextElement(_currentElement)->LastName))
				SwapElementWithNextOne(_head, _currentElement);
			_currentElement = GetNextElement(_currentElement);
		}
		_endElement = _currentElement;
	}
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

	Node _currentElement = GetNextElement(_head);
	while (!IsOutOfRange(_currentElement))
	{
		PrintListElement(_currentElement);
		_currentElement = GetNextElement(_currentElement);
	}
}

void SaveListElementsToFile(Node _head, char* fileName)
{
	FILE* listLog;
	listLog = fopen(fileName, "w");
	if (listLog == NULL) return;

	Node _currentElement = GetNextElement(_head);
	while (!IsOutOfRange(_currentElement))
	{
		fprintf(listLog, "%s %s %d\n", _currentElement->FirstName, _currentElement->LastName, _currentElement->YearOfBirth);
		_currentElement = GetNextElement(_currentElement);
	}

	fclose(listLog);
}

void ReadListElementsFromFile(Node _head, char* fileName)
{
	FILE* listLog;
	int yearOfBirth;
	char firstName[NAMES_MAX_LENGTH], lastName[NAMES_MAX_LENGTH];
	char buffer[BUFFER_MAX_SIZE];

	listLog = fopen(fileName, "r");
	if (listLog == NULL) return;

	while (!feof(listLog))
	{
		fgets(buffer, BUFFER_MAX_SIZE, listLog);
		if (!IsEmptyRow(buffer))
		{
			sscanf(buffer, "%s %s %d", firstName, lastName, &yearOfBirth);
			AddElementToListEnd(_head, CreateNode(firstName, lastName, yearOfBirth));
			memset(buffer, 0, strlen(buffer));
		}		
	}

	fclose(listLog);
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
		"Dodavanje elementa ispred nekog elementa",
		"Dodavanje elementa izad nekog elementa",
		"Sortiranje liste",
		"Upisivanje liste u datoteku",
		"Ucitavanje liste iz datoteke",
		"Izlaz" };
	for (i = 0; i < sizeof(options) / sizeof(char*); i++)
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
			printf("Unesite element u formatu <ime prezime godina_rodenja>: ");
			scanf("%s %s %d", firstName, lastName, &yearOfBirth);
			printf("Unesite prezime osobe ispred koje zelite ubaciti element: ");
			scanf("%s", searchQuery);
			InsertElement(GetPreviousElement(_head, searchQuery), CreateNode(firstName, lastName, yearOfBirth));
			break;
		case 7:
			printf("Unesite element u formatu <ime prezime godina_rodenja>: ");
			scanf("%s %s %d", firstName, lastName, &yearOfBirth);
			printf("Unesite prezime osobe nakon koje zelite ubaciti element: ");
			scanf("%s", searchQuery);
			InsertElement(GetElementBySurname(_head, searchQuery), CreateNode(firstName, lastName, yearOfBirth));
			break;
		case 8:
			SortList(_head);
			break;
		case 9:
			SaveListElementsToFile(_head, FILE_NAME);
			break;
		case 10:
			ReadListElementsFromFile(_head, FILE_NAME);
			break;
		case 11:
			return;
			break;
	}

	PrintUserMenu(_head);
}
