#include <stdlib.h>
#include <gmodule.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <dataStructs.h>


struct list{
    GArray *array;
};

struct thing {
    int id;
    char *params;
    char *output;
};

void freeThing(gpointer data) {
    THING t = (THING)data;
    free(t -> params);
    free(t -> output);
    free(t);
}

LIST init () {
    LIST l = malloc(sizeof(struct list));
    l -> array = g_array_new(TRUE,FALSE,sizeof(struct thing));
    g_array_set_clear_func (l -> array, freeThing);
    return l;
}

LIST load(LIST l, char* dump){
    return NULL;
}

void clean (GArray *array) {
    g_array_free(array, TRUE);
}
