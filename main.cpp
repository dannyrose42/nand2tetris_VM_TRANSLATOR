/* 
 * File:   main.cpp
 * Author: drose
 *
 * Created on July 11, 2015, 8:47 AM
 */

#include "Utility.h"
#include "VmParser.h"
#include "CodeWriter.h"
int main(int argc, char** argv) {
    string vmFile, asmFile = "";
    ofstream output;
    
    cout << "Enter .vm file name" << endl;
    cin >> vmFile;
    asmFile = vmFile;
    //Replace ".vm" extension with ".asm"
    asmFile.erase(asmFile.size()-3, 3);
    asmFile.append(".asm");
    
    VmParser Parser(vmFile);
    CodeWriter CodeWriter(asmFile);
    
    while (Parser.hasMoreCommands()){
        Parser.advance();
        if(Parser.valid_command){
            //debug
            cout << endl << "Current Command:" << Parser.getCurrentCommand() << endl;
            switch(Parser.commandType()){
                case C_ARITHMETIC:
                    CodeWriter.writeArithmetic(Parser.arg1());
                    break;
                case C_PUSH:
                    CodeWriter.writePushPop(C_PUSH, Parser.arg1(), Parser.arg2());
                    break;
                case C_POP:
                    CodeWriter.writePushPop(C_POP, Parser.arg1(), Parser.arg2());
                    break;                  
                case C_LABEL:
                    CodeWriter.writeLabel(Parser.arg1());
                    break;
                case C_GOTO:
                    CodeWriter.writeGoto(Parser.arg1());
                    break;
                case C_IF:
                    CodeWriter.writeIf(Parser.arg1());
                    break;
                case C_FUNCTION:
                    CodeWriter.writeFunction(Parser.arg1(), Parser.arg2());
                    break;
                case C_RETURN:
                    CodeWriter.writeReturn();
                    break;
                case C_CALL:
                    CodeWriter.writeCall(Parser.arg1(), Parser.arg2());
                    break;
                default:
                    break;
            } 
        }    
    }
    cout << "Translation complete." << endl;
}

