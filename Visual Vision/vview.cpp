#include "vview.h"

/*****************************************************************************
 *
 *****************************************************************************/
VView::VView()
{
    vSelected = false;
    isHighlighted = false;
    //setToolTip("Tooltip");
    setAcceptHoverEvents(true);
}

/*****************************************************************************
 *
 *****************************************************************************/
void VView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (vSelected)
    {
        painter->setBrush(QBrush(Qt::cyan));
        painter->drawRect(vrect.x(), vrect.y(), vrect.width(), vrect.height());
    }

    //painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::Qt4CompatiblePainting);

    if (isHighlighted)
        painter->setPen(QPen(Qt::blue));
    else
        painter->setPen(QPen(Qt::red));

    painter->drawRoundedRect(QRect(vrect.x(), vrect.y() + 15, vrect.width(), vrect.height() - 15), 3, 3);

    painter->setFont(QFont("Helvetica",8));
    painter->setPen(Qt::black);
    painter->drawText(QRect(vrect.x(), vrect.y(), vrect.width() + vrect.x(), vrect.y() + 15), caption);

    for (int i = 0; i < vInput.size(); i++)
    {
        PicPoint pp = vInput[i];
        painter->drawImage(vrect.x() + pp.ul.x(), vrect.y() + pp.ul.y(), getImage(pp.dtype.type));
    }

    for (int i = 0; i < vOutput.size(); i++)
    {
        PicPoint pp = vOutput[i];
        painter->drawImage(vrect.x() + pp.ul.x(), vrect.y() + pp.ul.y(), getImage(pp.dtype.type));
    }

}

/*****************************************************************************
 *
 *****************************************************************************/
QRectF VView::boundingRect() const
{
    return vrect;
}

/*****************************************************************************
 *
 *****************************************************************************/
void VView::setRect(QRectF val)
{
    vrect = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void VView::setRect(float x, float y, float width, float height)
{
    vrect = QRectF(x,y,width,height);
}

/*****************************************************************************
 *
 *****************************************************************************/
int VView::type() const
{
    return Type;
}

/*****************************************************************************
 *
 *****************************************************************************/
void VView::setCaption(QString txt)
{
    caption = txt;
}

/*****************************************************************************
 *
 *****************************************************************************/
void VView::setSelected(bool val)
{
    vSelected = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void VView::setTypes(QVector<DatInfo> inputTypes, QVector<DatInfo> outputTypes)
{
    vInput.clear();
    for (int i = 0; i < inputTypes.size(); i++)
    {
        PicPoint pp;
        pp.dtype = inputTypes[i];
        pp.ul = QPointF(0,0);
        pp.br = QPointF(0,0);
        vInput.push_back(pp);
    }

    vOutput.clear();
    for (int i = 0; i < outputTypes.size(); i++)
    {
        PicPoint pp;
        pp.dtype = outputTypes[i];
        pp.ul = QPointF(0,0);
        pp.br = QPointF(0,0);
        vOutput.push_back(pp);
    }

    int yp = 20;
    if (vInput.size() > 3)
    {
        yp = 20;
    }
    else
    {
        yp = vrect.height() / (vInput.size() + 1);
    }

    for (int i = 0; i < vInput.size(); i++)
    {
        vInput[i].ul = QPointF(5, yp);
        QImage img = getImage(vInput[i].dtype.type);
        vInput[i].br = QPointF(vInput[i].ul.x() + img.width(), vInput[i].ul.y() + img.height());
        yp += 20;
    }


    if (vOutput.size() > 3)
    {
        yp = 20;
    }
    else
    {
        yp = vrect.height() / (vOutput.size() + 1);
    }

    for (int i = 0; i < vOutput.size(); i++)
    {
        vOutput[i].ul = QPointF(vrect.width() - 20, yp);
        QImage img = getImage(vOutput[i].dtype.type);
        vOutput[i].br = QPointF(vOutput[i].ul.x() + img.width(), vOutput[i].ul.y() + img.height());
        yp += 20;
    }


}

/*****************************************************************************
 *
 *****************************************************************************/
SelDat VView::getClicked(QPointF p)
{
    SelDat ans;

    ans.selected = SelDat::C_NONE;

    for (int i = 0; i < vInput.size(); i++)
    {
        PicPoint pp = vInput[i];
        if (p.x() >= pp.ul.x() && p.y() >= pp.ul.y() && p.x() <= pp.br.x() && p.y() <= pp.br.y())
        {
            ans.selected = SelDat::C_IN;
            ans.itemnum = i;
            return ans;
        }

    }

    for (int i = 0; i < vOutput.size(); i++)
    {
        PicPoint pp = vOutput[i];
        if (p.x() >= pp.ul.x() && p.y() >= pp.ul.y() && p.x() <= pp.br.x() && p.y() <= pp.br.y())
        {
            ans.selected = SelDat::C_OUT;
            ans.itemnum = i;
            return ans;
        }

    }

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QPointF VView::getCenterPoint(SelDat d)
{
    if (d.selected == SelDat::C_IN)
    {
        PicPoint pp = vInput[d.itemnum];
        QPointF a = (pp.ul + pp.br) / 2.0;
        return a;
    }
    else if (d.selected == SelDat::C_OUT)
    {
        PicPoint pp = vOutput[d.itemnum];
        QPointF a = (pp.ul + pp.br) / 2.0;
        return a;
    }

    return QPointF(0,0);
}

/*****************************************************************************
 *
 *****************************************************************************/
DatType VView::getDatType(SelDat item)
{
    DatType ans;

    if (item.selected == SelDat::C_IN)
    {
        ans = vInput[item.itemnum].dtype.type;
    }
    else if (item.selected == SelDat::C_OUT)
    {
        ans = vOutput[item.itemnum].dtype.type;
    }
    else
    {
        ans = NONE;
    }

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void VView::setHighLight(bool value)
{
    isHighlighted = value;
}

/*****************************************************************************
 *
 *****************************************************************************/
void VView::setMapObject(MapObj* value)
{
    filt = value;

    setCaption(filt->getCaption());
    QSize siz = filt->getBaseSize();

    vrect = QRectF(0,0,siz.width(), siz.height());
    QVector<DatInfo> ipdt = filt->getInputTypes();
    QVector<DatInfo> odt = filt->getOutputTypes();
    setTypes(ipdt,odt);

}

/*****************************************************************************
 *
 *****************************************************************************/
MapObj* VView::getMapObj()
{
    return filt;
}

/*****************************************************************************
 *
 *****************************************************************************/
void VView::showConfig()
{
    filt->showConfig();
}


