#include "fsobel.h"

/*****************************************************************************
 *
 *****************************************************************************/
FSobel::FSobel(QObject* parent) : Filter(parent)
{
    type = 0;
    ksize = 3;
}

/*****************************************************************************
 *
 *****************************************************************************/
FSobel::~FSobel()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FSobel::getName()
{
    return QString("Sobel");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FSobel::getCaption()
{
    return QString("Sobel");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FSobel::getInputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1, "Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FSobel::getOutputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1, "Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FSobel::showConfig()
{
    dialog.exec();
    if (dialog.getType() == "X")
    {
        type = 0;
    }
    else //(dialog.getType() == "Y")
    {
        type = 1;
    }
    ksize = dialog.getKernelSize();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FSobel::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    ans.insert("Type", QVariant(dialog.getType()));
    ans.insert("Kernel", QVariant(dialog.getKernelSize()));


    return ans;

}

/*****************************************************************************
 *
 *****************************************************************************/
void FSobel::setData(QMap<QString, QVariant> data)
{

}

/*****************************************************************************
 *
 *****************************************************************************/
void FSobel::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FSobel::run(QVector<Data*> dat)
{
    DImage1* d = dynamic_cast<DImage1*>(dat[0]);

    Mat sMat;

    switch (type)
    {
        case 0:
            Sobel(d->getImage(), sMat,-1,1,0,ksize);
            break;
        default:
            Sobel(d->getImage(), sMat, -1, 0, 1, ksize);
            break;
    }

    DImage1* a = new DImage1();
    a->setImage(sMat);

    QVector<Data*> ans;
    ans.push_back(a);

    return ans;

}

static FilterFactory<FSobel> fSobel;
