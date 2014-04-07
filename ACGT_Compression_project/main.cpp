/* 
 * File:   main.cpp
 * Author: MoX
 *
 * Created on 01 March 2014, 10:18 AM
 */
using namespace std;

#include <cstdlib>

#include "module_5.h"
#include "module_0.h"
#include "module_1.h"
#include "module_2.h"
#include "module_3.h"
#include "module_4.h"
#include "module_6.h"
#include "module_7.h"
#include <string>
#include <iostream>

void createPreCache(unsigned long long int m, unsigned long int l, unsigned long int h, const char* expName);
void createPartitionedStrings(const char* expName);
void calcualteCompressionGain(const char* expName);

/*
 * 
 */
int main(int argc, char** argv)   
{    
    bool active = true;
    
    while (active)
    {
        
        cout << endl << "Module testing unit" << endl;
        cout << "Choose test:" << endl;
        cout << "1: Module 1 - getHuffmanCodeWords_File " << endl;
        cout << "2: Module 1 - getCodeWord_FromFile " << endl;
        cout << "10: Module 2 - getNonIsomorphicStrings_NLen_File" << endl;
        cout << "12: Module 2 - getNonIsomorphicString_FromFile" << endl;
        cout << "20: Module 3 - getAllRepetitions_XYX_File (Unit)" << endl;
        cout << "21: Module 3 - getAllRepetitions_XYX_File (On file)" << endl;
        cout << "22: Module 3 - getRepetionOfNIStringI_FromFile" << endl;
        cout << "30: Module 4 - getCompressionGain_2Str" << endl;
        cout << "40: Module 6 - partition (Partition a string)" << endl;
        cout << "41: Module 6 - partition (Calculate weight of partitioned string)" << endl;
        cout << "50: Module 7 - Repetition partitioner" << endl;
        cout << "60: Precache - Precache the experiment" << endl;
        
        int option = 0;
        cin >> option;
        
        // TODO: Get rid of this hard coding.
        unsigned long long int m;
        unsigned long long int i;
        
        int l;
        int h;
        
        char* fn = new char[STD_NUMBER_OF_CHARS];
        char* fn2 = new char[STD_NUMBER_OF_CHARS];
        char* strin = new char[STD_NUMBER_OF_CHARS];
        char* strin2 = new char[STD_NUMBER_OF_CHARS];
        
        mappedString* tempMappedString = NULL;
        char* tempPtr = NULL;
        repetition* tempRep = NULL;
        
        string inStr;
        string experiment;
        string directory;
        
        switch (option)
        {
            case 1: 
                cout << "Please enter the m for the Huffman code words: ";
                
                cin >> m;                
                
                sprintf(fn,"%llu.%s",m, HUFFMAN_FILE_EXT);
                
                getHuffmanCodeWords_File(fn, m, 2);
                
                break;
            case 2:
                cout << "Please enter the m for the Huffman code words: ";
                cin >> m;
                
                cout << "Please enter the index of the Huffman code word in the file: ";     
                cin >> i;
                
                cout << "Code word at " << i << ": " << cwToString(getCodeWord_FromFile("", m, i)) << endl;
                break;
            case 10:
                cout << "Please enter the length of the non isomorphic strings to be generated: ";
                cin >> m;
                
                sprintf(fn,"%llu.%s",m, NONISOMORPHIC_FILE_EXT);
                
                getNonIsomorphicStrings_NLen_File(fn, (int) m, 0);
                
                break;
            case 11: 
                cout << "Please enter the length of the non isomorphic strings to find: ";
                cin >> m;
                
                cout << "Please enter the index of the non isomorphic string in the file: ";     
                cin >> i;
                
                tempMappedString = getNonIsomorphicString_FromFile("", m, i);
                tempPtr = getStringFromMap(tempMappedString);
                
                cout << "Mapped string at " << i << ": " << tempPtr << endl;      
                
                delete [] tempPtr;
                delete [] tempMappedString->mappedStr;
                delete tempMappedString;
                
                break;
                
            case 20: 
                cout << "Please enter a string to be scanned for XYX repetitions: ";
                cin >> strin;
                
                //AGGTGGA check
                sprintf(fn,"%s.%s",strin,REPETITION_FILE_EXT);
                
                getAllRepetitions_XYX_File(strin, fn); 
                break;
            case 21:
                
                cout << "Please enter the length of the non isomorphic strings to be scanned for XYX repetitions: ";
                cin >> m;
                
                cout << "Please enter the index of the non isomorphic string in the file that needs to be scanned: ";     
                cin >> i;
                                
                sprintf(fn,"%llu_%llu.%s", m, i, REPETITION_FILE_EXT);
                cout << fn << endl;
                
                tempMappedString = getNonIsomorphicString_FromFile("", m, i);
                tempPtr = getStringFromMap(tempMappedString); 
                
                getAllRepetitions_XYX_File(tempPtr, fn); 
                
                delete [] tempPtr;
                delete [] tempMappedString->mappedStr;
                delete tempMappedString;
                
                break;
            case 22:
                cout << "Please enter the length of the non isomorphic string that was scanned: ";
                cin >> m;
                
                cout << "Please enter the index of the non isomorphic string that was scanned: ";     
                cin >> i;
                
                int j;
                
                cout << "Please enter the index of the XYX repetition: ";     
                cin >> j;
                
                tempMappedString = getNonIsomorphicString_FromFile("", m, i);
                tempPtr = getStringFromMap(tempMappedString);
                tempRep = getRepetionOfNIStringI_FromFile("",m,i,j);
                
                cout << "The repetition " << j << " of non isomorphic string " <<  tempPtr << " is: " ;
                
                delete [] tempPtr;
                
                tempPtr = repetitionToString(tempRep);      
                
                cout<< tempPtr << endl;
                
                delete [] tempPtr;
                
                delete [] tempMappedString->mappedStr;
                delete tempMappedString;
                
                delete []tempRep->repetitionStr;
                delete tempRep;
                
                break;
            case 30:
                
                //ACACACACACAC
                //ACA,CAC:1010
                cout << "Please enter a standard string: ";
                cin >> strin;
                
                cout << "Please enter a an encoded version of the string: ";
                cin >> strin2;
                
                cout << "The compression gain of " << strin << " over " << strin2 << " : " << getCompressionGain_2Str(strin,strlen(strin), strin2, strlen(strin)) << endl;
                break;
                
            case 40:
                cout << "Please enter a string to be partitioned: ";
                cin >> strin;
                
                sprintf(fn,"%s.%s", strin, PARTITION_FILE_EXT);
                
                //partition(strin,true,fn);
                
                break;
            case 41:
                cout << "Please enter a partitioned string to be analysed: ";
                //cin >> strin;
                cin.getline(strin,STD_NUMBER_OF_CHARS);
                //cin.getline(strin,STD_NUMBER_OF_CHARS,'\n');
                //getline(cin, inStr, '\n');
                
                sprintf(fn,"%s.%s", inStr.c_str(), PARTITION_FILE_EXT);
                
                //partition("TT B DAC ABBA ABBA C DAC B DAC TT",false,fn);
                
                break;
            case 50:
                cout << "Please enter the length of the non isomorphic string who's repetition needs to be partitioned: ";
                cin >> m;
                
                cout << "Please enter the index of the non isomorphic string who's repetition needs to be partitioned: ";     
                cin >> i;
                                
                sprintf(fn,"%llu_%llu.%s", m, i, REPETITION_FILE_EXT);
                sprintf(fn2,"%llu_%llu.%s", m, i, PARTITION_FILE_EXT);
                partitionRepetitions_FromFile(fn, fn2,0); 
                break;
            case 60:      
                cout << "Enter precache experiment name[ExpName]: ";
                cin >> experiment;
                cout << "Enter the maximum 'm' for the Huffman table:" << endl;
                cin >> m;
                cout << "Enter the range of the Non-isomorphic string lengths your are working with:" << endl;
                cout << "From lowest to highest." << endl << "Lowest: ";
                cin >> l;
                cout << "Highest: ";
                cin >> h;
                createPreCache(m,l,h,experiment.c_str());
                break;
            default: 
                active = false;
                break;                
        }
        delete [] strin;
        delete [] strin2;
        delete [] fn;
        delete [] fn2;
        cout << endl << "=========Ending test" << endl;
        
    
    }
    
    
    return 0;
}

void createPreCache(unsigned long long int m, unsigned long int l, unsigned long int h, const char* name)
{
    ostringstream strm;
    
    strm << "mkdir " << name;    
    system(strm.str().c_str());
    strm << FILEMANAGER_PATH_DELIMINATOR << PRECACHE_SUFFIX_FOLDER_NAME;
    
    system(strm.str().c_str());
    strm << FILEMANAGER_PATH_DELIMINATOR << HUFFMAN_FOLDER_NAME;
    system(strm.str().c_str());
    strm.str("");
    strm << "mkdir " << name << PRECACHE_SUFFIX_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR << NONISOMORPHIC_FOLDER_NAME;
    system(strm.str().c_str());
    
    if (m > 0)
    {
        for(int i = 1; i <= m; i++)
        {
            strm.str("");
            strm << name << PRECACHE_SUFFIX_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR << HUFFMAN_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR << i << "." << HUFFMAN_FILE_EXT;     
            
            getHuffmanCodeWords_File(strm.str().c_str(), i, 2);
        }
        
        if(l <= h && l > 0 && h > 0)
        {
            for(int i = l; i <= h; i++)
            {
                strm.str("");
                strm << name << PRECACHE_SUFFIX_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR << NONISOMORPHIC_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR << i << "." << NONISOMORPHIC_FILE_EXT;
                
                cout << "Generating NIF file for strings of length " << i << ":" << endl;                
                getNonIsomorphicStrings_NLen_File(strm.str().c_str(), i, 0);
            }
        }
        else
        {
            cout << "The l and h values must be bigger than 0 nor may l be more than h" << endl;
        }
    }
    else
    {
        cout << "m value must be bigger than 0" << endl;        
    }
}

void createPartitionedStrings(const char* expName)
{
    ostringstream strm;
    
    strm << "mkdir " << expName << PARTITIONEDDATA_SUFFIX_FOLDER_NAME;    
    system(strm.str().c_str());
    
    strm << FILEMANAGER_PATH_DELIMINATOR << REPETITIONS_FOLDER_NAME;
    system(strm.str().c_str());
    
    strm.str("");
    strm << "mkdir " << expName << PARTITIONEDDATA_SUFFIX_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR << ALLPARTITIONS_FOLDER_NAME;
    system(strm.str().c_str());
    
    strm.str("");
    strm << "mkdir " << expName << PARTITIONEDDATA_SUFFIX_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR << REPPARTITIONS_FOLDER_NAME;
    system(strm.str().c_str());
}