#include "fcorner.h"

FCorner::FCorner(QObject *parent) :
    Filter(parent)
{
}

QString FCorner::getName()
{
    return QString("Corner Detecting");
}

QString FCorner::getCaption()
{
    return QString("Corner");
}

QVector<DatInfo> FCorner::getInputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(IMAGE1,"Input Image"));
    return ans;
}

QVector<DatInfo> FCorner::getOutputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(POINT, "Found Corners"));
    return ans;
}

void FCorner::showConfig()
{
    dialog.exec();
}

QMap<QString, QVariant> FCorner::getData()
{

}

void FCorner::setData(QMap<QString, QVariant> data)
{

}

void FCorner::reset()
{

}

QVector<Data*> FCorner::run(QVector<Data*> dat)
{

}
