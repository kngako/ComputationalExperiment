/* 
 * File:   module_6.h
 * Author: K
 *
 * Created on 03 March 2014, 9:41 PM
 */

#ifndef MODULE_6_H
#define	MODULE_6_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "module_1.h"

using namespace std;

struct Bundle{
    string pattern;
    bool isReptition;
    int count;
    int rank;
    string codeWord;
};


struct Node{
    vector<Bundle> part;
    vector<Bundle> distinct;
    
    Bundle bun;
    int currentIndex;
};

void partition(string pattern, bool tree, const char* fn);

void partition(Node& part, vector<Node>& partitions, string pattern);

void partitionToFile(Node& part, vector<Node>& partitions, string pattern, fstream& file);

void createNode(string pattern, Node& newNode);

void createBundle(Bundle& tmpBun, string pattern);

void print(vector<Node>& collection, string pattern);

void print(Node& node);

void printToFile(Node& node, fstream& file);

void print(Bundle& word);

Node& split(int index, Node& node, Node& newPart);

Node& addToNode(Node& node, string newPart);

void copyNode(Node& orig, Node& newNode);

void setupDistinct(Node& node);

bool contains(Node& node, Bundle& bun);

void sort(Node& node);

void allocateSorted(Node& node);
#endif	/* MODULE_6_H */

