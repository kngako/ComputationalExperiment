//COMPRESSION PROJECT: MODULE 4 ENCODING : module4.cpp
//Created by Mathys Ellis 26/02/2014
#include "module_4.h"

void calculateCompressionGain_FromPartitionFile(char* str, const char* partitionFilename, const char* outputFilename, const char* huffmanTablesPath)
{
    unsigned long long int p = 1;
    partitionedString tempPartitoned;
    
    ostringstream strm;
    fstream file;
    
    file.open(outputFilename,ios::out);
    
    do
    {
        tempPartitoned = getPartition_FromFile(partitionFilename,p);
        
        if(tempPartitoned.size() > 0)
        {
            calculateAndStoreCompressionGain(str,tempPartitoned,huffmanTablesPath,file);

            p++;
        }
        
        for(unsigned int i = 0; i < tempPartitoned.size(); i++)
        {
            delete [] tempPartitoned[i]->partitionStr;
            delete tempPartitoned[i];
        }
        
    } while(tempPartitoned.size() > 0);
    cout << "Number of partitions found in file: " << p - 1 << endl;
    file.close();
}

void calculateAndStoreCompressionGain(char* str, partitionedString& partitionedStr, const char* huffmanTableFilename, fstream& file)
{
    compressionInfo* temp = new compressionInfo;
    
    char* encodedStr = encodePartitionedStringToEncodedString(partitionedStr,huffmanTableFilename);
    cout << "String: " << str << endl;
    cout << "Encoded str: " << encodedStr << endl;
    int len1 = strlen(str);
    int len2 = strlen(encodedStr);
    //cout << len1 <<" " << len2 << endl;
    temp->gain = getCompressionGain_2Str(str,len1,encodedStr,len2);
    
    temp->partstr = partitionedStringToStripedString(partitionedStr);
    
    delete [] encodedStr;
    //cout << temp->gain << " " << temp->partstr << endl;
    char* out = compressionInfoToString(temp);
    
    file << out << endl;
    
    delete [] out;
    delete [] temp->partstr;
    delete temp;
}

double getCompressionGain_2Str(char* normal, int len1, char* encoded, int len2)
{
	double norm = getBitSizeOfStr(normal, len1);
	return ((norm - getBitSizeOfStr(encoded, len2)) / norm);
}

double getBitSizeOfStr(char* str, int len)
{
	double count = 0;

	for (int i = 0; i < len; i++)
	{
		switch (str[i]) 
		{
			case 'A':
			case 'C':
			case 'G':
			case 'T':					
			case ',':					
			case ':':
				count = count + 3;
				break;				
			case '0':				
			case '1':
				count++;	  
				break;				
			default:
				break;
		}
	}
	
	return count;
}

char* encodePartitionedStringToEncodedString(partitionedString& input, const char* huffLookupDirectory)
{
    if(input.size() > 0)
    {
        int m = input[0]->distinicIndex;
        ostringstream strm;
        ostringstream strm2;
        vector<char*> dictionary(m,(char*)NULL);
        codeWords huffmanCWs = getAllCodewords_FromFile(huffLookupDirectory, m);
        
        if(huffmanCWs.size() == 0)
        {
            return NULL;
        }
        
        //Find and order each huffman code word for dictionary from heaviest to lightest
        for (unsigned int i = 0; i < input.size(); i++)
        {
            int ind = input[i]->huffmanCWIndex; 
            
            //Create dictionary
            if(dictionary[ind] == NULL)
            {
                dictionary[input[i]->huffmanCWIndex] = new char [strlen(input[i]->partitionStr) + 1];
                strcpy(dictionary[ind],input[i]->partitionStr);                
            }
            
            //construct encoded string
            strm2 << cwToString(huffmanCWs[ind]);
            
        }
        
        
        //construct dictionary string
        while(dictionary.size() > 1)
        {
            
            if(dictionary[dictionary.size() - 1] != NULL)
            {
                strm << dictionary[dictionary.size() - 1] << ",";
                delete [] dictionary[dictionary.size() - 1];
            }            
            dictionary.pop_back();
        }
        
        if(dictionary[dictionary.size() - 1] != NULL)
        {
            strm << dictionary[dictionary.size() - 1] << ":";
            delete [] dictionary[dictionary.size() - 1];
        }            
        dictionary.pop_back();
        
        //concatenate streams
        strm << strm2.str();
        
        char* out = new char[strm.str().length() + 1];
        strcpy(out,strm.str().c_str());

        return out;
        
    }
    
    return NULL;
}

partitionedString decodePartitionedStringFromEncodedString(char* input, const char* huffLookupDirectory)
{
    
}

