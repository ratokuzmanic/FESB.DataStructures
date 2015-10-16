#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX_BUFFER 50

typedef struct {
	char FirstName[50];
	char LastName[50];
	int Score;
} Student;

int CountRows(char*);
int EnlistStudents(char*, Student*, int);
void OutputData(Student*, int, int);

int main(void)
{
	int numberOfRows, maxScore;

	Student* _students;

	numberOfRows = CountRows("rezultati.txt");
	if (numberOfRows == -1)
	{
		printf("Problem kod citanja datoteke.\n");
		return 0;
	}
	_students = (Student*)malloc(sizeof(Student) * numberOfRows);

	maxScore = EnlistStudents("rezultati.txt", _students, numberOfRows);
	if (maxScore == -1)
	{
		printf("Problem kod citanja datoteke.\n");
		return 0;
	}
	else if (maxScore == 0)
	{
		printf("Ne mozemo dijeliti s nula, stoga ne vrijedi relativno ocijenjivanje.\n");
		return 0;
	}

	OutputData(_students, numberOfRows, maxScore);

	free(_students);
	return 0;
}

int CountRows(char* fileName)
{
	FILE *file;
	char* buffer;
	int numberOfRows = 0;

	file = fopen(fileName, "r");
	if (file == NULL) return -1;

	while (!feof(file))
	{
		buffer = (char*)malloc(sizeof(char) * MAX_BUFFER);

		fgets(buffer, MAX_BUFFER, file);
		if (strlen(buffer) > 0)
			numberOfRows++;

		free(buffer);
	}

	fclose(file);
	return numberOfRows;
}

int EnlistStudents(char* fileName, Student* _students, int numberOfStudents)
{
	FILE *file;
	int counter = 0;
	int maxScore = 0;

	file = fopen(fileName, "r");
	if (file == NULL) return -1;

	while (!feof(file))
	{
		fscanf(file, "%s %s %d", _students[counter].FirstName, _students[counter].LastName, &_students[counter].Score);

		if (_students[counter].Score > maxScore)
			maxScore = _students[counter].Score;

		counter++;
	}

	fclose(file);
	return maxScore;
}

void OutputData(Student* _students, int numberOfStudents, int maxScore)
{
	int i;
	for (i = 0; i < numberOfStudents; i++)
		printf("%s \t %s \t %d \t %.2f\n", _students[i].FirstName, _students[i].LastName, _students[i].Score, (float)_students[i].Score / maxScore * 100.0);
}
