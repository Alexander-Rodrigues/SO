#ifndef __DATA_STRUCTS__
#define __DATA_STRUCTS__

typedef struct list *LIST;
typedef struct thing *THING;

LIST list_new();
LIST example();
LIST list_load(LIST l, char* dump);
void list_clean (LIST l);
void test();
void list_print(LIST l);
void list_add(LIST l, int ref, char * params, char * output);

#endif
