#include "VmParser.h"
//Constructor opens the input file/stream and gets ready to parse it
Parser::Parser(string file){
    input_file = file;
    fin.open(input_file.c_str());
    if(fin.fail()){
        cout << "Invalid file name." << endl;
    }
    //advance(); // "Advance" to the first command of the file
}
