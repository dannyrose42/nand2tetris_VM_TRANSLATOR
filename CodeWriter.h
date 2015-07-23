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
    void writeArithmetic(string command);
    void writePushPop(COMMAND_TYPE command, string segment, int index);
    void close();
protected:
    ofstream fout;
    int eq, gt, lt;
    string currentVmFileName;
};
#endif	/* CODEWRITER_H */

