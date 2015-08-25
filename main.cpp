/* 
 * File:   main.cpp
 * Author: drose
 *
 * Created on July 11, 2015, 8:47 AM
 */


#include "Utility.h"
#include "VmParser.h"
#include "CodeWriter.h"

void getVmFileList(vector<string>& dirlist, string dirName){
  DIR           *d;
  struct dirent *dir;
  string st;
  
  d = opendir(dirName.c_str());
  if (d)
  {
    while ((dir = readdir(d)) != NULL)    {
        st = dir->d_name;     
        if(st.size() > 3)
            if(st.substr(st.size()-3,3).compare(".vm")==0)
                dirlist.push_back(st);
    }
    closedir(d);
  }
}
int main(int argc, char** argv) {
    string input, vmFilePath, asmFile = "";
    ofstream output;
    bool directory = true; 
    vector<string> vmFileList;
    vector<VmParser*> parserList;
    
    cout << "Enter .vm file or directory name" << endl;
    cin >> input;
    asmFile = input;
    
    /*Determine if input is the name of specific vm file or a directory
     * If input is a single vm file the ".vm" extension is required which
     * which means input.size() will be > 3.
     */
    if(input.size() > 3)
        if(input.substr(input.size()-3,3).compare(".vm")==0){
            directory = false;
            vmFileList.push_back(input);
            asmFile.erase(asmFile.size()-3, 3);
        }else
           getVmFileList(vmFileList, input);
    else//directory name could be < 3 chars
        getVmFileList(vmFileList, input);
    
    
    //add .asm extension to the output file name string and build the CodeWriter
    asmFile.append(".asm");    
    CodeWriter CodeWriter(asmFile);
    
    //Fill parserList vector with VmParser objects from vmFileList
    for(int i=0;i<vmFileList.size();i++){
        if(directory)
            parserList.push_back(new VmParser(input + "//" + vmFileList[i]));
        else           
        parserList.push_back(new VmParser(vmFileList[i]));
    }
        
    if(vmFileList.size() != parserList.size())
        cout << "vmFileList and parserList unequal" << endl;
    
    CodeWriter.writeBootStrap();
    for (int i = 0;i < vmFileList.size();i++){
        CodeWriter.setFileName(vmFileList[i]);
        while (parserList[i]->hasMoreCommands()){
            parserList[i]->advance();
            if(parserList[i]->valid_command){
                //debug
                cout << endl << "Current Command:" << parserList[i]->getCurrentCommand() << endl;
                switch(parserList[i]->commandType()){
                    case C_ARITHMETIC:
                        CodeWriter.writeArithmetic(parserList[i]->arg1());
                        break;
                    case C_PUSH:
                        CodeWriter.writePushPop(C_PUSH, parserList[i]->arg1(), parserList[i]->arg2());
                        break;
                    case C_POP:
                        CodeWriter.writePushPop(C_POP, parserList[i]->arg1(), parserList[i]->arg2());
                        break;                  
                    case C_LABEL:
                        CodeWriter.writeLabel(parserList[i]->arg1());
                        break;
                    case C_GOTO:
                        CodeWriter.writeGoto(parserList[i]->arg1());
                        break;
                    case C_IF:
                        CodeWriter.writeIf(parserList[i]->arg1());
                        break;
                    case C_FUNCTION:
                        CodeWriter.writeFunction(parserList[i]->arg1(), parserList[i]->arg2());
                        break;
                    case C_RETURN:
                        CodeWriter.writeReturn();
                        break;
                    case C_CALL:
                        CodeWriter.writeCall(parserList[i]->arg1(), parserList[i]->arg2());
                        break;
                    default:
                        break;
                } 
            }
        }    
    }
    cout << "Translation complete." << endl;
}

