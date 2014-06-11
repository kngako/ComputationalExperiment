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
codeWords getAllCodewords_FromFile(const char* path, unsigned long long int m);

//Function prototype for in/out
codeWords getHuffmanCodeWords_Memory(int m, int series);
bool getHuffmanCodeWords_File(const char* filename, unsigned long long int m, int series);

// Function to generate all possible huffman trees.
vector<codeWords> generateAllHuffmanCodeWordsI_CW(int noOfCodeWords, bool firstCode);

void show(codeWords temp);

// Construct a BST with the specified items and return the root to it.
Node* constructTree(int size);

//Create a new node with the specified item
Node* createNode(int item);

// Insert element into the tree
Node* insert(int item, Node* node);

// Make the rightmost node at the specified depth the root of the tree
Node* splay(Node* root);

Node* rotate(Node* gr, Node* par, Node* ch);

Node* rotateLeft(Node* gr, Node* par, Node* ch);

Node* rotateRight(Node* gr, Node* par, Node* ch);

Node* parent(Node* node, Node* subTreeRoot);

void finishRotation(Node* gr, Node* par, Node* ch, Node* chDesc, Node* oldPar);

void displayTree(Node* root, int depth);

void padding(char ch, int n);

codeWords codeWordsFromTree(Node* root, int noOfCodeWords, bool firstCode);

codeWords cwFromTree(Node* node, codeWord& cW, codeWords& cWs, bool firstCode);

Node* copy(Node* root);

Node* copyOver(Node* newSubTree, Node* oldSubtree);

void processTree(Node* root, int noOfCodeWords, bool firstCode, vector<codeWords>& store);

int rightmostDepth(Node* root);

int rightmostDepth(Node* node, int depth);

Node* rightmostAtDepth(Node* root, int depth);

Node* rightmostAtDepth(Node* node, int depthRequired, int depth);

void destoryTree(Node* node);

/******************************************************************************
**********************    HuffmanOptimally      *******************************
*******************************************************************************/

codeWords generateOptimalHuffmanCodeWords(partitionedString ptr, bool firstCode);

partitionedString distinction(partitionedString& pString);

void add(partition* part, partitionedString& pString);

void merge(int* smallest, vector<HuffmanNode*>& set);

void removeHuffmanNodes(HuffmanNode* hNode1, HuffmanNode* hNode2, vector<HuffmanNode*>& set);

int* getTwoSmallestPercentageNodeIndexes(vector<HuffmanNode*>& set);

HuffmanNode* createHuffmanNode(double percentage, char* pString, HuffmanNode* left, HuffmanNode* right);

codeWords codeWordsFromTree(HuffmanNode* root, int noOfCodeWords, bool firstCode);

codeWords cwFromTree(HuffmanNode* node, codeWord& cW, codeWords& cWs, bool firstCode);

#endif
