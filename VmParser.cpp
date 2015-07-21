#include "VmParser.h"
//Constructor opens the input file/stream and gets ready to parse it
VmParser::VmParser(string file){
    input_file = file;
    fin.open(input_file.c_str());
    if(fin.fail()){
        cout << "Failed to open input file:"<< file << endl;
    }
}
//Are there any more commands in the input?
bool VmParser::hasMoreCommands(){
    return !fin.eof();
}
/* Reads the next command from the input and makes it the current command.
 * Should be called only if hasMoreCommands() is true. Initially, there is no
 * current command*/
void VmParser::advance(){
    firstBlankIndex = secondBlankIndex = thirdBlankIndex = arg1Index = arg2Index = 0;
    valid_command = false;
    string current_line;
    while(!valid_command && hasMoreCommands()){
        getline(fin, current_line);
        //remove leading blanks
        current_line.erase(0, current_line.find_first_not_of(" \t\r\n"));
        //remove trailing comment
        for(int i = 0; i < current_line.size(); i++){
            if(current_line.substr(i, 2).compare("//") == 0){
              current_line.erase(i, string::npos);
            }
        }
        if(!current_line.empty()){ 
            valid_command = true;
            current_command = current_line;
            //find index of first blank in current_command
            while(current_command[firstBlankIndex]!= ' ' && firstBlankIndex < current_command.size())
                firstBlankIndex++;
            
            arg1Index = firstBlankIndex;
            //find index of first character of arg1 in current_command
            while(current_command[arg1Index]== ' ' && arg1Index < current_command.size())
                arg1Index++;
            
            secondBlankIndex = arg1Index;
            //find the index of the second blank (first blank after arg1) in current_command
            while(current_command[secondBlankIndex]!= ' ' && secondBlankIndex < current_command.size())
                secondBlankIndex++;    
           
            arg2Index = secondBlankIndex;
            //find the index of the first character of arg2 in current_command
            while(current_command[arg2Index]== ' ' && arg2Index < current_command.size())
                arg2Index++;
            
            thirdBlankIndex = arg2Index;
            //find the index of the third blank in current command. Third blank may occur
            //if there is a trailing comment on the VM command 
            //example: "pop local 4 //comment"
            while(current_command[thirdBlankIndex]!= ' ' && thirdBlankIndex < current_command.size())
                thirdBlankIndex++;
        }      
    }
}
/* Returns the type of the current VM command. 
 * Possibilities:
 * C_ARITHMETIC: 
 * C_PUSH:
 * C_POP:
 * C_LABEL:
 * C_GOTO:
 * C_IF:
 * C_FUNCTION:
 * C_RETURN:
 * C_CALL:
 */
COMMAND_TYPE VmParser::commandType(){
    string command = current_command.substr(0,firstBlankIndex);
    if (command.compare("add")== 0
            || command.compare("sub")== 0
            || command.compare("neg")== 0
            || command.compare("eq")== 0
            || command.compare("gt")== 0
            || command.compare("lt")== 0
            || command.compare("and")== 0
            || command.compare("or")== 0
            || command.compare("not")== 0)
        return C_ARITHMETIC;
    else if (command.compare("push")== 0)    
        return C_PUSH;
    else if (command.compare("pop")== 0)
        return C_POP;
    else if (command.compare("label")== 0)
        return C_LABEL;
    else if (command.compare("goto")== 0)
        return C_GOTO;
    else if (command.compare("if-goto")== 0)
        return C_IF;
    else if (command.compare("function")== 0)
        return C_FUNCTION;
    else if (command.compare("call")== 0)
        return C_CALL;
    else if (command.compare("return")== 0)
                return C_RETURN;
    else
        cout << "Invalid COMMAND_TYPE:" << command << endl;
}
/*Returns the first argument of the current command. In case of C_ARITHMETIC
 the command itself (add, sub, etc) is returned. Should not be called if the 
 current command is C_RETURN*/
string VmParser::arg1(){
    switch (commandType()){
        case C_RETURN:
            cout << "Arg1() called on C_RETURN" << endl;
            break;
        case C_ARITHMETIC:
            return current_command.substr(0, firstBlankIndex);
            break;
        default:
            return current_command.substr(arg1Index,(secondBlankIndex - arg1Index));
            break;
    }
}
/*Returns the second argument of the current command. Should be called only if
 the current command is C_PUSH, C_POP, C_FUNCTION, or C_CALL*/
int VmParser::arg2(){
    if(commandType() == C_PUSH || C_POP || C_FUNCTION || C_CALL){
        string arg2String = "";
        if (thirdBlankIndex < current_command.size())
            arg2String = current_command.substr(arg2Index, (thirdBlankIndex - arg2Index));
        else
            arg2String = current_command.substr(arg2Index, string::npos);
        return atoi(arg2String.c_str());
    } else
        cout << "arg2() called on invalid command type:" << commandType() << endl;   
}