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
    CodeWrite();
    void setFileName(string FileName);
    void writeArithmetic(string command);
    void writePushPop(COMMAND_TYPE command, string segment, int index);
};
#endif	/* CODERWRITER_H */

