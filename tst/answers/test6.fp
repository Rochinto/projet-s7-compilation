void call_fact(){
LOAD(fp+1)
LOADI(0)
LEQ
IFN(L0)
LOADI(1)
GOTO(L1)
L0:
LOAD(fp+1)
SAVEFP
LOAD(fp+1)
LOADI(1)
SUBI
CALL(call_fact)
RESTORE(1)
MULTI
L1:
return;
}

