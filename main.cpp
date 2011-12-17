#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwidget.h"
void customMessageHandler(QtMsgType type, const char *msg);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMsgHandler(customMessageHandler);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    MainWidget w;
    w.show();

    return a.exec();
}
//QT 调试日志输出
void customMessageHandler(QtMsgType type, const char *msg)
{
 QString txt;
 switch (type) {
 case QtDebugMsg:
  txt = QString("Debug: %1").arg(msg);
  break;

 case QtWarningMsg:
  txt = QString("Warning: %1").arg(msg);
 break;
 case QtCriticalMsg:
  txt = QString("Critical: %1").arg(msg);
 break;
 case QtFatalMsg:
  txt = QString("Fatal: %1").arg(msg);
  //abort();
  break;
 default:
  txt =QString("Other: %1").arg(msg);


 }

 QFile outFile("debuglog.txt");
 outFile.open(QIODevice::WriteOnly | QIODevice::Append);
 QTextStream ts(&outFile);
 ts << txt << endl;
}
