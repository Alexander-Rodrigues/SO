/*! \file dataStructs.h
    \brief Header file with data structure API

    This header files exists to ensure encapsulation and provide an API to work with LIST and THING.
*/
/*! \var typedef struct list *LIST
    \brief Creates a type name for a struct list pointer;
*/
/*! \var typedef struct thing *THING
    \brief Creates a type name for a struct thing pointer;
*/
#ifndef __DATA_STRUCTS__
#define __DATA_STRUCTS__

typedef struct list *LIST;
typedef struct thing *THING;

int thing_get_sline(THING t);
int thing_get_ref(THING t);
char * thing_get_comment(THING t);//pos texto do ficheiro
char * thing_get_params(THING t);
char * thing_get_output(THING t);

THING list_get_thing(LIST l, int index);
char * list_get_pre(LIST l);//pre texto do ficheiro
void list_set_pre(LIST l, char * pre);
void list_set_thing_output(LIST l, int index, char * output);
int list_size(LIST l);
LIST list_new();
LIST list_load(LIST l, char* dump);
void list_free(LIST l);
void list_print(LIST l);
void list_add(LIST l, int ref, char * params, char * output, int sline, char * comment);

#endif
