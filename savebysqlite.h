#ifndef SAVEBYSQLITE_H
#define SAVEBYSQLITE_H
#include <QRegExp>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "savepolicy.h"

#define MAX_CONNECTIONS 255
class SaveBySqlite : public SavePolicy
{
    Q_OBJECT
public:
    explicit SaveBySqlite(QObject *parent = 0);
    bool init(QHash<QString,QString> param);
signals:

public slots:
    void Save(QString data,int time);
    void SetRegxPattern(QString data);
private:
    QSqlDatabase db;
    QRegExp _exp;
    QSqlQuery _query;
    QString _insertSql;
    QHash<QString,QString> _config;
    int count;//计数

};

#endif // SAVEBYSQLITE_H
