//COMPRESSION PROJECT: MODULE 5 FILE API: module_5.cpp
//Created by Mathys Ellis 30/02/2014

#include "module_5.h"
#include <iostream>

char* getLine_FromFile(const char* filename, unsigned long long int line)
{
  ifstream file;

  file.open(filename);
  
  if(file)
  {
      unsigned long long int count = 0;
      while (!file.eof())
      {
          count++;
          char* temp = new char[MAX_READ_CHARS];
          file.getline(temp, MAX_READ_CHARS);
          
          if(count == line)
          {
              char* fit = new char[file.gcount() + 1];
              
              strncpy(fit, temp, file.gcount());
              fit[file.gcount()] = '\0';
              delete [] temp;
              return fit;
          }
          
          delete [] temp;         
          
      }
      
      file.close();
  }
  else
  {
      char msg[] = "Cannot open file";
      errorMsg(msg);
  }
  
  return NULL;
}

vector<char*> getAllLines_FromFile (const char* filename)
{
  ifstream file;
  
  vector<char*> out;
  
  file.open(filename);
  
  if(file)
  {
      unsigned int count = 0;
      while (!file.eof())
      {
          
          char* temp = new char[MAX_READ_CHARS];
          file.getline(temp, MAX_READ_CHARS);
          char* fit = new char[file.gcount() + 1];
          strncpy(fit, temp, file.gcount());
          fit[file.gcount()] = '\0';
          
          if (strcmp("",fit) != 0)
          {
             out.push_back(fit); 
          }
          else
          {
              delete [] fit;
          }
          
          delete [] temp;
          
      }

      file.close();
  }
  else
  {
      char msg[] = "Cannot open file";
      errorMsg(msg);
  }
  
  return out;
}

void ceateInfoFile(const char* path, unsigned long long int l, unsigned long long int h, unsigned long long int m, unsigned long long int c)
{
    fstream file;
    char* filename = new char[STD_NUMBER_OF_CHARS];
    
    sprintf(filename,"%s%s", path, EXP_INFO_FILE_NAME);
    file.open(filename,ios::out);
             
    file << m << endl;
    file << l << endl;
    file << h << endl;
    file << c << endl;
    
    file.close();
    delete [] filename;
}

unsigned long long int* readInfoFile(const char* path)
{
    unsigned long long int* tempInt = new unsigned long long int[4];
    tempInt[0] = 0;
    tempInt[1] = 0;
    tempInt[2] = 0;
    tempInt[3] = 0;
    
    char* filename = new char[STD_NUMBER_OF_CHARS];
    
    sprintf(filename,"%s%s", path, EXP_INFO_FILE_NAME);
    
    ifstream file;    
    
    file.open(filename);

    if(file)
    {
        int count = 0;
        while (!file.eof() && count < 4)
        {

            char* temp = new char[MAX_READ_CHARS];
            file.getline(temp, MAX_READ_CHARS);
            
            char* fit = new char[file.gcount() + 1];
            strncpy(fit, temp, file.gcount());
            fit[file.gcount()] = '\0';

            if (strcmp("",fit) != 0)
            {                
                tempInt[count] = atoll(fit); 
                count++;
            }
            
            delete [] fit;
            delete [] temp;

        }

        file.close();
    }
    else
    {
        char msg[] = "Cannot open file";
        errorMsg(msg);
    }
    
    delete [] filename;
    
    return tempInt;
}