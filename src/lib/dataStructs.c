#include <stdlib.h>
#include <gmodule.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <dataStructs.h>

/*! \struct list
 * \brief A list containing a GPtrArray and an int for size.
 *
 * Defines a list of pointers, in this case, a list of THINGs.
 */
struct list{
    int size;/**< \brief The list's size */
    GPtrArray *array;/**< \brief The array containg the "list" itself \detailed \n Using glib this array stores pointers to THING and grows in size as more elements are inserted. \n  <a href="https://developer.gnome.org/glib/stable/glib-Pointer-Arrays.html">GPtrArray \n \t</a>*/
};

/*! \struct thing
    \brief A struct which houses a command's parameters, it's, if parsed, output, reference and sline value.

    Defines a list of pointers, in this case, a list of THINGs.
*/
struct thing {
    int sline;/**< \brief An int which indicates if the present member is part of a sequence (SameLINE) */
    int ref;/**< \brief Indicates which thing's output this one should use as input. \detailed \n Is relative to the current position */
    char *params;/**< \brief  The command's parameters. \detailed \n Saves the entirety of the received command, with the exception of sequences which are treated as normal commands which use the previous' output.*/
    char *output;/**< \brief  The output after being processed by list_process"("LIST list")"*/
};

/**
 * Creates a new THING
 * @param  ref    how many steps back the desired output is
 * @param  params function parameters
 * @param  output processed output
 * @param  sline  is part of line, 0 if head of line
 * @return        a new THING.
 */
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

/**
 * Returns a t's reference nummber
 * @param  t a pointer to the thing
 * @return   a reference number
 */
int thing_get_ref(THING t){
    return t -> ref;
}

/**
 * Returns a t's sline
 * @param  t a pointer to the thing
 * @return   an sline number
 */
int thing_get_sline(THING t){
    return t -> sline;
}

/**
 * Returns a t's parameters
 * @param  t a pointer to the thing
 * @return   a string with parameters
 */
char * thing_get_params(THING t){
    char *a = malloc(strlen(t -> params) + 1);
    return strcpy(a,t -> params);
}

/**
 * Returns a t's parameters
 * @param  t a pointer to the thing
 * @return   a string with the output
 */
char * thing_get_output(THING t){
    if (t -> output == NULL) return NULL;
    char *a = malloc(strlen(t -> output) + 1);
    return strcpy(a,t -> output);
}

/**
 * Frees a thing's memory allocation
 * @param data a pointer to the thing
 */
void thing_free(gpointer data) {
    THING t = (THING)data;
    free(t -> params);
    if (t -> output != NULL) free(t -> output);
    free(t);
}

/**
 * Prints out a thing
 * @param data      thing pointer
 * @param user_data pointer to user passed data
 */
void thing_print(gpointer data, gpointer user_data) {
    THING t = (THING)data;
    printf("Ref: %d\nParams: %s\nOutPut: %s\n", t -> ref, t -> params, t -> output);
}

/**
 * Creates a new, empty list
 * @return an empty list
 */
LIST list_new () {
    LIST l = malloc(sizeof(struct list));
    l -> array = g_ptr_array_new_with_free_func(thing_free);
    l -> size = 0;
    return l;
}

/**
 * Adds an element to the list with thing_new"("int ref, char * params, char * output, int sline")""
 * @param l      target list
 * @param  ref    how many steps back the desired output is
 * @param  params function parameters
 * @param  output processed output
 * @param  sline  is part of line, 0 if head of line
 */
void list_add(LIST l, int ref, char * params, char * output, int sline) {
    (l -> size)++;
    g_ptr_array_add(l -> array, thing_new(ref,params,output,sline));
}

/**
 * Returns a list's size
 * @param  l a list pointer
 * @return   list size
 */
int list_size(LIST l){
    return l -> size;
}

/**
 * Gets a thing from list from position
 * @param  l     a list pointer
 * @param  index position index
 * @return       a thing from the list
 * /note Assumes the caller won't acess beyond the size
 */
THING list_get_thing(LIST l, int index) {
    THING t = g_ptr_array_index(l -> array, index);
    return thing_new(t -> ref, t -> params, t -> output, t -> sline);
}

/**
 * Changes a thing's output given it's position on the list
 * @param l      a list pointer
 * @param index  position index
 * @param output a pointer to a thing or NULL if it doesn't exist
 */
void list_set_thing_output(LIST l, int index, char * output){
    THING t = g_ptr_array_index(l -> array, index);
    t -> output = output;
}

/**
 * Prints a list by calling void thing_print"("gpointer data, gpointer user_data")" on every member of list
 * @param l a pointer to a list
 */
void list_print(LIST l) {
    printf("List size: %d\n",l -> size);
    g_ptr_array_foreach(l -> array, thing_print, NULL);
}

/**
 * Frees a list's memory allocation
 * @param l [description]
 */
void list_free(LIST l) {
    g_ptr_array_free(l -> array, TRUE);
    free(l);
}
