#include<iostream>
#include "compiler.tab.hh"
#include "headers/Node.cpp"
#include "headers/Statement.cpp"
#include "headers/Sequence.cpp"
#include "headers/Assign.cpp"
#include "headers/Constant.cpp"
#include "headers/Variable.cpp"
#include "headers/BBlock.cpp"
#include <fstream>
#include <string.h>
extern Statement* root;
extern FILE *yyin;
void yy::parser::error(string const&err)
{
  cout << "Parse error... " << err << endl;
}

int Expression::nameCounter = 0;
int BBlock::blockCounter = 0;
int main(int argc, char **argv)
{
  yy::parser parser;
  if(argc != 2){
    cout << "Usage: ./int program.lua" << endl;
    return 1;
  }
  yyin = fopen(argv[1], "r");
  if(errno != 0){
    cout << argv[1] << ": " << strerror(errno) << endl;
    return 1;
  }
  
  if(!parser.parse()){
    //root->dump();
    
    BBlock *start = new BBlock();
    BBlock *current = start;
    
    root->convert(&current);
    
    ofstream myfile;
    myfile.open("graph.dot");
    myfile << "digraph structs { node [shape=record];" << endl;
    start->dumpGraph(myfile);
    myfile << "}" << endl;
    myfile.close(); 
    system("dot -Tpdf graph.dot -ograph.pdf");
    
    // TODO clean parse tree & graphs
    return 0;
  }
  return 1;
}