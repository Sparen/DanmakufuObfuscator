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
  if(argc<2){
    cout << "Error: No File Specified." << endl;
  }
  vector<FILE*> files;
  for(int i = 0; i < argc-1; i++){//for every file
    //check filepath to see if exists. If it exists, add to files
    FILE* infile = fopen(argv[i], "r");
    if(infile){//exists
      freopen(argv[i], "a+", infile);
      files.push_back(infile);//add to vector.
    }else{
      cout << "Error: " << argv[i] << " does not exist." << endl;
    }
  }
  for(unsigned int i = 0; i < files.size(); i++){
    Obfuscate(files.at(i));
  }
  return 0;
}
