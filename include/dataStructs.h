#ifndef __DATA_STRUCTS__
#define __DATA_STRUCTS__

typedef struct list *LIST;
typedef struct thing *THING;

THING list_get_thing(LIST l, int index);

int thing_get_ref(THING t);
char * thing_get_params(THING t);
char * thing_get_output(THING t);

int list_size(LIST l);
LIST list_new();
LIST example();
LIST list_load(LIST l, char* dump);
void list_free(LIST l);
void test();
void list_print(LIST l);
void list_add(LIST l, int ref, char * params, char * output);

#endif
