#include "module_7.h"

vector<repetition*> generateRepetitionListFromFile(const char* filename, char*& string)
{
    vector<char*> temp = getAllLines_FromFile(filename);
    
    vector<repetition*> out;
    
    for(unsigned int i = 1; i < temp.size(); i++)
    {        
        repetition* ptr = stringToRepetitionPtr(temp[i]);
        out.push_back(ptr);
        
        delete [] temp[i];
        temp[i] = NULL;
    }
    
    if (temp.size() > 0)
    {
        string = temp[0];
        temp[0] = NULL;
    }
    
    return out;
}

//Sorts repetition list by order of starting position
vector<vector<repetition*>*> repetitionListSorter(vector<repetition*>& repetitionList, char* str)
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
    
    for(unsigned int i = 0; i < repetitionList.size(); i++)
    {        
        if(strlen(repetitionList[i]->repetitionStr) > 1)
        {
            out[repetitionList[i]->startpos]->push_back(repetitionList[i]);

            repetitionList[i] = NULL;
        } 
        else
        {
            delete [] repetitionList[i]->repetitionStr;
            delete repetitionList[i];
            repetitionList[i] = NULL;
        }
    } 
    
    return out;
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
            temp->distinicIndex = 0;
            temp->weight = 0;
            
            //Append new partition to the current partitioned string
            currentPartitionedString.push_back(temp);
            cout << "partition: " << partitionedStringToString(currentPartitionedString) << endl;
            //cout << curPos << endl;
            recConstructPartions_mem_file(currentPartitionedString,repetitionList,outFile,curPos + len, strLen);
            //cout << "partition: " << partitionedStringToString(currentPartitionedString) << endl;
            //Back track to save memory and create new partitions
            if(currentPartitionedString.size() > 0)
            {
                delete currentPartitionedString[currentPartitionedString.size() - 1];
                currentPartitionedString.pop_back();
                cout << currentPartitionedString.size() << endl;
            }
        }
    }
    else if(curPos >= strLen)
    {
        
        /*for(int i = 0; i< currentPartitionedString.size(); i++)
        {
            cout << currentPartitionedString[i]->partitionStr<<"-";
        }
        cout << endl;*/
        cout << "actual: " << partitionedStringToString(currentPartitionedString) << endl;
        outFile << partitionedStringToString(currentPartitionedString) << endl;
        return;
    }
    return;
}

void partitionRepetitions_FromFile(const char* sourceFilename, const char* destFilname, int mode)
{
    char* string = NULL;
    cout << sourceFilename << endl;
    cout << destFilname << endl;
    vector<repetition*> list = generateRepetitionListFromFile(sourceFilename, string);
    
    //If the list is in cluster order
    if(mode == 0)
    {
        vector<vector<repetition*>*> sortedList = repetitionListSorter(list,string);
        
        repetitionToPartitions_mem_file(string,sortedList,destFilname);
        
        //Free sorted list
        for(unsigned int i = sortedList.size(); i > 0; i--)
        {
            unsigned int k = i - 1;
            
            while(sortedList[k]->size() > 0)
            {

                delete [] (*sortedList[k])[sortedList[k]->size() - 1]->repetitionStr;
                delete (*sortedList[k])[sortedList[k]->size() - 1];
                sortedList[k]->pop_back();
            }

            delete sortedList[k];
        }
    }
    
    //Free list
    while(list.size() > 0)
    {
        if (list[list.size() - 1] != NULL)
        {
            delete [] list[list.size() - 1]->repetitionStr;
            delete list[list.size() - 1];            
        }
        list.pop_back();
    }
    
    if(string != NULL)
    {
        delete [] string;
    }
    
}

void repetitionToPartitions_mem_file(char* str, vector<vector<repetition*>*>& repetitionList, const char* filename)
{
    fstream outputFile;
        
    outputFile.open(filename,ios::out);
    
    partitionedString temp;
    
    recRepetitionPartitioner_file(str,0,temp,repetitionList,outputFile);

    while (temp.size() > 0)
    {
        delete [] temp[temp.size() - 1]->partitionStr;
        delete temp[temp.size() - 1];
        temp.pop_back();
        
    }
    
    outputFile.close();

}

void recRepetitionPartitioner_file(char*& str, int curPos, partitionedString& currentPartitionedString, vector<vector<repetition*>*>& repetitionList, fstream& outFile)
{
    if(curPos < repetitionList.size() && curPos > -1)
    {
        for(int i = 1; i <= repetitionList.size() - curPos; i++)
        {
            partition* temp = new partition;            
            temp->partitionStr = copyChar(str,curPos,i);
            temp->distinicIndex = 0;
            temp->weight = 0;
            
            currentPartitionedString.push_back(temp); 

            recRepetitionPartitioner_file(str, curPos + i, currentPartitionedString, repetitionList, outFile);            
            
            delete [] temp->partitionStr;
            delete temp;
            
            if(currentPartitionedString.size() > 0)
            {               
                currentPartitionedString.pop_back();
            }
        }
    }
    else if(curPos == repetitionList.size())
    {
        char* ptr = partitionedStringToString(currentPartitionedString);
        outFile << ptr << endl;
        delete [] ptr;
    }
}
