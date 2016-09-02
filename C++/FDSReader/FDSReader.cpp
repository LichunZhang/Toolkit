/*=========================================================================
   Program:   MainProject
   FileName:  FDSReader.cpp
   Date:      2016/08/22
   Purpose:	  Read .fds file information (ID and Name)
   Version:   v2.0
   Copyright: Lichun Zhang from Soochow University
   Email:     lczhang2011@gmail.com
=========================================================================*/

#include "FDSReader.h"

#include <iostream>
//#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;


FDSReader::FDSReader()
{
	

}

FDSReader::~FDSReader()
{

}


void FDSReader::readFile( const std::string filePath )
{
	m_ID=updatePatientID(filePath);
	m_Name=updatePatientName(filePath);
}


string FDSReader::updatePatientID (const string& filePath)
{
	std::ifstream in(filePath,ifstream::binary);
	//in.open(filePath,ifstream::binary);
	if (!in)
	{
		std::cerr<<"无法打开并解析文件"<<endl;
		return string();
	}

	char ch;	
	string str_id;
	for (int i=0;i<15;++i){
		for (int j=0;j<16;++j){
			//in>>ch;
			//cout<<j<<":"<<ch<<" ";
			in>>ch;
			if (i==14&&j>3){
				ch==0?str_id+=32:str_id+=ch;
			}
			//cout<<endl;
		}
	}
	str_id=Trim(str_id," ");
	in.close();
	return str_id;
}

string FDSReader::updatePatientName (const string& filePath)
{
	std::ifstream in(filePath,ifstream::binary);
	//in.open(filePath,ifstream::binary);
	if (!in)
	{
		std::cerr<<"无法打开并解析文件"<<endl;
		return string();
	}

	char ch;	
	string str_name;
	for (int i=0;i<15;++i){
		for (int j=0;j<16;++j){
			in>>ch;
		}
	}

	for (int i=15;i<19;++i){
		for (int j=0;j<16;++j){
			in>>ch;
			if (i==16&&j>3)
				ch==0?str_name+=32:str_name+=ch;
			if (i==18&&j>3)
				ch==0?str_name+=32:str_name+=ch;
		}
		i==16?str_name=Trim(str_name," ")+" ":str_name=str_name;
	}

	str_name=Trim(str_name," ");
	in.close();
	return str_name;
}


string FDSReader::Trim( string str,string str2)
{
	if (str.empty())
		return str;
	else{
		//int index=str.find_last_not_of(str2);
		str.erase(0,str.find_first_not_of(str2));
		str.erase(str.find_last_not_of(str2)+1);
		return str;
	}
	
}


