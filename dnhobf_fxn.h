#ifndef DNHOBF_FXN_H
#define DNHOBF_FXN_H

#include <iostream>
#include <string>
#include <vector>

int Obfuscate(char* infile);
int RemoveSingleLineComments(char* infile);
int RemoveBlockComments(char* infile);

#endif
