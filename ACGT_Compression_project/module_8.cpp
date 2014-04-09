#include "module_8.h"

void setupDistinct(partitionedString& partitionedStr)
{
    for(unsigned int j = 0; j < partitionedStr.size(); j++)
    {
        partitionedStr[j]->distinicIndex = -1;
        partitionedStr[j]->huffmanCWIndex = -1;
    }
    
    int highest = -1;
    for(int i = 0; i < partitionedStr.size(); i++)
    {
        partitionedStr[i]->distinicIndex = contains(partitionedStr, partitionedStr[i]);
        if(partitionedStr[i]->distinicIndex == -1)
        {
            partitionedStr[i]->distinicIndex = highestDistinct(partitionedStr) + 1;
            highest = partitionedStr[i]->distinicIndex;
        }
    }
    highest++;
    for(int i = 0; i < partitionedStr.size(); i++)
    {
        partitionedStr[i]->distinicIndex = highest;
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
        if(strcmp(partionedString[i]->partitionStr,partition->partitionStr) == 0)
        {
            return partionedString[i]->distinicIndex;
        }
    }
    return -1;
}

void setupHuffmanCW(partitionedString& partitionedStr)
{
    // TODO: Implement a more elegent technique.
    partitionedString sorted;
    partitionedString tmpSorted;

    sorted.push_back(partitionedStr.at(0));
    for(int i = 1; i < partitionedStr.size(); i++)
    {
        if(contains(sorted, partitionedStr.at(i)) == -1)
        {
            partition* tmpBun = partitionedStr.at(i);

            while(!sorted.empty())
            {
                if(rank(partitionedStr, sorted.back()) < rank(partitionedStr, tmpBun))
                {
                    tmpSorted.push_back(sorted.back()); sorted.pop_back();
                } else break;
            }

            sorted.push_back(tmpBun);

            while(!tmpSorted.empty())
            {
                sorted.push_back(tmpSorted.back()); tmpSorted.pop_back();
            }
        }
    }

    //print(partitionedStr);
    //cout << sorted.size() << ". The sorted partitionedStrings are...\n";
    for(int i = 0; i < sorted.size(); i++)
    {
        for(int k = 0; k < partitionedStr.size(); k++)
        {
            if(strcmp(partitionedStr.at(k)->partitionStr, sorted.at(i)->partitionStr) == 0)
            {
                partitionedStr.at(k)->huffmanCWIndex = i;
            }
        }
        //cout << sorted.at(i)->partitionStr << "(" << sorted.at(i)->distinicIndex << "," << sorted.at(i)->huffmanCWIndex << ")" << endl;
    }
    //cout << endl;
}

int rank(partitionedString& whole, partition* part)
{
    return strlen(part->partitionStr) * partitionCount(whole,  part);
}

int partitionCount(partitionedString& whole, partition* part)
{
    int count = 0;
    for(int i = 0; i < whole.size(); i++)
    {
        if(strcmp(whole.at(i)->partitionStr,part->partitionStr) == 0) count++;
    }
    return count;
}

int getHuffmanCW(int huffmanCWIndex, int m)
{
    // TODO: Get a huffman table of size highestDistinct(whole) and allocate values relative to partitions huffmanCW
    //codeWords hoff = getHuffmanCodeWords_Memory(m);
    //return hoff[huffmanCWIndex];
}
