#include "CoderWriter.h"
CodeWriter::CodeWriter(string output_file){
    eq, gt, lt = 0;
    fout.open(output_file.c_str());
    if (fout.fail()) cout << "Failed to initialize output file" << endl;   
}
CodeWriter::setFileName(string FileName){
    
}
CodeWriter::writeArithmetic(string command){
    switch (command){
        case "add":
            fout << "@SP" << endl;
            fout << "AM=M-1" << endl;   //Decrement SP and load it on A
            fout << "D=M" << endl;      //"pop y" off the stack ont D
            fout << "@SP" << endl;
            fout << "M=M-1" << endl;    //Decrement SP
            fout << "@SP" << endl;
            fout << "A=M" << endl;      //load SP into A
            fout << "A=M" << endl;      //"pop x" onto A
            fout << "D=D+A" << endl;    // D = "y + x"
            fout << "@SP" << endl;      //Load A with pointer to what is still "x"
            fout << "A=M" << endl;      //"x" pointer now loaded into A
            fout << "M=D" << endl;      //"push" sum into "x"'s place
            fout << "@SP" << endl;      //Load pointer to top of stack  
            fout << "M=M+1" << endl;    //Increment to point the next element of the stack
            break;
        case "sub":
            fout << "@SP" << endl;
            fout << "M=M-1" << endl;
            fout << "@SP" << endl;
            fout << "A=M" << endl;
            fout << "D=M" << endl;  //pop y to D
            fout << "@SP" << endl;
            fout << "M=M-1" << endl;
            fout << "@SP" << endl;
            fout << "A=M" << endl;
            fout << "A=M" << endl;  //pop x to A
            fout << "D=A-D" << endl;
            fout << "@SP" << endl;
            fout << "A=M" << endl;
            fout << "M=D" << endl;
            fout << "@SP" << endl;
            fout << "M=M+1" << endl;
            break;
        case "neg":
            fout << "@SP" << endl;
            fout << "M=M-1" << endl;
            fout << "A=M" << endl;
            fout << "D=M" << endl;
            fout << "M=-D" << endl;
            fout << "@SP" << endl;
            fout << "M=M+1" << endl;
            break;
        case "eq":                      //return true if (x = y)
            fout << "@SP" << endl;
            fout << "AM=M-1" << endl;
            fout << "D=M" << endl;      //pop y to D
            fout << "@SP" << endl;
            fout << "AM=M-1" << endl;
            fout << "D=D-M" << endl;    //D = y-x
            fout << "M=0" << endl;      //blindly set false
            fout << "@eq" << eq << endl;
            fout << "D;JNE" << endl;    //if (D!=0) then jump and keep false
            fout << "@SP" << endl;      //else replace false with true
            fout << "A=M" << endl;
            fout << "M=-1" << endl;
            fout << "(eq" << eq <<")" << endl;
            fout << "@SP" << endl;
            fout << "M=M+1" << endl;
            eq++;
            break;
        case "gt":                      //return true if (x > y)
            fout << "@SP" << endl;
            fout << "AM=M-1" << endl;
            fout << "D=M" << endl;      //pop y to D
            fout << "@SP" << endl;
            fout << "AM=M-1" << endl;
            fout << "D=D-M" << endl;    //D = y-x
            fout << "M=0" << endl;      //blindly set false
            fout << "@gt" << gt << endl;
            fout << "D;JGT" << endl;    //if (D >= 0) then jump and keep false
            fout << "@SP" << endl;      //else replace false with true
            fout << "A=M" << endl;
            fout << "M=-1" << endl;
            fout << "(gt" << gt <<")" << endl;
            fout << "@SP" << endl;
            fout << "M=M+1" << endl;
            gt++;
            break;
        case "lt":                      //return true if (x < y)
            fout << "@SP" << endl;
            fout << "AM=M-1" << endl;
            fout << "D=M" << endl;      //pop y to D
            fout << "@SP" << endl;
            fout << "AM=M-1" << endl;
            fout << "D=D-M" << endl;    //D = y-x
            fout << "M=0" << endl;      //blindly set false
            fout << "@lt" << lt << endl;
            fout << "D;JLT" << endl;    //if (D < 0) then jump and keep false
            fout << "@SP" << endl;      //else replace false with true
            fout << "A=M" << endl;
            fout << "M=-1" << endl;
            fout << "(lt" << lt <<")" << endl;
            fout << "@SP" << endl;
            fout << "M=M+1" << endl;
            lt++;
            break;
        case "and":                     //returns x AND y bit-wise
            fout << "@SP" << endl;
            fout << "AM=M-1" << endl;
            fout << "D=M" << endl;      //pop y to D
            fout << "@SP" << endl;
            fout << "AM=M-1" << endl;
            fout << "M=D&M" << endl;    //x = y&x
            fout << "@SP" << endl;
            fout << "M=M+1" << endl;
            break;
        case "or":
            fout << "@SP" << endl;
            fout << "AM=M-1" << endl;
            fout << "D=M" << endl;      //pop y to D
            fout << "@SP" << endl;
            fout << "AM=M-1" << endl;
            fout << "M=D|M" << endl;    //x = y|x
            fout << "@SP" << endl;
            fout << "M=M+1" << endl;
            break;
        case "not":                 //return bitwise not y
            fout << "@SP" << endl;
            fout << "AM=M-1" << endl;   
            fout << "M=!M" << endl;
            fout << "@SP" << endl;
            fout << "M=M+1" << endl;
            break;
    } 
}
CodeWriter::writePushPop(COMMAND_TYPE command, string segment, int index){
    switch (command){
        case C_PUSH:
            if(segment.compare("constant")){
                fout << "@" << index << endl;
                fout << "D=A" << endl;
                fout << "@SP" << endl;
                fout << "A=M" << endl;
                fout << "M=D" << endl;
                fout << "@SP" << endl;
                fout << "M=M+1" << endl;
            }
            else cout << "Pushing command other than constant" << endl;   
            break;
        case C_POP:
            break;
        default:
            cout <<"writePushPop() called on invalid command type:" << command << endl;                 
    }
    
    
}
