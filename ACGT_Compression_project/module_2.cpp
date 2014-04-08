//COMPRESSION PROJECT: MODULE 2 NON ISOMORPHIC STRING GEN: module_2.cpp
//Created by Mathys Ellis 02/12/2013

#include "module_2.h"

//This function returns all non isomorphic strings for the specified mappedString *Warning very high resource usage*
vector<mappedString> getAllNonIsomorphicStrings_NLen(int strLen)
{
   vector<mappedString> result;

   recDownString(strLen, 0, "", '0', -1, result);

   return result;
}

//This function returns the fist K non isomorphic strings fot the specified mappedString
vector<mappedString> getKNonIsomorphicStrings_NLen(int strLen, int K)
{
   vector<mappedString> result;

   recDownString(strLen, 0, "", '0', K, result);

   return result;
}

//This function is downward recursive funtion that finds all possible nonisomorphic patterns
void recDownString(int strLength, int curLength, char* curStr, char nextChar, int maxNoOfResults, vector<mappedString> &result)
{
	//Base Case: When the max number of strings has been created
	//
	if(maxNoOfResults > -1 && result.size() >= maxNoOfResults)
	{
		return;
	}
	//Base Case: When the string of the specified length has been created
	if(strLength == curLength)
	{
		return;
	}
	else
	{
		char* newStr = new char[curLength + 2]; //create a new char* string in memory

		strcpy(newStr, curStr); //Copy old string to new
		newStr[curLength] = nextChar; //Add new char to string
		newStr[curLength + 1] = '\0'; //Null terminate newStr

		int newLength = curLength + 1;

		//Store newly created string
		if (strLength == newLength)
		{
			mappedString temp;

			temp.mapping[A_IDX] = 0;
			temp.mapping[C_IDX] = 1;
			temp.mapping[G_IDX] = 2;
			temp.mapping[T_IDX] = 3;

			temp.mappedStr = new char[newLength + 1];
			strcpy(temp.mappedStr, newStr);

			result.push_back(temp);

			return;
		}

		//Allow for 0 or 1 next chars
		if(newLength >= 1)
		{
			recDownString(strLength, newLength, newStr, '0', maxNoOfResults, result);
			recDownString(strLength, newLength, newStr, '1', maxNoOfResults, result);
		}


		//Allow for 0 or 1 or 2 next chars
		if(strstr(newStr, "1") != NULL)
		{
			recDownString(strLength, newLength, newStr, '2', maxNoOfResults, result);
		}

		//Allow for 0 or 1 or 2 or 3 next chars
		if(strstr(newStr, "2") != NULL)
		{
			recDownString(strLength, newLength, newStr, '3', maxNoOfResults, result);
		}

		if (newStr != NULL)
		{
			delete [] newStr; //clear old c-string from memory
		}

		return;
	}

}

bool isIsomorphic(char* str1, char* str2)
{
	mappedString* ms1 = mapString(str1);
	mappedString* ms2 = mapString(str2);

	if(strcmp(ms1->mappedStr,ms2->mappedStr) == 0)
	{
                return true;
	}
        
        delete [] ms1->mappedStr;
        delete [] ms2->mappedStr;
        delete ms1;
        delete ms2;

	return false;
}

bool getNonIsomorphicStrings_NLen_File(const char* filename, int len, unsigned long long int limit)
{
	fstream outputFile;

	outputFile.open(filename,ios::out);
	
        unsigned long long int counter = 0;
        
        cout << "Number of strings: " << getNumberOfIsomorphicStringFor(len) << endl;
        
        char* temp = new char[1];
        temp[0] = '\0';
	if(limit > 0)
	{
		recDownString_File(len,0,temp,'0',limit, counter, outputFile);
	}
	else
	{
		recDownString_File(len,0,temp,'0',-1, counter, outputFile);
        }
        
        delete [] temp;
        
        cout << endl;
        
	outputFile.close();

	return true;
}

double getNumberOfIsomorphicStringFor(int len)
{
    double sum = 0;

	if(len > 1)
	{
        sum = 2;
		sum += 3 * (pow((double) 2,(len - 2)) - 1);

		if(len > 3)
		{
			for(int i = 3; i < len; i++)
			{
				sum += ((pow((double) 4, (len - i - 1)) * (pow((double)2,(i - 2)) - 1)) * 4);
			}
		}

	}
	else if(len == 1)
	{
		sum = 1;
	}

	return sum;
}



void recDownString_File(int strLength, int curLength, char*& curStr, char nextChar, unsigned long long int maxNoOfResults, unsigned long long int& counter, fstream& outFile)
{
	//Base Case: When the max number of strings has been created
	//
	if(maxNoOfResults > -1 && counter >= maxNoOfResults)
	{
		return;
	}
	//Base Case: When the string of the specified length has been created
	if(strLength == curLength)
	{
		return;
	}
	else
	{
		char* newStr = new char[curLength + 2]; //create a new char* string in memory

		strcpy(newStr, curStr); //Copy old string to new
		newStr[curLength] = nextChar; //Add new char to string
		newStr[curLength + 1] = '\0'; //Null terminate newStr

		if (curStr != 0)
		{
			delete [] curStr;
			curStr = 0;
		}

		curStr = newStr;

		int newLength = curLength + 1;

		//Store newly created string
		if (strLength == newLength)
		{
			mappedString* temp = new mappedString;

			temp->mapping[A_IDX] = 0;
			temp->mapping[C_IDX] = 1;
			temp->mapping[G_IDX] = 2;
			temp->mapping[T_IDX] = 3;

			temp->mappedStr = new char[newLength + 1];
			strcpy(temp->mappedStr, curStr);

			char* outStr = mappedStringToString(temp);
                        
			outFile << outStr << endl;

			delete [] outStr;
                        delete [] temp->mappedStr;
                        delete temp;

			counter++;

                        newStr = 0; //create a new char* string in memory
			newStr = new char[curLength + 1];

			cout << '\r' << "Generated: " << counter;

			strncpy(newStr, curStr, curLength); //Copy old string to new

			newStr[curLength] = '\0'; //Null terminate newStr

			if (curStr != 0)
			{
				delete [] curStr;
				curStr = 0;
			}

			curStr = newStr;

			return;
		}

		//Allow for 0 or 1 next chars
		if(newLength >= 1)
		{
			recDownString_File(strLength, newLength, curStr, '0', maxNoOfResults, counter, outFile);
			recDownString_File(strLength, newLength, curStr, '1', maxNoOfResults, counter, outFile);
		}


		//Allow for 0 or 1 or 2 next chars
		if(strstr(curStr, "1") != NULL)
		{
			recDownString_File(strLength, newLength, curStr, '2', maxNoOfResults, counter, outFile);
		}

		//Allow for 0 or 1 or 2 or 3 next chars
		if(strstr(curStr, "2") != NULL)
		{
			recDownString_File(strLength, newLength, curStr, '3', maxNoOfResults, counter, outFile);
		}

		/*if (newStr != 0)
		{
            countS++;
			//cout << '\r' << count << " " << newStr;
			delete [] newStr; //clear old c-string from memory
			cout << '\r' << countA << " " << countS << " " << countA / countS;
			newStr = 0;
			//cout << '\r' << count << " " << newStr;
		}*/

		newStr = 0; //create a new char* string in memory
		newStr = new char[curLength + 1];

		strncpy(newStr, curStr, curLength); //Copy old string to new

		newStr[curLength] = '\0'; //Null terminate newStr

		if (curStr != 0)
		{
			delete [] curStr;
			curStr = 0;
		}

		curStr = newStr;

		return;
	}

}

mappedString* getNonIsomorphicString_FromFile(const char* path, unsigned long long int lenIndex, unsigned long long int NIStringIndex)
{
    char* filename = new char[STD_NUMBER_OF_CHARS];
    sprintf(filename,"%s%llu.%s", path, lenIndex, NONISOMORPHIC_FILE_EXT);
    cout << filename << endl;
    char* data = getLine_FromFile(filename,NIStringIndex);
    
    delete [] filename;
    
    mappedString* temp = NULL;
    
    if(data != NULL)
    { 
    
        temp = stringToMappedString(data);
    
        delete [] data;
    }
    
    return temp;
}