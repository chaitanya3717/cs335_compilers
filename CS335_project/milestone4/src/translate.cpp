#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <list>
#include <vector>
#include "threeac.h"
using namespace std;


bool check_int(string str)
{
   if(str.empty() || ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+'))) return false ;

   char * p ;
   strtol(str.c_str(), &p, 10) ;

   return (*p == 0) ;
}

void generate(tac instr,string &block_str){

	string reg_var_1, reg_var_2, reg_var_3, reg_var_4, loc_var_1, loc_var_2, loc_var_3;

	int i=0;
	if(instr.type=="assign2"){
		string a = instr.out;
		string b = instr.in1;
		string c = instr.in2;
		
		if(check_int(b)){reg_var_2 = b;}	
		else{
			loc_var_2 = find_loc(b);
			if(loc_var_2=="mem"){
				reg_var_2 = find_reg(b, instr, symboltable);
				block_str = block_str + "lw\t" + reg_var_2 + ", " + b + "\n";
				change_reg(reg_var_2, b);
				change_loc(b, reg_var_2);
			}
			else{
				reg_var_2 = loc_var_2;
			}
		} 
		
		if(check_int(c)){reg_var_3 = c;}	
		else{
			loc_var_3 = find_loc(c);
			if(loc_var_3=="mem"){
				reg_var_3 = find_reg(c, instr, symboltable);
				block_str = block_str + "lw\t" + reg_var_3 + ", " + c + "\n";
				change_reg(reg_var_3, c);
				change_loc(c, reg_var_3);
			}
			else{
				reg_var_3 = loc_var_3;
			}
		} 
		
		loc_var_1 = find_loc(a);
		if(loc_var_1=="mem"){
			reg_var_1 = find_reg(a, instr, symboltable);
			change_reg(reg_var_1, a);
			change_loc(a, reg_var_1);
		}
		else reg_var_1 = loc_var_1;
		
		if(instr.op=="+"){
			if(check_int(reg_var_2)||check_int(reg_var_3)){
				block_str = block_str + "addi\t" + reg_var_1 + ", " + reg_var_2 + ", " + reg_var_3 + "\n";
			}
			else{
				block_str = block_str + "add\t" + reg_var_1 + ", " + reg_var_2 + ", " + reg_var_3 + "\n";
			}
		}
		
		else if(instr.op=="-"){
				block_str = block_str + "sub\t" + reg_var_1 + ", " + reg_var_2 + ", " + reg_var_3 + "\n";
		}
		
		else if(instr.op=="*"){
			block_str = block_str + "mul\t" + reg_var_1 + ", " + reg_var_2 + ", " + reg_var_3 + "\n";
		}
		
		else if(instr.op=="/"){
			block_str = block_str + "div\t" + reg_var_1 + ", " + reg_var_2 + ", " + reg_var_3 + "\n";
		}
		
		else if(instr.op=="%"){
			block_str = block_str + "rem\t" + reg_var_1 + ", " + reg_var_2 + ", " + reg_var_3 + "\n";
		}
		
		else if(instr.op=="&"){
			if(check_int(reg_var_2)||check_int(reg_var_3)){
				block_str = block_str + "andi\t" + reg_var_1 + ", " + reg_var_2 + ", " + reg_var_3 + "\n";
			}
			else{
				block_str = block_str + "and\t" + reg_var_1 + ", " + reg_var_2 + ", " + reg_var_3 + "\n";
			}
		}
		
		else if(instr.op=="|"){
			if(check_int(reg_var_2)||check_int(reg_var_3)){
				block_str = block_str + "ori\t" + reg_var_1 + ", " + reg_var_2 + ", " + reg_var_3 + "\n";
			}
			else{
				block_str = block_str + "or\t" + reg_var_1 + ", " + reg_var_2 + ", " + reg_var_3 + "\n";
			}
		}
		
		else if(instr.op=="^"){
			if(check_int(reg_var_2)||check_int(reg_var_3)){
				block_str = block_str + "xori\t" + reg_var_1 + ", " + reg_var_2 + ", " + reg_var_3 + "\n";
			}
			else{
				block_str = block_str + "xor\t" + reg_var_1 + ", " + reg_var_2 + ", " + reg_var_3 + "\n";
			}
		}
		
	}
	else if(instr.type=="assign1"){
		string a = instr.out;
		string b = instr.in1;
		
		if(check_int(b)){reg_var_2 = b;}
		else{
			loc_var_2 = find_loc(b);
			if(loc_var_2=="mem"){
				reg_var_2 = find_reg(b, instr, symboltable);
				block_str = block_str + "lw\t" + reg_var_2 + ", " + b + "\n";
				change_reg(reg_var_2, b);
				change_loc(b, reg_var_2);
			}
			else{
				reg_var_2 = loc_var_2;
			}
		} 
		
		loc_var_1 = find_loc(a);
		if(loc_var_1=="mem"){
			reg_var_1 = find_reg(a, instr, symboltable);
			change_reg(reg_var_1, a);
			change_loc(a, reg_var_1);
		}
		else reg_var_1 = loc_var_1;
		
		if(check_int(reg_var_2)){
			block_str = block_str + "li\t" + reg_var_1 + ", " + reg_var_2 + "\n";	
		}
		else{
			block_str = block_str + "move\t" + reg_var_1 + ", " + reg_var_2 + "\n";
			
		}
	}
	
	else if(instr.type=="call"){
		block_str = block_str + "jal\t" + instr.op + "\n";
	}

	else if(instr.type=="goto"){
		block_str = block_str + "j\t" + "l" + to_string(instr.target) + "\n";
	}
	
	else if(instr.type=="ifgoto"){

			if(check_int(instr.in1) && check_int(instr.in2)){

				if(instr.op=="leq"){
					block_str = block_str+ "ble\t" + instr.in1 + ", " + instr.in2 + ", " + "l" + to_string(instr.target) + "\n";			
				}

				if(instr.op=="geq"){
					block_str = block_str+ "bge\t" + instr.in1 + ", " + instr.in2 + ", " + "l" + to_string(instr.target)+ "\n";			
				}

				if(instr.op=="le"){
					block_str = block_str+ "blt\t" + instr.in1 + ", " + instr.in2 + ", " + "l" + to_string(instr.target) + "\n";			
				}

				if(instr.op=="ge"){
					block_str = block_str+ "bgt\t" + instr.in1 + ", " + instr.in2 + ", " + "l" + to_string(instr.target) + "\n";			
				}

				if(instr.op=="eq"){
					block_str = block_str+ "beq\t" + instr.in1 + ", " + instr.in2 + ", " + "l" + to_string(instr.target) + "\n";			
				}

				if(instr.op=="neq"){
					block_str = block_str+ "bne\t" + instr.in1 + ", " + instr.in2 + ", " + "l" + to_string(instr.target) + "\n";			
				}
			}

			if(!check_int(instr.in1) && check_int(instr.in2)){

				if(instr.op=="leq"){

					loc_var_2 = find_loc(instr.in1);

					if(loc_var_2!="mem"){
						block_str = block_str+ "ble\t" + loc_var_2 + ", " + instr.in2 + ", " + "l" + to_string(instr.target) + "\n";
					}else{
						reg_var_2=find_reg(instr.in1, instr, symboltable);
						block_str = block_str + "lw\t" + reg_var_2 + ", " + instr.in1 +"\n"; 
						block_str = block_str+ "ble\t" + reg_var_2 + ", " + instr.in2 + ", " + "l" + to_string(instr.target) + "\n";
						change_reg(reg_var_2, instr.in1);
						//cout << "HERE\n";
				        	change_loc(instr.in1, reg_var_2);
					}
					
				}

				if(instr.op=="geq"){

					loc_var_2 = find_loc(instr.in1);

					if(loc_var_2!="mem"){
						block_str = block_str+ "bge\t" + loc_var_2 + ", " + instr.in2 + ", " + "l" + to_string(instr.target) + "\n";
					}else{
						reg_var_2=find_reg(instr.in1, instr, symboltable);
						block_str = block_str + "lw\t" + reg_var_2 + ", " + instr.in1 +"\n";
						block_str = block_str+ "bge\t" + reg_var_2 + ", " + instr.in2 + ", " + "l" + to_string(instr.target) + "\n";
						change_reg(reg_var_2, instr.in1);
				        change_loc(instr.in1, reg_var_2);
					}
					
				}

				if(instr.op=="le"){

					loc_var_2 = find_loc(instr.in1);

					if(loc_var_2!="mem"){
						block_str = block_str+ "blt\t" + loc_var_2 + ", " + instr.in2 + ", " + "l" + to_string(instr.target)+ "\n";
					}else{
						reg_var_2=find_reg(instr.in1, instr, symboltable);
						block_str = block_str + "lw\t" + reg_var_2 + ", " + instr.in1 +"\n";
						block_str = block_str+ "blt\t" + reg_var_2 + ", " + instr.in2 + ", " + "l" + to_string(instr.target)+ "\n";
						change_reg(reg_var_2, instr.in1);
				        change_loc(instr.in1, reg_var_2);
					}
				  
				}
				
				if(instr.op=="ge"){

					loc_var_2 = find_loc(instr.in1);

					if(loc_var_2!="mem"){
						block_str = block_str+ "bgt\t" + loc_var_2 + ", " + instr.in2 + ", " + "l" + to_string(instr.target)+ "\n";
					}else{
						reg_var_2=find_reg(instr.in1, instr, symboltable);
						block_str = block_str + "lw\t" + reg_var_2 + ", " + instr.in1 +"\n";
						block_str = block_str+ "bgt\t" + reg_var_2 + ", " + instr.in2 + ", " + "l" + to_string(instr.target)+ "\n";
						change_reg(reg_var_2, instr.in1);
				        change_loc(instr.in1, reg_var_2);
					}
				}
				
				if(instr.op=="eq"){

					loc_var_2 = find_loc(instr.in1);

					if(loc_var_2!="mem"){
						block_str = block_str+ "beq\t" + loc_var_2 + ", " + instr.in2 + ", " + "l" + to_string(instr.target)+ "\n";
					}else{
						reg_var_2=find_reg(instr.in1, instr, symboltable);
						block_str = block_str + "lw\t" + reg_var_2 + ", " + instr.in1 +"\n";
						block_str = block_str+ "beq\t" + reg_var_2 + ", " + instr.in2 + ", " + "l" + to_string(instr.target)+ "\n";
						change_reg(reg_var_2, instr.in1);
				        change_loc(instr.in1, reg_var_2);
					}
				}
				
				if(instr.op=="neq"){

					loc_var_2 = find_loc(instr.in1);

					if(loc_var_2!="mem"){
						block_str = block_str+ "bne\t" + loc_var_2 + ", " + instr.in2 + ", " + "l" + to_string(instr.target)+ "\n";
					}else{
						reg_var_2=find_reg(instr.in1, instr, symboltable);
						block_str = block_str + "lw\t" + reg_var_2 + ", " + instr.in1 +"\n";
						block_str = block_str+ "bne\t" + reg_var_2 + ", " + instr.in2 + ", " + "l" + to_string(instr.target)+ "\n";
						change_reg(reg_var_2, instr.in1);
				        change_loc(instr.in1, reg_var_2);
					}

				}

				
			}

			if(!check_int(instr.in1) && !check_int(instr.in2)){

				loc_var_1 = find_loc(instr.in1);
				loc_var_2 = find_loc(instr.in2);

				if(loc_var_1 != "mem" && loc_var_2 != "mem"){

					if (instr.op=="leq"){

						block_str = block_str+ "ble\t" + loc_var_1 + ", " + loc_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
					}

					if (instr.op=="geq"){

						block_str = block_str+ "bge\t" + loc_var_1 + ", " + loc_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
					}

					if (instr.op=="le"){

						block_str = block_str+ "blt\t" + loc_var_1 + ", " + loc_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
					}

					if (instr.op=="ge"){

						block_str = block_str+ "bgt\t" + loc_var_1 + ", " + loc_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
					}

					if (instr.op=="eq"){

						block_str = block_str+ "beq\t" + loc_var_1 + ", " + loc_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
					}

					if (instr.op=="neq"){

						block_str = block_str+ "bne\t" + loc_var_1 + ", " + loc_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
					}
				}

				if(loc_var_1=="mem" && loc_var_2 !="mem"){

 					reg_var_1=find_reg(instr.in1,instr, symboltable);	

 					if (instr.op=="leq"){
 						block_str = block_str + "lw\t" + reg_var_1 + ", " + instr.in1 +"\n";
 						block_str = block_str+ "ble\t" + reg_var_1 + ", " + loc_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
 					}

 					if (instr.op=="geq"){
 						block_str = block_str + "lw\t" + reg_var_1 + ", " + instr.in1 +"\n";
 						block_str = block_str+ "bge\t" + reg_var_1 + ", " + loc_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
 					}

 					if (instr.op=="le"){

 						block_str = block_str + "lw\t" + reg_var_1 + ", " + instr.in1 +"\n";
 						block_str = block_str+ "blt\t" + reg_var_1 + ", " + loc_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
 					}

 					if (instr.op=="ge"){

 						block_str = block_str + "lw\t" + reg_var_1 + ", " + instr.in1 +"\n";
 						block_str = block_str+ "bgt\t" + reg_var_1 + ", " + loc_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
 					}

 					if (instr.op=="eq"){

 						block_str = block_str + "lw\t" + reg_var_1 + ", " + instr.in1 +"\n";
 						block_str = block_str+ "beq\t" + reg_var_1 + ", " + loc_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
 					}

 					if (instr.op=="neq"){

 						block_str = block_str + "lw\t" + reg_var_1 + ", " + instr.in1 +"\n";
 						block_str = block_str+ "bne\t" + reg_var_1 + ", " + loc_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
 					}
 					
 					change_reg(reg_var_1, instr.in1);
				    change_loc(instr.in1, reg_var_1);				
				}

				if(loc_var_1=="mem" && loc_var_2=="mem"){

					reg_var_1=find_reg(instr.in1,instr, symboltable);
					reg_var_2=find_reg(instr.in2,instr, symboltable);

					block_str = block_str + "lw\t" + reg_var_1 + ", " + instr.in1 +"\n";
					block_str = block_str + "lw\t" + reg_var_2 + ", " + instr.in2 +"\n";

					if (instr.op=="leq"){

 						block_str = block_str+ "ble\t" + reg_var_1 + ", " + reg_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
 					}

 					if (instr.op=="geq"){

 						block_str = block_str+ "bge\t" + reg_var_1 + ", " + reg_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
 					}

 					if (instr.op=="le"){

 						block_str = block_str+ "blt\t" + reg_var_1 + ", " + reg_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
 					}

 					if (instr.op=="ge"){

 						block_str = block_str+ "bgt\t" + reg_var_1 + ", " + reg_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
 					}

 					if (instr.op=="eq"){

 						block_str = block_str+ "beq\t" + reg_var_1 + ", " + reg_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
 					}

 					if (instr.op=="neq"){

 						block_str = block_str+ "bne\t" + reg_var_1 + ", " + reg_var_2 + ", " + "l" + to_string(instr.target)+ "\n";
 					}

					change_reg(reg_var_1, instr.in1);
				    change_loc(instr.in1, reg_var_1);

				    change_reg(reg_var_2, instr.in2);
				    change_loc(instr.in2, reg_var_2);
				}

			}
			
	}
	
	else if(instr.type=="label"){
		ret=1;
		block_str = block_str + instr.op + ":\n\t";
		block_str = block_str + "addi\t$sp,$sp,-4\n\t";
		block_str = block_str + "sw\t$t0, 0($sp)\n";
	}
	
	else if(instr.type=="return1"){

			if(ret==0){

				block_str = block_str+"li \t$v0, 10"  + "\n" + "syscall"  + "\n" ;    
			}

			if(ret==1){

				block_str = block_str + "lw \t$t0, 0($sp)\naddi \t$sp,$sp,4\njr \t$ra\n";
				ret=0; 
			}
	}

	else if(instr.type=="return2"){

		if(check_int(instr.in1)){
			block_str = block_str + "addi \t$v0, $0, "+ instr.in1 + "\n";
		}else{

			loc_var_1=find_loc(instr.in1);
			if(loc_var_1!="mem"){

				block_str = block_str + "add \t$v0, $0, " + loc_var_1 + "\n";
			}else{

				reg_var_1=find_reg(instr.in1,instr, symboltable);
				change_loc(instr.in1,reg_var_1);
				change_reg(reg_var_1,instr.in1);
				block_str=block_str+"lw \t$v0"+", "+instr.in1 + "\n";
			}
		}
	}

	else if(instr.type=="getreturn"){
		loc_var_1=find_loc(instr.in1);
		if(loc_var_1!="mem"){
			reg_var_1 = loc_var_1;
			block_str = block_str + "move \t" + reg_var_1 + ", $v0" + "\n";
		}else{

			reg_var_1=find_reg(instr.in1,instr, symboltable);
			change_loc(instr.in1,reg_var_1);
			change_reg(reg_var_1,instr.in1);
			block_str = block_str + "move \t" + reg_var_1 + ", $v0" + "\n";
		}
	}

	else if(instr.type=="print"){
			if(check_int(instr.in1)){
				block_str = block_str + "li\t$v0, 1\nli\t$a0, " + instr.in1 + "\n" + "syscall\n";	
			}
			else{
				loc_var_1 = find_loc(instr.in1);
				if(loc_var_1=="mem"){
					reg_var_1 = find_reg(instr.in1,instr, symboltable);
					change_loc(instr.in1,reg_var_1);
					change_reg(reg_var_1,instr.in1);
					block_str = block_str + "lw\t" + reg_var_1 + ", " + instr.in1 + "\n";
				}
				else reg_var_1 = loc_var_1;
				block_str = block_str + "li\t$v0, 1\nmove\t$a0, " + reg_var_1 + "\n" + "syscall\n";
			}
	}
		
}
