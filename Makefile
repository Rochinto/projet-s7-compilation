
SRC = ./src
BUILD = ./build

all			:	myml PCode.o tester

y.tab.c 	:	$(SRC)/myml.y
			bison -o $(BUILD)/$@ -y -d -v $(SRC)/myml.y 
lex.yy.c	:	$(SRC)/myml.l y.tab.c
			flex -o $(BUILD)/$@ $(SRC)/myml.l
myml		:	lex.yy.c $(BUILD)/y.tab.c $(SRC)/Table_des_symboles.c $(SRC)/Table_des_chaines.c $(SRC)/Attribut.c
			gcc -o myml $(BUILD)/lex.yy.c $(BUILD)/y.tab.c $(SRC)/Table_des_symboles.c $(SRC)/Table_des_chaines.c $(SRC)/Attribut.c
PCode.o		:	$(SRC)/PCode.c
			gcc -c $(SRC)/PCode.c -o $(BUILD)/PCode.o
tester		:	$(SRC)/tester.c $(SRC)/Attribut.c
			gcc $(SRC)/tester.c $(SRC)/Attribut.c -o tester

test		:
			./tester

clean		:	
			rm -f $(BUILD)/*
			rm -f myml PCompiler *.p *.fp test tester