#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "RegisterData.h"
#include "OpCodeData.h"
#include <math.h>
#define LENGTH 32
#define false 0
#define true 1

typedef struct _IFormat {
 char* OpcodeNumber;
 char* rs;
 char* rt;
 int Immediate;
 char* operation;
} IFormat;

typedef struct _RFormat {
 char* OpcodeNumber;
 char* rs;
 char* rt;
 char* rd;
 int shamt;
 char*  functionCode;
 char* operation;
} RFormat;

typedef struct _JFormat {
 char* OpcodeNumber;
 char* address;
 char* operation;
} JFormat;

char flip(char c) {
    return (c == '0') ? '1': '0';
}
 
//Gets full 32 bit address for  J operation
char* getFullAddress(char* arg1) {
    char* ret;
    ret = (char*) malloc (32*sizeof(char));
    for (int i=0;i<4;i++){
        ret[i]='1';
    }
    for (int i=4;i<30;i++){
        ret[i]=arg1[i+1];
    }
    for (int i=30;i<32;i++) {
        ret[i] = '0';
    }
    return ret;
}

void parseRFormat(RFormat *arg1) {
    if (strcmp(arg1->operation, "add") == 0) {
        printf("%s %s, %s, %s\n", arg1->operation, arg1->rd,  arg1->rs, arg1->rt);
    }
    if (strcmp(arg1->operation, "sub") == 0) {
        printf("%s %s, %s, %s\n", arg1->operation, arg1->rd,  arg1->rs, arg1->rt);
    }
    if (strcmp(arg1->operation, "slt") == 0) {
        printf("%s %s, %s, %s\n", arg1->operation, arg1->rd,  arg1->rs, arg1->rt);
    }
    if (strcmp(arg1->operation, "jr") == 0) {
        printf("%s %s\n", arg1->operation, arg1->rs);
    }
    if (strcmp(arg1->operation, "sll") == 0) {
        printf("%s %s, %s, %d\n", arg1->operation, arg1->rd,arg1->rt,arg1->shamt);
    }
    if (strcmp(arg1->operation, "srl") == 0) {
        printf("%s %s, %s, %d\n", arg1->operation, arg1->rd,arg1->rt,arg1->shamt);
    }
}

void  parseIFormat(IFormat *arg1) {
    if (strcmp(arg1->operation, "bne") == 0) {
        printf("%s %s, %s, %d\n", arg1->operation, arg1->rs,  arg1->rt, arg1->Immediate);
    }
    if (strcmp(arg1->operation, "sw") == 0) {
        printf("%s %s, %d(%s)\n", arg1->operation, arg1->rt, arg1->Immediate, arg1->rs);
    }
    if (strcmp(arg1->operation, "lw") == 0) {
        printf("%s %s, %d(%s)\n", arg1->operation, arg1->rt, arg1->Immediate, arg1->rs);
    }
    if (strcmp(arg1->operation, "beq") == 0) {
        printf("%s %s, %s, %d\n", arg1->operation, arg1->rs, arg1->rt, arg1->Immediate);
    }if (strcmp(arg1->operation, "addi") == 0) {
        printf("%s %s, %s, %d\n", arg1->operation, arg1->rt, arg1->rs, arg1->Immediate);
    }
}

void parseJFormat(JFormat *arg1)  {
    printf("%s %s\n", arg1->operation, arg1->address);
}
int charToBinary(char* arg1) {
    //immediate is 16 bits  --  only use for  immediate!!
    
    int answer =  0;
    int j = 15;
    for (int i=16;i<32;i++) {
        if(arg1[i] == '1') {
            answer+= pow(2,j);
            j--;
        } else {
            j--;
        }
    }
    return answer;
}

int charToBinaryAdvanced(char* cArray, int a, int b){
    //a = starting index
    //b = number of bits we need to get
    int answer =  0;
    int j = b-1;
    for (int i=a;i<(a+b);i++) {
        if(cArray[i] == '1') {
            answer+= pow(2,j);
            j--;
        } else {
            j--;
        }
    }
    return answer;
}

int getshamt(char*  arg1) {
    char*  shamt;
    shamt = (char*) malloc (5*sizeof(char));
    int j=0;
    for  (int i=21; i<26; i++)  {
        shamt[j] = arg1[i];
        j++;
    }
    int a = charToBinaryAdvanced(shamt,0,5);
    return a;
}
char* getrd(char*  arg1) {
    char* rd;
    rd = (char*) malloc (5*sizeof(char));
    int j=0;
    for  (int i=16; i<21; i++)  {
        rd[j] = arg1[i];
        j++;
    }
    int a = charToBinaryAdvanced(rd,0,5);
    rd =  searchRegisterData(a);
    return rd;
}

char* getrs(char* arg1)  {
    char*  rs;
    rs = (char*) malloc (5*sizeof(char));
    int j=0;
    for  (int i=6; i<11; i++)  {
        rs[j] = arg1[i];
        j++;
    }
    int a =  charToBinaryAdvanced(rs,0,5);
    rs  = searchRegisterData(a);
    return rs;
}

char*  getrt(char*  arg1)  {
    char*  rt;
    rt = (char*) malloc (5*sizeof(char));
    int j=0;
    for  (int i=11; i<16; i++)  {
        rt[j] = arg1[i];
        j++;
    }
    int  a = charToBinaryAdvanced(rt,0,5);
    rt  = searchRegisterData(a);
    return rt;
}

int getimm(char* arg1) {
    char* imm;
    imm =  (char*) malloc (16*sizeof(char));
    int j=0;
    for  (int i=16; i<31; i++)  {
        imm[j] = arg1[i];
        j++;
    }
    int answer = charToBinary(imm);
    return answer;
}

int convertToDecimal(char* arg1) {
    char* imm;
    char* ones;
    imm =  (char*) malloc (16*sizeof(char));
    ones = (char*) malloc (16*sizeof(char));
    int negative = 0;
    int j=0;
    for  (int i=16; i<32; i++)  {
        imm[j] = arg1[i];
        j++;
    }
    
    if (imm[0] == '1') {
        negative = 1;
        for (int i = 0; i < 16; i++) {
            ones[i] = flip(imm[i]);
        }
    } else {
        ones = imm;
    }
    
    
    int x = charToBinaryAdvanced(ones, 0, 16);
    
    if (negative) {
        x=x+1;
        x = x * -1;
    }

    return x;
}


// Checks that the char array is 32 bits long
// and only has 0 and 1 in it.
int check(char* bits) {
    if (strlen(bits) != LENGTH) {
        return false;
    }
    for (int i = 0; i < LENGTH; i++) {
        if (bits[i] != '0' && bits[i] != '1') {
            return false;
        }
    }
    return true;
}
// We will take the bitstring as a command line argument.
int main(int argc, char **argv) {
    // Make sure we have at least one argument.
    if (argc < 2) {
        fprintf(stderr, "No argument found\n");
        return -1;
    }
    // Get a pointer to the argument.
    char *instruction = argv[1];
    if (!check(instruction)) {
        fprintf(stderr, "Invalid bit string\n");
        return -2;
    }
    // Your code here!
    // You can use regular printf()'s to produce your output.
    OpCodeData lookup;
    char  *funtcode;
    char *opcode;
    opcode = (char*) malloc (6*sizeof(char));
    funtcode = (char*) malloc (6*sizeof(char));
    
    for (int i = 0; i<6; i++) {
        opcode[i] = argv[1][i];
    }
    
    if (strcmp(opcode, "000000") == 0) {
        int j = 0;
        for (int i=26;i<32;i++) {
            funtcode[j]  = argv[1][i];
            j++;
        }
        lookup = search(opcode,funtcode);
    } else {
        lookup = search(opcode,"null");
    }
    if (strcmp(lookup.OpcodeNumber, "Invalid") == 0)
        fprintf(stderr, "Unsupported or invalid opcode\n");
    
    char  format = lookup.format;
    IFormat *completeI;
    completeI = (IFormat *) malloc(sizeof(IFormat));
    RFormat *completeR;
    completeR = (RFormat *) malloc(sizeof(RFormat));
    JFormat *completeJ;
    completeJ = (JFormat *) malloc(sizeof(JFormat));
    switch (format) {
        case 'I':
            completeI->operation = lookup.Instruction;
            completeI->rs = getrs(argv[1]);
            completeI->rt = getrt(argv[1]);
           if  (strcmp(completeI->operation, "addi")  == 0) {
                completeI->Immediate = convertToDecimal(argv[1]);
            } else
                completeI->Immediate = charToBinary(argv[1]);
            parseIFormat(completeI);
            break;
        case 'R':
            completeR->OpcodeNumber = lookup.OpcodeNumber;
            completeR->operation = lookup.Instruction;
            completeR->rs = getrs(argv[1]);
            completeR->rt = getrt(argv[1]);
            completeR->rd = getrd(argv[1]);
            completeR->shamt = getshamt(argv[1]);
            parseRFormat(completeR);
            break;
            
        case 'J':
            completeJ->OpcodeNumber = lookup.OpcodeNumber;
            completeJ->operation = lookup.Instruction;
            completeJ->address = getFullAddress(argv[1]);
            parseJFormat(completeJ);
    }
    return 0;
}

