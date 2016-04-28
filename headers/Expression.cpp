#ifndef EXPRESSION_H
#define EXPRESSION_H
#include<string>
#include<map>
#include"BBlock.cpp"

#include<iostream>
#include<sstream>
using namespace std;

class Expression
{
public:
  class Expression *left, *right;
  static int nameCounter;
  static set<string> names;
  Expression(Expression *l, Expression *r) 
    : left(l), right(r){}

  virtual bool isLeaf(){
    return left == NULL && right == NULL;
  }
  
  static string newName()
  {
    stringstream result;
    result << "_t" << Expression::nameCounter++;
    names.insert(result.str());
    return result.str();
  }
  
  virtual void namePass(map<Expression*,string> &naming){
    cout << "undefined namepass";
  }
  
  virtual void emitPass(map<Expression*,string> &naming, BBlock** out){
    
    cout << "undefined emit";
  }
  
  string convert(BBlock** out){
    map<Expression*,string> naming;
    this->namePass(naming);
    this->emitPass(naming, out);
    
    return naming[this];
  }
};


#endif