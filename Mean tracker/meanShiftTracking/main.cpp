#include <QApplication>
#include "interactivewindow.h"
#include <QDebug>

#define TEST_TARGET_DETECTOR

#ifdef TEST_TARGET_DETECTOR
    #include "targetdetectortester.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#ifdef TEST_TARGET_DETECTOR
    qDebug() << "Testing Target Detector ... ";
    const string ref_img_file("video-0.png");
    const string target_img_file("video-1.png");
    qDebug() << "Reference Img file is " << QString::fromStdString(ref_img_file);
    qDebug() << "Target Img file is " << QString::fromStdString(target_img_file);
    Rect ref_rect(155, 272, 90, 70);
    qDebug() << "Reference Rect is " << ref_rect.x << " " << ref_rect.y << " " << ref_rect.width << " " << ref_rect.height;

    TargetDetectorTester * pTester = new TargetDetectorTester();
    pTester->testTargetDetection(ref_img_file, ref_rect, target_img_file);
#else
    InteractiveWindow window;
    window.show();
#endif
    return app.exec();
}
