#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "dnhobf_fxn.h"

using std::cout;
using std::endl;

int Obfuscate(FILE* infile){
  RemoveBlockComments(infile);
  RemoveSingleLineComments(infile);
  fclose(infile);
  return 0;
}

//moves through the entire file, one character at a time, and copies to a temporary file. When it finds a //, it will not copy until it finds a \n. After that, it will begin copying again. At the end, it will copy the temporary file back over to the original file.
int RemoveSingleLineComments(FILE* infile){
  rewind(infile);
  char c;

  FILE *tmp;
  tmp = tmpfile();

  do{
    c = getc(infile);//get next char
    if(c=='/'){
      char tempchar = getc(infile);
      if(tempchar!='/'){//if it is not a comment
	fputc(c, tmp);//Not a comment, put it down
      }else{//it's a comment
	while(getc(infile)!='\n'){}//move to new line marker
	fseek(infile, -1, SEEK_CUR);//move back one
      }
    }else{
      fputc(c, tmp);
    }
  }while(c != EOF);

  //DEBUG: Post temporary file to actual file
  /*cout << endl;
  rewind(tmp);
  char d;
  do{
    d = getc(tmp);
    if(d != EOF){
      cout << d;
    }
  }while(d != EOF);
  cout << endl;
  rewind(tmp);*/

  //copy temporary file to original
  //TODO

  fclose(tmp);//close temporary file
  return 0;
}

int RemoveBlockComments(FILE* infile){
  rewind(infile);
  return 0;
}
