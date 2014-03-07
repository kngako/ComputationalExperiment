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
        cout << "3: Module 2 - getNonIsomorphicStrings_NLen_File" << endl;
        cout << "4: Module 2 - getNonIsomorphicString_FromFile" << endl;
        cout << "5: Module 3 - getAllRepetitions_XYX_File" << endl;
        cout << "6: Module 3 - getRepetionOfNIStringI_FromFile" << endl;
        cout << "7: Module 4 - getCompressionGain_2Str" << endl;
        
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
                
                sprintf(fn,"%d.HUF",m);
                
                getHuffmanCodeWords_File(fn, m, 2);
                
                break;
            case 2:
                cout << "Please enter the m for the Huffman code words: ";
                cin >> m;
                
                cout << "Please enter the index of the Huffman code word in the file: ";     
                cin >> i;
                
                cout << "Code word at " << i << ": " << cwToString(getCodeWord_FromFile("", m, i)) << endl;
                break;
            case 3:
                cout << "Please enter the length of the non isomorphic strings to be generated: ";
                cin >> m;
                
                sprintf(fn,"%d.NIF",m);
                
                getNonIsomorphicStrings_NLen_File(fn, m, 0);
                
                break;
            case 4: 
                cout << "Please enter the length of the non isomorphic strings to find: ";
                cin >> m;
                
                cout << "Please enter the index of the non isomorphic string in the file: ";     
                cin >> i;

                cout << "Mapped string at " << i << ": " << getNonIsomorphicString_FromFile("", m, i).mappedStr << endl;                
                break;
            case 5: 
                cout << "Please enter a string to be scanned for XYX repetitions: ";
                cin >> strin;
                
                cout << "Please enter the index of the non isomorphic string in the file: ";     
                cin >> i;
                
                sprintf(fn,"%s.RFF",strin);
                
                getAllRepetitions_XYX_File(strin, fn); 
                break;
            case 6:
                
                //getRepetionOfNIStringI_FromFile();
                break;
            case 7:
                cout << "Please enter a a standard string: ";
                cin >> strin;
                
                cout << "Please enter a an encoded version of the string: ";
                cin >> strin2;
                
                getCompressionGain_2Str(strin,strlen(strin), strin2, strlen(strin));
                break;
            default: active = false;
                    break;                
        }
        
        cout << endl << "Ending testing" << endl;
    
    }
    
    
    return 0;
}

