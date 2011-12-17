#include <QHttp>
#include <QThread>
#include <QBuffer>
#include <QDateTime>
#include <QElapsedTimer>
#include "downunit.h"
#include "manager.h"

DownUnit::DownUnit(QObject *parent)// :
   // QRunnable()
{
    state=0;
    this->parent=parent;
    count=0;
    http= new QHttp(this);
    http->setHost("www.cdgjbus.com");
    buf =  new QBuffer(this);
    connect(http,SIGNAL(requestFinished(int,bool)),SLOT(Request(int,bool)));

}
void DownUnit::SendRequest(QString u,bool re){
    buf->open(QIODevice::WriteOnly|QIODevice::Truncate);
    state = 1;
    http->get(u,buf);
    if(!re)
        start_time = QDateTime::currentMSecsSinceEpoch();


}
void DownUnit::RunTask(){
    Manager* tt= qobject_cast<Manager*>(parent);
    cu=tt->Get_A_Task();

    if(cu==""){
        qDebug()<<"end thread="<<count;
       // emit Exit();
        this->deleteLater();
        return;
    }
   // qDebug()<<cu;
     SendRequest(cu);
   // ta="      <tr>          <td>00010000012</td>          <td>30</td>          <td>029001</td>          <td>2011-2-20 11:50:32</td>          <td>0</td>          <td>0</td>          <td></td>          <td></td>        </tr>";
    //emit Finished(ta);
    count++;
   // qDebug()<<"gettask:"<<ta;
//}
}
void DownUnit::Request(int id, bool e){
    QString data = QString(buf->buffer());
    int el=QDateTime::currentMSecsSinceEpoch()-start_time;
    buf->close();
    if(e){
        qDebug()<<http->errorString();
        this->SendRequest(cu,e);
    }
    //qDebug()<<data<<http->errorString();

    emit Finished(data,el);
    this->RunTask();
}
