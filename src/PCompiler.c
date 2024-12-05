
#include <stdio.h>
#include <stdlib.h>

FILE * file_in = NULL;
FILE * file_out = NULL;


int main(int argc, char** argv){

    //if(argc < 2) return 0;

    file_in = fopen("test.p","r");
    file_out = fopen("./build/test.c","w");
    if(!file_in) return 2;
    if(!file_out) return 1;

    //stdin = file_in;
    char ch;
    char contents[] = 
    "#include \"../src/PCode.h\" \n\
    int main(){                 \n\
        #include \"test.p\"     \n\
        print_stack();          \n\
        return 0;               \n\
    }";
    /*char header[] = "#include \"PCode.h\"\nint main(){\n";
    char header[] = "#include \"PCode.h\"\nint main(){\n";
    char ender[] = "\nprint_stack();\nreturn 0;\n}\n";*/

    int i = 0;
    while(contents[i] != 0)
        fprintf(file_out, "%c",contents[i++]);

    //while((ch = getc(file_in)) != EOF)
    //    fprintf(file_out, "%c",(char) ch);

    //i = 0;
    //while(ender[i] != 0)
    //    fprintf(file_out, "%c",ender[i++]);

    /* any open file shall be closed */
    fclose(file_out);
    fclose(file_in);

    int ret = system("gcc ./build/test.c ./build/PCode.o -o test");
    if (ret < 0) return 3;

    return 0;
}