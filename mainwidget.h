#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "manager.h"
namespace Ui {
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    Manager* manager;
private slots:
    void on_pushButton_clicked();
};

#endif // MAINWIDGET_H
