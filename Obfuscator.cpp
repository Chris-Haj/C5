//
// Created by chris on 12/30/2021.
//


#include "Obfuscator.h"

string Obfuscator::generateRandomVar() {

    /*rand() function was used to randomly pick the size
     * of the variable name, and choosing a letter/number/underscore
     * to add to the variable name
     * */
    int VarLength = (rand() % 16) + 2;
    string name;
    char small;
    char big;
    char num;
    char underscore = '_';
    int chance = rand() % 3;
    for (int i = 0; i < VarLength; i++) {
        small = (char) (97 + (rand() % 26));
        big = (char) (65 + (rand() % 26));
        num = (char) (48 + (rand() % 10));
        switch (chance) {
            case 0:
                name += small;
                break;
            case 1:
                name += big;
                break;
            case 2:
                name += underscore;
                break;
            case 3:
                name += num;
                break;
        }
        chance = rand() % 4;
    }

    return name;
}

string *Obfuscator::parseFile(string fileName) {
    vector<string> array;
    string line;
    fstream file{fileName, ios::in};
    //if file was not found
    if (!file) {
        cout << "File not found!" << endl;
        return nullptr;
    }
    //pass through the lines in the file and each line to the string vector
    while (!file.eof()) {
        getline(file, line);
        array.push_back(line);
    }
    file.close();
    linecount = array.size();
    //allocate dynamic array with size of vector array and copy each index.
    string *arr = new string[array.size()];
    for (int i = 0; i < array.size(); i++) {
        arr[i] = array[i];
    }
    return arr;
}

void Obfuscator::writeTofile(string *codearray) {
    ofstream f;
    f.open(OUT);
    if (linecount == 0) {
        cout << "String array was empty." << endl;
        return;
    }
    //pass through the received array and write each index into newcode.c file
    for (int i = 0; i < linecount; i++) {
        f << codearray[i];
        if (i != linecount - 1)
            f << '\n';
    }
    f.close();
}

void LineObfuscator::obfuscate(string fileName) {

    string *lines = parseFile(fileName);
    if (lines->empty()) {
        cout << "File was empty." << endl;
        return;
    }
    string randomVar = generateRandomVar();
    int randomline;
    /*go through array and once we find the main method we add the declaration of
     * new int variable with random name two lines below the main()
     * then randomly choose a line from where we declared the new int and the last line to initialise the
     * new int variable
     * */
    for(int i=0;i<linecount;i++){
        if(lines[i].find("main()")!=-1){
            int lastline = linecount-i+2;
            lines[i+2].append("\n\tint "+randomVar+";");
            randomline=rand()%lastline+i+2;
            lines[randomline].append("\n\t"+randomVar+"="+to_string((rand()%1000))+"+"+to_string((rand()%1000)));
            break;
        }
    }
    writeTofile(lines);
}

void VarObfuscator::obfuscate(string fileName) {
    string *lines = parseFile(fileName);

    vector<int> varDefs;
    //loop to store all lines where each a new int was declared
    for (int i = 0; i < linecount; i++) {
        if(lines[i].find("for"))
            continue;
        if (lines[i].find("int ") != -1 && (lines[i].find("int i ") == -1 || lines[i].find("int i;") == -1))
            varDefs.push_back(i);
    }
    /*randomVarIndex will be used to randomly pick an index from the vector which stored
     * all lines where a new integer was declared and StoreVar will be used to store the line
     * that randomVarIndex got*/
    int randomVarIndex= rand() % varDefs.size();
    string StoreVar = lines[varDefs[randomVarIndex]];

/*    the for loop and substr method are used to cut everything from the line stored in StoreVar except
    the variable name
    */
    int start = StoreVar.find("int ") + 4;
    for (start; start < StoreVar.size(); start++) {
        if (StoreVar[start] == ' ' || StoreVar[start] == '=' || StoreVar[start] == ';') {
            break;
        }
    }
    start -= StoreVar.find("int ") + 4;
    StoreVar = StoreVar.substr(StoreVar.find("int ") + 4);
    StoreVar = StoreVar.substr(0, start);
    string newVar = generateRandomVar();
    /*go through each index of the array and each time we encounter the old variable name(StoreVar)
     * we replace it with the new variable name(newVar)
     * */
    for (int i = 0; i < linecount; i++) {
        if (lines[i].find(StoreVar) != -1) {
            lines[i].replace(lines[i].find(StoreVar), StoreVar.length() - 1, newVar);
        }
    }
    writeTofile(lines);
}

void CommentObfuscator::obfuscate(string fileName) {

    string *lines = parseFile(fileName);
    //delete all lines that contain comments.
    for(int i=0;i<linecount;i++){
        if(lines[i].find("//")!=-1){
            lines[i].replace(lines[i].find("//"),lines[i].length()," ");
        }
    }
    string Comments[10];
    Comments[0]="//this is used to check if the graph has a cycle";
    Comments[1]="//check if number is palindrome";
    Comments[2]="//if a==b return false otherwise return true";
    Comments[3]="//while pointer does not point to null loop";
    Comments[4]="//if random number is between num1 and num2 multiply random number by num2-num1";
    Comments[5]="//calculate median of two arrays";
    Comments[6]="//this function is used to reverse the received string as input";
    Comments[7]="//Binary search algorithm";
    Comments[8]="//this function is used to merge Linked List A and Linked List B";
    Comments[9]="//Simple function to calculate num to the power of e";

//    randomly choose how many comments will be written and randomly write random comments into the array
    int howManyComments = linecount/(rand()%7+3);
    for(int i=0;i<howManyComments;i++){
        lines[(int)(rand()%linecount)].append("\n\t").append(Comments[(int)(rand()%Comments->length())]);
    }
    writeTofile(lines);
}
