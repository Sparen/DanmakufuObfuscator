#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "dnhobf_fxn.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::fstream;

//Removal of Block Comments MUST come before Removal of Single Line Comments
//Removal of New Lines And Tabs MUST come after Removal of Comments

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
  RemoveNewLinesAndTabs(infile);
  RemoveExtraWhitespace(infile);
  RestoreNewLinePostDirectory(infile);
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
    cerr << "Error: Failed to open Data File" << endl;
    exit(EXIT_FAILURE);
  }

  fstream tmp;
  //cout << "Creating Temporary File with name " << newfile << endl;//debug
  tmp.open(newfile.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  if(tmp.fail()){
    cerr << "Error: Failed to open Temporary File" << endl;
    exit(EXIT_FAILURE);
  }

  while(!orig.eof()){
    orig.get(c);
    if(orig.eof()){break;}//get will never throw an EOF, and will duplicate the last character instead.
    //cout << c; //debug
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
	cerr << "Error: Internal Logic Failure or File Stream Corruption" << endl;
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
    cerr << "Error: Failed to open Data File" << endl;
    exit(EXIT_FAILURE);
  }

  fstream tmp;
  //cout << "Creating Temporary File with name " << newfile << endl;//debug
  tmp.open(newfile.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  if(tmp.fail()){
    cerr << "Error: Failed to open Temporary File" << endl;
    exit(EXIT_FAILURE);
  }

  while(!orig.eof()){
    orig.get(c);
    if(orig.eof()){break;}//get will never throw an EOF, and will duplicate the last character instead.
    //cout << c; //debug
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
	cerr << "Error: Internal Logic Failure or File Stream Corruption" << endl;
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

//Replaces all instances of new lines and tabs (\n \r \t) with single spaces.
//EXCEPTIONS: Preserves all lines prefixed with a #, as include statements require seperate lines.
int RemoveNewLinesAndTabs(std::string infile){
  cout << "~~~Now Removing New Lines and Tabs~~~" << endl;
  char c;
  string newfile = infile + ".temp";
  bool removingtoggle = true;//whether removing new lines or not - used with # lines

  fstream orig;
  orig.open(infile.c_str(), std::fstream::in);
  if(orig.fail()){
    cerr << "Error: Failed to open Data File" << endl;
    exit(EXIT_FAILURE);
  }

  fstream tmp;
  //cout << "Creating Temporary File with name " << newfile << endl;//debug
  tmp.open(newfile.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  if(tmp.fail()){
    cerr << "Error: Failed to open Temporary File" << endl;
    exit(EXIT_FAILURE);
  }

  while(!orig.eof()){
    orig.get(c);
    if(orig.eof()){break;}//get will never throw an EOF, and will duplicate the last character instead.
    //cout << c; //debug
    if(c=='#'){//do not delete new line at end of line
      removingtoggle = false;
      tmp.put(c);
    }else if(c=='\n' || c=='\r' || c=='\t'){
      if(removingtoggle){
	tmp.put(' '); //replace with white space
      }else{//on a # line. Beware of \r\n things.
	tmp.put(c);
	char temp2;//check next char for \r\n
	orig.get(temp2);
	if(temp2!='\n' && temp2!='\r'){//not a double new line
	  orig.seekg(-1, std::ios_base::cur);//Move back one char
	}
	removingtoggle = true;//no longer on a # line, proceed.
      }
      if(orig.fail() || tmp.fail()){
	cerr << "Error: Internal Logic Failure or File Stream Corruption" << endl;
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

//when it finds a space, removes all following spaces, condensing multiple spaces into a total of one space
int RemoveExtraWhitespace(std::string infile){
  cout << "~~~Now Removing Extra Whitespace~~~" << endl;
  char c;
  string newfile = infile + ".temp";

  fstream orig;
  orig.open(infile.c_str(), std::fstream::in);
  if(orig.fail()){
    cerr << "Error: Failed to open Data File" << endl;
    exit(EXIT_FAILURE);
  }

  fstream tmp;
  //cout << "Creating Temporary File with name " << newfile << endl;//debug
  tmp.open(newfile.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  if(tmp.fail()){
    cerr << "Error: Failed to open Temporary File" << endl;
    exit(EXIT_FAILURE);
  }

  while(!orig.eof()){
    orig.get(c);
    if(orig.eof()){break;}//get will never throw an EOF, and will duplicate the last character instead.
    //cout << c; //debug
    if(c==' '){
      char tempchar;
      orig.get(tempchar);
      if(tempchar!=' '){//if only one space
	tmp.put(c); //Only one space, put both chars down
	if(!orig.eof()){//prevents pasting *BAD* things at end of file
	  tmp.put(tempchar);
	}
      }else{//multiple spaces
	bool satisfied = false;
	char temp2;
	while(!satisfied){
	  orig.get(temp2);
	  if(temp2 != ' '){//move to next non-space character
	    satisfied = true;
	  }
	  if(orig.eof()){satisfied = true;}//get will never throw an EOF
	}
	orig.seekg(-2, std::ios_base::cur);//Move back two chars, two in order to preserve a space, else everything is smushed
      }
      if(orig.eof()){break;} //juuuuust in case. Prevents next block from crashing program if end of file hit.
      if(orig.fail() || tmp.fail()){
	cerr << "Error: Internal Logic Failure or File Stream Corruption" << endl;
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

//Restores newlines after statements calling GetCurrentScriptDirectory
int RestoreNewLinePostDirectory(std::string infile){
  cout << "~~~Now Restoring New Lines for Certain Functions~~~" << endl;
  char c;
  string newfile = infile + ".temp";

  fstream orig;
  orig.open(infile.c_str(), std::fstream::in);
  if(orig.fail()){
    cerr << "Error: Failed to open Data File" << endl;
    exit(EXIT_FAILURE);
  }

  fstream tmp;
  //cout << "Creating Temporary File with name " << newfile << endl;//debug
  tmp.open(newfile.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  if(tmp.fail()){
    cerr << "Error: Failed to open Temporary File" << endl;
    exit(EXIT_FAILURE);
  }

  string target = "GetCurrentScriptDirectory";

  while(!orig.eof()){
    orig.get(c);
    if(orig.eof()){break;}//get will never throw an EOF, and will duplicate the last character instead.
    //cout << c; //debug
    if(c=='G'){
      int istarget = true;
      tmp.put(c);
      for(unsigned long i = 1; i < target.length(); i++){
	char tempchar;
	orig.get(tempchar);
	if(!orig.eof()){//prevents pasting *BAD* things at end of file
	  tmp.put(tempchar);
	}
	//cout << tempchar; //debug
	if(tempchar!=target[i] || orig.eof()){ //add everything so far then
	  istarget = false; //prevent next section from executing
	  break; //kill the inner for loop
	}
      }

      if (istarget) { //if target, insert new line!
	while(true) {
	  char tempchar;
	  orig.get(tempchar);
	  if (tempchar != ';' && tempchar != '}' && tempchar != ']') { 
	    //brace is for blocks where ; is not necessary, bracket is for header fields such as #Title
	    tmp.put(tempchar);
	  }else{
	    tmp.put(tempchar);
	    tmp.put('\n');
	    break;
	  }
	}
      }

      if(orig.eof()){break;} //juuuuust in case. Prevents next block from crashing program if end of file hit.
      if(orig.fail() || tmp.fail()){
	cerr << "Error: Internal Logic Failure or File Stream Corruption" << endl;
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
