//
// Created by chris on 12/30/2021.
//

#ifndef C5_OBFUSCATOR_H
#define C5_OBFUSCATOR_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Obfuscator {

public:
    int linecount=0;
    const string OUT = "newCode.c";
    virtual void obfuscate(string fileName) = 0;//abstract function
    string *parseFile(string filename);//function to read file and store all lines into a string array
    void writeTofile(string *codeArray);//function to write to "OUT" file received string array
    string generateRandomVar();//function to randomly generate a viable variable name in the C language
};

class LineObfuscator : public Obfuscator {
public:
    void obfuscate(string fileName) override;
};
class VarObfuscator : public Obfuscator {
public:
    void obfuscate(string fileName) override;
};
class CommentObfuscator : public Obfuscator {
public:
    void obfuscate(string fileName) override;
};


#endif //C5_OBFUSCATOR_H
