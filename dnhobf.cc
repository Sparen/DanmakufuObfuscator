#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "dnhobf_fxn.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main(int argc, char** argv){
  cout << endl << "DANMAKUFU OBFUSCATOR BY SPAREN" << endl;
  if(argc<2){
    cout << "Error: No File Specified." << endl;
  }
  for(int i = 1; i < argc; i++){//for every file
    FILE* infile = fopen(argv[i], "r");
    if(infile){//exists
      freopen(argv[i], "r+", infile);
      cout << "Preparing " << argv[i] << " for obfuscation." << endl;
      fclose(infile);
      string filename(argv[i]);

      //prompt user for obfuscation level here
      cout << "Please select an obfuscation level for " << filename << endl;
      string input;
      bool satisfied = false;
      while(!satisfied){
	cout << "1: Only remove comments - good for shrinking filesize" << endl;
	cout << "2: Remove comments and whitespace" << endl;
	cout << "q: quit" << endl;
	cin >> input;
	if(input == "1"){
	  ObfuscateA1(filename); satisfied = true;
	}else if(input == "2"){
	  ObfuscateA2(filename); satisfied = true;
	}else if(input == "q" || input == "Q"){
	  cout << "Thank you for using Sparen's Danmakufu Obfuscator" << endl;
	  exit(EXIT_SUCCESS);
	}else{
	  cout << "Invalid input. Please type '1', '2', or 'q' without quotes." << endl;
	}
      }
    }else{
      cout << "Error: " << argv[i] << " does not exist." << endl;
      fclose(infile);
    }
  }
  cout << "Thank you for using Sparen's Danmakufu Obfuscator" << endl;
  return 0;
}
