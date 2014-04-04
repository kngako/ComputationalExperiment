//COMPRESSION PROJECT: MODULE 2 NON ISOMORPHIC STRING GEN: module_2.h
//Created by Mathys Ellis 02/12/2013

#ifndef module_2
#define module_2

#include <bitset>
#include <iostream>
#include <cmath>

#include "module_0.h"
#include "module_5.h"

using namespace std;



//Module Inteface Function prototypes


//This function returns all non isomorphic strings for the specified mappedString *Warning very high resource usage*
vector<mappedString> getAllNonIsomorphicStrings_NLen(int);
//This function returns the fist K non isomorphic strings fot the specified mappedString
vector<mappedString> getKNonIsomorphicStrings_NLen(int, int);

bool isIsomorphic(char*, char*);

//Module Auxilary Function prototypes
double getNumberOfIsomorphicStringFor(int len);

//This function is downward recursive funtion that finds all possible nonisomorphic patterns
void recDownString(int, int, char*, char, int, vector<mappedString>&);
void recDownString_File(int strLength, int curLength, char*& curStr, char nextChar, unsigned long long int maxNoOfResults, unsigned long long int& counter, fstream& outFile);

//File in/out
bool getNonIsomorphicStrings_NLen_File(char* filename, int len, unsigned long long int limit);

//Get a mappedString from file at a particular path with a length x
mappedString* getNonIsomorphicString_FromFile(const char* path, unsigned long long int lenIndex, unsigned long long int NIStringIndex);

#endif
