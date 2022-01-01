#include <iostream>
#include "Obfuscator.h"

using namespace std;

int main() {



    Obfuscator* obfs[3];
    obfs[0] = new VarObfuscator();
    obfs[1] = new LineObfuscator();
    obfs[2] = new CommentObfuscator();

    for(int i=1;i<3;i++){
        obfs[i]->obfuscate(obfs[i-1]->OUT);
    }
    delete [] *obfs;



    return 0;
}
