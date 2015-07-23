/* 
 * File:   VmParser.h
 * Author: drose
 *
 * Created on July 11, 2015, 8:50 AM
 */

#ifndef __VMPARSER_H__
#define	__VMPARSER_H__
#include "Utility.h"
class VmParser
{
public:
    VmParser(string input_file);
    bool hasMoreCommands();
    string getCurrentCommand();
    void advance();
    COMMAND_TYPE commandType();
    string arg1();
    int arg2();
    bool valid_command;
    

protected:
    fstream fin;
    string input_file;
    string current_command;
    int firstBlankIndex, secondBlankIndex, thirdBlankIndex,
    arg1Index, arg2Index;
};
#endif	/* PARSER_H */

