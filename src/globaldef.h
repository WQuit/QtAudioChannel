#ifndef GLOBALDEF_H
#define GLOBALDEF_H

#include <QString>

typedef struct _fileInfo{
    QString fileName;
    QString filePath;   //LocalFile:localpath;StreamFile:urlpath
} FileInfo,*PFileInfo;

#endif // GLOBALDEF_H
