#include "module_7.h"

vector<repetition*> generateRepetitionListFromFile(const char* filename)
{
    vector<char*> temp = getAllLines_FromFile(filename);
    vector<repetition*> out;
    
    for(unsigned int i = 0; i < temp.size(); i++)
    {
        out.push_back(stringToRepetitionPtr(temp[i]));
    }
    
    return out;
}

//Sorts repetition list by order of starting position
vector<vector<repetition*>*> repetitionListSorter(vector<repetition*> repetitionList, char* str)
{
    vector<vector<repetition*>*> out;
    int strLen = strlen(str);
    
    for(int i = 0; i < strLen; i++)
    {
        vector<repetition*>* temp = new vector<repetition*>();
        repetition* tempRep = new repetition;
        
        tempRep->repetitionStr = new char[2];
        tempRep->repetitionStr[0] = str[i];
        tempRep->repetitionStr[1] = '\0';
        tempRep->startpos = i;
        
        temp->push_back(tempRep);        
        
        out.push_back(temp);
    }
    
    for(int i = 0; i < repetitionList.size(); i++)
    {        
        if(strlen(repetitionList[i]->repetitionStr) > 1)
        {
            out[repetitionList[i]->startpos]->push_back(repetitionList[i]);
        }
        else
        {
            if(repetitionList[i] != NULL)
            {
                delete repetitionList[i];
            }
        }     
    }
    
    return out;
}

void repetitionToPartitions_mem_file(vector<vector<repetition*>*> repetitionList, const char* filename)
{
    fstream outputFile;
        
    outputFile.open(filename,ios::out);
    
    partitionedString temp;
    
    recConstructPartions_mem_file(temp,repetitionList,outputFile,0, (int) repetitionList.size());
    
    
    outputFile.close();

}

void recConstructPartions_mem_file(partitionedString& currentPartitionedString, vector<vector<repetition*>*>& repetitionList, fstream& outFile, int curPos, int strLen)
{
    if(curPos < strLen)
    {
        for(unsigned int i = 0; i < repetitionList[curPos]->size(); i++)
        {
            int len = strlen((*repetitionList[curPos])[i]->repetitionStr);
            
            //Create new partition from repetition
            partition* temp = new partition;            
            temp->partitionStr = new char[len + 1];
            strcpy(temp->partitionStr,(*repetitionList[curPos])[i]->repetitionStr);
            
            //Append new partition to the current partitioned string
            currentPartitionedString.push_back(temp);
            
            recConstructPartions_mem_file(currentPartitionedString,repetitionList,outFile,curPos + 1, strLen);
            
            //Back track to save memory and create new partitions
            delete currentPartitionedString[currentPartitionedString.size() - 1];
            currentPartitionedString.pop_back();
        }
    }
    else if(curPos == strLen)
    {
        outFile << partitionedStringToString(currentPartitionedString) << endl;
    }
    
}
