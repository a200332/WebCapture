#ifndef SAVEBYSQLITE_H
#define SAVEBYSQLITE_H

#include <QObject>
#include "savepolicy.h"
class SaveBySqlite : public QObject,public SavePolicy
{
    Q_OBJECT
public:
    explicit SaveBySqlite(QObject *parent = 0);

signals:

public slots:
    void Save(QString data);
    void SetRegxPattern(QString data);

};

#endif // SAVEBYSQLITE_H
