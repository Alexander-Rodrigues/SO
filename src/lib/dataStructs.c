#include <stdlib.h>
#include <gmodule.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <dataStructs.h>


struct list{
    GPtrArray *array;
};

struct thing {
    int ref;
    char *params;
    char *output;
};

THING thing_new(int ref, char * params, char * output){
    THING t = malloc(sizeof(struct thing));
    char * a = malloc(strlen(params)+1);
    sprintf(a, "%s", params);
    char *b = NULL;

    if (output != NULL) {
        b = malloc(strlen(params)+1);
        sprintf(b, "%s", output);
    }

    t -> ref = ref;
    t -> params = a;
    t -> output = b;
    return t;
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
    return l;
}

LIST list_load(LIST l, char* dump){
    return NULL;
}

void list_add(LIST l, int ref, char * params, char * output) {
    g_ptr_array_add(l -> array, thing_new(ref,params,output));
}

void list_print(LIST l) {
    g_ptr_array_foreach(l -> array, thing_print, NULL);
}

void list_clean(LIST l) {
    g_ptr_array_free(l -> array, TRUE);
}

void test() {
    THING t = thing_new(-1,"ls",NULL);
    LIST l = list_new();
    g_ptr_array_add(l -> array,t);
    list_clean(l);

}

LIST example (LIST l) {
    THING t = thing_new(0,"ls",NULL);
    g_ptr_array_add(l -> array,t);
    THING t2 = thing_new(1,"sort",NULL);
    g_ptr_array_add(l -> array,t2);
    THING t3 = thing_new(1,"head -1",NULL);
    g_ptr_array_add(l -> array,t3);
    return l;
}
