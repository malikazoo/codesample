#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
using namespace std;

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
using namespace cv;


int widthpoints = 8;
int heightpoints = 10;


vector<Point3f> buildObjectPoints(int width, int height)
{
    vector<Point3f> outpoints;
    for (int j = 0; j < height; j++)
    {
        for (int k = 0; k < width; k++)
        {
            outpoints.push_back(Point3f(k*2.0, j*2.0, 0));
        }
    }

    return outpoints;
}

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int main()
{

    namedWindow("Price", CV_WINDOW_AUTOSIZE);

    vector<vector<Point2f> > imagepoints;
    vector<vector<Point3f> > objectpoints;

    Size boardSize(widthpoints,heightpoints);
    Size imageSize(850,480);

    cerr << "Creating picture points..." << endl;

    string nameEnd = ".png";

    string dir = "/home/tim/svn/computervision2/Run1/cam5/calibration/";

    vector<string> files;

    getdir(dir, files);


    for (int i = 0; i < files.size(); i++)
    {

        cerr << "pic: " << i << "\r";

        string fn = files[i];
        cerr << "File: " << fn << endl;
        if (fn.size() < 4 || fn.substr(fn.size()-4) != string(".png"))
            continue;

        fn = dir + string("/") + fn;

        cerr << fn << endl;

        Mat pic = imread(fn, CV_LOAD_IMAGE_GRAYSCALE);

        cerr << pic.rows << " " << pic.cols << endl;

        //cvtColor(pic,pic,CV_BGR2GRAY);

        /*
        for (int y = 0; y < 30; y++)
        {
            for (int x = 0; x < 30; x++)
            {
                pic.at<unsigned char>(y,x) = 128;
            }
        }*/

        //cvtColor(pic,pic,CV_BGR2GRAY);
        vector<Point2f> corners;

        findChessboardCorners(pic, boardSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH + CV_CALIB_CB_NORMALIZE_IMAGE + CV_CALIB_CB_FILTER_QUADS);

        if (corners.size() == 0)
            continue;

        cornerSubPix (pic, corners, cvSize(7,7), cvSize(-1, -1), cvTermCriteria (TermCriteria::COUNT + TermCriteria::EPS, 30, 1e-6));


        cvtColor(pic,pic,CV_GRAY2BGR);

        bool patternfound = true;
        drawChessboardCorners(pic,boardSize,corners,patternfound);

        Mat rs;
        resize(pic,rs,Size(pic.cols/3,pic.rows/3));

        imshow("Price",rs);
        int ar = waitKey();

        vector<Point2f> ncorners;
        if (ar == 'z')
        {
            //Reverse values
            for (int i = corners.size()-1; i >=0; i--)
            {
                ncorners.push_back(corners[i]);
            }
        }
        else
            ncorners = corners;

        if (ar != 'x')
        {
            imagepoints.push_back(ncorners);
            objectpoints.push_back(buildObjectPoints(widthpoints,heightpoints));
            cerr << "Image added" << endl;
        }

    }
    cerr << endl;
    cerr << "done" << endl;

    vector<Mat> rVectors;
    vector<Mat> tVectors;

    Mat distortion;
    Mat cameraMatrix;

    cerr << "Calibrating...";
    double rms = calibrateCamera(objectpoints, imagepoints, imageSize, cameraMatrix, distortion,
                                 rVectors, tVectors);
    cerr << "done" << endl;

    cout << "RMS: " << rms << endl;
    cout << "Camera matrix: " << endl << cameraMatrix << endl;
    cout << "Distortion _coefficients: " << distortion << endl;

    FileStorage outfile("catcherparamr.xml", FileStorage::WRITE);
    outfile << "rms" << rms;
    outfile << "cameramatrix" << cameraMatrix;
    outfile << "distortion" << distortion;

    outfile.release();

    return 0;
}

