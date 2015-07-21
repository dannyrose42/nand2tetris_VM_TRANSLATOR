#include "CodeWriter.h"
CodeWriter::CodeWriter(string asmFile){
    eq, gt, lt = 0;
    fout.open(asmFile.c_str());
    if (fout.fail()) cout << "Failed to initialize output file:" << asmFile << endl;   
}
void CodeWriter::setFileName(string FileName){
    
}
void CodeWriter::writeArithmetic(string command){
    if (command.compare("add")==0){
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
    }else if (command.compare("sub")==0){
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
    }else if (command.compare("neg")==0){
        fout << "@SP" << endl;
        fout << "M=M-1" << endl;
        fout << "A=M" << endl;
        fout << "D=M" << endl;
        fout << "M=-D" << endl;
        fout << "@SP" << endl;
        fout << "M=M+1" << endl;
    }else if (command.compare("eq")==0){//return true if (x = y)                     
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
    }else if (command.compare("gt")==0){ //return true if (x > y)
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
    }else if (command.compare("lt")==0){ //return true if (x < y))
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
    }else if (command.compare("and")==0){ //returns x AND y bit-wise
        fout << "@SP" << endl;
        fout << "AM=M-1" << endl;
        fout << "D=M" << endl;      //pop y to D
        fout << "@SP" << endl;
        fout << "AM=M-1" << endl;
        fout << "M=D&M" << endl;    //x = y&x
        fout << "@SP" << endl;
        fout << "M=M+1" << endl;
    }else if (command.compare("or")==0){
        fout << "@SP" << endl;
        fout << "AM=M-1" << endl;
        fout << "D=M" << endl;      //pop y to D
        fout << "@SP" << endl;
        fout << "AM=M-1" << endl;
        fout << "M=D|M" << endl;    //x = y|x
        fout << "@SP" << endl;
        fout << "M=M+1" << endl;
    } else if (command.compare("not")==0){ //return bitwise not y
            fout << "@SP" << endl;
            fout << "AM=M-1" << endl;   
            fout << "M=!M" << endl;
            fout << "@SP" << endl;
            fout << "M=M+1" << endl;
    }else
        cout << "WriteArithmetic() called on invalid command: " << command << endl; 
}
void CodeWriter::writePushPop(COMMAND_TYPE command, string segment, int index){
    string label = "";
    switch (command){
        case C_PUSH:
            if(segment.compare("constant")==0){ //Push constant
                fout << "@" << index << endl;
                fout << "D=A" << endl;
                fout << "@SP" << endl;
                fout << "A=M" << endl;
                fout << "M=D" << endl;
                fout << "@SP" << endl;
                fout << "M=M+1" << endl;
            }
            break;

        case C_POP:
            break;
        default:
            cout <<"writePushPop() called on invalid command type:" << command << endl;                 
    }
 
}
void CodeWriter::close(){
    fout.close();
}
