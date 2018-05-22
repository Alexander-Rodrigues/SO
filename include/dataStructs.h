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

/*! \var typedef struct list *LIST
    \brief A list containing a GPtrArray and an int for size.

    Defines a list of pointers, in this case, a list of THINGs.
*/
/*! \var typedef struct thing *THING
    \brief A struct which houses a command's parameters, it's, if parsed, output, reference and sline value.

    Defines a list of pointers, in this case, a list of THINGs.
*/
#ifndef __DATA_STRUCTS__
#define __DATA_STRUCTS__

typedef struct list *LIST;
typedef struct thing *THING;

int thing_get_sline(THING t);
int thing_get_ref(THING t);
char * thing_get_params(THING t);
char * thing_get_output(THING t);

THING list_get_thing(LIST l, int index);
void list_set_thing_output(LIST l, int index, char * output);
int list_size(LIST l);
LIST list_new();
LIST list_load(LIST l, char* dump);
void list_free(LIST l);
void list_print(LIST l);
void list_add(LIST l, int ref, char * params, char * output, int sline);

#endif
