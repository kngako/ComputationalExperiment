//COMPRESSION PROJECT: MODULE 3 STRING REPETITIONS FINDER : module_3.cpp
//Created by Mathys Ellis 08/01/2014
//Based on the algorithm of Michael G. Main and Richard J. Lorentz

#include "module_3.h"

bool getAllRepetitions_XYX_Mem (char* str, vector<repetition*>& reps)
{
	findReps_E_XYX_mem(str, reps);
	return true;
}

bool getAllRepetitions_XYX_File (char* str, char* filename)
{
	fstream outFile;

	outFile.open(filename,ios::out);

	outFile << str << endl;

	findReps_E_XYX_file(str, outFile);

	return true;
}

void findReps_E_XYX_mem (char* str, vector<repetition*>& reps)
{
	int* temp = findMaxLppattern_XYX(str);

	scanLPArrForRep_E_XYX_mem(str,temp,reps);
}

void findReps_E_XYX_file (char* str, fstream& outFile)
{
	int* temp = findMaxLppattern_XYX(str);

	scanLPArrForRep_E_XYX_file(str,temp,outFile);
}

int* findMaxLppattern_XYX(char* str)
{
	int strLen = strlen(str);
        //Used for zeroing all covered zones in LPpattern Overall
	int zeroCounter = 0;

	vector<int*> lppatterns;

	//Intialise 3 arrays
        //MOVE FROM ALL TO 1 string levels (no of chars from orignal string)
        //[0] Overall LPpattern
        //[1] current level LPpattern in string
        //[2] next level LPpattern in string
	lppatterns.push_back(new int[strLen]);
	lppatterns.push_back(new int[1]);
	lppatterns.push_back(new int[strLen]);

	for (int i = 0; i < strLen; i++)
	{
                lppatterns[0][i] = 0;
		lppatterns[2][i] = 0;
	}

	//Process str and find longest prefixs
	for (int i = 0; i < strLen - 1; i++)
	{
                //Replace Cur array lppatterns[1] with Temp array lppatterns[2]
		int* temp = lppatterns[2];
		lppatterns.pop_back();

		delete [] lppatterns[1];
		lppatterns.pop_back();

		lppatterns.push_back(temp);
                
                //Insert new array in lppatterns[2] and initialise
		temp = 0;
		temp = new int[strLen - i - 1];
                
		for (int j = 0; j < strLen - i - 1; j++)
		{
			temp[j] = 0;
		}

		lppatterns.push_back(temp);

		//Claculate the next level of lppattern
		calcLppattern_E_XYX(str, lppatterns, i);
                /*
                cout << "level " << i << ": " << endl;
                for(int m = 0; m < strLen - i; m++)
                {
                    cout << lppatterns[1][m];
                }
                cout << endl;
		*/
                //Zero already covered zones
		if(lppatterns[0][i] > zeroCounter) //If the current LP is bigger then the current number of elements to zero then needs to change zero counter that
		{
			zeroCounter = lppatterns[0][i] - 1;
		}
		else if(zeroCounter > 0) //If zones are covered
		{
		   lppatterns[0][i] = 0;
		   zeroCounter--;                   
		}
                

	}

	//Zero last if not covered yet
	if(zeroCounter > 0)
	{
                lppatterns[0][strLen - 1] = 0;
        }

	//Free memory
        delete [] lppatterns[1];
	delete [] lppatterns[2];

	lppatterns.pop_back();
	lppatterns.pop_back();

	return lppatterns[0];
}
void calcLppattern_E_XYX (char* pattern, vector<int*>& lppatterns, int offset)
{
	//cout << "======offset: " << offset << endl;
	//find pattern length

	int patternLen = strlen(pattern) - offset;

	int lppIndex = 1;//lppatterns.size() - patternLen;

	int curMatchLen = 0; //j

	//Find lppattern[1]
	if (patternLen > 1)     //modified
	{
		curMatchLen = lppatterns[lppIndex][1]; //j  //modified
	}

	while (curMatchLen < patternLen && pattern[curMatchLen + offset] == pattern[curMatchLen + offset + 1])
	{
		curMatchLen++;
	}

	lppatterns[lppIndex][1] = curMatchLen;

	//Adjust cur start max
	lppatterns[lppIndex][0] = max(lppatterns[lppIndex][1],lppatterns[lppIndex][0]);
   	//adjust max array
	lppatterns[0][offset + 1] = max(lppatterns[0][offset + 1],lppatterns[lppIndex][1]);

	//Special index value that maxs: k + lppattern[k] (1 <= k < i)
	int k = 1;

	//Find rest of lppattern
	for(int i = 2; i < patternLen; i++)
	{
		//lenX = length of substring X: pattern[i]...pattern[k + lppattern[k] - 1]
		int lenX = k + lppatterns[lppIndex][k] - (1 + i); //?

		if(lppatterns[lppIndex][(i - k)] < lenX)  //changed lppattern[i - k + 1]  to lppattern[i - k]
		{
			//gives length directly
			lppatterns[lppIndex][i] = lppatterns[lppIndex][(i - k)];  //changed lppattern[i - k + 1]  to lppattern[i - k]
		}
		else
		{
			if(i >= k + lppatterns[lppIndex][k])
			{
				//No hint is possiable
				curMatchLen = lppatterns[lppIndex][i];  //modified
			}
			else
			{
				//gives hint to length
				curMatchLen = max(lenX,lppatterns[lppIndex][i]); //modified
			}

			//Used to find substring length if no predetemined or aid given
			while(curMatchLen < patternLen && pattern[curMatchLen + offset] == pattern[curMatchLen + offset + i] )
			{
				curMatchLen++;
			}

			lppatterns[lppIndex][i] = curMatchLen;

			//since last update should max k + lppattern[k]
			k = i;
		}

		//Adjust max
		lppatterns[0][i + offset] = max(lppatterns[0][i + offset],lppatterns[lppIndex][i]);

		//Adjust cur start max
		lppatterns[lppIndex][0] = max(lppatterns[lppIndex][0],lppatterns[lppIndex][i]);

		//Write prepocessed data (speed up processing via hints)
		//****050000
		//*****04000
		if (lppatterns[lppIndex][i] > 1 && i + lppatterns[1][i] < patternLen - 1)
		{
			lppatterns[2][i] = lppatterns[lppIndex][i] - 1;
		}


	}
    //Adjust max
	lppatterns[0][offset] = max(lppatterns[0][offset],lppatterns[lppIndex][0]);
}

void scanLPArrForRep_E_XYX_mem (char* str, int* lpMaxPattern, vector<repetition*>& reps)
{
	int lpLen = strlen(str);

    //scan lpMaxPattern for reps
	for(int i = 0; i < lpLen; i++)
	{
		//Check if rep exist
		if(lpMaxPattern[i] > 0)
		{
			//Extract repetitions
			for(int j = 0; j < lpMaxPattern[i]; j++)
			{
				//cout << "J: " << j << endl;
				for(int k = 0; k < lpMaxPattern[i] - j; k++)
				{
					repetition* temp = new repetition;
					temp->repetitionStr = copyChar(str,i + k, j + 1);
					temp->startpos = i + k;

					reps.push_back(temp);
				}
			}
		}

		//skip if possible
		if(lpMaxPattern[i] > 1 && lpMaxPattern[lpMaxPattern[i] + i - 1] == 0)
		{
		   	//i = i + lpMaxPattern[i] - 1;
                }
	}
}

void scanLPArrForRep_E_XYX_file (char* str, int* lpMaxPattern, fstream& outFile)
{
	int lpLen = strlen(str);
        cout << lpLen << endl;
        
        //scan lpMaxPattern for reps
	for(int i = 0; i < lpLen; i++)
	{
            
            cout << lpMaxPattern[i];
                //Check if rep exist
		if(lpMaxPattern[i] > 0)
		{
			//Extract repetitions
			for(int j = 0; j < lpMaxPattern[i]; j++)
			{
				//cout << "J: " << j << endl;
				for(int k = 0; k < lpMaxPattern[i] - j; k++)
				{
					repetition temp;
					temp.repetitionStr = copyChar(str,i + k, j + 1);
					temp.startpos = i + k;

					char* strOut = repetitionToString(temp);

					outFile << strOut << endl;

					delete [] strOut;
				}
			}
		}

		//skip if possible
		if(lpMaxPattern[i] > 1 && lpMaxPattern[lpMaxPattern[i] + i - 1] == 0)
		{
		   	//i = i + lpMaxPattern[i] - 1;
                }
	}
}

void findReps_U_XYX (char* str, vector<repetition*>& reps)
{
	 /* ORGINAL CODE not efficent
	vector<int*> lppatterns;

	for (int i = 0; i < strLen - 1; i++)
	{
		lppatterns.push_back(new int[strLen - i]);
		for (int j = 0; j < strLen - i; j++)
		{
			lppatterns[i][j] = 0;
		}
	}

	for (int i = 0; i < lppatterns.size(); i++)
	{
		calcLppattern_XYX(str, lppatterns, i);
	}
	cout << "before" << endl;
	for (int i = 0; i < lppatterns.size(); i++)
	{
		cout << "[";
		for (int j = 0; j < lppatterns.size() + 1 - i; j++)
		{
			cout << "," << lppatterns[i][j];
		}
		cout << "]" << endl;
	}

	for (int i = 1; i < lppatterns.size(); i++)
	{
		//cout << "j: "<< lppatterns.size() - i<< endl;
		for(int j = 0; j <= lppatterns.size() - i; j++)
		{
		   //	cout << "cur: " << lppatterns[0][j + i] << " othe: " <<  lppatterns[i][j] << endl;
			if(lppatterns[0][j + i] < lppatterns[i][j])
			{
				lppatterns[0][j + i] = lppatterns[i][j];
			}
		}
		//cout << endl;
	}

	cout << "before 0" << endl;
	for (int i = 0; i < lppatterns.size(); i++)
	{
		cout << "[";
		for (int j = 0; j < lppatterns.size() + 1 - i; j++)
		{
			cout << "," << lppatterns[i][j];
		}
		cout << "]" << endl;
	}

	//values that are in range to be zeroed
	for (int i = 0; i < strLen; i++)
	{
		for(int j = i + 1; j < lppatterns[0][i] + i; j++)
		{
            //if value in range
			if(lppatterns[0][j] <= lppatterns[0][i] - (j - i))
			{
				lppatterns[0][j] = 0;
            }
		}
	}
    scanLPArrForRep_XYX(str, 0, strLen, lppatterns, 0, reps);
	/*for (int i = 0; i < lppatterns.size(); i++)
	{
		//scanLPArrForRep_XYX(str, i, strLen, lppatterns, i, reps);
	}*/

	/*cout << "after" << endl;
	for (int i = 0; i < lppatterns.size(); i++)
	{
		cout << "[";
		for (int j = 0; j < lppatterns.size() + 1 - i; j++)
		{
			cout << "," << lppatterns[i][j];
		}
		cout << "]" << endl;
	} */
}

void calcLppattern_U_XYX (char* pattern, vector<int*>& lppatterns, int offset)
{
	//cout << "======offset: " << offset << endl;
	//find pattern length
	int patternLen = strlen(pattern) - offset;

	int lppIndex = offset;//lppatterns.size() - patternLen;

	int curMatchLen = 0; //j

	//Find lppattern[1]
	if (patternLen > 1)     //modified
	{
		//cout << "lppatterns[lppIndex][1]: "<< lppatterns[lppIndex][1] << endl;
		curMatchLen = lppatterns[lppIndex][1]; //j  //modified
	}

	while (curMatchLen < patternLen && pattern[curMatchLen + offset] == pattern[curMatchLen + offset + 1])
	{
		curMatchLen++;
	}

	lppatterns[lppIndex][1] = curMatchLen;

	lppatterns[lppIndex][0] = max(lppatterns[lppIndex][1],lppatterns[lppIndex][0]);

	//Special index value that maxs: k + lppattern[k] (1 <= k < i)
	int k = 1;

	//Find rest of lppattern
	for(int i = 2; i < patternLen; i++)
	{
		//lenX = length of substring X: pattern[i]...pattern[k + lppattern[k] - 1]
		int lenX = k + lppatterns[lppIndex][k] - (1 + i); //?

		if(lppatterns[lppIndex][i - k] < lenX)  //changed lppattern[i - k + 1]  to lppattern[i - k]
		{
			//gives length directly
			lppatterns[lppIndex][i] = lppatterns[lppIndex][i - k ];  //changed lppattern[i - k + 1]  to lppattern[i - k]
		}
		else
		{
			if(i >= k + lppatterns[lppIndex][k])
			{
				//No hint is possiable
				curMatchLen = lppatterns[lppIndex][i];  //modified
			}
			else
			{
				//gives hint to length
				curMatchLen = max(lenX,lppatterns[lppIndex][i]); //modified
			}

			//Used to find substring length if no predetemined or aid given
			while(curMatchLen < patternLen && pattern[curMatchLen + offset] == pattern[curMatchLen + offset + i] )
			{
				curMatchLen++;
			}

			lppatterns[lppIndex][i] = curMatchLen;

			//since last update should max k + lppattern[k]
			k = i;
		}

		lppatterns[lppIndex][0] = max(lppatterns[lppIndex][0],lppatterns[lppIndex][i]);

		//Write prepocessed data
		//****050000
		//*****04000
		if (lppatterns[lppIndex][i] < patternLen)
		{
			for (int j = 1; j < lppatterns[lppIndex][i]; j++)
			{
				lppatterns[lppIndex + j][i] = lppatterns[lppIndex][i] - j;
			}
		}
	}
}

void scanLPArrForRep_U_XYX(char* str, int start, int len, vector<int*>& lppatterns, int pos, vector<repetition*>& reps)
{
	int lpLen = len - start;
	//cout << "lplen: " << lpLen << " start: " << start << " len: " << len << endl;
	for(int i = 0; i < lpLen; i++)
	{
		if(lppatterns[pos][i] > 0)
		{
			//Extract repetitions
			for(int j = 0; j < lppatterns[pos][i]; j++)
			{
				//cout << "J: " << j << endl;
				for(int k = 0; k < lppatterns[pos][i] - j; k++)
				{
					//cout << "k: " << k << endl;
					repetition* temp = new repetition;
					temp->repetitionStr = copyChar(str, start + i + k, j + 1);
					//cout << "Rep: " << temp->repetitionStr << " k: " << k << " j: " << j << endl;
					temp->startpos = start + i + k;

					reps.push_back(temp);
				}
			}

           	//Mark positions
			for(int j = pos + 1; j < lppatterns.size() && j < lppatterns[pos][i] + pos; j++)
			{
				for(int k = i; k <= i + (j - pos); k++)
				{
					lppatterns[j][k] = 0;
                }
			}
        }
    }
}

char* copyChar (char* src, int start, int len)
{
	char* temp = new char[len + 1];

	for(int i = 0; i < len; i++)
	{
                temp[i] = src[start + i];
	}

	temp[len] = '\0';

	return temp;
}

int max(int x, int y)
{
	if(x > y)
	{
		return x;
	}

	return y;
}

int min(int x, int y)
{
    //cout << "x: " << x << endl << "y: " << y << endl;
	if(x < y)
	{
		return x;
	}

	return y;
}

//========================================XX Repetition code====================


int* calcLppattern_XX (char* pattern)
{
	//find pattern length
	int patternLen = strlen(pattern);

	int* lppattern = new int[patternLen];

	//Find lppattern[1]
	int curMatchLen = 0; //j

	while (pattern[curMatchLen] == pattern[curMatchLen + 1] && curMatchLen < patternLen)
	{
		curMatchLen++;
	}

	lppattern[1] = curMatchLen;

	//Special index value that maxs: k + lppattern[k] (1 <= k < i)
	int k = 1;

	//Find rest of lppattern
	for(int i = 2; i < patternLen; i++)
	{
		//lenX = length of substring X: pattern[i]...pattern[k + lppattern[k] - 1]
		int lenX = k + lppattern[k] - (1 + i); //?

		if(lppattern[i - k] < lenX)  //changed lppattern[i - k + 1]  to lppattern[i - k]
		{
			//gives length directly
			lppattern[i] = lppattern[i - k ];  //changed lppattern[i - k + 1]  to lppattern[i - k]
		}
		else
		{
			if(i >= k + lppattern[k])
			{
				//No hint is possiable
				curMatchLen = 0;
			}
			else
			{
				//gives hint to length
				curMatchLen = lenX;
			}

			//Used to find substring length if no predetemined or aid given
			while(pattern[curMatchLen] == pattern[curMatchLen + i] && curMatchLen < patternLen)
			{
				curMatchLen++;
			}

			lppattern[i] = curMatchLen;

			//since last update should max k + lppattern[k]
			k = i;
		}
	}

	return lppattern;
}

int* calcLptext_XX (char* pattern, char* text, int* lppattern)
{
    //find pattern length
	int patternLen = strlen(pattern);
	int textLen = strlen(text);

	int* lptext = new int[textLen];

	//Find lptext[0]
	int curMatchLen = 0; //j

	while (pattern[curMatchLen] == text[curMatchLen] && curMatchLen < patternLen && curMatchLen < textLen)
	{
		curMatchLen++;
	}

	lptext[0] = curMatchLen;

	//Special index value that maxs: k + lptext[k] (0 <= k < i)
	int k = 0;

	//Find rest of lptext
	for(int i = 1; i < textLen; i++)
	{
		//lenX = length of substring X: text[i]...text[k + lptext[k] - 1]
		int lenX = k + lptext[k] - (1 + i); //?

		if(lppattern[i - k] < lenX)  //changed lppattern[i - k + 1]  to lppattern[i - k]
		{
			//gives length directly
			lptext[i] = lppattern[i - k];  //changed lppattern[i - k + 1]  to lppattern[i - k]
			//cout << i << ": " << 1 << " lppattern[i - k] " << lppattern[i - k] << endl;
		}
		else
		{
			if(i >= k + lptext[k])
			{
				//No hint is possiable
				curMatchLen = 0;
				//cout << i << ": " << 2 << endl;
			}
			else
			{
				//gives hint to length
				curMatchLen = lenX;

				//cout << i << ": " << 3 << " xlen " << lenX << endl;
			}

			//Used to find substring length if no predetemined or aid given
			while(pattern[curMatchLen] == text[curMatchLen + i] && curMatchLen < patternLen && curMatchLen + i < textLen)
			{
				curMatchLen++;
			}

			lptext[i] = curMatchLen;

			//since last update should max k + lppattern[k]
			k = i;
		}
	}

	return lptext;
}

int* calcLsPatternLR_XX (char* pattern)
{
	//find pattern length
	int patternLen = strlen(pattern);

	int* lspattern = new int[patternLen];

	//Find lppattern[1]
	int curMatchLen = patternLen - 1; //j

	while (pattern[curMatchLen] == pattern[curMatchLen - 1] && curMatchLen > 1)
	{
		curMatchLen--;
	}

	lspattern[patternLen - 1] = curMatchLen;

	//Special index value that maxs: k + lppattern[k] (1 <= k < i)
	int k = patternLen - 2;

	//Find rest of lppattern
	for(int i = patternLen; i > patternLen; i++)
	{
		//lenX = length of substring X: pattern[-(k + lppattern[k] - 1)]...pattern[i]
		int lenX = (i - 1) - (patternLen - (k + lspattern[k])); //?

		if(lspattern[i - (k - i)] < lenX)  //changed lppattern[i - k + 1]  to lppattern[i - k]
		{
			//gives length directly
			lspattern[i] = lspattern[i - (k - i) ];  //changed lppattern[i - k + 1]  to lppattern[i - k]
		}
		else
		{
			if(i <= k + lspattern[k])
			{
				//No hint is possiable
				curMatchLen = 0;
			}
			else
			{
				//gives hint to length
				curMatchLen = lenX;
			}

			//Used to find substring length if no predetemined or aid given
			while (pattern[curMatchLen] == pattern[curMatchLen - 1] && curMatchLen > 1)
			{
				curMatchLen--;
			}

			lspattern[i] = curMatchLen;

			//since last update should max k + lppattern[k]
			k = i;
		}
	}

	return lspattern;
}

//Find longest suffix in terms of pos i indicating end of ls starting left of it [start suffix char]...[end suffix char or i]
int* calcLstextLR_XX (char* pattern, char* text)
{
	int* lppattern = calcLppattern_XX(reverseString(pattern));
	int* lspattern = calcLptext_XX(reverseString(pattern),text,lppattern);

	for(int i = 0; i < strlen(text); i = i)
	{
		int j = lspattern[i];

		for (int k = 0; k < j; k++)
		{
			lspattern[i + k] = k + 1;
		}

		if(j == 0)
		{
			i++;
		}
		else
		{
			i = i + j;
		}
	}

	return lspattern;
}
//Find longest suffix substing of pattern that ends at i and starts at i - ls[i] hence it is [start of suffix]...[end char of pattern]
int* calcLstext_XX (char* pattern, char* text)
{
	char* rpattern = reverseString(pattern);
	char* rtext = reverseString(text);
	//cout << "rpattern: "<< rpattern << endl;
	//cout << "rtext: "<< rtext << endl;
	int* lppatternr = calcLppattern_XX(rpattern);
	//cout << "lp: " << lppatternr[0]<< endl;
	int* lstextr = calcLptext_XX(rpattern, rtext, lppatternr);

	int textLen = strlen(text);

	int* lstext = new int[textLen];

	for(int i = 0; i < textLen; i++)
	{
		lstext[i] = lstextr[(textLen - 1) - i];
	}

	return lstext;
}


char* reverseString (char* str)
{
	int len = strlen(str);

	char* reversedString = new char[len + 1];

	for(int i = 0; i < len; i++)
	{
		reversedString[i] = str[(len - 1) - i];
	}

	reversedString[len] = '\0';

	return reversedString;
}

void newRight_XX (char* u, char* v, vector<int*>& reps)
{
	//cout << "right: " << endl;
	//cout << "v: " << v << endl;
	//cout << "u: " << u << endl;

	int* lp = calcLppattern_XX(v);
	int* ls = calcLstext_XX(u,v);

	/*cout << "lp:" << endl;
	for(int i = 0; i < strlen(v); i++)
	{
		cout <<  v[i] << ": " << lp[i] <<endl;
	}

	cout << "ls:" << endl;
	for(int i = 0; i < strlen(v); i++)
	{
		cout << v[i] << ": " << ls[i] <<endl;
	} */

	for(int n = 1; n <= strlen(v); n++)
	{
		int first = (2 * n) - ls[n - 1] - 1;
        int last = min((2*n) - 1,(n + lp[n])) - 1;

		if(n == strlen(v))
		{
            last = n - 1;
		}


       // cout << "===run v[" << n << "]====" << endl;
	   //	cout << "first: " << first << endl;
	   // cout << "last: " << last << endl;
		//cout << "len: " << 2 * n << endl;

		if (!(last < first))
		{
			int* repEnds = new int[3];
			repEnds[0] = first;
			repEnds[1] = last;
			repEnds[2] = n * 2;

			reps.push_back(repEnds);
		}
	}
}

void newLeft_XX (char* u, char* v, vector<int*>& reps)
{
	//This algoritm exploits the symmetry of a repetition
	//Therefore reversing the strings u and v allows u to contain the end point on the side of v

	//cout << "left: " << endl;

	char* vr = reverseString(v);
	char* ur = reverseString(u);

	//cout << "vr: " << vr << endl;
	//cout << "ur: " << ur << endl;

	int* lp = calcLppattern_XX(ur);
	int* ls = calcLstext_XX(vr,ur);

	for(int n = 1; n <= strlen(ur); n++)
	{
		int first = (2 * n) - ls[n - 1] - 1;
		int last = min((2*n) - 1,(n + lp[n])) - 1;

		//If max n is reached
		if(n == strlen(ur))
		{
			last = n - 1;
		}

		if (!(last < first))
		{
			int* repEnds = new int[3];
            //This modification allows the end positions to be mapped to the correct text and not the reversed
			repEnds[0] = (n * 2) - first - 2;
			repEnds[1] = (n * 2) - last - 2;
			repEnds[2] = n * 2;

			reps.push_back(repEnds);
		}
	}
}

void newReps_XX (char* u, char* v, int realPos, vector<repetition*>& reps)
{

	vector<int*> left;
	vector<int*> right;

	newLeft_XX(u, v, left);
	newRight_XX(u, v, right);

	int lenU = strlen(u);
	int lenV = strlen(v);

	char* text = new char[lenU + lenV + 1];
	char* textr = new char[lenU + lenV + 1];
	text[0] = '\0';

	text = strcpy(text,u);
	text = strcat(text,v);

	text[lenU + lenV] = '\0';
	textr[lenU + lenV] = '\0';

	bool* centerCounter = new bool[strlen(u) + strlen(v)];

	for(int i = 0; i < right.size(); i++)
	{
		//cout << "Right repetition " << i << ": first-> " << right[i][0] << " last-> " << right[i][1] << " len " << right[i][2] << endl;

		for(int k = lenU + right[i][0]; k <= lenU + right[i][1]; k++)
		{

			if(k + 1 == static_cast<int>(right[i][2] / 2) + lenU)
			{
				centerCounter[static_cast<int>(right[i][2] / 2) - 1] = true;
            }

			int m = 0;

			char* tempRep = new char[right[i][2] + 1];

			for(int j = k - right[i][2] + 1; j <= k; j++)
			{
				tempRep[m++] = text[j];
			}

			tempRep[right[i][2]] = '\0';

			repetition* temp = new repetition;
			temp->repetitionStr = tempRep;
			temp->startpos = k - right[i][2] + 1 + realPos;

			reps.push_back(temp);
		}

	}

	for(int i = 0; i < left.size(); i++)
	{
		//cout << "Left repetition " << i << ": first-> " << left[i][0] << " last-> " << left[i][1] << " len " << left[i][2] << endl;

		for(int k = lenU + left[i][0]; k <= lenU + left[i][1]; k++)
		{
			int m = 0;

			//To insure duplicate repitions are removed centers
			if(!(k + 1 == static_cast<int>(left[i][2] / 2) + lenU && centerCounter[static_cast<int>(left[i][2] / 2) - 1] == true))
			{
				char* tempRep = new char[left[i][2] + 1];

				for(int j = k - left[i][2] + 1; j <= k; j++)
				{
					tempRep[m++] = text[j];
				}

				tempRep[left[i][2]] = '\0';

				repetition* temp = new repetition;
				temp->repetitionStr = tempRep;
				temp->startpos = k - left[i][2] + 1 + realPos;
				//cout <<  temp->repetitionStr  << endl;
				reps.push_back(temp);
            }
		}
	}
}

void newReps_file_XX (char* u, char* v, int realPos, fstream& outFile)
{

	vector<int*> left;
	vector<int*> right;

	newLeft_XX(u, v, left);
	newRight_XX(u, v, right);

	int lenU = strlen(u);
	int lenV = strlen(v);

	char* text = new char[lenU + lenV + 1];
	char* textr = new char[lenU + lenV + 1];
	text[0] = '\0';

	text = strcpy(text,u);
	text = strcat(text,v);

	text[lenU + lenV] = '\0';
	textr[lenU + lenV] = '\0';

	bool* centerCounter = new bool[strlen(u) + strlen(v)];

	for(int i = 0; i < right.size(); i++)
	{
		//cout << "Right repetition " << i << ": first-> " << right[i][0] << " last-> " << right[i][1] << " len " << right[i][2] << endl;

		for(int k = lenU + right[i][0]; k <= lenU + right[i][1]; k++)
		{

			if(k + 1 == static_cast<int>(right[i][2] / 2) + lenU)
			{
				centerCounter[static_cast<int>(right[i][2] / 2) - 1] = true;
            }

			int m = 0;

			char* tempRep = new char[right[i][2] + 1];

			for(int j = k - right[i][2] + 1; j <= k; j++)
			{
				tempRep[m++] = text[j];
			}

			tempRep[right[i][2]] = '\0';

			repetition* temp = new repetition;
			temp->repetitionStr = tempRep;
			temp->startpos = k - right[i][2] + 1 + realPos;

			outFile << repetitionToString(*temp) << endl;
		}

	}

	for(int i = 0; i < left.size(); i++)
	{
		//cout << "Left repetition " << i << ": first-> " << left[i][0] << " last-> " << left[i][1] << " len " << left[i][2] << endl;

		for(int k = lenU + left[i][0]; k <= lenU + left[i][1]; k++)
		{
			int m = 0;

			//To insure duplicate repitions are removed centers
			if(!(k + 1 == static_cast<int>(left[i][2] / 2) + lenU && centerCounter[static_cast<int>(left[i][2] / 2) - 1] == true))
			{
				char* tempRep = new char[left[i][2] + 1];

				for(int j = k - left[i][2] + 1; j <= k; j++)
				{
					tempRep[m++] = text[j];
				}

				tempRep[left[i][2]] = '\0';

				repetition* temp = new repetition;
				temp->repetitionStr = tempRep;
				temp->startpos = k - left[i][2] + 1 + realPos;
				//cout <<  temp->repetitionStr  << endl;
				outFile << repetitionToString(*temp) << endl;
            }
		}
	}
}

void findReps_XX (char* str, int realPos, vector<repetition*>& reps)
{
	if (strlen(str) > 1)
	{
		char* u = ""; //left
		char* v = ""; //right

		splitStr(str, u, v);
		//cout << u << endl;
		//cout << v << endl;
		newReps_XX(u,v, realPos, reps);

		findReps_XX(u, realPos, reps);
		findReps_XX(v, realPos + strlen(u), reps);
	}

}

void findReps_file_XX (char* str, int realPos, fstream& outFile)
{
	if (strlen(str) > 1)
	{
		char* u = ""; //left
		char* v = ""; //right

		splitStr(str, u, v);
		//cout << u << endl;
		//cout << v << endl;
		newReps_file_XX(u,v, realPos, outFile);

		findReps_file_XX(u, realPos, outFile);
		findReps_file_XX(v, realPos + strlen(u), outFile);
	}

}

void splitStr(char* str, char*& u, char*& v)
{
	if (strlen(str) > 1)
	{

		int len = strlen(str);
		int half = static_cast<int>(len/2);

		char* left = new char[half + 1];
		char* right = new char[len - half + 1];

		for(int i = 0; i < half; i++)
		{
			left[i] = str[i];
		}
		left[half] = '\0';

		for(int i = half; i < len; i++)
		{
			right[i - half] = str[i];
		}
		right[len - half] = '\0';

		u = left;
		v = right;


	}

}

bool getAllRepetitions_XX (char* filename, char* str)
{
	fstream outputFile;

	outputFile.open(filename,ios::out);

	findReps_file_XX(str,0,outputFile);

	outputFile.close();

	return true;
}

repetition getRepetionOfNIStringI_FromFile(const char* path, int lenIndex, int NIStringIndex, int repIndex)
{
    char* filename = new char[STD_NUMBER_OF_CHARS];
    sprintf(filename,"%s%d_%d.%s", path, lenIndex, NIStringIndex, REPETITION_FILE_EXT);
    
    char* data = getLine_FromFile(filename,repIndex);
    
    delete [] filename;
    
    repetition temp;
    
    if(data != NULL)
    {    
        temp = stringToRepetition(data);

        delete [] data;
    }
    
    return temp;
}
