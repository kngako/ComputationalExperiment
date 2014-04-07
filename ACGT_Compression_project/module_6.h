/* 
 * File:   module_6.h
 * Author: K
 *
 * Created on 03 March 2014, 9:41 PM
 * Last Updated: 03 April 2014, 10:16 PM
 */
#include "module_0.h"

#ifndef MODULE_6_H
#define	MODULE_6_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>


//#include "module_1.h"

using namespace std;

void Partition(string pattern, bool tree, const char* fn);

void Partition(partitionedString& partition, 
        vector<partitionedString>& partitions, string pattern); // TODO: Implement this function

void partitionToFile(partitionedString& partitioned, 
        vector<partitionedString>& partitions, string pattern, int currentIndex, 
        fstream& file); // TODO: Implement this 

void createPartitionedString(string pattern, partitionedString& newPartitionedString);

/**
 * Create new partition from pattern
 * @param pattern
 * @param newPartition
 */
void createPartition(string pattern, partition* newPartition);

void print(vector<partitionedString>& collection, string pattern);

void print(partitionedString& partitions);

void printToFile(partitionedString& partitions, fstream& file);

void print(partition* word);

partitionedString& split(int index, int currentIndex, 
        partitionedString& partitionedStr, partitionedString& newPart, string pattern);

partitionedString& addToPartitionedString(partitionedString& partitionedStr, string partitionToAdd); 

void copyPartitionedString(partitionedString& orig, partitionedString& newPartition); 

void setupDistinct(partitionedString& partitionedStr);

int highestDistinct(partitionedString& partitionedStr);

void copyOverPatritionString(partition* newPartition, string pattern);

void copyPartition(partition* orig, partition* newPart);

/**
 * Checks to see if a partioned is contained in a partioned string and returns 
 * the distinct index it is associated with, else it returns -1.
 * @param partionedString
 * @param partition
 * @return 
 */
int contains(partitionedString& partionedString, partition* partition);

#endif	/* MODULE_6_H */

