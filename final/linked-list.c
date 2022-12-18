#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *key;
    int value;
    struct Node *next;
};

struct Table {
    struct Node *first;
};

struct Table *Table_create(void) {
    struct Table *t;
    t = (struct Table *) malloc(sizeof(struct Table));
    t->first = NULL;
    return t;
}

void Table_add(struct Table *t, const char *key, int value)
{
    struct Node *p = (struct Node*)malloc(sizeof(struct Node*));
    /* we omit error checking here (e.g., p == NULL) */
    p->key = malloc(strlen(key) + 1);
    strcpy(p->key, key);
    p->value = value;
    p->next = t->first;
    t->first = p;
}

int Table_search(struct Table *t, const char *key, int *value)
{
    struct Node *p;
    for (p = t->first; p != NULL; p = p->next)
        if (strcmp(p->key, key) == 0) {
            *value = p->value;
            return 1;
    }
    return 0;
}

void Table_free(struct Table *t) {
    struct Node *p;
    struct Node *nextp;
    for (p = t->first; p != NULL; p = p->next) {
            nextp = p->next;
        free(p->key);
        free(p);
        free(p);
    }
    free(t);
}

int Table_remove(struct Table *t, const char *key) {
    struct Node *p, *prev = NULL;
    for (p = t->first; p != NULL; p = p->next) {
        if (strcmp(p->key, key) == 0) {
            if (prev == NULL)
                t->first = p->next;
            else
                prev->next = p->next;
            free(p);
            return 1;
        }
        prev = p;
    }
    return 0;
}

int main() {
    struct Table* t;
    int value;
    int found;

    t = Table_create();
    Table_add(t, "Ruth", 3);
    Table_add(t, "Gerhig", 4);
    Table_add(t, "Mantle", 7);

    found = Table_search(t, "Gerhig", &value);
    printf("[+] Table_search: found=%d, value=%d\n", found, value);
    
    Table_remove(t, "Gerhig");

    found = Table_search(t, "Gerhig", &value);
    printf("[+] Table_search: found=%d, value=%d\n", found, value);
    Table_free(t);
}