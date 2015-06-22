#ifndef DNHOBF_FXN_H
#define DNHOBF_FXN_H

#include <iostream>
#include <string>
#include <vector>

int Obfuscate(FILE* infile);
int RemoveSingleLineComments(FILE* infile);
int RemoveBlockComments(FILE* infile);

#endif
