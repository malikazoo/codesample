#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"

//#include <QtCore/QCoreApplication>
#include <QtDebug>
#include "meanshiftfilter.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    if (argc < 2)
    {
        qDebug() << "No file";
    }

    QString filename = QString::fromStdString(argv[1]);

    qDebug() << filename;

    //return a.exec();
    IplImage *img = cvLoadImage(filename.toStdString().c_str());

    // Mean shift filter
    MeanShiftFilter * msf = new MeanShiftFilter();
    IplImage *img_filtered = msf->filter(img);

    cvNamedWindow("Mean Shift Filter",CV_WINDOW_AUTOSIZE);
    cvShowImage("Mean Shift Filter",img_filtered);

    QString output_filename = filename + "-filtered.png";
    cvSaveImage(output_filename.toStdString().c_str(), img_filtered);

    cvWaitKey();
    cvDestroyWindow("Mean Shift Filter");
    cvReleaseImage(&img_filtered);
    cvReleaseImage(&img);

    //return a.exec();
    return 0;
}
