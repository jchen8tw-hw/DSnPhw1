/****************************************************************************
  FileName     [ p2Json.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define member functions of class Json and JsonElem ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2018-present DVLab, GIEE, NTU, Taiwan ]
****************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <sstream>
#include "p2Json.h"
#define ss stringstream

using namespace std;

// Implement member functions of class Row and Table here
bool Json::read(const string& jsonFile){
  ifstream infile(jsonFile);
  if(infile.is_open() == false ) return false;
  string tmp;
  int i = 0;
  while(getline(infile,tmp)){
    JsonElem tmpJ;
    if(tmp >> tmpJ) _obj.push_back(tmpJ);
  }
  infile.close();
  return true;
}
bool Json::comm(const string& command){
  smatch options;
  regex_search(command,options,regex(" *([A-Z]*) *([A-Z]*) *([A-Z]*) *"));
  cout << options[1] << endl;
  if(options[1].str() == "PRINT"){
    print();
    return true;
  }
  return false;
}
void Json::print(){
  cout << "{" << endl;
  if(!_obj.empty()){  
    for(int i = 0;i<_obj.size()-1;i++){
      cout << _obj[i] << "," << endl;
    }
    cout << _obj[_obj.size()-1] << endl;
  }
  cout << "}" << endl;
}
ostream& operator << (ostream& os, const JsonElem& j)
{
   return (os << "\"" << j._key << "\" : " << j._value);
}
bool operator >> (string& in,JsonElem& j){
  if(regex_match(in,regex("[ \t]*\"([A-Za-z]*)\"[ \t]*:[ \t]*(-[0-9]*|[0-9]*).*"))){
    smatch sm;
    regex_search(in,sm,regex("[ \t]*\"([A-Za-z]*)\"[ \t]*:[ \t]*(-[0-9]*|[0-9]*).*"));
    j._key = sm[1];
    ss tmp;
    tmp << sm[2].str();
    tmp >> j._value;
    return true;
  }
  else return false;
}