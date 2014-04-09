/* 
 * File:   module_8.h
 * Author: K
 *
 * Created on 09 April 2014, 8:38 AM
 */

#ifndef MODULE_8_H
#define	MODULE_8_H

#include "module_0.h"
#include "module_1.h"
#include "module_6.h"

void setupDistinct(partitionedString& partitionedStr);

int highestDistinct(partitionedString& partitionedStr);

/**
 * Checks to see if a partioned is contained in a partioned string and returns 
 * the distinct index it is associated with, else it returns -1.
 * @param partionedString
 * @param partition
 * @return 
 */
int contains(partitionedString& partionedString, partition* partition);

void setupHuffmanCW(partitionedString& partitionedStr);

int rank(partitionedString& whole, partition* part);

int partitionCount(partitionedString& whole, partition* part);

int getHuffmanCW(int huffmanCWIndex, int m);

#endif	/* MODULE_8_H */

