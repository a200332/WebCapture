#include <QThreadPool>
#include <QThread>
#include "manager.h"
#include "downunit.h"
#include "processthread.h"
#include "orderbuilder.h"
#include "txtfilebuilder.h"
#include "savepolicy.h"
Manager::Manager(int m,QString u,QObject *parent) :
    QObject(parent)
{
    url = u;
    pool_change = 0;
    process =  new QThread(this);
    tt = new ProcessThread();
    connect(this,SIGNAL(TransData(QString,int)),tt,SLOT(Process(QString,int)));
    connect(tt,SIGNAL(curstate(QString)),this,SIGNAL(StateData(QString)));
    //tt->moveToThread(process);
    //process->start();
    pool =  new QThreadPool(this);
    pool->setMaxThreadCount(m);
    pool_max=m;
    running=0;
}
void Manager::setParams(int s, int e, int t,int l,QString dbname){
    start=s;
    cur=s;
    end=e;
    if(end-start>0&&t<1){
        t=1;
    }else if(end-start<0&&t>0){
        t=-1;
    }
    if(t==0)t=1;
    length=l;
    //builder =  new OrderBuilder(url,s,e,t,l);
   builder= new TxtFileBuilder("./url.txt");
    tt->SetDbName(dbname);
}
void Manager::setParams(UrlBuilder *b, QString db){
    builder = b;
    tt->SetDbName(db);
}
void Manager::setParams(UrlBuilder *b, SavePolicy *s){
    builder = b;
    saver = s;

    saver->moveToThread(this->process);
    process->start();
    connect(this,SIGNAL(TransData(QString,int)),saver,SLOT(Save(QString,int)));
    connect(saver,SIGNAL(curStatus(QString)),this,SIGNAL(StateData(QString)));
}
QString Manager::Get_A_Task(){
//    if(cur>end)return"";
    QString  cururl=builder->BuildAdd();
    if(cururl!=""&&pool_change<0){
        pool_change++;
        return "";//当需要减少并发时，对一些任务不回复，使它自己结束
    }else if(pool_change>0){
       // this->Start(pool_change);
        pool_change=0;

    }


//    QString ttt="%1";
//    if(length>0){
//        ttt=ttt.arg(cur,length,10,QLatin1Char('0'));
//    }else{
//        ttt=QString::number(cur);
//    }
//    cur++;
     return cururl;
}
void Manager::StartAll(){
    qDebug()<<"Main:"<<QThread::currentThreadId();
    DownUnit* t;
    do{
        t= new DownUnit(this);
        connect(t,SIGNAL(Finished(QString,int)),SIGNAL(TransData(QString,int)));
        connect(t,SIGNAL(destroyed()),SLOT(PoolRemove()));
        t->RunTask();
        running++;
    }while(running<pool_max);
    emit RunningChange(running);
}
void Manager::Start(int num){//增加并发时
    int i=0;
    DownUnit* t;
    for(i=0;i<num;i++){
        qDebug()<<"add a request";
        t = new DownUnit(this);
        //if(pool_change>0)pool_change--;
        connect(t,SIGNAL(Finished(QString,int)),SIGNAL(TransData(QString,int)));
        connect(t,SIGNAL(destroyed()),SLOT(PoolRemove()));
        t->RunTask();
        running++;
    }
    emit RunningChange(running);
}
void Manager::ProcessIt(QString data){
    qDebug()<<QThread::currentThreadId()<<":"<<data;
}
void Manager::ResizePool(int p){
    pool_change += p-pool_max;
    pool_max = p;
    int delt=p-running;
    DownUnit* t;
    for(int i=0;i<delt;i++){
        t = new DownUnit(this);
        connect(t,SIGNAL(Finished(QString,int)),SIGNAL(TransData(QString,int)));
        connect(t,SIGNAL(destroyed()),SLOT(PoolRemove()));
        t->RunTask();
        running++;
    }
    emit RunningChange(running);
    //qDebug()<<"change pool:"<<pool_change;
}
void Manager::PoolRemove(){//在退出并发时减小running值
    running--;
    emit RunningChange(running);
}
void Manager::PreTest(int num){

}
