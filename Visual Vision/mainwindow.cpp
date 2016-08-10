#include "mainwindow.h"
#include "ui_mainwindow.h"

/*****************************************************************************
 *
 *****************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    map = FilterMap::getInstance();// = new filtermap(this);
    ui->gphWindow->setfiltermap(map);

    ui->gphWindow->setVisible(true);

    registry = FilterRegister::getInstance();

    QVector<InputFactoryBase*> inputItems = registry->getInputs();
    for (int i = 0; i < inputItems.size(); i++)
    {
        InputFactoryBase* it = inputItems[i];
        GphListItem itm;
        itm.setText(it->getName());
        itm.setType(INPUT);
        itm.setId(i);

        ui->gphList->addItem(itm);
    }


    QVector<FilterFactoryBase*> items = registry->getFilters();
    for (int i = 0; i < items.size(); i++)
    {
        FilterFactoryBase* it = items[i];

        GphListItem itm;
        itm.setText(it->getName());
        itm.setType(FILTER);
        itm.setId(i);

        ui->gphList->addItem(itm);
    }

    QVector<OutputFactoryBase*> outputItems = registry->getOutputs();
    for (int i = 0; i < outputItems.size(); i++)
    {
        OutputFactoryBase* it = outputItems[i];

        GphListItem itm;
        itm.setText(it->getName());
        itm.setType(OUTPUT);
        itm.setId(i);

        ui->gphList->addItem(itm);
    }

    connect(ui->gphWindow, SIGNAL(updateWindow()), this, SLOT(update()));
    currPlay = false;
    ui->cmdPlay->setEnabled(false);

    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

/*****************************************************************************
 *
 *****************************************************************************/
MainWindow::~MainWindow()
{
    //ui->gphWindow->clear();
    delete ui;
}

/*****************************************************************************
 *
 *****************************************************************************/
void MainWindow::update()
{
    map->updateSystem();
    int maxFrames = map->getMaxFrames();

    ui->hslPlay->setMaximum(maxFrames);
    ui->hslPlay->setValue(0);
    ui->lblFrames->setText(QString::number(0) + "/" + QString::number(maxFrames));

    if (maxFrames != 0)
    {
        ui->cmdPlay->setEnabled(true);
        map->fullReset();
        map->runCurrent();
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void MainWindow::on_cmdPlay_clicked()
{
    if (ui->hslPlay->value() < ui->hslPlay->maximum())
    {
        if (currPlay)
        {
            ui->cmdPlay->setIcon(QIcon(":/interface/play.png"));
            currPlay = false;
        }
        else
        {
            ui->cmdPlay->setIcon(QIcon(":/interface/pause.png"));
            currPlay = true;
            run();
        }
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void MainWindow::run()
{
    int currFrame = ui->hslPlay->value();
    int maxFrames = map->getMaxFrames();

    map->fullReset();

    while((currFrame < maxFrames || maxFrames < 0) && currPlay)
    {
        currFrame = map->runNext();
        ui->hslPlay->setValue(currFrame);
        ui->lblFrames->setText(QString::number(currFrame) + "/" + QString::number(maxFrames));
        QApplication::processEvents();
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void MainWindow::saveFile(QString filename)
{
    QList<VView*> views = ui->gphWindow->getViews();

    QJsonObject mainObj;
    QJsonArray objArray;
    for (QList<VView*>::iterator it = views.begin(); it != views.end(); it++)
    {
        VView* v = *it;
        MapObj* obj  = v->getMapObj();
        QPointF pnt = v->pos();

        QMap<QString, QVariant> a = obj->getRep();
        QJsonObject b;
        for (QMap<QString, QVariant>::iterator it2 = a.begin(); it2 != a.end(); it2++)
        {
            QVariant v = it2.value();
            QJsonValue itVal;

            switch (v.type())
            {
                case QVariant::String:
                {
                    itVal = QJsonValue(v.toString());
                    break;
                }
                case QVariant::Int:
                {
                    itVal = QJsonValue(v.toInt());
                    break;
                }
                case QVariant::Double:
                {
                    itVal = QJsonValue(v.toDouble());
                    break;
                }
                case QVariant::Size:
                {
                    QJsonArray arr;
                    QSize siz = v.toSize();
                    arr.append(siz.width());
                    arr.append(siz.height());
                    itVal = QJsonValue(arr);
                    break;
                }
                default:
                {
                    itVal = QJsonValue();
                    break;
                }
            }

            b.insert(it2.key(), itVal);
        }
        QJsonArray pntval;
        pntval.append(QJsonValue(pnt.x()));
        pntval.append(QJsonValue(pnt.y()));
        b.insert("Map_Point", pntval);
        b.insert("Map_ID", QJsonValue(obj->getId()));
        objArray.append(b);
    }

    mainObj.insert("Objects", QJsonValue(objArray));

    QVector<connectionOut> conns = map->getConnections();
    QJsonArray connectArray;
    for (int i = 0; i < conns.size(); i++)
    {
        QJsonObject connObj;
        connObj.insert("Type1", QJsonValue(conns[i].type1));
        connObj.insert("id1", QJsonValue(conns[i].id1));
        connObj.insert("item1", QJsonValue(conns[i].item1));
        connObj.insert("Type2", QJsonValue(conns[i].type2));
        connObj.insert("id2", QJsonValue(conns[i].id2));
        connObj.insert("item2", QJsonValue(conns[i].item2));
        connectArray.append(QJsonValue(connObj));
    }

    mainObj.insert("Connections", QJsonValue(connectArray));

    QJsonDocument doc;
    doc.setObject(mainObj);

    QFile s(filename);
    s.open(QFile::WriteOnly);
    s.write(doc.toJson());
    s.close();

}

/*****************************************************************************
 *
 *****************************************************************************/
void MainWindow::loadFile(QString filename)
{
    QFile fil(filename);
    fil.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray a = fil.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(a);

    QJsonObject main = doc.object();
    QJsonValue objs = main.value("Objects");
    QJsonArray arr = objs.toArray();
    ui->gphWindow->clearScene();

    for (int i = 0; i < arr.size(); i++)
    {
        QJsonObject o = arr.at(i).toObject();
        QJsonValue mapid = o.value("Map_ID");
        QJsonValue point = o.value("Map_Point");
        QJsonValue name = o.value("Name");
        QVariantMap map = o.toVariantMap();
        QMap<QString, QVariant> var = map;

        QJsonArray pntArray = point.toArray();
        QJsonValue pntValX = pntArray.at(0);
        QJsonValue pntValY = pntArray.at(1);

        QPointF pnt(pntValX.toDouble(), pntValY.toDouble());

        ui->gphWindow->addObject(name.toString(), pnt, mapid.toInt(), var);
    }


    QJsonValue conns = main.value("Connections");
    QJsonArray connsarr = conns.toArray();

    for (int i = 0; i < connsarr.size(); i++)
    {
        connectionOut c;
        QJsonObject o = connsarr.at(i).toObject();

        c.id1 = o.value("id1").toInt();
        c.id2 = o.value("id2").toInt();
        c.item1 = o.value("item1").toInt();
        c.item2 = o.value("item2").toInt();
        c.type1 = o.value("Type1").toInt();
        c.type2 = o.value("Type2").toInt();
        ui->gphWindow->addConnection(c);
    }

    update();

}

/*****************************************************************************
 *
 *****************************************************************************/
void MainWindow::on_hslPlay_sliderMoved(int position)
{
    ui->lblFrames->setText(QString::number(position) + "/" + QString::number(map->getMaxFrames()));
}

/*****************************************************************************
 *
 *****************************************************************************/
void MainWindow::on_hslPlay_sliderReleased()
{
    int position = ui->hslPlay->value();
    ui->lblFrames->setText(QString::number(position) + "/" + QString::number(map->getMaxFrames()));
    map->setFrame(position);
}

/*****************************************************************************
 *
 *****************************************************************************/
void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName();
    if (file != "")
    {
        loadFile(file);
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void MainWindow::on_actionSave_triggered()
{
    QString file = QFileDialog::getSaveFileName();
    if (file != "")
    {
        saveFile(file);
    }
}
