#include <stdlib.h>
#include <gmodule.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <dataStructs.h>


struct list{
    int size;
    GPtrArray *array;
};

struct thing {
    int sline;
    int ref;
    char *params;
    char *output;
};

THING thing_new(int ref, char * params, char * output, int sline){
    THING t = malloc(sizeof(struct thing));
    char * a = malloc(strlen(params)+1);
    sprintf(a, "%s", params);
    char *b = NULL;

    if (output != NULL) {
        b = malloc(strlen(output)+1);
        sprintf(b, "%s", output);
    }

    t -> sline = sline;
    t -> ref = ref;
    t -> params = a;
    t -> output = b;
    return t;
}

int thing_get_ref(THING t){
    return t -> ref;
}

char * thing_get_params(THING t){
    char *a = malloc(strlen(t -> params) + 1);
    return strcpy(a,t -> params);
}

char * thing_get_output(THING t){
    if (t -> output == NULL) return NULL;
    char *a = malloc(strlen(t -> output) + 1);
    return strcpy(a,t -> output);
}

void thing_free(gpointer data) {
    THING t = (THING)data;
    free(t -> params);
    if (t -> output != NULL) free(t -> output);
    free(t);
}

void thing_print(gpointer data, gpointer user_data) {
    THING t = (THING)data;
    printf("Ref: %d\nParams: %s\nOutPut: %s\n", t -> ref, t -> params, t -> output);
}

LIST list_new () {
    LIST l = malloc(sizeof(struct list));
    l -> array = g_ptr_array_new_with_free_func(thing_free);
    l -> size = 0;
    return l;
}

LIST list_load(LIST l, char* dump){
    return NULL;
}

void list_add(LIST l, int ref, char * params, char * output, int sline) {
    (l -> size)++;
    g_ptr_array_add(l -> array, thing_new(ref,params,output,sline));
}

int list_size(LIST l){
    return l -> size;
}

THING list_get_thing(LIST l, int index) {
    THING t = g_ptr_array_index(l -> array, index);
    return thing_new(t -> ref, t -> params, t -> output, t -> sline);
}

void list_set_thing_output(LIST l, int index, char * output){
    THING t = g_ptr_array_index(l -> array, index);
    t -> output = output;
}

void list_print(LIST l) {
    printf("List size: %d\n",l -> size);
    g_ptr_array_foreach(l -> array, thing_print, NULL);
}

void list_free(LIST l) {
    g_ptr_array_free(l -> array, TRUE);
    free(l);
}
