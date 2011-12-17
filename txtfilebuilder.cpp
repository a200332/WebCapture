#include <QFile>
#include "txtfilebuilder.h"

TxtFileBuilder::TxtFileBuilder(QString fn)
{
    file =  new QFile(fn);
    cur=0;

    file->open(QIODevice::ReadOnly);

}
QString TxtFileBuilder::BuildAdd(bool next){
    cur++;
    return QString(file->readLine()).trimmed();
}
