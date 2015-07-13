/* 
 * File:   CoderWriter.h
 * Author: drose
 *
 * Created on July 11, 2015, 9:10 AM
 */

#ifndef CODERWRITER_H
#define	CODERWRITER_H
#include "Utility.h"
class CodeWriter
{
public:
    CodeWriter();
    void setFileName(string FileName);
    void writeArithmetic(string command);
    void writePushPop(string command, string segment, int index);
protected:
    ofstream fout;
    int eq, gt, lt;
};
#endif	/* CODERWRITER_H */

