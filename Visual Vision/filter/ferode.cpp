#include "ferode.h"

/*****************************************************************************
 *
 *****************************************************************************/
FErode::FErode(QObject* parent) :
    Filter(parent)
{
}

/*****************************************************************************
 *
 *****************************************************************************/
FErode::~FErode()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FErode::getName()
{
    return QString("Erode");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FErode::getCaption()
{
    return QString("Erode");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FErode::getInputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1,"Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FErode::getOutputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1, "Eroded Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FErode::showConfig()
{
    dialog.exec();

}

/*****************************************************************************
 * Returns data associated with the erode filter.  Used when saving file
 *****************************************************************************/
QMap<QString, QVariant> FErode::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    QString type;
    switch (dialog.getErodeType())
    {
        case FErodeDialog::RECTANGLE:
            type = "Rectangle";
            break;
        case FErodeDialog::CROSS:
            type = "Cross";
            break;
        case FErodeDialog::ELLIPSE:
            type = "Ellipse";
            break;
    }

    ans.insert("Type", QVariant(type));
    ans.insert("SizeX", QVariant(dialog.getSizeX()));
    ans.insert("SizeY", QVariant(dialog.getSizeY()));

    return ans;

}

/*****************************************************************************
 * Takes settings used for erode filter and applies it to filter.  Used when
 * loading a file in
 *****************************************************************************/
void FErode::setData(QMap<QString, QVariant> data)
{
    if (data.contains("Type"))
    {
        QString t = data["Type"].toString();
        FErodeDialog::ERODETYPE type = FErodeDialog::RECTANGLE;
        if (t == "Rectangle")
        {
            type = FErodeDialog::RECTANGLE;
        }
        else if (t == "Cross")
        {
            type = FErodeDialog::CROSS;
        }
        else if (t == "Ellipse")
        {
            type = FErodeDialog::ELLIPSE;
        }
        dialog.setErodeType(type);
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
void FErode::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FErode::run(QVector<Data*> dat)
{
    DImage1* d = dynamic_cast<DImage1*>(dat[0]);

    Mat matAns;

    int erosiontype = MORPH_RECT;
    switch(dialog.getErodeType())
    {
        case FErodeDialog::RECTANGLE:
            erosiontype = MORPH_RECT;
            break;
        case FErodeDialog::CROSS:
            erosiontype = MORPH_CROSS;
            break;
        case FErodeDialog::ELLIPSE:
            erosiontype = MORPH_ELLIPSE;
            break;
    }

    Mat element = getStructuringElement(erosiontype, Size(2 * dialog.getSizeX() + 1, 2 * dialog.getSizeY() + 1), Point(dialog.getSizeX(), dialog.getSizeY()));

    cv::erode(d->getImage(), matAns, element);

    DImage1* a = new DImage1();
    a->setImage(matAns);

    QVector<Data*> ans;
    ans.push_back(a);

    return ans;
}

static FilterFactory<FErode> fErode;
