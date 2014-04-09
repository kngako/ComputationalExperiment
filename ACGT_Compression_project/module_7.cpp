#include "module_7.h"



void partitionRepetitions_FromFile(const char* sourceFilename, const char* destFilname, int mode = 0)
{
    char* string = NULL;
    cout << sourceFilename << endl;
    cout << destFilname << endl;
    vector<repetition*> list = generateRepetitionListFromFile(sourceFilename, string);
    
    //If the list is in cluster order
    /*if(mode == 0)
    {
        vector<vector<repetition*>*> sortedList = repetitionListSorter(list,string);
        
        //repetitionToPartitions_mem_file(string,sortedList,list,destFilname);
        
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
    } */  
   
    if(mode == 0)
    {
        vector<vector<repetition*>*> sortedList = repetitionListSorterSingleRef(list,string);
        
        repetitionToPartitions_mem_file(string,sortedList,list,destFilname);
        
        //Free sorted list
        for(unsigned int i = sortedList.size(); i > 0; i--)
        {
            unsigned int k = i - 1;
            delete sortedList[k];
        }
    }
    
    //Free list

    while(list.size() > 0)
    {

        delete [] list[list.size() - 1]->repetitionStr;
        delete list[list.size() - 1];            
        
        list.pop_back();
    }
    
    if(string != NULL)
    {
        delete [] string;
    }
    
}

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


//Outputs a list sorted in starting order but each element points to single pointer representing that particular repetition string
//Note that the startpos of these repetition structures are now seen as counters of that particular repetition string
vector<vector<repetition*>*> repetitionListSorterSingleRef(vector<repetition*>& repetitionList, char* str)
{
    vector<repetition*> alreadyUsed;
    vector<vector<repetition*>*> out;
    int strLen = strlen(str);
    
    for(int i = 0; i < strLen; i++)
    {        
        vector<repetition*>* temp = new vector<repetition*>();       
        
        out.push_back(temp);
    }
    
    for(unsigned int i = 0; i < repetitionList.size(); i++)
    {        
        bool used = false;
        
        for(unsigned int j = 0; j < alreadyUsed.size(); j++)
        {
            //Check if already inserted in out
            if (strcmp(repetitionList[i]->repetitionStr,alreadyUsed[j]->repetitionStr) == 0)
            {                
                out[repetitionList[i]->startpos]->push_back(alreadyUsed[j]);

                //Discard unused pointers
                delete [] repetitionList[i]->repetitionStr;
                delete repetitionList[i];
                
                used = true;
                
                break;
            }
        }
        
        if(used == false)
        {
            //Convert startpos to a Counter
            repetitionList[i]->startpos = 0;
            
            out[repetitionList[i]->startpos]->push_back(repetitionList[i]);
            alreadyUsed.push_back(repetitionList[i]);
        }
        
        repetitionList[i] = NULL;
        
    } 
    repetitionList = alreadyUsed;
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

void repetitionToPartitions_mem_file(char* str, vector<vector<repetition*>*>& repetitionList, vector<repetition*>& list, const char* filename)
{
    fstream outputFile;
        
    outputFile.open(filename,ios::out);
    
    partitionedString temp;
    
    recRepetitionPartitioner_file(str,0,temp,repetitionList, list, outputFile);

    while (temp.size() > 0)
    {
        delete [] temp[temp.size() - 1]->partitionStr;
        delete temp[temp.size() - 1];
        temp.pop_back();
        
    }
    
    outputFile.close();

}

void recRepetitionPartitioner_file(char*& str, int curPos, partitionedString& currentPartitionedString, vector<vector<repetition*>*>& repetitionList, vector<repetition*>& list, fstream& outFile)
{

    if(curPos < repetitionList.size() && curPos > -1)
    {
        for(int i = 1; i <= repetitionList.size() - curPos; i++)
        {
            partition* temp = new partition;            
            temp->partitionStr = copyChar(str,curPos,i);
            temp->distinicIndex = -1;
            temp->huffmanCWIndex = -1;
            
            bool doSubtract = false;

            if(repetitionList[curPos]->size() >= i && strcmp(temp->partitionStr,(*repetitionList[curPos])[i - 1]->repetitionStr) == 0)
            {
                (*repetitionList[curPos])[i - 1]->startpos++;
                doSubtract = true;
            }
            
            currentPartitionedString.push_back(temp); 

            recRepetitionPartitioner_file(str, curPos + i, currentPartitionedString, repetitionList, list, outFile);            
            
            if(doSubtract)
            {
                (*repetitionList[curPos])[i - 1]->startpos--;
            }            
            
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
        
        for(unsigned int i = 0; i < list.size(); i++)
        {
            if(list[i]->startpos > 1)
            {
                
                setupDistinct(currentPartitionedString);
                setupHuffmanCW(currentPartitionedString);
                char* ptr = partitionedStringToString(currentPartitionedString);

                outFile << ptr << endl;
                delete [] ptr;
                
                break;
            }
        }        
        
    }
}

void recPartitioner_file(char*& str, int curPos, partitionedString& currentPartitionedString, fstream& outFile)
{
    int len = strlen(str);
    if(curPos < len && curPos > -1)
    {
        for(int i = 1; i <= len - curPos; i++)
        {
            partition* temp = new partition;            
            temp->partitionStr = copyChar(str,curPos,i);
            temp->distinicIndex = 0;
            temp->huffmanCWIndex = 0;
            
            currentPartitionedString.push_back(temp); 

            recPartitioner_file(str, curPos + i, currentPartitionedString, outFile);            
            
            delete [] temp->partitionStr;
            delete temp;
            
            if(currentPartitionedString.size() > 0)
            {               
                currentPartitionedString.pop_back();
            }
        }
    }
    else if(curPos == len)
    {
        char* ptr = partitionedStringToString(currentPartitionedString);
        outFile << ptr << endl;
        delete [] ptr;
    }
}


partitionedString getPartition_FromFile(const char* filename, unsigned long long int partIndex)
{    
    cout << filename << endl;
    char* data = getLine_FromFile(filename,partIndex);
    
    partitionedString temp;
    
    if(data != NULL)
    { 
    
        temp = stringToPartitionedString(data);
    
        delete [] data;
    }
    
    return temp;
}