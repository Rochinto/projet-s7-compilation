
%{

  // header included in y.tab.h
#include "../src/Attribut.h"  
#include "../src/Table_des_symboles.h"
#include <stdio.h>
#include <stdlib.h>

FILE * file_in = NULL;
FILE * file_out = NULL;
FILE * file_func = NULL;
FILE * out = NULL;

int label_counter = 0;
  
extern int yylex();
extern int yyparse();
extern int yylex_destroy();

void yyerror (char* s) {
   printf("\n%s\n",s);
 }

%}

%union {
  int n;
  void* a;
  char* c;
}

%token <n>NUM FLOAT <a>ID <c>STRING //ID est un sid donné par la table des chaînes.

%token PV LPAR RPAR LET IN VIR

%token IF THEN ELSE

%token ISLT ISGT ISLEQ ISGEQ ISEQ
%left ISEQ
%left ISLT ISGT ISLEQ ISGEQ


%token AND OR NOT BOOL
%left OR
%left AND



%token PLUS MOINS MULT DIV EQ
%left PLUS MOINS
%left MULT DIV
%left CONCAT
%nonassoc UNA    /* pseudo token pour assurer une priorite locale */

%type<a> def_id
%type<a> let_def
%type<a> def_fun
%type<a> fun_head
%type<a> name_funcall

%start prog 

%%

 /* a program is a list of instruction */

prog : inst PV {
}

| prog inst PV {
}
;

/* a instruction is either a value or a definition (that indeed looks like an affectation) */

inst : let_def
{
  if(has_multiple_values($1)){
    remove_symbol_value($1);
    fprintf(out, "STORE(%d)\n", get_symbol_value($1).offset); depile();
  }
}
| exp {fprintf(out, "DROP\n"); depile();}
;



let_def : def_id {$$=$1;}
| def_fun {$$=$1;}
;

def_id : LET ID EQ exp  
{
  $$=$2;
  add_symbol_value($2, create_symb());
}
;

def_fun : LET fun_head EQ exp
{
  $$=$2;
  fprintf(out, "return;\n}\n\n");

  remove_last_n_symbols(get_argc()+1);
  add_symbol_value($2, create_function());
  leave_function();
  out = stdout;
}
;

fun_head : ID LPAR id_list RPAR 
{
  $$=$1;
  if(has_value($1)){
    fprintf(stderr,"Error : cannot override a function definition (%s)\n", sid_to_string($1));
    exit(-1);
  }
  add_symbol_value($1, create_function());
  fprintf(out, "void call_%s(){\n", sid_to_string($1));
}
;

id_list : ID
{
  enter_function();
  out = file_func;
  add_symbol_value($1, create_argument());
}
| id_list VIR ID
{
  add_symbol_value($3, create_argument());
}
;


exp : arith_exp
| let_exp
;

arith_exp : MOINS arith_exp %prec UNA {fprintf(out, "LOADI(-1)\n"); fprintf(out, "MULTI\n");} //Car, -a = (-1)*a ou 0-a;
| arith_exp MOINS arith_exp {fprintf(out, "SUBI\n"); depile();}
| arith_exp PLUS arith_exp {fprintf(out, "ADDI\n"); depile();}
| arith_exp DIV arith_exp {fprintf(out, "DIVI\n"); depile();}
| arith_exp MULT arith_exp {fprintf(out, "MULTI\n"); depile();}
| arith_exp CONCAT arith_exp
| atom_exp
;

atom_exp : NUM {fprintf(out, "LOADI(%d)\n", $1); empile();}
| FLOAT
| STRING {}
| ID
{
  fprintf(out, "LOAD(fp+%d)\n", get_symbol_value($1).offset); empile();
}
| control_exp
| funcall_exp
| LPAR exp RPAR
;

control_exp : if_exp
;


if_exp : if cond then atom_exp else atom_exp
{

  int label = $<n>3;
  fprintf(out, "L%d:\n", 2*label+1);
}
;

if : IF;
cond : LPAR bool RPAR;
then : THEN           
{
  int label = label_counter++;
  fprintf(out, "IFN(L%d)\n", 2*label); depile();
  $<n>$ = label;
};
else : ELSE           
{
  int label = $<n>-1;
  fprintf(out, "GOTO(L%d)\n", 2*label+1);
  fprintf(out, "L%d:\n", 2*label);
};


let_exp : let_def IN atom_exp 
{
  fprintf(out, "DRCP\n"); depile();
  remove_symbol_value($1);
}
| let_def IN let_exp
{
  fprintf(out, "DRCP\n"); depile();
  remove_symbol_value($1);
}
;

funcall_exp : name_funcall LPAR arg_list RPAR
{
  int argc = get_symbol_value($1).argc;
  if(argc != $<n>3){
    fprintf(stderr,"Error : wrong number of function arguments (%s)\n", sid_to_string($1));
    exit(-1);
  }
  fprintf(out, "CALL(call_%s)\n", sid_to_string($1));
  fprintf(out, "RESTORE(%d)\n", argc);
  int i;
  for(i=0; i<argc; i++) depile();
}
;

name_funcall : ID {$$=$1; fprintf(out, "SAVEFP\n"); empile();}
;

arg_list : arith_exp {$<n>$ = 1;}
| arg_list VIR arith_exp {$<n>$ = $<n>1+1;}
;

bool : BOOL
| bool OR bool
| bool AND bool
| NOT bool %prec UNA 
| exp ISLT exp        {fprintf(out, "LT\n"); depile();}
| exp ISGT exp        {fprintf(out, "GT\n"); depile();}
| exp ISLEQ exp       {fprintf(out, "LEQ\n"); depile();}
| exp ISGEQ exp       {fprintf(out, "GEQ\n"); depile();}
| exp ISEQ exp        {fprintf(out, "EQ\n"); depile();}
| LPAR bool RPAR
;


/*comp :  ISLT  {fprintf(out, "LT\n"); depile();}
| ISGT        {fprintf(out, "GT\n"); depile();}
| ISLEQ       {fprintf(out, "LEQ\n"); depile();}
| ISGEQ       {fprintf(out, "GEQ\n"); depile();}
| ISEQ        {fprintf(out, "EQ\n"); depile();}
;*/

%% 
int main (int argc, char** argv) {
  /* The code below is just a standard usage example.
     Of cours, it can be changed at will.

     for instance, one could grab input and ouput file names 
     in command line arguements instead of having them hard coded */

  /*stderr = stdin;*/
  
  /* opening target code file and redirecting stdout on it */

  char* file_in_name = get_ml_file_name(argv[1]);
  char* file_out_name = get_file_name_with_extension(file_in_name, ".p");
  char* file_func_name = get_file_name_with_extension(file_in_name, ".fp");

  file_out = fopen(file_out_name,"w");
  file_func = fopen(file_func_name,"w");
  stdout = file_out;
  stderr = file_out;
  out = stdout;

  /* openng source code file and redirecting stdin from it */
  file_in = fopen(argv[1],"r");
  stdin = file_in; 

  /* As a starter, on may comment the above line for usual stdin as input */
  
  yyparse();

  /* any open file shall be closed */
  fclose(file_out);   free(file_out_name);
  fclose(file_func);  free(file_func_name);
  fclose(file_in);    free(file_in_name);

  remove_all_symbols();
  remove_all_chaines();
  yylex_destroy();
  
  return 0;
} 

