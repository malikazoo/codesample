#include "fblur.h"

/*****************************************************************************
 *
 *****************************************************************************/
FBlur::FBlur(QObject* parent) :
    Filter(parent)
{
}

/*****************************************************************************
 *
 *****************************************************************************/
FBlur::~FBlur()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FBlur::getName()
{
    return QString("Blur");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FBlur::getCaption()
{
    return QString("Blur");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FBlur::getInputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1, "Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FBlur::getOutputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1, "Blurred Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FBlur::showConfig()
{
    dialog.exec();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FBlur::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    FBlurDialog::BLURTYPE bt = dialog.getBlurType();

    QString type;
    switch (bt)
    {
        case FBlurDialog::UNIFORM:
            type = "Uniform";
            break;
        case FBlurDialog::MEDIAN:
            type = "Median";
            break;
        case FBlurDialog::GAUSSIAN:
            type = "Gaussian";
            break;
    }

    ans.insert("Type", QVariant(type));
    ans.insert("KernelX", QVariant(dialog.getKernelX()));
    ans.insert("KernelY", QVariant(dialog.getKernelY()));
    ans.insert("SigmaX", QVariant(dialog.getSigmaX()));
    ans.insert("SigmaY", QVariant(dialog.getSigmaY()));

    return ans;

}

/*****************************************************************************
 *
 *****************************************************************************/
void FBlur::setData(QMap<QString, QVariant> data)
{
    if (data.contains("Type"))
    {
        FBlurDialog::BLURTYPE bt;
        QString t = data["Type"].toString();
        if (t == "Uniform")
            bt = FBlurDialog::UNIFORM;
        else if (t == "Median")
            bt = FBlurDialog::MEDIAN;
        else if (t == "Gaussian")
            bt = FBlurDialog::GAUSSIAN;
        else
            bt = FBlurDialog::UNIFORM;
        dialog.setBlurType(bt);
    }

    if (data.contains("KernelX"))
    {
        dialog.setKernelX(data["KernelX"].toInt());
    }

    if (data.contains("KernelY"))
    {
        dialog.setKernelY(data["KernelY"].toInt());
    }

    if (data.contains("SigmaX"))
    {
        dialog.setSigmaX(data["SigmaX"].toDouble());
    }

    if (data.contains("SigmaY"))
    {
        dialog.setSigmaY(data["SigmaY"].toDouble());
    }
}


/*****************************************************************************
 *
 *****************************************************************************/
void FBlur::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FBlur::run(QVector<Data*> dat)
{
    DImage1* d = dynamic_cast<DImage1*>(dat[0]);

    Mat gauMat;

    switch(dialog.getBlurType())
    {
        case FBlurDialog::UNIFORM:
            blur(d->getImage(), gauMat, Size(dialog.getKernelX(), dialog.getKernelY()));
            break;
        case FBlurDialog::MEDIAN:
            medianBlur(d->getImage(), gauMat, dialog.getKernelX());
            break;
        case FBlurDialog::GAUSSIAN:
            GaussianBlur(d->getImage(), gauMat, Size(dialog.getKernelX(), dialog.getKernelY()), dialog.getSigmaX(), dialog.getSigmaY());
            break;
    }

    QVector<Data*> ans;
    DImage1* adat = new DImage1();
    adat->setImage(gauMat);
    ans.push_back(adat);

    return ans;
}

static FilterFactory<FBlur> fBlur;
