#include "fdialate.h"

/*****************************************************************************
 *
 *****************************************************************************/
FDialate::FDialate(QObject* parent) :
    Filter(parent)
{
}

FDialate::~FDialate()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FDialate::getName()
{
    return QString("Dialate");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FDialate::getCaption()
{
    return QString("Dialate");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FDialate::getInputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1, "Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FDialate::getOutputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1, "Dialated Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDialate::showConfig()
{
    dialog.exec();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FDialate::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    QString type;
    switch(dialog.getDialateType())
    {
        case FDialateDialog::RECTANGLE:
            type = "Rectangle";
            break;
        case FDialateDialog::CROSS:
            type = "Cross";
            break;
        case FDialateDialog::ELLIPSE:
            type = "Ellipse";
            break;
    }

    ans.insert("Type", QVariant(type));
    ans.insert("SizeX", QVariant(dialog.getSizeX()));
    ans.insert("SizeY", QVariant(dialog.getSizeY()));

    return ans;

}

/*****************************************************************************
 *
 *****************************************************************************/
void FDialate::setData(QMap<QString, QVariant> data)
{
    FDialateDialog::DIALATETYPE type = FDialateDialog::RECTANGLE;
    if (data.contains("Type"))
    {
        QString t = data["Type"].toString();
        if (t == "Rectangle")
        {
            type = FDialateDialog::RECTANGLE;
        }
        else if (t == "Cross")
        {
            type = FDialateDialog::CROSS;
        }
        else if (t == "Ellipse")
        {
            type = FDialateDialog::ELLIPSE;
        }
        dialog.setDialateType(type);
    }

    if (data.contains("SizeX"))
    {
        dialog.setSizeX(data["SizeX"].toInt());
    }

    if (data.contains("SizeY"))
    {
        dialog.setSizeY(data["SizeY"].toInt());
    }

}

/*****************************************************************************
 *
 *****************************************************************************/
void FDialate::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FDialate::run(QVector<Data*> dat)
{
    DImage1* d = dynamic_cast<DImage1*>(dat[0]);

    Mat matAns;

    int erosiontype = MORPH_RECT;
    switch(dialog.getDialateType())
    {
        case FDialateDialog::RECTANGLE:
            erosiontype = MORPH_RECT;
            break;
        case FDialateDialog::CROSS:
            erosiontype = MORPH_CROSS;
            break;
        case FDialateDialog::ELLIPSE:
            erosiontype = MORPH_ELLIPSE;
            break;
    }

    Mat element = getStructuringElement(erosiontype, Size(2 * dialog.getSizeX() + 1, 2 * dialog.getSizeY() + 1), Point(dialog.getSizeX(), dialog.getSizeY()));

    cv::dilate(d->getImage(), matAns, element);

    DImage1* a = new DImage1();
    a->setImage(matAns);

    QVector<Data*> ans;
    ans.push_back(a);
    return ans;
}

static FilterFactory<FDialate> fDialate;
