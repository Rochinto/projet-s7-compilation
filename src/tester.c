
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tester.h"

int is_same_code(FILE* file_A, FILE* file_B){
    char ch_A = getc(file_A);
    char ch_B = getc(file_B);
    int c = 1;
    while((ch_A != EOF) && (ch_B != EOF)){
        if(ch_A != ch_B){return 0;}
        ch_A = getc(file_A);
        ch_B = getc(file_B);
        c++;
    }
    if((ch_A == EOF) && (ch_B != EOF)) return 0;
    if((ch_A != EOF) && (ch_B == EOF)) return 0;
    return 1;
}

char buffer[1000];

int check_answer(int test_rank){
    strcpy(buffer, "./myml ");
    strcat(buffer, test_paths[test_rank]);
    int ret = system(buffer);
    if (ret < 0){fprintf(stderr, "Test error : can't execute ./myml on %s", test_paths[test_rank]); exit(-1);}

    char* file_name = get_ml_file_name(test_paths[test_rank]);
    char* file_pcode_name = get_file_name_with_extension(file_name, ".p");
    char* file_fpcode_name = get_file_name_with_extension(file_name, ".fp");

    strcpy(buffer, "tst/answers/");
    strcat(buffer, file_pcode_name);
    FILE* answer_p = fopen(buffer,"r");

    strcpy(buffer, "tst/answers/");
    strcat(buffer, file_fpcode_name);
    FILE* answer_fp = fopen(buffer,"r");

    FILE* pcode = fopen(file_pcode_name,"r");
    FILE* fpcode = fopen(file_fpcode_name,"r");

    int r1 = is_same_code(pcode, answer_p);
    int r2 = is_same_code(fpcode, answer_fp);

    free(file_name);
    free(file_pcode_name);
    free(file_fpcode_name);
    fclose(pcode);
    fclose(fpcode);
    fclose(answer_p);
    fclose(answer_fp);

    return (r1 && r2);
}

int main(int argc, char** argv){
    int c = 0;
    int i;
    for(i=0; i<TEST_NUMBER; ++i){
        printf(TEST_PREFIX);
        if(check_answer(i)){
            c++;
            printf(SUCCESS_SUFFIX);
        }
        else printf(FAIL_SUFFIX);
        printf("%s", test_paths[i]);
        printf(RESET_LINE);
    }
    printf(TEST_PREFIX);
    printf("(%d/%d) passed tests\n", c, TEST_NUMBER);

    return 0;
} 