#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "dnhobf_fxn.h"

using std::cout;
using std::endl;
using std::fstream;

int Obfuscate(char* infile){
  RemoveBlockComments(infile);
  RemoveSingleLineComments(infile);
  return 0;
}

//moves through the entire file, one character at a time, and copies to a temporary file. When it finds a //, it will not copy until it finds a \n. After that, it will begin copying again. At the end, it will copy the temporary file back over to the original file.
int RemoveSingleLineComments(char* infile){
  cout << "~~~Now Removing Single Line Comments~~~" << endl;
  char c;

  fstream orig;
  orig.open(infile, std::fstream::in | std::fstream::out);

  fstream tmp;
  tmp.open(infile, std::fstream::in | std::fstream::out | std::fstream::app);

  while(!orig.eof()){
    orig.get(c);
    if(orig.eof()){break;}//get will never throw an EOF, and will duplicate the last character instead.
    cout << c; //debug
    if(c=='/'){
      char tempchar;
      orig.get(tempchar);
      if(tempchar!='/'){//if it is not a comment
	tmp.put(c); //Not a comment, put both chars down
	tmp.put(tempchar);
      }else{//it's a comment
	while(orig.get()!='\n'){}//move to new line marker
	orig.seekg(-1, std::ios_base::cur);//may need to be seekp. Move back one char
      }
    }else{
      tmp.put(c);
    }
  }
 
  orig.close();
  orig.open(infile, std::ofstream::out | std::fstream::trunc);//wipe contents of original

  //overwrite original file with new
  tmp.seekg(std::ios_base::beg);//read, move to front
  orig.seekp(std::ios_base::beg);//write, move to front;
  char a;
  while (!tmp.eof()){
    tmp.get(a);
    if(tmp.eof()){break;}//get will never throw an EOF, and will duplicate the last character instead.
    cout << a; //debug
    orig.put(a);
  }

  tmp.close();//close temporary file
  return 0;
}

int RemoveBlockComments(char* infile){
  return 0;
}
