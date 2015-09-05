#ifndef HOSPITAL_LIST_H
#define HOSPITAL_LIST_H

#include <stdio.h>

typedef struct list LIST;
typedef struct node NODE;

LIST *create_list(void);
void delete_list(LIST**);
void print_list(LIST*);
LIST *get_list(FILE*);
LIST *get_special_list(LIST*);

#endif
