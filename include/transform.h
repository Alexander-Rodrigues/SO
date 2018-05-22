/*! \file transform.h
    \brief Header file with functions to transform notebook data into dataStructs data

    This header files exists to ensure encapsulation and provide an API to work with dataStructs data bases.
*/
#ifndef __TRANSFORM__
#define __TRANSFORM__

void noteToList(int argc, char *argv[], LIST list);
void listToNote(int argc, char *argv[], LIST list);

#endif