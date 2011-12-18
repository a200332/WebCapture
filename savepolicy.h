#ifndef SAVEPOLICY_H
#define SAVEPOLICY_H
#include <QHash>
#include <QObject>

class SavePolicy:public QObject
{
    Q_OBJECT
public:
    SavePolicy(QObject* parent=0);

     virtual bool init(QHash<QString,QString>)=0;//初始化参数

 public slots:
     virtual void Save(QString data,int time)=0;
   signals:
      void curStatus(QString msg);

};

#endif // SAVEPOLICY_H
