//COMPRESSION PROJECT: MODULE 7 REPETION PARTIONIZER: module_7.h
//Created by Mathys Ellis 26/03/2014

/* 
 * File:   module_7.h
 * Author: MoX
 *
 * Created on 26 March 2014, 9:04 AM
 */




#ifndef MODULE_7_H
#define	MODULE_7_H

#include "module_0.h"
#include "module_5.h"
#include "module_3.h"

vector<repetition*> generateRepetitionList(const char* path, int lenIndex, int NIStringIndex, int repIndex);
vector<vector<repetition*>*> repetitionSorter(vector<repetition*> repetitionList, char* str);
void repetitionToPartitions_mem(vector<vector<repetition*>*> repetitionList);


#endif	/* MODULE_7_H */

