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

        /*cout << "Cam matrix:" << endl;
        for(int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 3; x++)
            {
                cout << (double)info.cammatrix.at<double>(y,x) << " ";
            }
            cout << endl;
        }

        cout << "Distortion" << endl;
        for (int y = 0; y < 5; y++)
        {
            cout << (double)info.distortion.at<double>(y,0) << " ";
        }
        cout.flush();*/

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

    QVector<Mat> ans;

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
    QVector<Mat> ans;

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

Mat videoreader::getCamMatrix(int id)
{
    return vidinfo[id].cammatrix;
}

Mat videoreader::getDistortion(int id)
{
    return vidinfo[id].distortion;
}
