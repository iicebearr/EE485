#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {BUCKET_COUNT = 1024};

struct Node {
    char *key;
    int value;
    struct Node *next;
};

struct Table {
    struct Node *array[BUCKET_COUNT];
};

unsigned int hash(const char *x) {
    int i;
    unsigned int h = 0U;
    for (i=0; x[i]!='\0'; i++)
        h = h * 65599 + (unsigned char)x[i];
    return h % BUCKET_COUNT;
}

struct Table *Table_create(void) {
    struct Table *t;
    t = (struct Table*)calloc(1, sizeof(struct Table));
    return t;
}

void Table_add(struct Table *t, const char *key, int value) {
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));
    int h = hash(key);
    p->key = malloc(strlen(key) + 1);
    strcpy(p->key, key);
    p->value = value;
    p->next = t->array[h];
    t->array[h] = p;
}

int Table_search(struct Table *t, const char *key, int *value) {
    struct Node *p;
    int h = hash(key);
    for (p = t->array[h]; p != NULL; p = p->next)
        if (strcmp(p->key, key) == 0) {
        *value = p->value; return 1;
        }
    return 0;
}

int Table_remove(struct Table *t, const char *key) {
    struct Node *p, *prev = NULL;
    int h = hash(key);
    for (p = t->array[h]; p != NULL; prev = p, p = p->next)
        if (strcmp(p->key, key) == 0) {
            if (prev == NULL) t->array[h] = p->next;
            else prev->next = p->next;
            free(p->key);
            free(p);
            return 1;
        }
    return 0;
}

void Table_free(struct Table *t) {
    struct Node *p;
    struct Node *nextp;
    int b;
    for (b = 0; b < BUCKET_COUNT; b++)
        for (p = t->array[b]; p != NULL; p = nextp) {
            nextp = p->next;
            free(p->key);
            free(p);
        }
    free(t);
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