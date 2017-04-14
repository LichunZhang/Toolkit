// Program: DIP
// FileName:MHDReader.h
// Author:  Lichun Zhang
// Date:    2017/4/5 下午8:28
// Copyright (c) 2017 Lichun Zhang. All rights reserved.

#ifndef DIP_MHD_READER_H
#define DIP_MHD_READER_H


#include <string>
class MHDReader {
public:
    MHDReader(const char *name = nullptr);

    virtual ~MHDReader();

    void ReadFile(const char* name);
    void Write(const char* name);

    const std::string &GetFileName() const {
        return _fileName;
    }

    //TODO: Return various type data
    unsigned char * GetImData() const {
        return _dataType.empty()? nullptr:_imData;
    }

    size_t GetImWidth() { return _dimX;}
    size_t GetImHeight() { return _dimY;}
    size_t GetImSlice() { return _dimZ;}

private:
    std::string _fileName;
    std::size_t _dimX, _dimY, _dimZ;
    double _spacingX, _spacingY, _spacingZ;
    std::string _dataType;
    unsigned char * _imData;
    void ReadHeader(const char *name);
    void ReadRaw(const char* name);
    void ConstructData(std::string type, FILE *fp);
};


#endif //DIP_MHD_READER_H