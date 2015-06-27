#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "dnhobf_fxn.h"

using std::string;
using std::cout;
using std::endl;
using std::fstream;

//Removal of Block Comments MUST come before Removal of Single Line Comments

//Only removes comments
int ObfuscateA1(std::string infile){
  RemoveBlockComments(infile);
  RemoveSingleLineComments(infile);
  return 0;
}

//Removes comments, etc.
int ObfuscateA2(std::string infile){
  RemoveBlockComments(infile);
  RemoveSingleLineComments(infile);
  return 0;
}

//moves through the entire file, one character at a time, and copies to a temporary file. When it finds a //, it will not copy until it finds a \n. After that, it will begin copying again. At the end, it will copy the temporary file back over to the original file.
int RemoveSingleLineComments(std::string infile){
  cout << "~~~Now Removing Single Line Comments~~~" << endl;
  char c;
  string newfile = infile + ".temp";

  fstream orig;
  orig.open(infile.c_str(), std::fstream::in);
  if(orig.fail()){
    cout << "Error: Failed to open Data File" << endl;
    exit(EXIT_FAILURE);
  }

  fstream tmp;
  cout << "Creating Temporary File with name " << newfile << endl;//debug
  tmp.open(newfile.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  if(tmp.fail()){
    cout << "Error: Failed to open Temporary File" << endl;
    exit(EXIT_FAILURE);
  }

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
	bool satisfied = false;
	char temp2;
	while(!satisfied){
	  orig.get(temp2);
	  if(temp2 == '\n' || temp2 == '\r'){//move to new line marker
	    satisfied = true;
	  }
	  if(orig.eof()){satisfied = true;}//get will never throw an EOF
	}
	orig.seekg(-1, std::ios_base::cur);//Move back one char
      }
      if(orig.fail() || tmp.fail()){
	cout << "Error: Internal Logic Failure or File Stream Corruption" << endl;
	exit(EXIT_FAILURE);
      }
    }else{
      tmp.put(c);
    }
  }
 
  orig.close();
  tmp.close();

  remove(infile.c_str());//remove original
  rename(newfile.c_str(), infile.c_str());//replace original with temp

  return 0;
}

//moves through the file, one character at a time, and purges block comments. When it finds a /*, it will ignore everything until a */
int RemoveBlockComments(std::string infile){
  cout << "~~~Now Removing Block Comments~~~" << endl;
  char c;
  string newfile = infile + ".temp";

  fstream orig;
  orig.open(infile.c_str(), std::fstream::in);
  if(orig.fail()){
    cout << "Error: Failed to open Data File" << endl;
    exit(EXIT_FAILURE);
  }

  fstream tmp;
  cout << "Creating Temporary File with name " << newfile << endl;//debug
  tmp.open(newfile.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  if(tmp.fail()){
    cout << "Error: Failed to open Temporary File" << endl;
    exit(EXIT_FAILURE);
  }

  while(!orig.eof()){
    orig.get(c);
    if(orig.eof()){break;}//get will never throw an EOF, and will duplicate the last character instead.
    cout << c; //debug
    if(c=='/'){
      char tempchar;
      orig.get(tempchar);
      if(tempchar!='*'){//if it is not a comment
	tmp.put(c); //Not a comment, put both chars down
	tmp.put(tempchar);
      }else{//it's a comment
	bool satisfied = false;
	while(!satisfied){
	  char temp2;
	  orig.get(temp2);
	  if(temp2=='*'){
	    if(orig.get()=='/'){
	      satisfied = true;
	    }//else no good, keep on looking
	  }
	  if(orig.eof()){satisfied = true;}//get will never throw an EOF
	}
      }
      if(orig.fail() || tmp.fail()){
	cout << "Error: Internal Logic Failure or File Stream Corruption" << endl;
	exit(EXIT_FAILURE);
      }
    }else{
      tmp.put(c);
    }
  }

  orig.close();
  tmp.close();

  remove(infile.c_str());//remove original
  rename(newfile.c_str(), infile.c_str());//replace original with temp

  return 0;
}
