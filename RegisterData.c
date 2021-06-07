#include <stdio.h>
#include "RegisterData.h"

#define NUM_OF_REGISTERS 32

static const RegisterData RegisterTable[NUM_OF_REGISTERS] = {
	{0,"$zero"},
	{1, "$at"},
	{2, "$v0"},
	{3, "$v1"},
	{4, "$a0"},
	{5, "$a1"},
	{6, "$a2"},
	{7, "$a3"},
	{8, "$t0"},
	{9, "$t1"},
	{10, "$t2"},
	{11, "$t3"},
	{12, "$t4"},
	{13, "$t5"},
	{14, "$t6"},
	{15, "$t7"},
	{16, "$s0"},
	{17, "$s1"},
	{18, "$s2"},
	{19, "$s3"},
	{20, "$s4"},
	{21, "$s5"},
	{22, "$s6"},
	{23, "$s7"},
	{24, "$t8"},
	{25, "$t9"},
	{26, "$k0"},
	{27, "$k1"},
    {28, "$gp"},
    {29, "$sp"},
    {30, "$fp"},
    {31, "ra"}
};

char* searchRegisterData (int arg12)  {
    char*  answer = NULL;
        for (int i=0; i < NUM_OF_REGISTERS; i++) {
            if(RegisterTable[i].Number == arg12)  {
                answer = RegisterTable[i].Register;
                return answer;
            }
        }
    return  answer;
}
