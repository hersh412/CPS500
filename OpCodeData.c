//add, addi, sub, beq, bne, slt, j, jr, sll, srl, lw, sw
/*
 * References:
 * https://www2.engr.arizona.edu/~ece369/Resources/spim/MIPSReference.pdf
 * https://max.cs.kzoo.edu/cs230/Resources/MIPS/MachineXL/InstructionFormats.html
 * https://en.m.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats
*/
#include "OpCodeData.h"
#include <string.h>

#define NUM_OF_OPS 12

 OpCodeData search(char* binaryCode, char* funtionCode);


static const OpCodeData OpCodeTable[NUM_OF_OPS] = {
	{"000000","add", 'R',"100000"},
	{"001000", "addi", 'I', "null"},
	{"000000", "sub", 'R', "100010"},
	{"000100" , "beq", 'I',"null"},
	{"000101", "bne", 'I', "null"},
	{"000000" , "slt", 'R', "101010"},
	{"000010" , "j", 'J', "null"},
	{"000000", "jr",'R', "001000"},
	{"000000", "sll", 'R', "000000"},
	{"000000", "srl", 'R', "000010"},
	{"100011", "lw", 'I', "null"},
	{"101011", "sw", 'I', "null"}
};

OpCodeData search(char* binaryCode, char* functionCode) {
    OpCodeData opcodedata;
    opcodedata.OpcodeNumber =  "Invalid";

    for (int i=0; i<NUM_OF_OPS; i++)  {
        if ((strcmp(binaryCode,OpCodeTable[i].OpcodeNumber) == 0) && (strcmp(functionCode, OpCodeTable[i].FunctionCode) ==  0)) {
            opcodedata.OpcodeNumber = OpCodeTable[i].OpcodeNumber;
            opcodedata.Instruction = OpCodeTable[i].Instruction;
            opcodedata.format =  OpCodeTable[i].format;
            opcodedata.FunctionCode = OpCodeTable[i].FunctionCode;
        }
    }
    return opcodedata;
}

