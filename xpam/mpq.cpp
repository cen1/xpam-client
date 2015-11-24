/*
Copyright (c) 2013, cen (imbacen@gmail.com)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "mpq.h"
#include "StormLib.h"
#include "util.h"

Mpq::Mpq(){

}

int Mpq::open(QString filename){
    //QByteArray ba = filename.toLocal8Bit();
    //const char *c_str = ba.data();
    //wchar_t fn[1024];
    //filename.toWCharArray(fn);
    return SFileOpenArchive(filename.toStdWString().c_str(), 0, 0, &(this->hMpq));
}

bool Mpq::flush(){
    return SFileFlushArchive(this->hMpq);
}

bool Mpq::close() {
    return SFileCloseArchive(this->hMpq);
}

bool Mpq::openFile(QString filename) {
    QByteArray ba = filename.toLocal8Bit();
    const char *c_str = ba.data();
    return SFileOpenFileEx(this->hMpq, c_str, 0, &(this->hOpenFile));
}

DWORD Mpq::getFileSize() {
    return SFileGetFileSize(this->hOpenFile, NULL);
}

bool Mpq::readFile(QByteArray * ba) {
    char  szBuffer[0x1000];
    DWORD dwTransferred;
    int nError = ERROR_SUCCESS;

    while(true) {
       // dwTransferred is only set to nonzero if something has been read.
       // nError can be ERROR_SUCCESS or ERROR_HANDLE_EOF
       if(!SFileReadFile(this->hOpenFile, szBuffer, sizeof(szBuffer), &dwTransferred, NULL))
           nError = GetLastError();
       if(nError == ERROR_HANDLE_EOF)
           nError = ERROR_SUCCESS;
       if(dwTransferred == 0)
           break;

       // If something has been actually read, write it
       ba->append(szBuffer);
    }
    return (nError == ERROR_SUCCESS);
}

QString Mpq::readFileToString() {
    char  szBuffer[1];
    DWORD dwBytes = 1;
    QString content = "";
    while(dwBytes > 0)
    {
        SFileReadFile(this->hOpenFile, szBuffer, sizeof(szBuffer), &dwBytes, NULL);
        if(dwBytes > 0) {
            content = content+QString::fromLocal8Bit(szBuffer, 1);
        }
    }
    return content;
}

bool Mpq::closeFile() {
    return SFileCloseFile(this->hOpenFile);
}

QString Mpq::getFileName() {
    char buffer[255];
    if (SFileGetFileName(this->hOpenFile, buffer)) {
        return QString::fromLocal8Bit(buffer);
    }
    else return "";
}

bool Mpq::createFile(QString filename, DWORD filesize) {
    QByteArray ba = filename.toLocal8Bit();
    const char *c_str = ba.data();
    return SFileCreateFile(this->hMpq, c_str, 0, filesize, SFileGetLocale(), MPQ_FILE_REPLACEEXISTING, &(this->hOpenFile));
}

bool  Mpq::writeFile(QByteArray ba) {
    return SFileWriteFile(this->hOpenFile, ba.constData(), (DWORD)ba.size(), NULL);
}

bool Mpq::finishWriteFile() {
    return SFileFinishFile(this->hOpenFile);
}

bool Mpq::removeFile(QString filename) {
    QByteArray ba = filename.toLocal8Bit();
    const char *c_str = ba.data();

    return SFileRemoveFile(this->hMpq, c_str, 0);
}

bool Mpq::extractFile(QString mpqfile, QString localfile) {
    std::string smpqfile=mpqfile.toStdString();
    std::wstring slocalfile=localfile.toStdWString();
    return SFileExtractFile(this->hMpq, smpqfile.c_str(), slocalfile.c_str(), SFILE_OPEN_FROM_MPQ);
}

