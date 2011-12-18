#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QDebug>
#include <QDateTime>
#include "processthread.h"

ProcessThread::ProcessThread(QString name ,QObject *parent) :
    QObject(parent)
{
    count = 0;

   // QString str_exp="<tr>[\s]*<td>([\d]+)</td>[\s]*<td>(.+)</td>[\s]*<td>(.+)</td>";
   // str_exp+="[\s]*<td>(.+)</td>[\s]*<td>(.*)</td>[\s]*<td>(.*)</td>[\s]*<td>(.*)</td>";
   // str_exp+="[\s]*<td>(.*)</td>[\s]*</tr>"
    QString str_exp="<tr>[\\s]*<td>([\\d]+)</td>[\\s]*<td>([^<]+)</td>[\\s]*<td>([^<]+)</td>";
    str_exp+="[\\s]*<td>([\\s\\d\\-\\:]*)</td>[\\s]*<td>([^<]*)</td>[\\s]*<td>([^<]*)</td>[\\s]*<td>([^<]*)</td>";
    str_exp+="[\\s]*<td>([^<]*)</td>[\\s]*</tr>";
    exp.setPattern(str_exp);


}
void ProcessThread::Process(QString data,int http_time){
    int pos=0;
    int cc=0;
    int cctime=QDateTime::currentMSecsSinceEpoch();
    QStringList capt;
    db.transaction();
    while((pos = exp.indexIn(data,pos)) != -1){
        count++;
        cc++;
        pos+= exp.matchedLength();
        capt=exp.capturedTexts();
        capt.removeFirst();
        //Q_ASSERT(capt.length()==8);
        QString sql="INSERT INTO data VALUES('"+capt.join("','")+"')";
        // sql="INSERT INTO data VALUES('"+capt.at(1)+"','"+capt.at(2)+"','";
        //sql+=capt.at(3)+"','"+capt.at(4)+"','"+capt.at(5)
        query.exec(sql);

    }
    db.commit();

    cctime=QDateTime::currentMSecsSinceEpoch()-cctime;
    qDebug()<<"elp_time:"<<cctime+http_time;
    if(cc>0)
       // emit curstate("正在处理:"+capt.at(0)+",已处理:"+QString::number(count)+",本次耗时:"+QStringcctime+http_time);
    emit this->curstate(QString("正在处理:%1,已处理%2,本次耗时:%3").arg(capt.at(0)).arg(count).arg(cctime+http_time));
}
void ProcessThread::SetDbName(QString name){
    db= QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(name);
    db.open();
    query =  QSqlQuery(db);
    query.exec("SELECT * FROM sqlite_master WHERE name='data'");
    if(!query.next()){
        ///
        ///
        QString sql="CREATE TABLE 'data' ('cid'  varchar(12),'line'  varchar(10),";
        sql+="'busnum'  varchar(10),'time'  datetime,";
        sql+="'cur'  INTEGER,'over'  INTEGER,'price'  INTEGER,'over_price'  INTEGER,";
        sql+="PRIMARY KEY ('cid' ASC, 'time' ASC));";
        query.exec(sql);
    }
}
