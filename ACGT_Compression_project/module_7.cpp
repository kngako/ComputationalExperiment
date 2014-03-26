#include "module_7.h"

vector<repetition*> generateRepetitionList(const char* path, int lenIndex, int NIStringIndex, int repIndex)
{
    
}

vector<vector<repetition>*> repetitionSorter(vector<repetition*> repetitionList, char* str)
{
    vector<vector<repetition>*> out;
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

void repetitionToPartitions_mem_file(vector<vector<repetition*>*> repetitionList)
{
    
}

void recConstructPartions_mem_file(vector<partition*>& currentPartitionedString, vector<vector<repetition*>*>& repetitionList, fstream& outFile, int curPos, int strLen)
{
    if(curPos < strLen)
    {
        for(int i = 0; i < repetitionList[curPos].size(); i++)
        {
            int len = strlen(repetitionList[curPos][i]->repetitionStr);
            partition* temp = new partition;
            
            temp->partitionStr = new char[len + 1];
            strcpy(temp->partitionStr,repetitionList[curPos][i]->repetitionStr);
            currentPartitionedString.push_back(temp);
            
            recConstructPartions_mem_file(currentPartitionedString,repetitionList,outFile,curPos + 1, strLen);
            
            delete currentPartitionedString[currentPartitionedString.size() - 1];
            currentPartitionedString.pop_back();
        }
    }
    else if(curPos == strLen)
    {
        
    }
}
