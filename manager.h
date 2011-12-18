#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "myutil.h"
class QThreadPool;
class QThread;
class ProcessThread;
class UrlBuilder;
class SavePolicy;
class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(int max,QString url,QObject *parent = 0);
    void init();
    ///
    /// start 参数开始 end结束　step　步长 length参数在URL中的长度，不足补前导0,数据库名
    void setParams(int start,int end,int step=0,int length=0,QString dbname="test.db");
    void setParams(UrlBuilder* b,QString db);
    void setParams(UrlBuilder *b, SavePolicy* s);
    QString Get_A_Task();
signals:
    void TransData(QString,int);
    void StateData(QString);//回传状态
    void RunningChange(int);//当前运行并发数
public slots:
    void StartAll();
    void Start(int num);
    void ProcessIt(QString);
    void ResizePool(int);
    void PoolRemove();
    void PreTest(int num);
private:
    QThreadPool *pool;
    QThread* process;
    UrlBuilder* builder;
    ProcessThread* tt;
    SavePolicy* saver;
    int pool_max;
    int running;
    QString url;
    QString cookie;
    int start;
    int end;
    int cur;
    int step;
    int length;
    int pool_change;//pool_change用来调整并发数量，正时增加，负数减少

};

#endif // MANAGER_H
