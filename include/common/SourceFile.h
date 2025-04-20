#pragma once

#include "HogString.h"
#include "Iterator.h"

using LineIterator = Iterator<HogString>;
// Represents a static, unchanging file that is read upon compiler invocation.
// The contents will not change for as long as the compiler is still running from
// said invocation; as such, once the file contents are read, the underlying pointer
// to this class will not change until the end of the compiler's attempt to build 
// your shit code.
//
// Please note this will never ever change because hot module replacement isn't real.
class SourceFile
{
public:
    SourceFile() = default;
    ~SourceFile() = default;
    SourceFile(SourceFile &aOther);
    SourceFile(SourceFile &&aOther);
    SourceFile(const char* apPath);
    SourceFile operator=(SourceFile aOther);
    SourceFile operator+(SourceFile aOther);

    void SetSourceFile(const char8_t* apFilePath);
    void SetSourceFile(HogString apFilePath);
    HogString ToHogString();
    HogString GetContents();
    LineIterator Iterator();
    HogString ReadLine();
    char8_t* ToString();

private:

    HogString m_filePath;
    HogString m_fileContents;
    HogString* m_fileLines;
};
