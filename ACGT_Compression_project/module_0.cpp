//COMPRESSION PROJECT: MODULE 0 TYPES AND CONVERSION: module_0.cpp
//Created by Mathys Ellis 01/03/2014
#include "module_0.h"

void errorMsg(char* msg)
{
    fprintf(stdout, "%s \n", msg);
}

//module_1
//==============================================================================

char* cwToString(codeWord cw)
{
    int len = cw.size();
    char* temp = new char[len + 1];

    for(int i = 0; i < len; i++)
    {
            temp[i] = (char) (cw[i] + 48);
    }
    temp[len] = '\0';

    return temp;
}

char** cwsToString(codeWords cws)
{
    int len = cws.size();
    char** temp = new char*[len];

    for(int i = 0; i < len; i++)
    {
            temp[i] = cwToString(cws[i]);
    }

    return temp;
}

char* bsToString(bitstream bs)
{
    int len = bs.size();
    char* temp = new char[len];

    for(int i = 0; i < len; i++)
    {
            temp[i] = (char) (bs[i] + 48);
    }

    return temp;
}

codeWord stringToCodeWord(char* str)
{
    int len = strlen(str);
    
    codeWord temp;
    
    for(int i = 0; i < len; i++)
    {
        temp.push_back((str[i]=='0')?false:true);        
    }
    
    return temp;
}

codeWord findCodeWordInString(char* str, int index)
{
    codeWord temp; 
    char* curTok = strtok(str," ");
    int count = -1;

    while(curTok != NULL)
    {
        if(count == index)
        {
            return stringToCodeWord(curTok);
        }
        curTok = strtok(NULL," ");
        count++;
    }

    return temp;
}
//Heaviest to lightest
codeWords getAllCodeWordsInString(char* str)
{
    codeWords temp; 
    int curPos = 0;
    char* curTok = nextTok(str,curPos," ");
    int count = 0;

    while(curTok != NULL)
    {
        if(count > 0)
        {
            temp.push_back(stringToCodeWord(curTok));
        }
        
        delete [] curTok;
        
        curTok = nextTok(str,curPos," ");
        
        count++;
    }

    return temp;
}

//module_2
//==============================================================================

//This function maps the inputted string and returns a mappedString
mappedString* mapString(char* inputStr)
{
    mappedString* result = new mappedString; //resulting mappedString
    int len = strlen(inputStr); //length of the input string
    int curIDXCount = 0; //Mapping counter for the A-C-G-T chars

    //intialise result;
    result->mapping[A_IDX] = -1;
    result->mapping[C_IDX] = -1;
    result->mapping[G_IDX] = -1;
    result->mapping[T_IDX] = -1;

    result->mappedStr = new char[len];

    for(int i = 0; i < len; i++)
    {
    int* cur; //Pointer to current INDEX a.k.a IDX *used to simplfiy code*

            //Checks current char of inputStr and sets cur to point to correct mapping index of result
            switch (toupper(inputStr[i]))
            {
                    case 'A': cur = &result->mapping[A_IDX];
                            break;
                    case 'C': cur = &result->mapping[C_IDX];
                            break;
                    case 'G': cur = &result->mapping[G_IDX];
                            break;
                    case 'T': cur = &result->mapping[T_IDX];
                            break;
                    default:
                            result->mappedStr = NULL;
                            result->mapping[A_IDX] = -1;
                            result->mapping[C_IDX] = -1;
                            result->mapping[G_IDX] = -1;
                            result->mapping[T_IDX] = -1;
                            return result;//error code
                            break;
            }

            //Checks if index not set
            if(*cur == -1)
            {
                    *cur = curIDXCount++; //sets index to the lowest avalible map value avalible *This must be in range of 0..3*
            }

            result->mappedStr[i] = (char)(*cur + 48); //Adds the current map value to the complete mapped string of result
    }

    result->mappedStr += '\0'; //Null terminate the mappedStr of result

    return result;
}

//This function converts the mappedString to a normal c-string
char* getStringFromMap(mappedString* inputMap)
{
    int len = strlen(inputMap->mappedStr);

    char* result = new char[len + 1];

    //scan and replace mappedStr with orginal chars and store it in result
    for(int i = 0; i < len; i++)
    {
    //Check mappedStr[i] against the mapping value of each A-C-G-T char
            if((int) inputMap->mappedStr[i] == inputMap->mapping[A_IDX] + 48)
            {
                    result[i] = 'A';
            }
            else if((int) inputMap->mappedStr[i] == inputMap->mapping[C_IDX] + 48)
            {
                    result[i] = 'C';
            }
            else if((int) inputMap->mappedStr[i] == inputMap->mapping[G_IDX] + 48)
            {
                    result[i] = 'G';
            }
            else if((int) inputMap->mappedStr[i] == inputMap->mapping[T_IDX] + 48)
            {
                    result[i] = 'T';
            }
            else
            {
        return NULL; //error code
    }

    }

    result[len] = '\0';  //Null terminate the result

    return result;
}

char* mappedStringToString(mappedString* map)
{
    ostringstream strm;
    strm << map->mappedStr << " " << map->mapping[A_IDX] << " " << map->mapping[C_IDX] << " " << map->mapping[G_IDX] << " " << map->mapping[T_IDX];
	
    char* outStr = new char[strm.str().length() + 1];

    strcpy(outStr,strm.str().c_str());

    return outStr;
}

mappedString* stringToMappedString(char* str)
{
        mappedString* temp = new mappedString;

	char* curTok = strtok(str," ");
	int count = 0;

	while(curTok != NULL && count <= 4)
	{
		switch (count)
		{
			case 0: temp->mappedStr = new char[strlen(curTok) + 1];
                                strcpy(temp->mappedStr,curTok);       
				break;
                        case 1: temp->mapping[A_IDX] = atoi(curTok);
				break;
                        case 2: temp->mapping[C_IDX] = atoi(curTok);
				break;
                        case 3: temp->mapping[G_IDX] = atoi(curTok);
				break;
                        case 4: temp->mapping[T_IDX] = atoi(curTok);
				break;
			default:
				break;
		}

		curTok = strtok(NULL," ");
	  	count++;
	}

	return temp;
}

//module_3
//==============================================================================
char* repetitionToString(repetition* rep)
{
        ostringstream strm;

	strm << rep->repetitionStr;
	strm << " " << rep->startpos;

	char* ptrStr = new char[strm.str().length() + 1];
        
	strcpy(ptrStr,strm.str().c_str());

	return ptrStr;
}

repetition stringToRepetition(char* str)
{
	repetition temp;

	char* curTok = strtok(str," ");
	int count = 0;

	while(curTok != NULL && count <= 1)
	{
		switch (count)
		{

			case 0: temp.repetitionStr = new char[strlen(curTok) + 1];
                                strcpy(temp.repetitionStr,curTok);                       
				break;

			case 1: temp.startpos = atoi(curTok);
				break;

			default:
				break;
		}

		curTok = strtok(NULL," ");
	  	count++;
	}

	return temp;
}

repetition* stringToRepetitionPtr(char* str)
{
        repetition* temp = new repetition;

	char* curTok = strtok(str," ");
	int count = 0;

	while(curTok != NULL && count <= 1)
	{
		switch (count)
		{

			case 0: temp->repetitionStr = new char[strlen(curTok) + 1];
                                strcpy(temp->repetitionStr,curTok);                       
				break;
			case 1: temp->startpos = atoi(curTok);
				break;

			default:
				break;
		}

		curTok = strtok(NULL," ");
	  	count++;
	}

	return temp;
}


//module_4
//==============================================================================
bitstream encodeString_compressed(char * string, int len)
{
	/*Mapping
	  A = 000;
	  C = 001;
	  G = 010;
	  T = 011;
	  , = 100;
	  : = 101;
	*/

	bool posSwitch = false;
	bitstream output;

	for (int i = 0; i < len; i++)
	{
		if(posSwitch == false)
		{
			switch (string[i]) 
			{
				case 'A':
					output.push_back(0);  
					output.push_back(0);
					output.push_back(0);
					break;
				case 'C':
					output.push_back(0);  
					output.push_back(0);
					output.push_back(1);
					break;
				case 'G':
					output.push_back(0);  
					output.push_back(1);
					output.push_back(0);
					break;
				case 'T':
					output.push_back(0);  
					output.push_back(1);
					output.push_back(1);
					break;
				case ',':
					output.push_back(1);  
					output.push_back(0);
					output.push_back(0);
					break;
				case ':':
					output.push_back(1);  
					output.push_back(0);
					output.push_back(1);
					posSwitch = true;
					break;
				default:
					break;
			}
			
		}
		else
		{
             switch (string[i]) 
			{
				case '0':
					output.push_back(0);  
					break;
				case '1':
					output.push_back(1);  
					break;				
				default:
					break;
			}
        }
	}

}

char* decodeString_compressed(bitstream bits)
{
    int size = (int) (bits.size());
    char* temp = new char[size];
    bool switchMode = false;
    
    for(int i = 0; i < size; i++)
    {
        if (switchMode == false)
        {
            for(int k = 0; k < 3; k++)
            {
                char ch[3] = "";            
                ch[k] = (bits[i + k] == false)?'0':'1';
                
                int j = (int) (i/3);
                if(strcmp(ch, "000") == 0)
                {
                    temp[j] = 'A';
                }
                else if(strcmp(ch, "001") == 0)
                {
                    temp[j] = 'C';
                }
                else if(strcmp(ch, "010") == 0)
                {
                    temp[j] = 'G';
                }
                else if(strcmp(ch, "011") == 0)
                {
                    temp[j] = 'T';
                }
                else if(strcmp(ch, "100") == 0)
                {
                    temp[j] = ',';
                }
                else if(strcmp(ch, "101") == 0)
                {
                    temp[j] = ':';
                    switchMode = true;
                }
                
                
            }
            i = i + 3;
        }
        else
        {
            temp[i] = (bits[i] == false)?'0':'1';
            i++;
        }
    }
}

//converts a compressionInfo in to "<partionStr> <gain>
char* compressionInfoToString(compressionInfo* info)
{
    std::ostringstream strm;
    
    strm << info->partstr;
    strm << " ";
    strm << info->gain;
    
    char* outStr = new char [strm.str().length() + 1];
    strcpy(outStr,strm.str().c_str());
    
    return outStr;
}

//converts a string to  compressionInfo
compressionInfo* stringToCompressionInfo(char* str)
{
    compressionInfo* temp = new compressionInfo;

    char* curTok = strtok(str," ");
    int count = 0;

    while(curTok != NULL && count <= 1)
    {
            switch (count)
            {
                    case 0: temp->partstr = new char[strlen(curTok) + 1];
                            strcpy(temp->partstr,curTok);       
                            break;
                    case 1: temp->gain = atof(curTok);
                            break;                    
                    default:
                            break;
            }
            curTok = strtok(NULL," ");
            count++;
    }

    return temp;
}

//Module_7 & Module_6
//==============================================================================
char* partitionToString(partition part)
{
    
    std::ostringstream strm;
    
    strm << part.partitionStr;
    strm << " ";
    strm << part.distinicIndex;
    strm << " ";
    strm << part.huffmanCWIndex;
    
    char* outStr = new char [strm.str().length() + 1];
    strcpy(outStr,strm.str().c_str());
    return outStr;
}

char* partitionToString(partition* part)
{
    
    std::ostringstream strm;

    strm << part->partitionStr;
    strm << " ";
    strm << part->distinicIndex;
    strm << " ";
    strm << part->huffmanCWIndex;   
    
    char* outStr = new char [strm.str().length() + 1];
    strcpy(outStr,strm.str().c_str());
    return outStr;
}

char* partitionedStringToString(partitionedString& partStr)
{
    std::ostringstream strm;
    
    for(int i = 0; i < partStr.size() - 1; i++)
    {        
        char * ptr = partitionToString(partStr[i]);
        strm << ptr;
        delete [] ptr;
        
        strm << "-";
    }
    
    if(partStr.size() > 0)
    {
        char * ptr = partitionToString(partStr[partStr.size() - 1]);
        strm << ptr;
        delete [] ptr;        
    }
    
    strm << "\0";

    char* outStr = new char[strm.str().length() + 1];
    
    strcpy(outStr,strm.str().c_str());

    return outStr;
}

char* partitionedStringToStripedString(partitionedString& partStr)
{
    std::ostringstream strm;
    
    for(int i = 0; i < partStr.size() - 1; i++)
    {        
        char * ptr = new char[strlen(partStr[i]->partitionStr) + 1];
        strcpy(ptr,partStr[i]->partitionStr);
        strm << ptr;
        delete [] ptr;
        
        strm << "-";
    }
    
    if(partStr.size() > 0)
    {
        char * ptr = new char[strlen(partStr[partStr.size() - 1]->partitionStr) + 1];
        strcpy(ptr,partStr[partStr.size() - 1]->partitionStr);
        strm << ptr;
        delete [] ptr;        
    }
    
    strm << "\0";

    char* outStr = new char[strm.str().length() + 1];
    
    strcpy(outStr,strm.str().c_str());

    return outStr;
}

partition stringToPartition (char* string)
{
    partition temp;

    char* curTok = strtok(string," ");
    int count = 0;

    while(curTok != NULL && count <= 2)
    {
            switch (count)
            {
                    case 0: temp.partitionStr = new char[strlen(curTok) + 1];
                            strcpy(temp.partitionStr,curTok);       
                            break;
                    case 1: temp.distinicIndex = atoi(curTok);
                            break;
                    case 2: temp.huffmanCWIndex = atoi(curTok);
                    
                    default:
                            break;
            }
            curTok = strtok(NULL," ");
            count++;
    }

    return temp;
}

partition* stringToPartitionPtr (char* string)
{
    partition* temp = new partition;
    
    char* curTok = strtok(string," ");
    int count = 0;

    while(curTok != NULL && count <= 2)
    {
            switch (count)
            {
                    case 0: temp->partitionStr = new char[strlen(curTok) + 1];
                            strcpy(temp->partitionStr,curTok);       
                            break;
                    case 1: temp->distinicIndex = atoi(curTok);
                            break;
                    case 2: temp->huffmanCWIndex = atoi(curTok);
                    
                    default:
                            break;
            }
            curTok = strtok(NULL," ");
            count++;
    }

    return temp;
}

partitionedString stringToPartitionedString (char* string)
{
    partitionedString temp;
    
    //cout << string << endl;
    int curPos = 0;
    
    char* curTok = nextTok(string,curPos,"-");

    //cout << curTok << endl;
    while(curTok != NULL)
    {
        //cout << "Loop tok: " << curTok << endl;
        partition* tempPart = stringToPartitionPtr(curTok);
                
        //Add to partitionedString vector       
        temp.push_back(tempPart);
        
        delete [] curTok;

        curTok = nextTok(string,curPos,"-");     
    }

    return temp;
}

char* nextTok(char* str, int& curPos, const char* delim)
{
    string temp = string(str);
    
    char* outstr = NULL;
    
    //cout << "temp: " << temp << endl;
    //cout << "Curpos: " << curPos << endl;
    
    if (curPos < temp.length())
    {
        
        int newPos = temp.find(delim, curPos);
        
        //cout << "New pos: " << newPos << endl;
        
        if(newPos == string::npos)
        {
            
            newPos = temp.length();
            //cout << "endPos: " << newPos << endl;
        }
        
        string newtemp = temp.substr(curPos, newPos - curPos);
        
        //cout << "newtemp: " << newtemp << endl;
        
        curPos = newPos + 1;
        
        outstr = new char[newtemp.length() + 1];
        strcpy(outstr,newtemp.c_str());    
    }
    
    return outstr;
    
    
}