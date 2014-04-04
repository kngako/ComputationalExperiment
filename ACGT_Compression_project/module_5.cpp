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
      unsigned int count = 0;
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