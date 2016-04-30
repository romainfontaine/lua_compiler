#ifndef THREEAD_H
#define THREEAD_H

#include <string>
#include<iostream>
#include<sstream>
#include <fstream>
using namespace std;

class ThreeAd
{
public:
  string result;
  string op;
  string lhs, rhs;

  ThreeAd(string out, string o, string l, string r)
    :  result(out), op(o), lhs(l), rhs(r)      {}

  void graph(ofstream &f)
  {
    f << result << " := " << lhs << " " 
         << op << " " << rhs;
  }
  
  // Returns true if the last instruction is the beginning of a jump
  bool assembly(ofstream &f){
    //cout << "'"<<op<<"'"<<endl;
    f<< endl<<"\t #" << result << " := " << lhs << " " 
         << op << " " << rhs << endl;
    if(op.compare("call")!=0
      && op.compare("push")!=0
      && op.compare("popn")!=0
      && op.compare("print")!=0
      && !lhs.empty()){
      f<< "\tmovq\t"<<lhs<<",\t%rax"<<endl;
    }
    if(op.compare("c")!=0 && !rhs.empty())
      f<< "\tmovq\t"<<rhs<<",\t%rbx"<<endl;
    
    if(!op.compare("c")){
        //f<< "\tmv\t%rax,\t%rbx"<<endl;
    } else if (!op.compare("+")){
        f<< "\taddq\t%rbx,\t%rax"<<endl;
    } else if (!op.compare("-")){
        f<< "\tsubq\t%rbx,\t%rax"<<endl;
    } else if (!op.compare("*")){
        f<< "\timulq\t%rbx,\t%rax"<<endl;
    } else if (!op.compare("/")){
        f << "\tcqto"<<endl;
        f<< "\tidivq\t%rbx"<<endl;
    } else if (!op.compare("call")){
        f<< "\tcall \t"<<lhs<<endl;
    } else if (!op.compare("EQ")){
        f<< "\tsubq\t%rbx,\t%rax"<<endl;
        f<<"\tjz";
        return true;
    } else if (!op.compare("NE")){
        f<< "\tsubq\t%rbx,\t%rax"<<endl;
        f<<"\tjnz";
        return true;
    } else if (!op.compare("LT")){
        f<< "\tsubq\t%rbx,\t%rax"<<endl;
        f<<"\tjs";
        return true;
    } else if (!op.compare("LE")){
        f<< "\tsubq\t%rax,\t%rbx"<<endl;
        f<<"\tjns";
        return true;
    } else if (!op.compare("GE")){
        f<< "\tsubq\t%rbx,\t%rax"<<endl;
        f<<"\tjns";
        return true;
    } else if (!op.compare("GT")){
        f<< "\tsubq\t%rax,\t%rbx"<<endl;
        f<<"\tjs";
        return true;
    } else if (!op.compare("print")){
        f   << "movq $4, %rax"<<endl
            << "movq $1, %rbx" << endl
            << "movq $"<< lhs <<"_len, %rdx" << endl
            << "movq $"<< lhs <<", %rcx" << endl
            << "int  $0x80" << endl
            
            << "movq $4, %rax"<<endl
            << "movq $1, %rbx" << endl
            << "movq $1, %rdx" << endl
            << "movq $10, _char" << endl
            << "movq $_char, %rcx" << endl
            << "int  $0x80" << endl;
    } else if (!op.compare("popn")){
        f   << "addq $"<< 8*stoi(lhs) <<", %rsp"<<endl;
    } else if (!op.compare("push")){
        f   << "push "<<lhs<<endl;
    }

    if(!result.empty())
      f<< "\tmovq\t%rax,\t"<<result<<endl;
    return false;
  }

  
};
#endif