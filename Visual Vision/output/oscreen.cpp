#include "oscreen.h"

int OScreen::winNumber = 0;

/*****************************************************************************
 * Default Constructor output screen
 *****************************************************************************/
OScreen::OScreen(QObject* parent) : Output(parent)
{
    currNumber = QString("Screen-" + QString::number(winNumber));
    winNumber++;
}

/*****************************************************************************
 * Returns the name of the screen
 *****************************************************************************/
QString OScreen::getName()
{
    return QString("Screen");
}

/*****************************************************************************
 * Returns the name of the screen
 *****************************************************************************/
QString OScreen::getCaption()
{
    return QString("Screen");
}

/*****************************************************************************
 * A single color image input
 *****************************************************************************/
QVector<DatInfo> OScreen::getInputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE3, "Frame"));
    return ans;
}

/*****************************************************************************
 * Shows the config screen
 *****************************************************************************/
void OScreen::showConfig()
{
    config.exec();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> OScreen::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", getName());

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void OScreen::setData(QMap<QString, QVariant> data)
{

}

/*****************************************************************************
 *
 *****************************************************************************/
void OScreen::reset()
{

}

/*****************************************************************************
 * Runs the output showing the curent image on screen
 *****************************************************************************/
QVector<Data*> OScreen::run(QVector<Data*> dat)
{
    if (dat.size() > 0)
    {
        Data* d = dat[0];
        if (d->getType() == IMAGE3)
        {
            DImage3* img = dynamic_cast<DImage3*>(d);
            imshow(currNumber.toStdString(), img->getImage());
            waitKey(10);
        }
    }

    return QVector<Data*>();
}



static OutputFactory<OScreen> oScreen;
