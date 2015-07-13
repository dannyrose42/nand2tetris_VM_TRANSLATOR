//Push constant 7
@7	//Load constant 7 onto A register
D=A	//Move constant 7 onto D register
@SP	//SP is RAM[0] and contains the address of the top of the stack
A=M	//Load the value at the location pointed to by SP
M=D	//
@SP
M=M+1
@8
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
@SP
A=M
D=M
@SP
M=M-1
@SP
A=M
A=M
D=D+A
@SP
A=M
M=D
@SP
M=M+1