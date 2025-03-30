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
    SourceFile(const char8_t* apPath);
    SourceFile operator=(SourceFile aOther);
    SourceFile operator+(SourceFile aOther);

    HogString GetContents();
    HogString ReadLine();
    void SetSourceFile(const char8_t* apFilePath);
    void SetSourceFile(HogString apFilePath);
    char8_t* ToString();
    HogString ToHogString();
    LineIterator Iterator();

private:
    char8_t* ToStringWindows();
    char8_t* ToStringPosix();

    HogString m_filePath;
    HogString m_fileContents;
    HogString* m_fileLines;
};
