//COMPRESSION PROJECT: MODULE 0 TYPES AND CONVERSION: module_0.h
//Created by Mathys Ellis 01/03/2014

/* 
 * File:   module_0.h
 * Author: MoX
 *
 * Created on 01 March 2014, 10:53 AM
 */

#ifndef MODULE_0_H
#define	MODULE_0_H

#include <vector>
#include <string>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <sstream>

using namespace std;

const int STD_NUMBER_OF_CHARS = 255;

//Type declarations
//==============================================================================

//Module_1
//==============================================================================
//codeWord is based on a pointer of boolean type. To allow for dynamic length of number of bits in codeWord
typedef std::vector<bool> codeWord;
//codeWords is based on a pointer of codeWord type. To allow for dynamic length of number of codeWords
typedef std::vector<codeWord> codeWords;
//bitstream is based on a pointer of boolean type to allow for a dynamic length of bits in the stream
typedef std::vector<bool> bitstream;

typedef struct node_struct
{
    int item;
    struct node_struct* left;
    struct node_struct* right;
} Node;

typedef struct huffman_node_struct
{
    double percentage;
    char* partitionStr;
    struct huffman_node_struct* left;
    struct huffman_node_struct* right;
} HuffmanNode;

//Module_2
//==============================================================================
//Special structure used to store data that has been mapped from a genetic string.
struct mappedString
{
	int mapping[4]; //[0] -> A; [1] -> C; [2] -> G; [3] -> T; Stores order of occurance according to first
	char* mappedStr; //Converted String
};

//Constants for mappedString;
const int A_IDX = 0;
const int C_IDX = 1;
const int G_IDX = 2;
const int T_IDX = 3;

//Module_3
//==============================================================================
//Special structure to hold a repetitions data
struct repetition
{
	char* repetitionStr;
	int startpos;
};

//Module_4
//==============================================================================
struct compressionInfo
{
    char* partstr;
    double gain;
};

//Module_7 & Module_6
//==============================================================================
struct partition
{
    char* partitionStr;
    int huffmanCWIndex;
    int distinicIndex;
    int frequency;
};

typedef vector<partition*> partitionedString;

//Type converstion functions

//Module_0
//==============================================================================
void errorMsg(char*);
char* nextTok(char* str, int& curPos, const char* delim);

//Module_1
//==============================================================================
//Function prototype for coverting codeWords and bitstream to cstrings
char* cwToString(codeWord);
char** cwsToString(codeWords);
char* bsToString(bitstream);

//Convert a string of 0s and 1s to a codeword;
codeWord stringToCodeWord(char*);
//Find a codeword at an index in a string "<m> <cw0> <cw1> ..."
codeWord findCodeWordInString(char*, int);
//Find all codewords in a string "<m> <cw0> <cw1> ..."
codeWords getAllCodeWordsInString(char* str);

//Module_2
//==============================================================================
//This function maps the inputted string and returns a mappedString
mappedString* mapString(char*);
//This function converts the mappedString to a normal c-string
char* getStringFromMap(mappedString*);
//To string "<str> <A> <B> <G> <T>" function for mapped string 
char* mappedStringToString(mappedString*);
//From storage string "<str> <A> <B> <G> <T>" to mapped string 
mappedString* stringToMappedString(char*);


//Module_3
//==============================================================================
//Convert repetition struct to "<str> <int>"
char* repetitionToString(repetition*);
//Convert string "<str> <int>" to repetition struct
repetition stringToRepetition(char* str);
repetition* stringToRepetitionPtr(char* str);

//Module_4
//==============================================================================
//Converts a D:H formated string to a bit stream
bitstream encodeString_compressed(char * string, int len);
//Converts a  bit stream to a D:H formated string
char* decodeString_compressed(bitstream estr);

//converts a compressionInfo in to "<partionStr> <gain>
char* compressionInfoToString(compressionInfo* info);
//converts a string to  compressionInfo
compressionInfo* stringToCompressionInfo(char* str);


//Module_7 & Module_6
//==============================================================================
//converts a partition in to "<partionStr> <distincIndex> <weight>
char* partitionToString(partition part);
char* partitionToString(partition* part);
//converts a partitioned string in to "<partition1>-<partion2>-<partition3>-..."
char* partitionedStringToString(partitionedString& partStr);
//converts a partitioned string in to "<partionStr1>-<partionStr2>-<partionStr3>-..."
char* partitionedStringToStripedString(partitionedString& partStr);

//converts a string in the format "<partionStr> <distincIndex> <weight>" to a partition struct
partition stringToPartition (char* string);
partition* stringToPartitionPtr (char* string);
//converts a string in the format "<partition1>-<partion2>-<partition3>-...-<partitionN>" to a partitionedString type
partitionedString stringToPartitionedString (char* string);

#endif	/* MODULE_0_H */

