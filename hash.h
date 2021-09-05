#include <stdio.h>
#define SIZE 3
#define GOLDS 0.6180339887
#define MUL 7

struct _student
{
char sn[256];
char fn[256];
char gender[7];
float h;
float w;
int gr;
float as;
};

struct listnode 
{
char *key;
struct _student st;
struct listnode *next;
};

struct listnode* hashtab[SIZE];

struct _student *new_st (FILE* student);

unsigned int hashtab_hash (char* key);

void hashtab_init (struct listnode** hashtab);

int hashtab_add (struct listnode** hashtab, char* key, struct _student* st);

struct listnode* hashtab_lookup (struct listnode** hashtab, char* key);

int hashtab_del (struct listnode** hashtab, char* key);

void hashtab_printf (struct listnode** hashtab);

void interface ();