#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "utlist.h"

#define BUFLEN  20

typedef uint8_t EUI[8];

typedef struct el {
    char bname[BUFLEN];
    EUI eui;
    int endpoint;
    struct el *next, *prev;
} el;

int namecmp(el *a, el *b)
{
    return strcmp(a->bname, b->bname);
}

int epcmp(el *a, el *b)
{
    return a->endpoint - b->endpoint;
}

el *head = NULL;

int main()
{
    el *name;
    el *elt, *tmp1, *tmp2;

    char linebuf[BUFLEN];
    int count;
    FILE *file;

    if ( (file = fopen("input.txt", "r")) == NULL) {
        perror("Can't open: ");
        exit(-1);
    }

    while (fgets(linebuf, BUFLEN, file) != NULL) {
        if ( (name = (el*)malloc(sizeof(el))) == NULL) {
            exit(-1);
        }
        strncpy(name->bname, linebuf, BUFLEN);
        CDL_APPEND(head, name);
    }

    count = 0;
    elt = head;
    do {
        if (elt) {
            printf("%s\n", elt->bname);
            elt = elt->next;
        }
        count++;
    } while(count < 10);
/*
    CDL_FOREACH(head, elt) {
        printf("%s\n", elt->bname);
        break;
    }

    printf("Original\n");
    CDL_FOREACH(head, elt) {
        printf("%s\n", elt->bname);
    }
*/

/*
    do{
        DL_FOREACH(head, elt) {
            printf("%s\n", elt->bname);
            DL_DELETE(head, elt);
            free(elt);
            break;
        }
        printf("while\n");
    }while(elt);
*/
    printf("Sort \n");
    CDL_SORT(head, namecmp);

    CDL_FOREACH(head, elt) {
        printf("%s\n", elt->bname);
    };

    CDL_COUNT(head, elt, count);
    printf("%d number of elements in list.\n", count);

    el etmp;
    memcpy(&etmp.bname, "8\n", 3);
    CDL_SEARCH(head, elt, &etmp, namecmp);
    if (elt) {
        printf("Found!:%s", elt->bname);
    }

    CDL_FOREACH_SAFE(head, elt, tmp1, tmp2) {
        CDL_DELETE(head, elt);
        free(elt);
    }

    fclose(file);

    return 0;
}
