#include "CodeWriter.h"
CodeWriter::CodeWriter(string asmFile){
    equalCount, greaterCount, lessCount, ifCount,  returnCount, functionCount = 0;
    fout.open(asmFile.c_str());
    if (fout.fail()) cout << "Failed to initialize output file:" << asmFile << endl;
    //Trim .asm extension to set currentFileName for static varibles
    asmFile.erase(asmFile.size()-4, 4);
    currentVmFile = asmFile;
}
void CodeWriter::setFileName(string fileName){
    currentVmFile = fileName;
}
void CodeWriter::close(){
    fout.close();
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
        fout << "@eq" << equalCount << endl;
        fout << "D;JNE" << endl;    //if (D!=0) then jump and keep false
        fout << "@SP" << endl;      //else replace false with true
        fout << "A=M" << endl;
        fout << "M=-1" << endl;
        fout << "(eq" << equalCount <<")" << endl;
        fout << "@SP" << endl;
        fout << "M=M+1" << endl;
        equalCount++;
    }else if (command.compare("gt")==0){ //return true if (x > y)
        fout << "@SP" << endl;
        fout << "AM=M-1" << endl;
        fout << "D=M" << endl;      //pop y to D
        fout << "@SP" << endl;
        fout << "AM=M-1" << endl;
        fout << "D=D-M" << endl;    //D = y-x
        fout << "M=0" << endl;      //blindly set false
        fout << "@gt" << greaterCount << endl;
        fout << "D;JGE" << endl;    //if (D >= 0) then jump and keep false
        fout << "@SP" << endl;      //else replace false with true
        fout << "A=M" << endl;
        fout << "M=-1" << endl;
        fout << "(gt" << greaterCount <<")" << endl;
        fout << "@SP" << endl;
        fout << "M=M+1" << endl;
        greaterCount++;
    }else if (command.compare("lt")==0){ //return true if (x < y))
        fout << "@SP" << endl;
        fout << "AM=M-1" << endl;
        fout << "D=M" << endl;      //pop y to D
        fout << "@SP" << endl;
        fout << "AM=M-1" << endl;
        fout << "D=D-M" << endl;    //D = y-x
        fout << "M=0" << endl;      //blindly set false
        fout << "@lt" << lessCount << endl;
        fout << "D;JLE " << endl;    //if (D < 0) then jump and keep false
        fout << "@SP" << endl;      //else replace false with true
        fout << "A=M" << endl;
        fout << "M=-1" << endl;
        fout << "(lt" << lessCount <<")" << endl;
        fout << "@SP" << endl;
        fout << "M=M+1" << endl;
        lessCount++;
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
void CodeWriter::writePushPop(COMMAND_TYPE command, string segment, int index)  {
    /* Replace vm segment with asm symbol equivalent:
     * local -> LCL
     * argument -> ARG
     * this -> THIS
     * that -> THAT
     * pointer -> R3
     * temp -> R5
     * static -> "xxx." (xxx = currentVmFileName) */
    //debug
//    cout << "Segment before:" << segment << endl;
    if (segment.compare("local")==0)
        segment = "LCL";
    else if (segment.compare("argument")==0)
        segment = "ARG";
    else if (segment.compare("this")==0)
        segment = "THIS";
    else if (segment.compare("that")==0)
        segment = "THAT";
    else if (segment.compare("pointer")==0)
        segment = "R3";
    else if (segment.compare("temp")==0)
        segment = "R5";
//    cout << "Segment after:" << segment << endl << endl;
    
    switch (command){
        case C_PUSH:
            //debug
            //cout << "CodeWriter dectects PUSH" << endl;
            if (segment.compare("constant")==0){ //Push constant
                fout << "@" << index << endl;
                fout << "D=A" << endl;
                fout << "@SP" << endl;
                fout << "A=M" << endl;
                fout << "M=D" << endl;
                fout << "@SP" << endl;
                fout << "M=M+1" << endl;
            }else if (segment.compare("static")==0){  //push static
                fout << "@" << currentVmFile << "." << index << endl;
                fout << "D=M" << endl;
                fout << "@SP" << endl;
                fout << "A=M" << endl;
                fout << "M=D" << endl;
                fout << "@SP" << endl;
                fout << "M=M+1" << endl;
            }else if (segment.compare("R3") == 0 // push pointer || temp
                   || segment.compare("R5") ==0){
                fout << "@" << segment << endl;
                fout << "D=A" << endl;
                fout << "@" << index << endl;
                fout << "A=D+A" << endl;
                fout << "D=M" << endl;
                fout << "@SP" << endl;
                fout << "A=M" << endl;
                fout << "M=D" << endl;
                fout << "@SP" << endl;
                fout << "M=M+1" << endl;             
            }else{  //push local || argument || this || that
                fout << "@" << segment << endl;
                fout << "D=M" << endl;
                fout << "@" << index << endl;
                fout << "A=D+A" << endl;
                fout << "D=M" << endl;
                fout << "@SP" << endl;
                fout << "A=M" << endl;
                fout << "M=D" << endl;
                fout << "@SP" << endl;
                fout << "M=M+1" << endl;
            }
            break;
        case C_POP:// static only special case
            //debug
            //cout << "CodeWriter dectects POP" << endl;
            if (segment.compare("static")==0){
                fout << "@SP" << endl;
                fout << "AM=M-1" << endl;
                fout << "D=M" << endl;
                fout << "@" << currentVmFile <<"." << index << endl;
                fout << "M=D" << endl;
            }else if (segment.compare("R3") == 0 //pop pointer || temp
                   || segment.compare("R5") ==0){
                fout << "@" << segment << endl;
                fout << "D=A" << endl;
                fout << "@" << index << endl;
                fout << "D=D+A" << endl;
                fout << "@R13" << endl;
                fout << "M=D" << endl;
                fout << "@SP" << endl;
                fout << "AM=M-1" << endl;
                fout << "D=M" << endl;
                fout << "@R13" << endl;
                fout << "A=M" << endl;
                fout << "M=D" << endl;      
            }else{ // PUSH local || argument || this || that
                fout << "@" << segment << endl;
                fout << "D=M" << endl;
                fout << "@" << index << endl;
                fout << "D=D+A" << endl;
                fout << "@R13" << endl;
                fout << "M=D" << endl;
                fout << "@SP" << endl;
                fout << "AM=M-1" << endl;
                fout << "D=M" << endl;
                fout << "@R13" << endl;
                fout << "A=M" << endl;
                fout << "M=D" << endl;
            }
            
            break;
        default:
            cout <<"writePushPop() called on invalid command type:" << command << endl;                 
    }
}
void CodeWriter::writeLabel(string label){
    fout << "(" << currentFunction << "$" << label << ")" << endl;
}
void CodeWriter::writeGoto(string label){
    fout << "@" << currentFunction << "$" << label << endl;
    fout << "0;JMP" << endl;
}
void CodeWriter::writeIf(string label){
    fout << "@SP" << endl;
    fout << "AM=M-1" << endl;
    fout << "D=M" << endl;
    fout << "@wIf" << ifCount << endl;
    fout << "D;JEQ" << endl;
    fout << "@" << currentFunction << "$" << label << endl;
    fout << "0;JMP" << endl;
    fout << "(wIf" << ifCount << ")" << endl;
    ifCount++;
}
void CodeWriter::writeCall(string functionName, int numOfArgs){
    cout << "returnCount:" << returnCount << endl;
    fout << "@returnAddress" << returnCount << endl;    //push return address
    fout << "D=A" << endl;
    fout << "@SP" << endl;
    fout << "A=M" << endl;
    fout << "M=D" << endl;
    fout << "@SP" << endl;
    fout << "M=M+1" << endl;
    
    fout << "@LCL" << endl;     //push LCL   
    fout << "D=M" << endl;
    fout << "@SP" << endl;
    fout << "A=M" << endl;
    fout << "M=D" << endl;
    fout << "@SP" << endl;
    fout << "M=M+1" << endl;
    
    fout << "@ARG" << endl;     //push ARG
    fout << "D=M" << endl;
    fout << "@SP" << endl;
    fout << "A=M" << endl;
    fout << "M=D" << endl;
    fout << "@SP" << endl;
    fout << "M=M+1" << endl;
    
    fout << "@THIS" << endl;     //push THIS
    fout << "D=M" << endl;
    fout << "@SP" << endl;
    fout << "A=M" << endl;
    fout << "M=D" << endl;
    fout << "@SP" << endl;
    fout << "M=M+1" << endl;
    
    fout << "@THAT" << endl;     //push THAT
    fout << "D=M" << endl;
    fout << "@SP" << endl;
    fout << "A=M" << endl;
    fout << "M=D" << endl;
    fout << "@SP" << endl;
    fout << "M=M+1" << endl;
    
    fout << "@SP" << endl;      //ARG = SP-numOfArgs-5
    fout << "D=M" << endl;
    fout << "@" << numOfArgs << endl;
    fout << "D=D-A" << endl;
    fout << "@5" << endl;
    fout << "D=D-A" << endl;
    fout << "@ARG" << endl;
    fout << "M=D" << endl;
    
    fout << "@SP" << endl;     //LCL = SP
    fout << "D=M" << endl;
    fout << "@LCL" << endl;
    fout << "M=D" << endl;
  
    fout << "@" << functionName << endl;     //goto functionName
    fout << "0;JMP" << endl;
    fout << "(returnAddress" << returnCount << ")" << endl;
    returnCount++; 
}
void CodeWriter::writeReturn(){            
    fout << "@LCL" << endl;     //FRAME(R13) = LCL
    fout << "D=M" << endl;
    fout << "@R13" << endl;
    fout << "M=D" << endl;
    
    fout << "@5" << endl;     //RET(R14) = FRAME(R13) - 5
    fout << "D=D-A" << endl;
    fout << "A=D" << endl;
    fout << "D=M" << endl;
    fout << "@R14" << endl;
    fout << "M=D" << endl;
    
    fout << "@SP" << endl;     //ARG = pop()
    fout << "AM=M-1" << endl;
    fout << "D=M" << endl;
    fout << "@ARG" << endl;
    fout << "A=M" << endl; 
    fout << "M=D" << endl;
    
    fout << "@ARG" << endl;     // SP = ARG+1
    fout << "D=M+1" << endl;
    fout << "@SP" << endl;
    fout << "M=D" << endl;
    
    fout << "@R13" << endl;     // THAT = FRAME(R13)-1
    fout << "D=M" << endl;
    fout << "D=D-1" << endl;
    fout << "A=D" << endl;
    fout << "D=M" << endl;
    fout << "@THAT" << endl;
    fout << "M=D" << endl;
    
    fout << "@R13" << endl;     //THIS = FRAM(R13)-2
    fout << "D=M" << endl;
    fout << "@2" << endl;
    fout << "D=D-A" << endl;
    fout << "A=D" << endl;
    fout << "D=M" << endl;
    fout << "@THIS" << endl;
    fout << "M=D" << endl;
    
    fout << "@R13" << endl;     //ARG = FRAM(R13)-3
    fout << "D=M" << endl;
    fout << "@3" << endl;
    fout << "D=D-A" << endl;
    fout << "A=D" << endl;
    fout << "D=M" << endl;
    fout << "@ARG" << endl;
    fout << "M=D" << endl;
    
    fout << "@R13" << endl;     //LCL = FRAM(R13)-4
    fout << "D=M" << endl;
    fout << "@4" << endl;
    fout << "D=D-A" << endl;
    fout << "A=D" << endl;
    fout << "D=M" << endl;
    fout << "@LCL" << endl;
    fout << "M=D" << endl;
    
    fout << "@R14" << endl;     //goto RET(R14)
    fout << "A=M" << endl;
    fout << "0;JMP" << endl;
}
void CodeWriter::writeFunction(string functionName, int numOfLocals){
    currentFunction = functionName;
    fout << "(" << functionName << ")" << endl;
    if (numOfLocals > 0){
        fout << "@" << numOfLocals << endl;
        fout << "D=A" << endl;

        fout << "(localLOOP" << functionCount << ")" << endl;
        fout << "@SP" << endl;      //push zero
        fout << "A=M" << endl;
        fout << "M=0" << endl;
        fout << "@SP" << endl;
        fout << "M=M+1" << endl;

        fout << "D=D-1" << endl;

        fout << "@" << "localLOOP" << functionCount << endl;
        fout << "D;JNE" << endl;
        functionCount++;
    }
}
void CodeWriter::writeBootStrap(){
    //SP = 256
    fout << "@256" << endl;
    fout << "D=A" << endl;
    fout << "@SP" << endl;
    fout << "M=D" << endl;
    //LCL = -1
    fout << "@0" << endl;
    fout << "A=A+1" << endl;
    fout << "M=-A" << endl;
    //ARG = -2
    fout << "A=A+1" << endl;
    fout << "M=-A" << endl;
    //THIS = -3
    fout << "A=A+1" << endl;
    fout << "M=-A" << endl;
    //that = -4
    fout << "A=A+1" << endl;
    fout << "M=-A" << endl;
    //Call Sys.init
    writeCall("Sys.init", 0);
}
