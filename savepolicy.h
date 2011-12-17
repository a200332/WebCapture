#ifndef SAVEPOLICY_H
#define SAVEPOLICY_H
#include <QString>
class SavePolicy
{
public:
     virtual void Save(QString)=0;
     virtual void SetRegxPattern(QString)=0;
};

#endif // SAVEPOLICY_H
