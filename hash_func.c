#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hash.h"

struct _student *new_st (FILE* student)
{
	struct _student *st;
	st = malloc (sizeof(struct _student));
	if (st == NULL)
		return NULL;
	int i = fscanf (student, "%s%s%s%f%f%d%f", st->sn, st->fn, st->gender, &(st->h), &(st->w), &(st->gr), &(st->as));
	//printf("fscanf ret %d\n", i);
	if (i < 7)
		return NULL;
	return st;
}

unsigned int hashtab_hash (char* key)
{
	unsigned int h = 0;
	char *p;
	double c;

	for (p = key; *p != 0; p++)
		h = h * MUL + (unsigned int)*p - 1;

	return (unsigned int)floor (modf((double)h * GOLDS, &c) * (double)SIZE);
}

void hashtab_init (struct listnode** hashtab)
{
	for (int i = 0; i < SIZE; i++)
		hashtab[i] = NULL;
}

int hashtab_add (struct listnode** hashtab, char* key, struct _student* st)
{
	unsigned int index = hashtab_hash(key);
	struct listnode* data_st;
	data_st = malloc (sizeof(struct listnode));
	if (data_st == NULL)
		return 1;

	data_st->key = malloc(strlen(key)*sizeof(char));
	if (data_st->key == NULL)
		return 2;
	strncpy (data_st->key, key, strlen(key));

	data_st->st = *st;

	if (hashtab[index] == NULL)
		data_st->next = NULL;
	else
		data_st->next = hashtab[index];
	hashtab[index] = data_st;
	return 0;
}

struct listnode* hashtab_lookup (struct listnode** hashtab, char* key)
{
	unsigned int index = hashtab_hash(key);
	struct listnode* node;
	node = hashtab[index];
	if (node == NULL)
		return NULL;

	while (node != NULL)
	{
		if (!strcmp(node->key, key))
		{
			printf("Hash %d: Key %s: %s %s %s ", index, node->key, (node->st).sn, (node->st).fn, (node->st).gender);
			printf("%f %f %d %f\n", (node->st).h, (node->st).w, (node->st).gr, (node->st).as);
			return node;
		}
		node = node->next;
	}
	return NULL;
}

int hashtab_del (struct listnode** hashtab, char* key)
{
	int index = hashtab_hash(key);
	if (hashtab[index] == NULL)
		return 1;
	struct listnode *prev = NULL, *to_del = hashtab[index];
	while (to_del != NULL)
	{
		if (!strcmp(to_del->key, key))
		{
			if (prev != NULL)
				prev->next = to_del->next;
			else 
				hashtab[index] = to_del->next;
			free (to_del);
			return 0;
		}
		prev = to_del;
		to_del = to_del->next;
	}
	return 2;
}

void hashtab_printf (struct listnode** hashtab)
{
	int i = 0;
	while (i < SIZE)
	{
		if (hashtab[i] != NULL)
		{
			struct listnode* temp = hashtab[i];
			printf("\nHash %d:\n", i);
			while (temp != NULL)
			{
				printf("Key %s: %s %s %s ", temp->key, (temp->st).sn, (temp->st).fn, (temp->st).gender);
				printf("%f %f %d %f\n", (temp->st).h, (temp->st).w, (temp->st).gr, (temp->st).as);
				temp = temp->next;
			}
		}
		else 
			printf ("\nHash %d is empty\n", i);

		i++;
	}
}

void interface ()
{
	int cnt = 0, error, examp = 0;
	char name[25] = {0}, filename[256] = {0};
	struct _student *st;
	struct listnode *error_l;
	FILE* fp = NULL;
	hashtab_init(hashtab);
	printf ("\nHello!\n"
			"This programm can structure the information about the students\n"
			"Please, before you start, check, that your file written in English and contains\n"
			"the student's name, surname, gender, height, weight, "
			"group number, average score\n!!!in exactly this order separated by space/ tabs/ enters!!!\n"
			"Do you want to see an example?\n"
			"1 - yes\nelse numb - no\n");
	scanf("%d", &examp);

	if (examp == 1)
		printf("\nFor example:\nIvan\nIvanov\nm\n175\n75\n121\n4.0\n");	
	
	printf ("\nEnter the file name with extension: ");
	scanf ("%s", filename);
	fp = fopen (filename, "r");
	//fp = fopen ("students.txt", "r");

	printf ("\nWhat do you want to do?\n"
			"0 - stop the programm\n"
			"1 - add the student\n"
			"2 - delete the student\n"
			"3 - find the student\n"
			"4 - print all the elements\n");

	while (1)
	{
		scanf ("%d", &cnt);
		if (cnt == 0)
			break;
		else if (cnt == 1)
		{
			error = feof (fp);
			if (error != 0)
				printf("You have riched the end of file, the student was not added\n");
			
			else 
			{
				st = new_st (fp);
				if (st != NULL)
				{
					/*printf("\nEnter the key for this student: ");
					scanf ("%s", name);*/
					error = hashtab_add (hashtab, st->sn/*name*/, st);
					if (!error)
						printf ("Student was added.\n");
					else if (error)
						printf ("Memmory allocation error. Error code: %d\n", error);
				}
				else 
					printf ("Memmory allocation error\n");//printf("You have riched the end of file, the student was not added\n");
			}
		}
		else if (cnt == 2)
		{
			printf("\nEnter the key of node what you want to delete: ");
			scanf("%s", name);
			error = hashtab_del(hashtab, name);
			if (error)
				printf ("There is no students with this key (surname). Code error: %d\n", error);
			else
				printf("The data about student with key (surname) %s was deleted\n", name);
		}
		else if (cnt == 3)
		{
			printf("\nEnter the key of node what you want to find: ");
			scanf("%s", name);
			error_l = hashtab_lookup(hashtab, name);
			if (error_l == NULL)
				printf ("There is no students with this key (surname). Code error: %d\n", error);
		}
		else if (cnt == 4)
			hashtab_printf(hashtab);
	
		else if (cnt == 5)
		{
			printf ("\n0 - stop the programm\n"
					"1 - add the student\n"
					"2 - delete the student\n"
					"3 - find the student\n"
					"4 - print all the elements\n");
		}
		else
			printf("\nYou entered incorrect numb.\n");

		printf("\nEnter the numb again. If you do not remember the commands press 5.\n");
	}
}