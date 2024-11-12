#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

char str1[20], str2[20], str3[20];
FILE *input, *optab, *intermediate, *symtab, *prgm_length;
char label[20], opcode[20], operand[20];

void read_line(){
    strcpy(str1, "");
    strcpy(str2, "");
    strcpy(str3,"");

    fscanf(input, "%s", str1);
    if(getc(input) != '\n'){
        fscanf(input, "%s", str2);
        if(getc(input) != '\n'){
            fscanf(input, "%s", str3);
        }
    }

    if(strcmp(str1, "")!=0 && strcmp(str2, "")!= 0 && strcmp(str3, "")!= 0){
        strcpy(label, str1);
        strcpy(opcode, str2);
        strcpy(operand, str3);
    }
    else if(strcmp(str1, "")!=0 && strcmp(str2, "")!= 0 && strcmp(str3, "")== 0){
        strcpy(label, "");
        strcpy(opcode, str1);
        strcpy(operand, str2);
    }
    else if(strcmp(str1, "")!=0 && strcmp(str2, "")== 0 && strcmp(str3, "")== 0){
        strcpy(label, "");
        strcpy(opcode, str1);
        strcpy(operand, "");
    }

}


void main(){
    //FILE *input, *optab, *intermediate, *symtab;
    input = fopen("input.txt", "r");
    optab = fopen("optab.txt", "r");
    intermediate = fopen("intermediate.txt", "w+");
    symtab = fopen("symtab.txt", "w+");
    prgm_length = fopen("prgm_length.txt", "w+");

    if(input == NULL || optab == NULL || intermediate == NULL || symtab == NULL || prgm_length == NULL) {
        perror("Error opening file");
        exit(1);
    }


    //char label[20], opcode[20], operand[20];
    int locctr = 0x00, start = 0x00, program_length;
    bool symbol_found = false, opcode_found = false;
    char symtab_data[20], optab_data[20];
    

    fscanf(input, "%s%s%s", label, opcode, operand);
    if( strcmp( opcode, "START" ) == 0){
        start = strtol(operand, NULL, 16);
        locctr = start;

        fprintf(intermediate, "\t\t%-7s %-7s %-7s\n", label, opcode, operand);
        read_line();
        
    }
    else{
        locctr += 0;
    }

    while( strcmp(opcode, "END")!= 0){
        fprintf(intermediate, "%x \t%-7s %-7s %-7s\n", locctr, label, opcode, operand);
        if(strcmp(label, "")!= 0){
            symbol_found = false;
            rewind(symtab);
            while(!feof(symtab)){
                fscanf(symtab, "%s", symtab_data);
                if(strcmp(label, symtab_data)==0){
                    printf("Duplicate symbol");
                    symbol_found = true;
                }
            }

            if(symbol_found == false){
                fprintf(symtab, "%-7s %-7x\n", label, locctr);
            }
            else{
                fprintf(stderr, "Error: Duplicate symbol %s\n", label);
            }
        }
        
        opcode_found = false;
        rewind(optab);
        while(!feof(optab)){
            fscanf(optab, "%s", optab_data);

            if(strcmp(opcode, optab_data)== 0){
                opcode_found = true;
            }
        }
        
        if(opcode_found == true){
            locctr += 3;
        }
        else if(strcmp(opcode, "WORD")== 0){
            locctr += 3;
        }
        else if(strcmp(opcode, "RESW")== 0){
            locctr += 3 * atoi(operand);
        }
        else if(strcmp(opcode, "RESB")== 0){
            locctr += atoi(operand);
        }
        else if(strcmp(opcode, "BYTE") == 0) {
            if(operand[0] == 'C') {
                locctr += strlen(operand) - 3;  // C'...'
            }
            else if(operand[0] == 'X') {
                locctr += (strlen(operand) - 3) / 2;  // X'...'
            }
        }

        else{
            fprintf(stderr, "Invalid opcode : %s\n",opcode);
        }

        read_line();
    }
    fprintf(intermediate, "\t\t\t\t%-7s %-7s", opcode, operand);
    program_length = locctr - start;
    fprintf(prgm_length, "Program length is %d\n", program_length);

    fclose(input);
    fclose(optab);
    fclose(intermediate);
    fclose(symtab);
    fclose(prgm_length);
    
}
