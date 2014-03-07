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

//module_2
//==============================================================================

//This function maps the inputted string and returns a mappedString
mappedString mapString(char* inputStr)
{
	mappedString result; //resulting mappedString
	int len = strlen(inputStr); //length of the input string
	int curIDXCount = 0; //Mapping counter for the A-C-G-T chars

	//intialise result;
	result.mapping[A_IDX] = -1;
	result.mapping[C_IDX] = -1;
	result.mapping[G_IDX] = -1;
	result.mapping[T_IDX] = -1;

	result.mappedStr = new char[len];

	for(int i = 0; i < len; i++)
	{
        int* cur; //Pointer to current INDEX a.k.a IDX *used to simplfiy code*

		//Checks current char of inputStr and sets cur to point to correct mapping index of result
		switch (toupper(inputStr[i]))
		{
			case 'A': cur = &result.mapping[A_IDX];
				break;
			case 'C': cur = &result.mapping[C_IDX];
				break;
			case 'G': cur = &result.mapping[G_IDX];
				break;
			case 'T': cur = &result.mapping[T_IDX];
				break;
			default:
				result.mappedStr = NULL;
				result.mapping[A_IDX] = -1;
				result.mapping[C_IDX] = -1;
				result.mapping[G_IDX] = -1;
				result.mapping[T_IDX] = -1;
				return result;//error code
				break;
		}

		//Checks if index not set
		if(*cur == -1)
		{
			*cur = curIDXCount++; //sets index to the lowest avalible map value avalible *This must be in range of 0..3*
		}

		result.mappedStr[i] = (char)(*cur + 48); //Adds the current map value to the complete mapped string of result
	}

	result.mappedStr += '\0'; //Null terminate the mappedStr of result

	return result;
}

//This function converts the mappedString to a normal c-string
char* getStringFromMap(mappedString inputMap)
{
	int len = strlen(inputMap.mappedStr);

	char* result = new char[len + 1];

	//scan and replace mappedStr with orginal chars and store it in result
	for(int i = 0; i < len; i++)
	{
        //Check mappedStr[i] against the mapping value of each A-C-G-T char
		if((int) inputMap.mappedStr[i] == inputMap.mapping[A_IDX] + 48)
		{
			result[i] = 'A';
		}
		else if((int) inputMap.mappedStr[i] == inputMap.mapping[C_IDX] + 48)
		{
			result[i] = 'C';
		}
		else if((int) inputMap.mappedStr[i] == inputMap.mapping[G_IDX] + 48)
		{
			result[i] = 'G';
		}
		else if((int) inputMap.mappedStr[i] == inputMap.mapping[T_IDX] + 48)
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

char* mappedStringToString(mappedString map)
{
	string temp = "";
	char a[200];
	sprintf(a,"%d", map.mapping[A_IDX]);
	char c[200];
	sprintf(c,"%d", map.mapping[C_IDX]);
	char g[200];
	sprintf(g,"%d", map.mapping[G_IDX]);
	char t[200];
	sprintf(t,"%d", map.mapping[T_IDX]);

	//temp += string("{str:");
	temp += map.mappedStr;
        temp += " ";
	//temp += ",a:";
	temp += a;
	//temp += ",c:";
        temp += " ";
	temp += c;
	//temp += ",g:";
        temp += " ";
	temp += g;
	//temp += ",t:";
	temp += " ";
        temp += t;
	//temp += "}";
        temp += "\0";
	
        char* outStr = new char[temp.length()];
        
        strcpy(outStr,temp.c_str());

	return outStr;
}

mappedString stringToMappedString(char* str)
{
        mappedString temp;

	char* curTok = strtok(str," ");
	int count = 0;

	while(curTok != NULL && count <= 4)
	{
		switch (count)
		{
			case 0: temp.mappedStr = new char[strlen(curTok)];
                                strcpy(temp.mappedStr,curTok);       
				break;
                        case 1: temp.mapping[A_IDX] = atoi(curTok);
				break;
                        case 2: temp.mapping[C_IDX] = atoi(curTok);
				break;
                        case 3: temp.mapping[G_IDX] = atoi(curTok);
				break;
                        case 4: temp.mapping[T_IDX] = atoi(curTok);
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
char* repetitionToString(repetition rep)
{
	string temp = "";
	char i[200];

	sprintf(i,"%d",rep.startpos);
	//temp += "repstr ";
	temp += rep.repetitionStr;
	//temp += " pos ";
        temp += " ";
	temp += i;
	temp += "\0";

	char* ptrStr = new char[temp.length()];
	strcpy(ptrStr,temp.c_str());

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
			/*case 0: if(strcmp(curTok,"repstr") != 0)
                                {
                                        temp.repetitionStr = "";
                                        temp.startpos = -1;
                                        return temp;
                                }
				break;*/

			case 0: temp.repetitionStr = new char[strlen(curTok)];
                                strcpy(temp.repetitionStr,curTok);                       
				break;

			/*case 2: if(strcmp(curTok,"pos") != 0)
                                {
                                        temp.repetitionStr = "";
                                        temp.startpos = -1;
                                        return temp;
                                }
				break;*/

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
                
                i = i + 3;
            }
        }
        else
        {
            temp[i] = (bits[i] == false)?'0':'1';
            i++;
        }
    }
}