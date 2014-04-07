#include "module_6.h"

void Partition(string pattern, bool tree, const char* fn)
{
    fstream file;
    vector<partitionedString> partitions;
    if(tree)
    {
        string filename = fn;
        
        file.open(filename.c_str());
        
        //if (!file.is_open()) 
        //{
            file.open(filename.c_str(), ios::out);
        
            partitionedString part;
            cout << "We are here..." << endl;
            createPartitionedString(pattern, part);
            cout << "We are here..." << endl;
            partitions.push_back(part);
            cout << "We are here..." << endl;
            printToFile(part, file);
            //file << part;
            cout << "We are here..." << endl;
            for(int i = 1; i < pattern.length(); i++) // i is number of partitions
            {                                         // per being found.
                cout << "We are here...\n";
                partitionedString newNode;
                split(i, 0, part, newNode, pattern);
                partitionToFile(newNode, partitions, pattern, 0, file);
            }
        /*}
        else
        {
            cout << pattern << " already computed.";
        }*/
    }
    else
    {
        istringstream tokens(pattern);
        string tmp;
        tokens >> tmp;
        
        while(tokens)
        {
            partitionedString part;
            
            cout << "We got: " << tmp <<endl;
            if(partitions.size() == 0)
            {
                createPartitionedString(tmp, part);
                partitions.push_back(part);
            }
            else partitions[0] = addToPartitionedString(partitions[0], tmp);
            
            tokens >> tmp;
        }
    }
    print(partitions, pattern);
}

partitionedString& addToPartitionedString(partitionedString& partitionedStr, string partitionToAdd)
{
    partition* tmpPartition = new partition;
    createPartition(partitionToAdd, tmpPartition);
    partitionedStr.push_back(tmpPartition);
    setupDistinct(partitionedStr);
    return partitionedStr;
}

void Partition(int currentIndex, partitionedString& part, 
        vector<partitionedString>& partitions, string pattern)
{        
    partitions.push_back(part);
    cout<<endl;
    print(part);
    
    for(int i = currentIndex + 1; i < pattern.length(); i++)
    {
        partitionedString newPart;
        split(i, currentIndex, part, newPart, pattern);
        Partition(currentIndex, newPart, partitions, pattern);
    }
}

void partitionToFile(partitionedString& partitioned, vector<partitionedString>& partitions, string pattern, int currentIndex, fstream& file)
{
    partitions.push_back(partitioned);
    cout<<endl;
    printToFile(partitioned, file);
    
    for(int i = currentIndex++; i < pattern.length(); i++)
    {
        partitionedString newPartitionedString;
        split(i, currentIndex, partitioned, newPartitionedString, pattern);
        partitionToFile(newPartitionedString, partitions, pattern, i, file);
    }
}

void createPartitionedString(string pattern, partitionedString& newPartitionedString)
{
    cout << "We are in createPartitionedString..." << endl;
    partition* initial = new partition;
    createPartition(pattern, initial);
    newPartitionedString.push_back(initial);
}


void createPartition(string pattern, partition* newPartition)
{
    cout << "We are in createPartition..." << endl;
    copyOverPatritionString(newPartition, pattern);
    newPartition->huffmanCWIndex; // TODO: Implement weight calculation
    newPartition->distinicIndex = -1;
}

void copyOverPatritionString(partition* newPartition, string pattern)
{
    /*cout << "We are in copyOverPatritionString..." << endl;
    newPartition->partitionStr = new char[pattern.length() + 1];
    cout << "Boo...";
    for(int i = 0; i < pattern.length(); i++)
    {
        cout << "*";
        newPartition->partitionStr[i] = pattern[i];
    }*/
    cout << "###  " << pattern.length() <<endl;
    newPartition->partitionStr = new char[pattern.length() + 1];
    cout << "***" <<endl;
    strcpy(newPartition->partitionStr, pattern.c_str());
}
void print(vector<partitionedString>& collection, string pattern)
{
    cout << "\nThe partitions for " << pattern << " are:\n";
    for(int i = 0; i < collection.size(); i++)
    {
        cout << i + 1 <<". "; print(collection[i]); cout <<endl;
    }
}

void print(partitionedString& partitions)
{
    for(int i = 0; i < partitions.size(); i++)
    {
        if(i == 0)
        {
            cout << partitions[i]->partitionStr;
        }
        else 
        {
            cout << "-" << partitions[i]->partitionStr;
        }
    }
    cout << endl;
}

void printToFile(partitionedString& partitions, fstream& file)
{
    for(int i = 0; i < partitions.size(); i++)
    {
        if(i == 0)
        {
            file << partitions[i]->partitionStr;
            cout << partitions[i]->partitionStr;
        }
        else 
        {
            file << "-" << partitions[i]->partitionStr;
            cout << "-" << partitions[i]->partitionStr;
        }
    }
    file << endl;
    cout << endl;
}

void print(partition* word)
{
    cout << word->partitionStr;
}

partitionedString& split(int index, int currentIndex, partitionedString& partStr, partitionedString& newPartStr, string pattern)
{
    copyPartitionedString(partStr, newPartStr);
    partition* part = newPartStr[newPartStr.size() - 1];

    string tmpStr = part->partitionStr;
    
    //newPart[newPart.size() - 1]->partitionStr = tmpStr.substr(0, index - currentIndex).c_str();
    copyOverPatritionString(newPartStr[newPartStr.size() - 1], tmpStr.substr(0, index - currentIndex));
    partition* tmpPart;
    createPartition(pattern.substr(index), tmpPart);
    newPartStr.push_back(tmpPart);
    setupDistinct(newPartStr);
        
    return newPartStr;
}

void copyPartitionedString(partitionedString& orig, partitionedString& newPartition)
{
    newPartition = orig;
    for(int i = 0; i < orig.size(); i++)
    {
        newPartition.push_back(orig.at(i));
    }
}

void setupDistinct(partitionedString& partitionedStr)
{
    for(int i = 0; i < partitionedStr.size(); i++)
    {
        partitionedStr[i]->distinicIndex = contains(partitionedStr, partitionedStr[i]);
        if(partitionedStr[i]->distinicIndex == -1)
        {
            partitionedStr[i]->distinicIndex = highestDistinct(partitionedStr) + 1;
        }
    }
}

int highestDistinct(partitionedString& partitionedStr)
{
    int tmpMax = -1;
    for(int i = 0; i < partitionedStr.size(); i++)
    {
        if(partitionedStr[i]->distinicIndex > tmpMax)
        {
            tmpMax = partitionedStr[i]->distinicIndex;
        }
    }
    
    return tmpMax;
}

int contains(partitionedString& partionedString, partition* partition)
{
    for(int i = 0; i < partionedString.size(); i++)
    {
        if(partionedString[i]->partitionStr == partition->partitionStr)
        {
            return partionedString[i]->distinicIndex;
        }
    }
    return -1;
}