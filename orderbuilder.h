#ifndef ORDERBUILDER_H
#define ORDERBUILDER_H
#include <QString>
#include "urlbuilder.h"
class OrderBuilder : public UrlBuilder
{
public:
    OrderBuilder();
    OrderBuilder(QString url,int s,int e,int step,int len);
    virtual QString BuildAdd(bool next=true);
private :
        QString baseurl;
        int start;
        int end;
        int step;
        int length;
        int cur;
};

#endif // ORDERBUILDER_H
