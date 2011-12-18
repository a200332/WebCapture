#include <QStringList>
#include <QDebug>
#include "savebysqlite.h"

SaveBySqlite::SaveBySqlite(QObject *parent) :
    SavePolicy(parent)
{
}

void SaveBySqlite::Save(QString data, int time){
    int pos=0;
    int cc=0;
    QStringList capt;
    db.transaction();
    while((pos = _exp.indexIn(data,pos)) != -1){
        count++;
        cc++;
        pos+= _exp.matchedLength();
        capt=_exp.capturedTexts();

        capt.removeFirst();
        //Q_ASSERT(capt.length()==8);
        QString sql=_insertSql.arg(capt.join("','"));//;"INSERT INTO data VALUES('"+capt.join("','")+"')";
        // sql="INSERT INTO data VALUES('"+capt.at(1)+"','"+capt.at(2)+"','";
        //sql+=capt.at(3)+"','"+capt.at(4)+"','"+capt.at(5)
        _query.exec(sql);

    }
    qDebug()<<"finished:"<<cc<<data;
    db.commit();

}

void SaveBySqlite::SetRegxPattern(QString data){

}

bool SaveBySqlite::init(QHash<QString, QString> param){
    count = 0;
    if(!db.connectionName().isEmpty()){
        db.close();
    }
    if(false&&!(param.contains("DBMS")&&param.contains("DBName"))){
        qDebug()<<"few arguments given!";
        return false;         //参数不足
    }
    int cc=0;
    QString conName("webc_conn_");
    //for(;cc<MAX_CONNECTIONS;cc++){
        //if(!QSqlDatabase::contains(conName.append(cc))){
          db=QSqlDatabase::addDatabase(param.value("DBMS"),conName);
           // break;
       // }
   // }
    if(cc==MAX_CONNECTIONS){
        qDebug()<<"too many connections!";
        return false; //数据库连接添加失败，连接太多
    }
    db.setDatabaseName(param.value("DBName"));
    if(!db.open()){
        qDebug()<<"couldnt open the database!";
        return false;
    }
    _query = QSqlQuery(db);
    if(param.contains("INIT_SQL")){
        _query.exec(param.value("INIT_SQL"));
    }
    _exp.setPattern(param.value("PATTERN",".*"));
    _insertSql = param.value("INSERT_SQL");
    qDebug()<<_exp.pattern()<<_insertSql;
    return true;

}
