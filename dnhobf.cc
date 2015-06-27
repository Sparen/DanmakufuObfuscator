#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include "dnhobf_fxn.h"

using std::string;
using std::cout;
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
      //prompt user for obfuscation level here in the future
      ObfuscateA2(argv[i]);
    }else{
      cout << "Error: " << argv[i] << " does not exist." << endl;
      fclose(infile);
    }
  }
  return 0;
}
