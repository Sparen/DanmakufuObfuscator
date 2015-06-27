#ifndef DNHOBF_FXN_H
#define DNHOBF_FXN_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int ObfuscateA1(char* infile);
int ObfuscateA2(char* infile);
int RemoveSingleLineComments(char* infile);
int RemoveBlockComments(char* infile);

#endif
