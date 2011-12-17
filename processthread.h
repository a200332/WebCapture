#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H
#include <QObject>
#include <QThread>
#include <QRegExp>
#include <QSqlQuery>
class QSqlDatabase;
class QSqlQuery;

class ProcessThread : public QObject
{
    Q_OBJECT
public:
    explicit ProcessThread(QString dbname="",QObject *parent = 0);
    void SetDbName(QString);
    void init(QString regx,QString insertSql,QString initSql="");
signals:
    void curstate(QString);
public slots:
    void Process(QString data,int);
private:
    QSqlDatabase db;
    QRegExp exp;
    QSqlQuery query;
    int count;//计数
};

#endif // PROCESSTHREAD_H
