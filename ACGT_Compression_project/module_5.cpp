#include "module_5.h"
#include <iostream>

char* getLine_FromFile(const char* filename, unsigned int line)
{
  ifstream file;

  file.open(filename);
  
  if(file.is_open())
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
  
  return NULL;
}