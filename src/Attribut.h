/*
 *  Attribut.h
 *
 *  Module defining teh type of attributes in 
 *  symbol table.
 *
 */

#ifndef ATTRIBUT_H
#define ATTRIBUT_H

#include <stdio.h>

//typedef int symb_value_type;
typedef struct{
   int offset;
   int argc;
} symb_value_type;

 /* Dummy definition of symbol_value_type.
    Could be instead a structure with as many fields
    as needed for the compiler such as:
    - name in source code
    - name (or position in the stack) in the target code
    - type (if ever)
    - other info....
 */

symb_value_type create_symb();
void empile();
void depile();

// LABELS //
// deprecated
/*int push_label();
int top_label();
int pop_label();*/

// FUNCTIONS //
int is_in_function();
int get_argc();
void enter_function();
void leave_function();
symb_value_type create_argument();
symb_value_type create_function();
int is_symb_function(symb_value_type);

// FILES //
char* get_ml_file_name(char* file_path);
char* get_file_name_with_extension(char* file_name, char* extension);

#endif
