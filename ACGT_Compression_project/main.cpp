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

#include <iostream>



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
        cout << "20: Module 3 - getAllRepetitions_XYX_File (Modular)" << endl;
        cout << "21: Module 3 - getAllRepetitions_XYX_File (Modular)" << endl;
        cout << "22: Module 3 - getRepetionOfNIStringI_FromFile" << endl;
        cout << "30: Module 4 - getCompressionGain_2Str" << endl;
        
        int option = 0;
        cin >> option;
        
        int m;
        int i;
        char* fn = new char[STD_NUMBER_OF_CHARS];
        char* strin = new char[STD_NUMBER_OF_CHARS];
        char* strin2 = new char[STD_NUMBER_OF_CHARS];
        
        switch (option)
        {
            case 1: 
                cout << "Please enter the m for the Huffman code words: ";
                
                cin >> m;                
                
                sprintf(fn,"%d.%s",m, HUFFMAN_FILE_EXT);
                
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
                
                sprintf(fn,"%d.%s",m, NONISOMORPHIC_FILE_EXT);
                
                getNonIsomorphicStrings_NLen_File(fn, m, 0);
                
                break;
            case 11: 
                cout << "Please enter the length of the non isomorphic strings to find: ";
                cin >> m;
                
                cout << "Please enter the index of the non isomorphic string in the file: ";     
                cin >> i;

                cout << "Mapped string at " << i << ": " << getStringFromMap(getNonIsomorphicString_FromFile("", m, i))<< endl;                
                break;
                
            case 20: 
                cout << "Please enter a string to be scanned for XYX repetitions: ";
                cin >> strin;
                
                cout << "Please enter the index of the non isomorphic string in the file: ";     
                cin >> i;
                //AGGTGGA check
                sprintf(fn,"%s.%s",strin,REPETITION_FILE_EXT);
                
                getAllRepetitions_XYX_File(strin, fn); 
                break;
            case 21:
                
                cout << "Please enter the length of the non isomorphic strings to be scanned for XYX repetitions: ";
                cin >> m;
                
                cout << "Please enter the index of the non isomorphic string in the file that needs to be scanned: ";     
                cin >> i;
                                
                sprintf(fn,"%d_%d.%s", m, i, REPETITION_FILE_EXT);
                
                getAllRepetitions_XYX_File(getStringFromMap(getNonIsomorphicString_FromFile("", m, i)), fn); 
                
                break;
            case 22:
                cout << "Please enter the length of the non isomorphic string that was scanned: ";
                cin >> m;
                
                cout << "Please enter the index of the non isomorphic string that was scanned: ";     
                cin >> i;
                
                int j;
                
                cout << "Please enter the index of the XYX repetition: ";     
                cin >> j;
                
                cout << "The repetition " << j << " of non isomorphic string " <<  getStringFromMap(getNonIsomorphicString_FromFile("", m, i)) << " is: " << repetitionToString(getRepetionOfNIStringI_FromFile("",m,i,j)) << endl;
                
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
            default: active = false;
                    break;                
        }
        delete [] strin;
        delete [] strin2;
        delete [] fn;
        cout << endl << "=========Ending test" << endl;
        
    
    }
    
    
    return 0;
}

