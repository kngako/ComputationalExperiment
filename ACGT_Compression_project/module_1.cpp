//COMPRESSION PROJECT: MODULE 1 HUFFMAN CODE GENERATOR: module_1.cpp
//Created by Mathys Ellis 31/01/2013

#include "module_1.h"

codeWords generateHuffmanCodeWordsI_CW(int noOfCodeWords, bool firstCode)
{
	codeWords temp;
	temp.resize(noOfCodeWords);

	//Loop throught each code word
	for(int i = 0; i < noOfCodeWords; i++)
	{
        //First value generated is always the firstCode value
		if (i == 0)
		{
			temp[i].push_back(firstCode);
		}
		//Last value generated is always same length as the prior value but has a firstCode at the end
		else if (i == (noOfCodeWords - 1))
		{
			temp[i].push_back(!firstCode);
			for(int x = 1; x < noOfCodeWords - 1; x++)
			{
				temp[i].push_back(firstCode);
			}
		}
		//The values generated inbetween always have the same length as (i + 1) but the start and end bits are !firstCode
		else
		{
			temp[i].push_back(!firstCode);
			for(int x = 1; x <= i - 1; x++)
			{
				temp[i].push_back(firstCode);
			}
			temp[i].push_back(!firstCode);
		}
	}

	return temp;
}

bitstream generateHuffmanCodeWordsI_BS(int noOfCodeWords, bool firstCode)
{
	bitstream temp;

	//Loop throught each code word
	for(int i = 0; i < noOfCodeWords; i++)
	{
		//First value generated is always the firstCode value
		if (i == 0)
		{
			temp.push_back(firstCode);
		}
		//Last value generated is always same length as the prior value but has a firstCode at the end
		else if (i == (noOfCodeWords - 1))
		{
			temp.push_back(!firstCode);
			for(int x = 1; x < noOfCodeWords - 1; x++)
			{
				temp.push_back(firstCode);
			}
		}
		//The values generated inbetween always have the same length as (i + 1) but the start and end bits are !firstCode
		else
		{
			temp.push_back(!firstCode);
			for(int x = 1; x <= i - 1; x++)
			{
				temp.push_back(firstCode);
			}
			temp.push_back(!firstCode);
		}
	}

	return temp;
}

codeWords generateHuffmanCodeWordsR_CW(int noOfCodeWords, bool firstCode)
{
	codeWords temp;

	int toplevel = (int) ((log10l(noOfCodeWords)/log10l(2)) + 1);
	int total = (int) (powl(2,(double)toplevel));

	int noOnPreLevel = total - noOfCodeWords;

	int codeWordCount = 0;

	recDownCodeWords(toplevel, noOfCodeWords - noOnPreLevel, noOfCodeWords, 0, codeWordCount, temp, *(new codeWord), false);

	return temp;

}

void recDownCodeWords(int levels, int noInTopLevels, int noOfCW, int countLevel, int& codeWordCount, codeWords& cws, codeWord curCW, bool side)
{
	if(codeWordCount < noInTopLevels)
	{
		if(countLevel < levels)
		{
			if(countLevel > 0)
			{
				curCW.push_back(side);
			}
			countLevel++;
			//Left and right side
			recDownCodeWords(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,cws,curCW,0);
			recDownCodeWords(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,cws,curCW,1);
		}
		else
		{
			curCW.push_back(side);
			cws.push_back(curCW);
			codeWordCount++;
		}
	}
	else if (codeWordCount < noOfCW)
	{
		if(countLevel < levels - 1)
		{

			if(countLevel > 0)
			{
				curCW.push_back(side);
			}
			countLevel++;
			//Left and right side
			recDownCodeWords(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,cws,curCW,0);
			recDownCodeWords(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,cws,curCW,1);
		}
		else
		{
			curCW.push_back(side);
			cws.push_back(curCW);
			codeWordCount++;
		}
	}

	return;
}

void recDownCodeWords_File(unsigned long long int levels, unsigned long long int noInTopLevels, unsigned long long int noOfCW, unsigned long long int countLevel, unsigned long long int& codeWordCount, fstream& outFile, codeWord curCW, bool side)
{
	if(codeWordCount < noInTopLevels)
	{
		if(countLevel < levels)
		{
			if(countLevel > 0)
			{
				curCW.push_back(side);
			}
			countLevel++;
			//Left and right side
			recDownCodeWords_File(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,outFile,curCW,0);
			recDownCodeWords_File(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,outFile,curCW,1);
		}
		else
		{
			curCW.push_back(side);
                        char* ptr = cwToString(curCW);
			outFile << ptr;
                        
                        delete [] ptr;
			codeWordCount++;

			if(codeWordCount < noOfCW)
			{
				//outFile << ",";
                                outFile << " ";
			}
		}
	}
	else if (codeWordCount < noOfCW)
	{
		if(countLevel < levels - 1)
		{

			if(countLevel > 0)
			{
				curCW.push_back(side);
			}
			countLevel++;
			//Left and right side
			recDownCodeWords_File(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,outFile,curCW,0);
			recDownCodeWords_File(levels, noInTopLevels, noOfCW, countLevel,codeWordCount,outFile,curCW,1);
		}
		else
		{
			curCW.push_back(side);
                        char* ptr = cwToString(curCW);
                        
			outFile << ptr;
                        delete [] ptr;
                        
			codeWordCount++;                        
                        cout << "Generated: " << codeWordCount << '\r';
			if(codeWordCount < noOfCW)
			{
				outFile << " ";
                            //outFile << ",";
			}

		}
	}

	return;
}


codeWord getCodeWord(int noOfCodeWords, bool firstCode, int index)
{
	codeWord temp;
	
	//First value generated is always the firstCode value
	if (index == 1)
	{
		temp.push_back(firstCode);
	}
	//Last value generated is always same length as the prior value but has a firstCode at the end
	else if (index == noOfCodeWords)
	{
		temp.push_back(!firstCode);
		for(int x = 1; x < noOfCodeWords - 1; x++)
		{
			temp.push_back(firstCode);
		}
	}
	//The values generated inbetween always have the same length as (i + 1) but the start and end bits are !firstCode
	else
	{
		temp.push_back(!firstCode);
		for(int x = 1; x <= index - 2; x++)
		{
			temp.push_back(firstCode);
		}
		temp.push_back(!firstCode);
	}
		
	return temp;
}

codeWord getCodeWord_FromFile(const char* path, unsigned long long int m, unsigned long long int codewordIndex)
{
    char* filename = new char[STD_NUMBER_OF_CHARS];
    sprintf(filename,"%s%llu.%s", path,m, HUFFMAN_FILE_EXT);
    
    char* data = getLine_FromFile(filename,m);
    
    delete [] filename;
    
    codeWord temp;
    
    if(data != NULL)
    {    
        temp = findCodeWordInString(data, codewordIndex);

        delete [] data;
    }
    
    return temp;
}

codeWords getHuffmanCodeWords_Memory(int m, int series)
{
	if (series == 1)
	{
		return generateHuffmanCodeWordsI_CW(m, true);
	}
	else
	{
		return generateHuffmanCodeWordsR_CW(m, true);
    }
}

bool getHuffmanCodeWords_File(const char* filename, unsigned long long int m, int series)
{
	fstream outputFile;
        
	outputFile.open(filename,ios::out);

	codeWord temp;

	bool firstCode = true;
        
        
	for(unsigned long long int j = 1; j <= m; j++)
	{
                cout << "Huffman codewords for m = " << j << endl;
                outputFile << j << " ";
                //outputFile << "{m:" << j << ",data:[";

		if (series == 1)
		{

			//Loop throught each code word
			for(int i = 0; i < j; i++)
			{
				//First value generated is always the firstCode value
				if (i == 0)
				{
					temp.push_back(firstCode);
				}
				//Last value generated is always same length as the prior value but has a firstCode at the end
				else if (i == (j - 1))
				{
					temp.push_back(!firstCode);
					for(int x = 1; x < j - 1; x++)
					{
						temp.push_back(firstCode);
					}
				}
				//The values generated inbetween always have the same length as (i + 1) but the start and end bits are !firstCode
				else
				{
					temp.push_back(!firstCode);
					for(int x = 1; x <= i - 1; x++)
					{
						temp.push_back(firstCode);
					}
					temp.push_back(!firstCode);
				}

				outputFile << cwToString(temp);
				if(i < j - 1)
				{
                                    outputFile << " ";
                                    //outputFile << ",";
				}

				temp.clear();
			}
		}
		else
		{
			unsigned long long int toplevel = (unsigned long long int) ((log10l(j)/log10l(2)) + 1);
			unsigned long long int total = (unsigned long long int) (powl(2,toplevel));

			unsigned long long int noOnPreLevel = total - j;

			unsigned long long int codeWordCount = 0;
                        
                        cout << "Number of codewords to generate: " << j << endl;
                        codeWord* tempCW = new codeWord;
                        
			recDownCodeWords_File(toplevel, j - noOnPreLevel, j, 0, codeWordCount, outputFile, *tempCW, false);
                        
                        delete tempCW;
                        
                        cout << endl;
		}
                outputFile << endl;
		//outputFile << "]}" << endl;

	}

	outputFile.close();

	return true;
}


