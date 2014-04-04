//COMPRESSION PROJECT: MODULE 1 HUFFMAN CODE GENERATOR: module_1.h
//Created by Mathys Ellis 31/01/2013

#ifndef MODULE_1_H
#define MODULE_1_H

#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stddef.h>


#include "module_0.h"
#include "module_5.h"

using namespace std;

//Function prototypes for generating a series 1 of huffman code words. (ITERATIVE METHOD) Different optimisation
codeWords generateHuffmanCodeWordsI_CW(int, bool);
bitstream generateHuffmanCodeWordsI_BS(int, bool);

//Function prototypes for generating a series 2 of huffman code words. (RECURSIVE METHOD) Different optimisation
codeWords generateHuffmanCodeWordsR_CW(int, bool);
void recDownCodeWords(int, int, int, int, int&, codeWords&, codeWord, bool);
void recDownCodeWords_File(unsigned long long int levels, unsigned long long int noInTopLevels, unsigned long long int noOfCW, unsigned long long int countLevel, unsigned long long int& codeWordCount, fstream& outFile, codeWord curCW, bool side);

//Function prototype for finding code word using an explicit formula
codeWord getCodeWord(int, bool, int);

codeWord getCodeWord_FromFile(const char* path, unsigned long long int m, unsigned long long int codewordIndex);

//Function prototype for in/out
codeWords getHuffmanCodeWords_Memory(int m, int series);
bool getHuffmanCodeWords_File(const char* filename, unsigned long long int m, int series);

#endif
