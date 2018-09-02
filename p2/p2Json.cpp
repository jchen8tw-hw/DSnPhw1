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
#include<iomanip>
#include <sstream>
#include "p2Json.h"
#define ss stringstream

using namespace std;

// Implement member functions of class Row and Table here
bool Json::read(const string& jsonFile){
  ifstream infile(jsonFile);
  if(infile.is_open() == false ) return false;
  string tmp;
  while(getline(infile,tmp)){
    JsonElem tmpJ;
    if(tmp >> tmpJ) _obj.push_back(tmpJ);
  }
  infile.close();
  return true;
}
bool Json::comm(const string& command){
  smatch options;
  regex_match(command,options,regex(" *([A-Z]*) *([a-zA-Z]*) *(-[0-9]*|[0-9]*) *"));
  if(options[1].str() == "PRINT"){
    print();
    return true;
  } 
  else if (options[1] == "AVE"){
    if(_obj.empty()){
      cout << "Error: No element found!!" << endl;
      return true;
    }
    else{
      double ave = 0;
      for(int i = 0;i<_obj.size();i++){
        ave += ((double)_obj[i].value())/(double)_obj.size();
      }
      cout << "The average of the values is: " << fixed<< setprecision(1) <<  ave << "." << endl;
      return true;
    }
  }
  else if (options[1] == "SUM"){
    if(_obj.empty()){
      cout << "Error: No element found!!" << endl;
      return true;
    }
    else{
      int sum = 0;
      for(int i = 0;i<_obj.size();i++){
        sum+=_obj[i].value();
      }
      cout << "The summation of the values is: " << sum << "." << endl;
      return true;
    }
  }
  else if (options[1] == "MAX"){
    if(_obj.empty()){
      cout << "Error: No element found!!" << endl;
      return true;
    }
    else{
      int max = -1000;
      int maxi =0;
      for(int i = 0;i<_obj.size();i++){
        if(_obj[i].value()>max){ 
          max = _obj[i].value();
          maxi = i;
        }
      }
      cout <<"The maximum element is: { " << _obj[maxi] << " }."<< endl;
      return true;
    }
  }
  else if (options[1] == "MIN"){
    if(_obj.empty()){
      cout << "Error: No element found!!" << endl;
      return true;
    }
    else{
      int min = 1000;
      int mini =0;
      for(int i = 0;i<_obj.size();i++){
        if(_obj[i].value()<min){ 
          min = _obj[i].value();
          mini = i;
        }
      }
      cout <<"The minimum element is: { " << _obj[mini] << " }."<< endl;
      return true;
    }
  }
  else if (options[1] == "ADD"){
    ss buffer;
    string key = options[2].str();
    buffer << options[3];
    int value;
    buffer >> value;
    JsonElem tmp(key,value);
    _obj.push_back(tmp);
    return true;
  }
  else return false;
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
  smatch sm;
  if(regex_match(in,sm,regex("[ \t]*\"([A-Za-z_0-9]*)\"[ \t]*:[ \t]*(-[0-9]*|[0-9]*).*"))){
    j._key = sm[1];
    ss tmp;
    tmp << sm[2].str();
    tmp >> j._value;
    return true;
  }
  else return false;
}
int JsonElem::value(){
  return _value;
}
string JsonElem::key(){
  return _key;
}