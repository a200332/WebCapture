#ifndef TXTFILEBUILDER_H
#define TXTFILEBUILDER_H
#include "urlbuilder.h"
class QFile;
class TxtFileBuilder : public UrlBuilder
{
public:
    TxtFileBuilder(QString filename);
    QString BuildAdd(bool next);
private:
    QString filename;
    QFile* file;
    int count;
    int cur;
};

#endif // TXTFILEBUILDER_H
