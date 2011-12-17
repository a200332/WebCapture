#include <QDebug>
#include "orderbuilder.h"

OrderBuilder::OrderBuilder(){}
OrderBuilder::OrderBuilder(QString u,int s,int e,int st,int l)
{
    baseurl = u;
    start = s;
    cur = s;
    end = e;
    step = st;
    length = l;
    qDebug()<<"construct "+baseurl;

}
QString OrderBuilder::BuildAdd(bool next){
    if(cur>end) return"";
    QString ttt="%1";
    if(length>0){
        ttt=ttt.arg(cur,length,10,QLatin1Char('0'));
    }else{
        ttt=QString::number(cur);
    }
    if(next)cur++;
    return baseurl+ttt;
}
