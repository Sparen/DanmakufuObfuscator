#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "dnhobf_fxn.h"

int Obfuscate(FILE* infile){
  fseek(infile, 0, SEEK_SET);
  RemoveSingleLineComments(infile);
  RemoveBlockComments(infile);
  fclose(infile);
}

int RemoveSingleLineComments(FILE* infile){
  
  return 0;
}

int RemoveBlockComments(FILE* infile){
  return 0;
}
