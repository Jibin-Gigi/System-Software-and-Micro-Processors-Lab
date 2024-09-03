#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{
	FILE *fp1,*fp2,*fp3,*fp4;
	char operand[20],opcode[20],label[20],code[20],hexa[20];
	int locctr, start, length, flag;
	fp1=fopen("input.txt","r");
	fp2=fopen("optab.txt","r");
	fp3=fopen("symtab.txt","w+");
	fp4=fopen("intermediate.txt","w");
	fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
	if(strcmp(opcode,"START")==0){
      		start=atoi(operand);
      		locctr=start;
      		fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);
	}
	else
		locctr=0;
	fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
	while(strcmp(opcode,"END")!=0){
		flag = 0;
		fprintf(fp4,"%d\t",locctr);
		
		if(strcmp(label,"**")!=0){
			fprintf(fp3,"%s\t%d\n",label,locctr);
    	    	}
    	       	else{
    	       		fscanf(fp2,"%s\t%s",code,hexa);
    	       		while(strcmp(code, "END")!= 0){
    	       			fscanf(fp2,"%s\t%s",code,hexa);
    	       			if(strcmp(opcode, code) == 0){
    	       				locctr += 3;
    	       				flag = 1;
    	       				break;
    	       			}
    	       			/*if(flag == 0){
    	       				printf("Error\n");
    	       				exit(0);
    	       			}*/
    	       			fscanf(fp2,"%s\t%s",code,hexa);
    	       		}

    	   	}
    	   	if( strcmp(opcode, "WORD") == 0){
    	   		locctr += 3;
    	   	}
    	   	else if(strcmp(opcode, "RESW") == 0){
    	   		locctr += 3*(atoi(operand));
    	   	}
    	   	else if(strcmp(opcode, "RESW") == 0){
    	   		locctr += atoi(operand);
    	   	}
    	   	else if(strcmp(opcode, "BYTE") == 0){
    	   		locctr += strlen(operand)-3;
    	   	}
    	   	else{
    	   		locctr += 3;
    	   	}
    	   	fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);
    	   	fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    	   	
	}
    	   	fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);
    	   	printf("%d\n", locctr);
    	   	length = locctr - start;
    	   	fprintf(fp4, "Program length = %d", length);
    	   	printf("Program length = %d\n", length);
    	   	fclose(fp1);
    		fclose(fp2);
    		fclose(fp3);
    		fclose(fp4);
    
	   	
}   	   	

