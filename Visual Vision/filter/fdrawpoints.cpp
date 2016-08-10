#include "fdrawpoints.h"

FDrawPoints::FDrawPoints(QObject *parent) :
    Filter(parent)
{
}

QString FDrawPoints::getName()
{
    return QString("Draw Points");
}

QString FDrawPoints::getCaption()
{
    return QString("Points");
}

QVector<DatInfo> FDrawPoints::getInputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(POINT, "Input Points"));
    ans.push_back(DatInfo(IMAGE3, "Input image"));

    return ans;
}

QVector<DatInfo> FDrawPoints::getOutputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(IMAGE3, "Output Image"));

    return ans;
}

void FDrawPoints::showConfig()
{
    dialog.exec();
}

QMap<QString, QVariant> FDrawPoints::getData()
{

}

void FDrawPoints::setData(QMap<QString, QVariant> data)
{

}

void FDrawPoints::reset()
{

}

QVector<Data*> FDrawPoints::run(QVector<Data*> dat)
{

}

static FilterFactory<FDrawPoints> fDrawPoints;
