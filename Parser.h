/* 
 * File:   Parser.h
 * Author: drose
 *
 * Created on July 11, 2015, 8:50 AM
 */

#ifndef __PARSER_H__
#define	__PARSER_H__
#include "Utility.h"
class Parser
{
public:
    Parser(string input_file);
    bool hasMoreCommands();
    void advance();
    COMMAND_TYPE commandType();
    string arg1();
    int arg2();
};


#endif	/* PARSER_H */

