/*=========================================================================
   Program:   MainProject
   FileName:  FDSReader.h
   Date:      2016/08/22
   Purpose:	  Read .fds file information (ID and Name)
   Version:   v2.0
   Copyright: Lichun Zhang from Soochow University
   Email:     lczhang2011@gmail.com
=========================================================================*/

#ifndef __FDSReader_H
#define __FDSReader_H

#include <fstream>
#include <string>

class FDSReader
{
public:
	FDSReader();
	~FDSReader();
	void readFile(const std::string filePath);

	std::string getID() const {return m_ID;}
	std::string getName() const {return m_Name;}


protected:
	std::string updatePatientID (const std::string& filePath);
	std::string updatePatientName (const std::string& filePath);
	static std::string Trim(std::string,std::string );

private:
	std::string m_ID,m_Name;
};

#endif	//__FDSReader_H
