#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "txtfilebuilder.h"
#include "orderbuilder.h"
#include "savebysqlite.h"
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
   // manager =  new Manager(10,"http://www.baidu.com/index.php?value=",this);
    manager = new Manager(ui->pool_size->value(),"http://www.cdgjbus.com/Card.aspx?Pid=96&CardNumder=",this);
    connect(manager,SIGNAL(StateData(QString)),ui->state_label,SLOT(setText(QString)));
    connect(manager,SIGNAL(RunningChange(int)),ui->cur_size,SLOT(display(int)));
    connect(ui->pool_size,SIGNAL(valueChanged(int)),manager,SLOT(ResizePool(int)));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_pushButton_clicked()
{
    UrlBuilder* build;
    SavePolicy* save;
    //manager->setParms(ui->start->text().toInt(),ui->end->text().toInt(),ui->step->value(),ui->length->value(),ui->dbname->text());
    switch(ui->builderTab->currentIndex()){
    case 0:{
            int s=ui->start->text().toInt();
            int e=ui->end->text().toInt();
            int step=ui->step->text().toInt();
            int len=ui->length->text().toInt();
            if(e-s>0&&step<1){
                step=1;
            }else if(e-s<0&&step>0){
                step=-1;
            }
            if(step==0)step=1;

            build =  new OrderBuilder(ui->baseurl->text(),s,e,step,len);
        }
        break;
    case 1:{
            build = new TxtFileBuilder(ui->txtfile->text());
        }
        break;
    default:
        return;

    }
    QHash<QString,QString> config;
    config.insert("INIT_SQL",ui->initText->toPlainText());
    config.insert("DBMS","QSQLITE");
    config.insert("DBName",ui->dbname->text());
    config.insert("INSERT_SQL",ui->insertText->toPlainText());
    config.insert("PATTERN",ui->expText->toPlainText());
    save =  new SaveBySqlite();
    if(!save->init(config)){
        qDebug("项止初始化失败!");
        return ;
    }

    manager->setParams(build,save);
    ui->builderTab->setDisabled(true);
    manager->StartAll();
}
