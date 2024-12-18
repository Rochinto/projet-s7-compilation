/*
 *  Table des symboles.c
 *
 *  Created by Janin on 12/10/10.
 *  Copyright 2010 LaBRI. All rights reserved.
 *
 */
#include "Table_des_symboles.h"

#include <stdlib.h>
#include <stdio.h>

extern FILE * file_in;
extern FILE * file_out;


/* The storage structure is implemented as a linked chain */

/* linked element def */


typedef struct elem {
	sid symbol_name;
	symb_value_type symbol_value;
	struct elem * next;
} elem;

/* linked chain initial element */
static elem * storage=NULL;

void check_sid_valid(sid symb_id){
	if (!sid_valid(symb_id)) {
		fprintf(stderr,"Error : symbol id %p is not have no valid sid\n",symb_id);
		exit(-1);
	}
}

/* get the symbol value of symb_id from the symbol table */
symb_value_type get_symbol_value(sid symb_id) {
	elem * tracker=storage;

	/* (optionnal) check that sid is valid symbol name and exit error if not */
	check_sid_valid(symb_id);

	/* look into the linked list for the symbol value */
	while (tracker) {
		if (tracker -> symbol_name == symb_id) return tracker -> symbol_value; 
		tracker = tracker -> next;
	}
    
	/* if not found does cause an error */
	fprintf(stderr,"Error : symbol %s have no defined value\n",(char *) symb_id);
	exit(-1);
};

/* set the value of symbol symb_id to value */
symb_value_type set_symbol_value(sid symb_id,symb_value_type value) {

	elem * tracker;
	
	/* (optionnal) check that sid is valid symbol name and exit error if not */
	check_sid_valid(symb_id);
		
	/* look for the presence of symb_id in storage */
	
	tracker = storage;
	while (tracker) {
		if (tracker -> symbol_name == symb_id) {
			tracker -> symbol_value = value;
			return tracker -> symbol_value;
		}
		tracker = tracker -> next;
	}
	
	/* otherwise insert it at head of storage with proper value */
	
	tracker = malloc(sizeof(elem));
	tracker -> symbol_name = symb_id;
	tracker -> symbol_value = value;
	tracker -> next = storage;
	storage = tracker;
	return storage -> symbol_value;
}

symb_value_type add_symbol_value(sid symb_id,symb_value_type value){
	elem * tracker;
	
	/* (optionnal) check that sid is valid symbol name and exit error if not */
	check_sid_valid(symb_id);
	
	/* insert it at head of storage with proper value */
	tracker = malloc(sizeof(elem));
	tracker -> symbol_name = symb_id;
	tracker -> symbol_value = value;
	tracker -> next = storage;
	storage = tracker;
	return storage -> symbol_value;
}

void remove_symbol_value(sid symb_id){
	elem * tracker;
	elem * last;
	
	/* (optionnal) check that sid is valid symbol name and exit error if not */
	check_sid_valid(symb_id);
	
	/* insert it at head of storage with proper value */
	tracker = storage;
	if(!tracker) return; //Cas où la liste est vide

	if (tracker -> symbol_name == symb_id) { //Cas où le 1er élément correspond
		storage = tracker -> next;
		free(tracker);
		return;
	}

	//Sinon cas général
	last = tracker;
	tracker = tracker -> next;

	while (tracker) {
		if (tracker -> symbol_name == symb_id) {
			last -> next = tracker -> next;
			free(tracker);
			return;
		}
		last = tracker;
		tracker = tracker -> next;
	}

	//Cas où il n'y a pas de valeur
}

void remove_last_n_symbols(int n){
	elem * tracker;
	elem * last;

	tracker = storage;
	if(!tracker) return; //Cas où la liste est vide

	//Sinon cas général
	last = tracker;
	tracker = tracker -> next;

	while (tracker && (n > 0)) {
		free(last);
		n--;
		last = tracker;
		tracker = tracker -> next;
	}
	if(!tracker && (n > 0)){
		free(last);
		storage = NULL;
		return;
	}//else
	storage = last;
	return;
}

void remove_all_symbols(){
	remove_last_n_symbols(__INT_MAX__);
}

int has_value(sid symb_id){
	elem * tracker=storage;
	while (tracker) {
		if (tracker -> symbol_name == symb_id) return 1; 
		tracker = tracker -> next;
	}
	return 0;
}

int has_multiple_values(sid symb_id){
	elem * tracker=storage;
	int count = 0;
	while (tracker && (count <= 1)) {
		if (tracker -> symbol_name == symb_id) count++; 
		tracker = tracker -> next;
	}
	if(count > 1) return 1;
	return 0;
}

void show_table(){
	elem * tracker=storage;
	printf("-> ");
	while (tracker) {
		printf("%s -> ", (char*)tracker->symbol_name); 
		tracker = tracker -> next;
	}
	printf("\n");
}