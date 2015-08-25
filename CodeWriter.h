/* 
 * File:   CodeWriter.h
 * Author: drose
 *
 * Created on July 11, 2015, 9:10 AM
 */

#ifndef CODEWRITER_H
#define	CODEWRITER_H
#include "Utility.h"
class CodeWriter
{
public:
    CodeWriter(string asmFile);
    void setFileName(string FileName);
    void close();
    void writeArithmetic(string command);
    void writePushPop(COMMAND_TYPE command, string segment, int index);
    void writeLabel(string label);
    void writeGoto(string label);
    void writeIf(string label);
    void writeCall(string functionName, int numOfArgs);
    void writeReturn();
    void writeFunction(string functionName, int numOfLocals);
    void writeBootStrap();
protected:
    ofstream fout;
    int equalCount, greaterCount, lessCount, ifCount, returnCount, functionCount;
    string currentFunction, currentVmFile;
};
#endif	/* CODEWRITER_H */

