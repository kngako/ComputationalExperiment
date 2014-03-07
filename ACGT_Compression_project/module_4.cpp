//COMPRESSION PROJECT: MODULE 4 ENCODING : module4.cpp
//Created by Mathys Ellis 26/02/2014
#include "module_4.h"

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

