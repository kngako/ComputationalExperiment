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
              char* fit = new char[file.gcount()];
              
              strncpy(fit, temp, file.gcount() + 1);
              
              return fit;
          }
          
          
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
          count++;
          char* temp = new char[MAX_READ_CHARS];
          file.getline(temp, MAX_READ_CHARS);
          char* fit = new char[file.gcount()];

          strncpy(fit, temp, file.gcount() + 1);
          
          out.push_back(fit);
          
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