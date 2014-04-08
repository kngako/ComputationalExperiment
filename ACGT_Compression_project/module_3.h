//COMPRESSION PROJECT: MODULE 3 STRING REPETITIONS FINDER : module_3.h
//Created by Mathys Ellis 08/01/2014
//Based on the algorithm of Michael G. Main and Richard J. Lorentz

#ifndef module_3
#define module_3

#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "module_0.h"
#include "module_5.h"

using namespace std;

//=================Core function prototypes for XYX repetitions

//=========Efficent impelmentations
void findReps_E_XYX_mem (char*, vector<repetition*>&);

void findReps_E_XYX_file (char*, fstream& outFile);

//Used to mark repetition clusters
int* findMaxLppattern_XYX(char*);

void calcLppattern_E_XYX (char*, vector<int*>&, int);

//Used to extract repetition clusters
void scanLPArrForRep_E_XYX_mem(char*, int*, vector<repetition*>&);

void scanLPArrForRep_E_XYX_file(char*, int*, fstream& outFile);

//========ineffiecent impementation

void findReps_U_XYX (char*, vector<repetition*>&);

void calcLppattern_U_XYX (char*, vector<int*>&, int);

void scanLPArrForRep_U_XYX(char*, int, int, vector<int*>&, int, vector<repetition*>&);

//========Interface functions
bool getAllRepetitions_XYX_Mem (char* str, vector<repetition*>&);
bool getAllRepetitions_XYX_File (char* str, const char* filename);

repetition* getRepetionOfNIStringI_FromFile(const char* path, unsigned long long int lenIndex, unsigned long long int NIStringIndex, unsigned long long int repIndex);

//========Auxilary functions

//Used to copy a substring at pos n of length len
char* copyChar (char*, int, int);

//Used to find the maximum value between two values
int max(int, int);

//Used to find the minimum value between two values
int min(int, int);

//=====================Core function prototypes for XX repetitions

//Used to calculate an array that holds the length of the longest prefix starting at i of the same string specifing the prefix
int* calcLppattern_XX (char*);

//Used to calculate an array that holds the length of the longest prefix starting at i of a different string then the one specifing the prefix
int* calcLptext_XX (char*, char*, int*);

//Used to calculate an array that holds the length of the longest suffix that ends at i of a different string then the one specifing the suffix
int* calcLstext_XX (char*, char*);

//Used to find right repetitions of a string formed by u + v. Right repetition =  a repetition with its center at the boundary or right of it
void newRight_XX (char*, char*, vector<int*>& rep);

//Used to find left repetitions of a string formed by u + v. Left repetition =  a repetition with its center at the boundary or left of it
void newLeft_XX (char*, char*, vector<int*>& rep);

//Used to find all new righ and left repetitions formed by u + v
void newReps_XX (char*, char*, int, vector<repetition*>&);

//Used to find all repetitions in a string
void findReps_XX (char*, int, vector<repetition*>&);

//Auxilary  function prototypes

//Used to reverse the specified string
char* reverseString (char*);

//Used to split the specifed string into two substrings
void splitStr(char*, char*&, char*&);


void findReps_file_XX(char*, int, fstream&);
void newReps_file_XX (char*, char*, int, fstream&);

bool getAllRepetitions_XX (char* filename, char* str);

//Not used
int* calcLstextLR_XX (char*, char*);



#endif
