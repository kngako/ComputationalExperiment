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

void execStage1_precache(unsigned long long int m, unsigned long int l, unsigned long int h, const char* expName);
void execStage2_partitiondata(const char* expName);
void execStage3_calculationdata(const char* expName);
void execStage4_analysisdata(const char* expName);

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
            case 51:
                cout << "A partitoned string: ";
                cin >> strin;
                cout << strin;
                stringToPartitionedString (strin);
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
                execStage1_precache(m,l,h,experiment.c_str());
                execStage2_partitiondata(experiment.c_str());
                execStage3_calculationdata(experiment.c_str());
                execStage4_analysisdata(experiment.c_str());
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

void execStage1_precache(unsigned long long int m, unsigned long int l, unsigned long int h, const char* name)
{
    ostringstream strm;
    
    cout << "Setting up precache data folder for stage 1..." << endl;
    
    strm << name << FILEMANAGER_PATH_DELIMINATOR;
    char* experimentPath = new char[strm.str().length() + 1];
    strcpy(experimentPath,strm.str().c_str());
    
    strm << PRECACHE_SUFFIX_FOLDER_NAME;
    char* precachePath = new char[strm.str().length() + 1];
    strcpy(precachePath,strm.str().c_str());
    
    strm << FILEMANAGER_PATH_DELIMINATOR << HUFFMAN_FOLDER_NAME;
    char* humffmanFolderPath = new char[strm.str().length() + 1];
    strcpy(humffmanFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << precachePath << FILEMANAGER_PATH_DELIMINATOR << NONISOMORPHIC_FOLDER_NAME;
    char* NIstringsFolderPath = new char[strm.str().length() + 1];
    strcpy(NIstringsFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << "mkdir " << name;
        cout << strm.str().c_str() << endl;    
    system(strm.str().c_str());
    
    ceateInfoFile(experimentPath,l,h,m);
    
    strm.str("");
    strm << "mkdir " << precachePath;
    cout << strm.str().c_str() << endl;
    system(strm.str().c_str());
    
    
    strm.str("");
    strm << "mkdir " <<  humffmanFolderPath;
    cout << strm.str().c_str() << endl;
    system(strm.str().c_str());

    strm.str("");
    strm << "mkdir " << NIstringsFolderPath;
    cout << strm.str().c_str() << endl;
    system(strm.str().c_str());
    
    if (m > 0)
    {
        cout << "Populating " << HUFFMAN_FOLDER_NAME << " folder for stage 1..." << endl;
        for(int i = 1; i <= m; i++)
        {
            strm.str("");
            strm << humffmanFolderPath << FILEMANAGER_PATH_DELIMINATOR << i << "." << HUFFMAN_FILE_EXT;     
            
            getHuffmanCodeWords_File(strm.str().c_str(), i, 2);
        }
        
        cout << "Populating " << NONISOMORPHIC_FOLDER_NAME << " folder for stage 1..." << endl;
        
        if(l <= h && l > 0 && h > 0)
        {
            for(int i = l; i <= h; i++)
            {
                strm.str("");
                strm << NIstringsFolderPath << FILEMANAGER_PATH_DELIMINATOR << i << "." << NONISOMORPHIC_FILE_EXT;
                
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
    
    delete [] NIstringsFolderPath;
    delete [] experimentPath;
    delete [] humffmanFolderPath;
    delete [] precachePath;
    
    cout << "Stage 1 complete..." << endl << "=======================================" << endl;
}

void execStage2_partitiondata(const char* expName)
{
    ostringstream strm;
    
    cout << "Setting up partitioned data folder for stage 2..." << endl;
    
    strm << expName << FILEMANAGER_PATH_DELIMINATOR;
    char* experimentPath = new char[strm.str().length() + 1];
    strcpy(experimentPath,strm.str().c_str());
    
    unsigned long long int* infoFiledata = readInfoFile(experimentPath);
    
    strm.str("");
    strm << experimentPath << PARTITIONEDDATA_SUFFIX_FOLDER_NAME;
    char* partitionedDataPath = new char[strm.str().length() + 1];
    strcpy(partitionedDataPath,strm.str().c_str());
    
    strm << FILEMANAGER_PATH_DELIMINATOR << REPETITIONS_FOLDER_NAME;
    char* repetitionsFolderPath = new char[strm.str().length() + 1];
    strcpy(repetitionsFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << partitionedDataPath << FILEMANAGER_PATH_DELIMINATOR << ALLPARTITIONS_FOLDER_NAME;
    char* allpartitionsFolderPath = new char[strm.str().length() + 1];
    strcpy(allpartitionsFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << partitionedDataPath << FILEMANAGER_PATH_DELIMINATOR << REPPARTITIONS_FOLDER_NAME;
    char* reppartitionsFolderPath = new char[strm.str().length() + 1];
    strcpy(reppartitionsFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << expName << FILEMANAGER_PATH_DELIMINATOR << PRECACHE_SUFFIX_FOLDER_NAME;
    char* precachePath = new char[strm.str().length() + 1];
    strcpy(precachePath,strm.str().c_str());
    
    strm.str("");
    strm << precachePath << FILEMANAGER_PATH_DELIMINATOR << HUFFMAN_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR;
    char* humffmanFolderPath = new char[strm.str().length() + 1];
    strcpy(humffmanFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << precachePath << FILEMANAGER_PATH_DELIMINATOR << NONISOMORPHIC_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR;
    char* NIstringsFolderPath = new char[strm.str().length() + 1];
    strcpy(NIstringsFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << "mkdir " << partitionedDataPath;
    system(strm.str().c_str());

    strm.str("");
    strm << "mkdir " << repetitionsFolderPath;
    system(strm.str().c_str());    
    
    strm.str("");
    strm << "mkdir " << allpartitionsFolderPath;
    system(strm.str().c_str());

    strm.str("");
    strm << "mkdir " << reppartitionsFolderPath;
    system(strm.str().c_str());
    
    cout << "Populating " << REPETITIONS_FOLDER_NAME << " , " << REPPARTITIONS_FOLDER_NAME << " and " << ALLPARTITIONS_FOLDER_NAME << " folders for stage 2..." << endl;

    for (unsigned long long int i = infoFiledata[1]; i <= infoFiledata[2]; i++)
    {
        cout << "Generating partition files for stings of length: " << i << endl;
        double count = getNumberOfIsomorphicStringFor(i);
        for(unsigned long long int j = 1; j <= getNumberOfIsomorphicStringFor(i); j++)
        {
            cout << "\r Processing " << j << " of " << count << " files (" << (100 * (j/count)) << "% complete)";
            mappedString* temp = getNonIsomorphicString_FromFile(NIstringsFolderPath,i,j);
            char* str = getStringFromMap(temp);
            
            delete [] temp->mappedStr;
            delete temp;
            
            strm.str("");
            strm << repetitionsFolderPath << FILEMANAGER_PATH_DELIMINATOR;
            strm << i << "_" << j << "." << REPETITION_FILE_EXT;
            
            char* repfile = new char[strm.str().length() + 1];
            strcpy(repfile,strm.str().c_str());
            //cout << endl << "============================================" << endl;
            //cout << "Generating repetitions for " << str << "..." << endl;
            getAllRepetitions_XYX_File(str,repfile);
            
            strm.str("");
            strm << reppartitionsFolderPath << FILEMANAGER_PATH_DELIMINATOR;
            strm << i << "_" << j << "." << PARTITION_FILE_EXT;
            
            //cout << "Generating partitions that contain repetitions for " << str << "..." << endl;
            partitionRepetitions_FromFile(repfile,strm.str().c_str(),0);
            
            strm.str("");
            strm << allpartitionsFolderPath << FILEMANAGER_PATH_DELIMINATOR;
            strm << i << "_" << j << "." << PARTITION_FILE_EXT;
            
            //cout << "Generating all partitions for " << str << "..." << endl;
            Partition(str,strm.str().c_str());
            
            delete [] repfile;
            
            delete [] str;
        }
        cout << endl;
    }
    
    
    delete [] NIstringsFolderPath;
    delete [] experimentPath;
    delete [] humffmanFolderPath;
    delete [] precachePath;
    delete [] allpartitionsFolderPath;
    delete [] repetitionsFolderPath;
    delete [] reppartitionsFolderPath;
    delete [] partitionedDataPath;
    delete [] infoFiledata;
    
    cout << "Stage 2 complete..." << endl << "=======================================" << endl;
}

void execStage3_calculationdata(const char* expName)
{
    ostringstream strm;
    
    cout << "Setting up calculation data folder for stage 3..." << endl;
    
    strm << expName << FILEMANAGER_PATH_DELIMINATOR;
    char* experimentPath = new char[strm.str().length() + 1];
    strcpy(experimentPath,strm.str().c_str());
    
    unsigned long long int* infoFiledata = readInfoFile(experimentPath);
    
    strm.str("");
    strm << experimentPath << CALCULATIONDATA_SUFFIX_FOLDER_NAME;
    char* calculationDataPath = new char[strm.str().length() + 1];
    strcpy(calculationDataPath,strm.str().c_str());
    
    strm.str("");
    strm << experimentPath << CALCULATIONDATA_SUFFIX_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR << ALLRESULTS_FOLDER_NAME;
    char* allresultsPath = new char[strm.str().length() + 1];
    strcpy(allresultsPath,strm.str().c_str());
    
    strm.str("");
    strm << experimentPath << CALCULATIONDATA_SUFFIX_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR << REPRESULTS_FOLDER_NAME;
    char* represultsPath = new char[strm.str().length() + 1];
    strcpy(represultsPath,strm.str().c_str());
    
    strm.str("");
    strm << experimentPath << PARTITIONEDDATA_SUFFIX_FOLDER_NAME;
    char* partitionedDataPath = new char[strm.str().length() + 1];
    strcpy(partitionedDataPath,strm.str().c_str());
    
    strm << FILEMANAGER_PATH_DELIMINATOR << REPETITIONS_FOLDER_NAME;
    char* repetitionsFolderPath = new char[strm.str().length() + 1];
    strcpy(repetitionsFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << partitionedDataPath << FILEMANAGER_PATH_DELIMINATOR << ALLPARTITIONS_FOLDER_NAME;
    char* allpartitionsFolderPath = new char[strm.str().length() + 1];
    strcpy(allpartitionsFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << partitionedDataPath << FILEMANAGER_PATH_DELIMINATOR << REPPARTITIONS_FOLDER_NAME;
    char* reppartitionsFolderPath = new char[strm.str().length() + 1];
    strcpy(reppartitionsFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << expName << FILEMANAGER_PATH_DELIMINATOR << PRECACHE_SUFFIX_FOLDER_NAME;
    char* precachePath = new char[strm.str().length() + 1];
    strcpy(precachePath,strm.str().c_str());
    
    strm.str("");
    strm << precachePath << FILEMANAGER_PATH_DELIMINATOR << HUFFMAN_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR;
    char* humffmanFolderPath = new char[strm.str().length() + 1];
    strcpy(humffmanFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << precachePath << FILEMANAGER_PATH_DELIMINATOR << NONISOMORPHIC_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR;
    char* NIstringsFolderPath = new char[strm.str().length() + 1];
    strcpy(NIstringsFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << "mkdir " << calculationDataPath;
    system(strm.str().c_str());

    strm.str("");
    strm << "mkdir " << allresultsPath;
    system(strm.str().c_str());    
    
    strm.str("");
    strm << "mkdir " << represultsPath;
    system(strm.str().c_str());  
    
    cout << "Populating " << ALLRESULTS_FOLDER_NAME << " and " << REPRESULTS_FOLDER_NAME << " folder for stage 3..." << endl;

    for (unsigned long long int i = infoFiledata[1]; i <= infoFiledata[2]; i++)
    {
        cout << "Generating results files for stings of length: " << i << endl;
        double count = getNumberOfIsomorphicStringFor(i);
        for(unsigned long long int j = 1; j <= count; j++)
        {
            cout << "\r Processing " << j << " of " << count << " files (" << (100 * (j/count)) << "% complete)";
            mappedString* temp = getNonIsomorphicString_FromFile(NIstringsFolderPath,i,j);
            char* str = getStringFromMap(temp);
            
            delete [] temp->mappedStr;
            delete temp;
            
            
            //cout << endl << "============================================" << endl;
            
            strm.str("");
            strm << represultsPath << FILEMANAGER_PATH_DELIMINATOR;
            strm << i << "_" << j << "." << COMPRESSION_GAIN_FILE_EXT; 
            char* resultFile = new char[strm.str().length() + 1];
            strcpy(resultFile,strm.str().c_str());
            
            //cout << "Generating results for all partitions of " << str << " that contain repetitions..." << endl;
            
            strm.str("");
            strm << reppartitionsFolderPath << FILEMANAGER_PATH_DELIMINATOR;
            strm << i << "_" << j << "." << PARTITION_FILE_EXT; 
            char* partFile = new char[strm.str().length() + 1];
            strcpy(partFile,strm.str().c_str());
            
            calculateCompressionGain_FromPartitionFile(str,partFile,resultFile,humffmanFolderPath);
            
            delete [] resultFile;
            delete [] partFile;
            
            //cout << "Generating results for all partitions of " << str << "..." << endl;
            
            strm.str("");
            strm << allresultsPath << FILEMANAGER_PATH_DELIMINATOR;
            strm << i << "_" << j << "." << COMPRESSION_GAIN_FILE_EXT; 
            resultFile = new char[strm.str().length() + 1];
            strcpy(resultFile,strm.str().c_str());
            
            strm.str("");
            strm << allpartitionsFolderPath << FILEMANAGER_PATH_DELIMINATOR;
            strm << i << "_" << j << "." << PARTITION_FILE_EXT;            
            partFile = new char[strm.str().length() + 1];
            strcpy(partFile,strm.str().c_str()); 
            
            calculateCompressionGain_FromPartitionFile(str,partFile,resultFile,humffmanFolderPath);
            
            delete [] partFile;
            delete [] resultFile;
            
            delete [] str;
        }
        cout << endl;
    }
    
    delete [] NIstringsFolderPath;
    delete [] experimentPath;
    delete [] humffmanFolderPath;
    delete [] precachePath;
    delete [] allpartitionsFolderPath;
    delete [] repetitionsFolderPath;
    delete [] reppartitionsFolderPath;
    delete [] partitionedDataPath;
    delete [] calculationDataPath;
    delete [] represultsPath;
    delete [] allresultsPath;
    delete [] infoFiledata;
    
    cout << "Stage 3 complete..." << endl << "=======================================" << endl;
}

void execStage4_analysisdata(const char* expName)
{
    ostringstream strm;
    
    cout << "Setting up analysis data folder for stage 4..." << endl;
    
    strm << expName << FILEMANAGER_PATH_DELIMINATOR;
    char* experimentPath = new char[strm.str().length() + 1];
    strcpy(experimentPath,strm.str().c_str());
    
    unsigned long long int* infoFiledata = readInfoFile(experimentPath);
    
    strm.str("");
    strm << experimentPath << CALCULATIONDATA_SUFFIX_FOLDER_NAME;
    char* calculationDataPath = new char[strm.str().length() + 1];
    strcpy(calculationDataPath,strm.str().c_str());
    
    strm.str("");
    strm << experimentPath << CALCULATIONDATA_SUFFIX_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR << ALLRESULTS_FOLDER_NAME;
    char* allresultsPath = new char[strm.str().length() + 1];
    strcpy(allresultsPath,strm.str().c_str());
    
    strm.str("");
    strm << experimentPath << CALCULATIONDATA_SUFFIX_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR << REPRESULTS_FOLDER_NAME;
    char* represultsPath = new char[strm.str().length() + 1];
    strcpy(represultsPath,strm.str().c_str());
    
    strm.str("");
    strm << experimentPath << CALCULATIONDATA_SUFFIX_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR << ALL_ANALYSIS_FOLDER_NAME;
    char* AllAnalysisPath = new char[strm.str().length() + 1];
    strcpy(AllAnalysisPath,strm.str().c_str());
    
    strm.str("");
    strm << experimentPath << CALCULATIONDATA_SUFFIX_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR << REP_ANALYSIS_FOLDER_NAME;
    char* RepAnalysisPath = new char[strm.str().length() + 1];
    strcpy(RepAnalysisPath,strm.str().c_str());
    
    strm.str("");
    strm << experimentPath << PARTITIONEDDATA_SUFFIX_FOLDER_NAME;
    char* partitionedDataPath = new char[strm.str().length() + 1];
    strcpy(partitionedDataPath,strm.str().c_str());
    
    strm << FILEMANAGER_PATH_DELIMINATOR << REPETITIONS_FOLDER_NAME;
    char* repetitionsFolderPath = new char[strm.str().length() + 1];
    strcpy(repetitionsFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << partitionedDataPath << FILEMANAGER_PATH_DELIMINATOR << ALLPARTITIONS_FOLDER_NAME;
    char* allpartitionsFolderPath = new char[strm.str().length() + 1];
    strcpy(allpartitionsFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << partitionedDataPath << FILEMANAGER_PATH_DELIMINATOR << REPPARTITIONS_FOLDER_NAME;
    char* reppartitionsFolderPath = new char[strm.str().length() + 1];
    strcpy(reppartitionsFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << expName << FILEMANAGER_PATH_DELIMINATOR << PRECACHE_SUFFIX_FOLDER_NAME;
    char* precachePath = new char[strm.str().length() + 1];
    strcpy(precachePath,strm.str().c_str());
    
    strm.str("");
    strm << precachePath << FILEMANAGER_PATH_DELIMINATOR << HUFFMAN_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR;
    char* humffmanFolderPath = new char[strm.str().length() + 1];
    strcpy(humffmanFolderPath,strm.str().c_str());
    
    strm.str("");
    strm << precachePath << FILEMANAGER_PATH_DELIMINATOR << NONISOMORPHIC_FOLDER_NAME << FILEMANAGER_PATH_DELIMINATOR;
    char* NIstringsFolderPath = new char[strm.str().length() + 1];
    strcpy(NIstringsFolderPath,strm.str().c_str());

    strm.str("");
    strm << "mkdir " << AllAnalysisPath;
    system(strm.str().c_str());
    
    strm.str("");
    strm << "mkdir " << RepAnalysisPath;
    system(strm.str().c_str());
    
    cout << "Populating " << ALL_ANALYSIS_FOLDER_NAME << " and " << REP_ANALYSIS_FOLDER_NAME << " folder for stage 4..." << endl;

    for (unsigned long long int i = infoFiledata[1]; i <= infoFiledata[2]; i++)
    {
        cout << "Generating analysis files for stings of length: " << i << endl;
        double count = getNumberOfIsomorphicStringFor(i);                       
            
        //cout << endl << "============================================" << endl;

        strm.str("");
        strm << represultsPath << FILEMANAGER_PATH_DELIMINATOR;
        char* resultPath = new char[strm.str().length() + 1];
        strcpy(resultPath,strm.str().c_str());

        //cout << "Generating results for all partitions of " << str << " that contain repetitions..." << endl;

        strm.str("");
        strm << RepAnalysisPath << FILEMANAGER_PATH_DELIMINATOR; 
        char* analysisPath = new char[strm.str().length() + 1];
        strcpy(analysisPath,strm.str().c_str());

        analysisCompressionGainInfo_ForLenN(analysisPath,resultPath,i,count);

        delete [] resultPath;
        delete [] analysisPath;

        //cout << "Generating results for all partitions of " << str << "..." << endl;

        strm.str("");
        strm << allresultsPath << FILEMANAGER_PATH_DELIMINATOR;
        resultPath = new char[strm.str().length() + 1];
        strcpy(resultPath,strm.str().c_str());

        strm.str("");
        strm << AllAnalysisPath << FILEMANAGER_PATH_DELIMINATOR;            
        analysisPath = new char[strm.str().length() + 1];
        strcpy(analysisPath,strm.str().c_str());

        analysisCompressionGainInfo_ForLenN(analysisPath,resultPath,i,count);


        delete [] resultPath;
        delete [] analysisPath;
        
        cout << endl;
    }
    
    delete [] NIstringsFolderPath;
    delete [] experimentPath;
    delete [] humffmanFolderPath;
    delete [] precachePath;
    delete [] allpartitionsFolderPath;
    delete [] repetitionsFolderPath;
    delete [] reppartitionsFolderPath;
    delete [] partitionedDataPath;
    delete [] AllAnalysisPath;
    delete [] RepAnalysisPath;
    delete [] calculationDataPath;
    delete [] represultsPath;
    delete [] allresultsPath;
    delete [] infoFiledata;
    
    cout << "Stage 4 complete..." << endl << "=======================================" << endl;

}