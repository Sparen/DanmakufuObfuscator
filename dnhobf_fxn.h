#ifndef DNHOBF_FXN_H
#define DNHOBF_FXN_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int ObfuscateA1(std::string infile);
int ObfuscateA2(std::string infile);
int RemoveSingleLineComments(std::string infile);
int RemoveBlockComments(std::string infile);

#endif
