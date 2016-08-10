#include "videoreader.h"

/*****************************************************************************
 *
 *****************************************************************************/
videoreader::videoreader()
{
    isopen = false;
}

/*****************************************************************************
 * Reads in the file, parses the data and sticks it in the video objects.
 *****************************************************************************/
void videoreader::readFile(QString location)
{
    QFile fil(location);
    fil.open(QIODevice::ReadOnly);

    QJsonDocument jsondoc = QJsonDocument::fromJson(fil.readAll());
    QJsonObject object = jsondoc.object();

    QJsonArray array = object["files"].toArray();

    qDebug() << "Array Size: " << array.size();
    for (int i = 0; i < array.size(); i++)
    {
        QJsonObject obj = array[i].toObject();
        QJsonValue firstframe = obj.value("firstframe");
        QJsonValue id = obj.value("id");
        QJsonValue location = obj.value("location");

        QJsonValue rms = obj.value("RMS");
        QJsonValue camMatrix = obj.value("CameraMatrix");
        QJsonValue distortion = obj.value("Distortion");

        QJsonValue rotation = obj.value("rotation");
        QJsonValue translation = obj.value("translation");
        QJsonValue essential = obj.value("essential");
        QJsonValue fundamental = obj.value("fundamental");

        QJsonArray camArray = camMatrix.toArray();
        QJsonArray distArray = distortion.toArray();

        videoinfo info;
        info.firstframe = firstframe.toInt();
        info.id = id.toInt();
        info.location = location.toString();
        info.rms = rms.toDouble();

        Mat camMat = Mat(3,3,CV_64FC1);
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                double camMatVal = camArray[3*j+k].toDouble();
                camMat.at<double>(j,k) = camMatVal;
            }
        }

        Mat dist = Mat(5,1,CV_64FC1);

        info.cammatrix = camMat;

        for (int j = 0; j < distArray.size(); j++)
        {
            double camDistVal = distArray[j].toDouble();
            dist.at<double>(j,0) = camDistVal;
        }

        info.distortion = dist;


        Mat rot = Mat(3,3,CV_64FC1);
        Mat trans = Mat(3,1,CV_64FC1);
        Mat ess = Mat(3,3,CV_64FC1);
        Mat fund = Mat(3,3,CV_64FC1);

        QJsonArray rotArray = rotation.toArray();
        QJsonArray transArray = translation.toArray();
        QJsonArray essArray = essential.toArray();
        QJsonArray fundArray = fundamental.toArray();

        for (int j = 0; j < transArray.size(); j++)
        {
            double camDistVal = transArray[j].toDouble();
            trans.at<double>(j,0) = camDistVal;
        }

        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                double camMatVal = rotArray[3*j+k].toDouble();
                rot.at<double>(j,k) = camMatVal;
            }
        }

        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                double camMatVal = essArray[3*j+k].toDouble();
                ess.at<double>(j,k) = camMatVal;
            }
        }

        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                double camMatVal = fundArray[3*j+k].toDouble();
                fund.at<double>(j,k) = camMatVal;
            }
        }


        vidinfo[i] = info;
    }

}

/*****************************************************************************
 * Retrieves the first frame in all of the videos (The first frame indicated
 * in the JSON file)
 *****************************************************************************/
QVector<Mat> videoreader::firstframe()
{
    if (isopen)
    {
        for (int i = 0; i < 4; i++)
        {
            vid[i].release();
        }
    }

    ans.clear();

    //Go through each video and grab the correct frame
    for (int i = 0; i < 4; i++)
    {
        vid[i].open(vidinfo[i].location.toStdString());

        //qDebug() << "Firstframe " << i << ": " << vidinfo[i].firstframe;

        //Move to the frame before the first one
        for (int j = 0; j < vidinfo[i].firstframe-1; j++)
        {
            vid[i].grab();
        }

        //Grab the first frame and put it into the vector
        Mat a;
        vid[i] >> a;
        //Distortion a
        Mat b;
        undistort(a, b, vidinfo[i].cammatrix, vidinfo[i].distortion);
        ans.push_back(b);

        isopen = true;
    }

    width = 0;
    height = 0;

    //Figure out the largest height and width of all the images
    for (int i = 0; i < 4; i++)
    {
        if (ans[i].cols > width)
            width = ans[i].cols;
        if (ans[i].rows > height)
            height = ans[i].rows;
    }

    //Return the first frame for each video
    return ans;

}

/*****************************************************************************
 * Retrieves the frame after the last one was displayed in all of the videos
 *****************************************************************************/
QVector<Mat> videoreader::nextframe()
{
    ans.clear();

    if (isopen)
    {
        for (int i = 0; i < 4; i++)
        {
            Mat a;
            vid[i] >> a;
            Mat b;
            undistort(a, b, vidinfo[i].cammatrix, vidinfo[i].distortion);
            ans.push_back(b);
        }
    }

    return ans;
}

/*****************************************************************************
 * Returns the width of the largest item
 *****************************************************************************/
int videoreader::getWidth()
{
    return width;
}

/*****************************************************************************
 * Returns the height of the largest item
 *****************************************************************************/
int videoreader::getHeight()
{
    return height;
}

Mat videoreader::getFundamental(int id)
{
    return vidinfo[id].fundamental;
}

Mat videoreader::getEssential(int id)
{
    return vidinfo[id].essential;
}

Mat videoreader::getRotation(int id)
{
    return vidinfo[id].rotation;
}

Mat videoreader::getTranslation(int id)
{
    return vidinfo[id].translation;
}

QVector<Mat> videoreader::rectify()
{
    QVector<Mat> newans;
    newans.push_back(ans[0]);

    Size imageSize(850,480);
    Size boardSize(10,13);

    for (int i = 1; i < 2; i++)
    {

        Mat lFixed;
        Mat rFixed;

        lFixed = ans[0].clone();
        rFixed = ans[i].clone();

        Mat r1;
        Mat r2;
        Mat p1;
        Mat p2;
        Mat q;

        stereoRectify(vidinfo[0].cammatrix,vidinfo[0].distortion,vidinfo[i].cammatrix,vidinfo[i].distortion,boardSize,vidinfo[i].rotation,vidinfo[i].translation,r1,r2,p1,p2,q);

        Mat loutmap1;
        Mat loutmap2;
        Mat routmap1;
        Mat routmap2;

        initUndistortRectifyMap(vidinfo[0].cammatrix,vidinfo[0].distortion,r1,p1,imageSize,CV_32F,loutmap1,loutmap2);
        initUndistortRectifyMap(vidinfo[i].cammatrix,vidinfo[i].distortion,r2,p2,imageSize,CV_32F,routmap1,routmap2);

        remap(lFixed,lFixed,loutmap1,loutmap2,INTER_LINEAR);
        remap(rFixed,rFixed,routmap1,routmap2,INTER_LINEAR);

        imshow("LFixed",lFixed);
        imshow("rFixed",rFixed);
        cvWaitKey();
    }

    return newans;

}

