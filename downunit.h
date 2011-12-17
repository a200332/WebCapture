#ifndef DOWNUNIT_H
#define DOWNUNIT_H
#include <QObject>
#include <QRunnable>
class QHttp;
class QBuffer;
class DownUnit : public QObject//,public QRunnable
{
Q_OBJECT
public:
    explicit DownUnit(QObject *parent = 0);
    void RunTask();
    void SendRequest(QString,bool re=0);//错误重试时置true
signals:
    void Finished(QString result,int time);
    void Exit();
public slots:
    void Request(int id,bool e);
private:
    QHttp* http;
    QObject* parent;
    QBuffer* buf;
    QString cu;
    int count;
    int state;//0 idle 1 running  2 finished
    qint64 start_time;
};

#endif // DOWNUNIT_H
