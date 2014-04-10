#include "module_6.h"

void Partition(string pattern, const char* fn)
{
    fstream file;
    vector<partitionedString> partitions;
//    if(tree)
//    {
    string filename = fn;

    file.open(filename.c_str());

    if (!file.is_open()) 
    {
        file.open(filename.c_str(), ios::out);

        partitionedString part;
        createPartitionedString(pattern, part);
        setupDistinct(part);
        setupHuffmanCW(part);
        partitions.push_back(part);
        printToFile(part, file);
        //file << part;
        for(int i = 1; i < pattern.length(); i++) // i is number of partitions
        {
            partitionedString newNode;
            split(i, 0, part, newNode, pattern);
            partitionToFile(newNode, partitions, pattern, i, file);
        }
        
        for(unsigned int i = 0; i < partitions.size(); i++)
        {
            for(unsigned int j = 0; j < partitions[i].size(); j++)
            {
                delete [] partitions[i][j]->partitionStr;
                delete partitions[i][j];
            }
        }
        
        file.close();
    }
    else
    {
        cout << " -NOTE: " << pattern << " already computed.";
    }
//    }
//    else
//    {
//        // TT-AAA-BCD
//        istringstream tokens(pattern);
//        string tmp;
//        tokens >> tmp;
//        
//        while(tokens)
//        {
//            partitionedString part;
//            
//            cout << "We got: " << tmp <<endl;
//            if(partitions.size() == 0)
//            {
//                createPartitionedString(tmp, part);
//                partitions.push_back(part);
//            }
//            else partitions[0] = addToPartitionedString(partitions[0], tmp);
//            
//            tokens >> tmp;
//        }
//    }
    //print(partitions, pattern);
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
    
    for(int i = currentIndex + 1; i < pattern.length() - 1; i++)
    {
        partitionedString newPart;
        split(i, currentIndex, part, newPart, pattern);
        Partition(currentIndex + 1, newPart, partitions, pattern);
    }
}

void partitionToFile(partitionedString& partitioned, vector<partitionedString>& partitions, string pattern, int currentIndex, fstream& file)
{
    partitions.push_back(partitioned);
    printToFile(partitioned, file);
    
    for(int i = currentIndex + 1; i < pattern.length(); i++)
    {
        partitionedString newPartitionedString;
        split(i, currentIndex, partitioned, newPartitionedString, pattern);
        partitionToFile(newPartitionedString, partitions, pattern, i, file);
    }
}

void createPartitionedString(string pattern, partitionedString& newPartitionedString)
{
    partition* initial = new partition;

    createPartition(pattern, initial);
    newPartitionedString.push_back(initial);
}


void createPartition(string pattern, partition* newPartition)
{
    
    copyOverPatritionString(newPartition, pattern);
    newPartition->huffmanCWIndex = -1; // TODO: Implement weight calculation
    newPartition->distinicIndex = -1;
}

void copyOverPatritionString(partition* newPartition, string pattern)
{
    newPartition->partitionStr = new char[pattern.length() + 1];
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
            cout << partitions[i]->partitionStr << "(" <<partitions[i]->distinicIndex <<"," <<partitions[i]->huffmanCWIndex  <<")" ;
            
        }
        else 
        {
            cout << "-" << partitions[i]->partitionStr << "(" <<partitions[i]->distinicIndex <<"," <<partitions[i]->huffmanCWIndex << ")";
        }
    }
    cout << endl;
}

void printToFile(partitionedString& partitions, fstream& file)
{
    char* temp = partitionedStringToString(partitions);
    
    file << temp << endl;
    
    delete [] temp;
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
    
    delete [] part->partitionStr;
    
    copyOverPatritionString(newPartStr[newPartStr.size() - 1], tmpStr.substr(0, index - currentIndex));
    partition* tmpPart = new partition;

    createPartition(pattern.substr(index), tmpPart);
    
    newPartStr.push_back(tmpPart);
    setupDistinct(newPartStr);
    setupHuffmanCW(newPartStr);
     
    // TODO: Output to the file
    return newPartStr;
}

void copyPartitionedString(partitionedString& orig, partitionedString& newPartition)
{
    for(int i = 0; i < orig.size(); i++)
    {
        partition* newPart = new partition;

        copyPartition(orig.at(i), newPart);
        newPartition.push_back(newPart);
    }
}

void copyPartition(partition* orig, partition* newPart)
{
    string tmp = orig->partitionStr;
    copyOverPatritionString(newPart, tmp);
    newPart->distinicIndex = orig->distinicIndex;
    newPart->huffmanCWIndex = orig->huffmanCWIndex;
}

