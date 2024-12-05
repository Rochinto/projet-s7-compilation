/*
 *  Attribut.c
 *
 */

#include "Attribut.h"

/* HERE COMES YOUR CODE */
#include <stdlib.h>
#include <string.h>

int sp = 0;
int fun_sp = 1;

void empile(){
    if(is_in_function()) fun_sp++;
    else sp++;
}

void depile(){
    if(is_in_function()) fun_sp--;
    else sp--;
    
    if(sp < 0){
        fprintf(stderr,"Error : negative stack pointeur\n");
        exit(-1);
    }if(fun_sp < 1){
        fprintf(stderr,"Error : negative (or null) function stack pointeur\n");
        exit(-1);
    }
}

symb_value_type create_symb(){
    symb_value_type temp;
    if(is_in_function()) temp.offset=fun_sp-1;
    else temp.offset=sp-1;
    temp.argc = -1;
    return temp;
}

// LABELS //
// deprecated
/* 
int label_counter = 0;
int label_stack_size = 0;
int label_stack[MAX_STACK_SIZE];

void check_stack_empty(){
    if(label_stack_size <= 0){ fprintf(stderr,"Error : label stack is empty\n"); exit(-1); }
}

void check_stack_overflow(){
    if(label_stack_size >= MAX_STACK_SIZE){ fprintf(stderr,"Error : label stack overflow (size limit = %d)\n", MAX_STACK_SIZE); exit(-1); }
}

int top_label(){
    check_stack_empty();
    return label_stack[label_stack_size-1];
}

int push_label(){
    check_stack_overflow();
    label_stack[label_stack_size++] = label_counter++;
    return top_label();
}

int pop_label(){
    int temp = top_label();
    label_stack_size--;
    return temp;
}*/




// FUNCTIONS //
int is_in_fun = 0; //Bool
int argc = 0;

int is_in_function(){
    return is_in_fun;
}

int get_argc(){
    return argc;
}

void enter_function(){
    is_in_fun = 1;
    fun_sp = 1;
    argc = 0;
}

void leave_function(){
    is_in_fun = 0;
}

symb_value_type create_argument(){
    if(!is_in_function()){
        fprintf(stderr,"Error : cannot create argument while not in a function definition\n");
        exit(-1);
    }if(argc+1 != fun_sp){
        fprintf(stderr,"Error : cannot create argument (corrupted function stack pointeur)\n");
        exit(-1);
    }
    symb_value_type temp;
    temp.offset=argc+1;
    temp.argc = -1;
    argc++;
    fun_sp++;
    return temp;
}

symb_value_type create_function(){
    /*if(!is_in_function()){
        fprintf(stderr,"Error : cannot create argument while not in a function definition\n");
        exit(-1);
    }*/
    symb_value_type temp;
    temp.offset=-1;
    temp.argc = argc;
    return temp;
}

int is_symb_function(symb_value_type symb){
    return (symb.argc >= 0);
}


// FILES //

char* get_ml_file_name(char* file_path){
    if(file_path == NULL){fprintf(stderr, "Error : file path cannot be NULL\n"); exit(-1);}

    size_t path_len = strlen(file_path);
    if((path_len < 4) || strcmp(file_path+(path_len-3), ".ml")){
        fprintf(stderr, "Error : file name must finish with extension .ml\n"); exit(-1);
    }
    
    int last_slash_pos = path_len-5; //En supposant que le nom fait au moins un caractère, on part alors de path_len-5
    //Obtention du dernier '/' (en partant de la fin)
    while((last_slash_pos >= 0) && (file_path[last_slash_pos]!='/')) last_slash_pos--;
    
    char* file_name = NULL;
    size_t final_size = 0;
    if(last_slash_pos < 0){
        final_size = path_len-3;
        last_slash_pos = -1;
    }else
        final_size = path_len-last_slash_pos-4;
    
    file_name = malloc(sizeof(char)*(final_size+1));
    strncpy(file_name, file_path+last_slash_pos+1, final_size);
    file_name[final_size] = '\0';
    
    return file_name;
}

char* get_file_name_with_extension(char* file_name, char* extension){
    size_t name_len = strlen(file_name);
    size_t ext_len = strlen(extension);
    char* new_name = malloc(sizeof(char)*(name_len+ext_len+1));

    strcpy(new_name, file_name);
    strcpy(new_name+name_len, extension);

    return new_name;
}