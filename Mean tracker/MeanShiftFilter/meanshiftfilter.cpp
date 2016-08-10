#include "meanshiftfilter.h"
#include <cmath>

#include <QDebug>

MeanShiftFilter::MeanShiftFilter()
{
    mSpatialRadius = 10;
    mRangeRadius = 10;
    mShiftDelta = 3.0;
}

IplImage * MeanShiftFilter::filter(const IplImage* img, int iterationNum)
{
    IplImage * imgLuv = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
    cvCvtColor(img, imgLuv, CV_RGB2Luv);

    int percent_cnt = 0;
    for(int j=0;j<img->height;j++)
    {
        for(int i=0;i<img->width;i++)
        {
            vector<float> luv = readImgLuv(imgLuv, i, j);

            int ic = i;
            int jc = j;
            int ic_prev = 0, jc_prev = 0;
            float L_prev = 0.0, U_prev = 0.0, V_prev = 0.0;

            double shift = 100.0;
            for(int k=0; shift > mShiftDelta && k < iterationNum; k++)
            {
                ic_prev = ic;
                jc_prev = jc;
                L_prev = luv[0];
                U_prev = luv[1];
                V_prev = luv[2];

                float mi = 0;
                float mj = 0;
                float mL = 0;
                float mU = 0;
                float mV = 0;
                int num=0;

                int m_from = max(0, i-mSpatialRadius), m_to = min(img->width, i+mSpatialRadius);
                int n_from = max(0, j-mSpatialRadius), n_to = min(img->height, j+mSpatialRadius);

                for(int m=m_from; m<m_to; m++)
                {
                    for(int n=n_from; n<n_to; n++)
                    {
                        vector<float> luv_local = readImgLuv(imgLuv, m, n);

                        double dL = luv_local[0] - luv[0];
                        double dU = luv_local[1] - luv[1];
                        double dV = luv_local[2] - luv[2];
                        if( dL*dL+dU*dU+dV*dV <= mRangeRadius*mRangeRadius)
                        {
                            mi += m;
                            mj += n;
                            mL += luv_local[0];
                            mU += luv_local[1];
                            mV += luv_local[2];
                            num++;
                        }
                    }
                }
                luv[0] = mL / (float)num;
                luv[1] = mU / (float)num;
                luv[2] = mV / (float)num;

                ic = (int)(mi*num+0.5);
                jc = (int)(mj*num+0.5);
                int di = ic - ic_prev;
                int dj = jc - jc_prev;
                double dL = luv[0] - L_prev;
                double dU = luv[1] - U_prev;
                double dV = luv[2] - V_prev;

                shift = di*di+dj*dj+dL*dL+dU*dU+dV*dV;

            }

            writeImgLuv(imgLuv, i, j, luv);

            int new_percent_cnt = (int)(100.0*(i+j*img->width)/(img->width*img->height));
            if (new_percent_cnt > percent_cnt)
            {
                percent_cnt = new_percent_cnt;
                qDebug() << percent_cnt << "%";
            }
        }
    }


    IplImage * filteredImg = cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
    cvCvtColor(imgLuv, filteredImg, CV_Luv2RGB);
    return filteredImg;
}

//http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html
vector<float> MeanShiftFilter::readImgLuv(const IplImage* img, int i, int j)
{
    vector<float> luv;
    float L = (float)((uchar *)(img->imageData + j*img->widthStep))[i*img->nChannels + 0];
    float U = (float)((uchar *)(img->imageData + j*img->widthStep))[i*img->nChannels + 1];
    float V = (float)((uchar *)(img->imageData + j*img->widthStep))[i*img->nChannels + 2];

    luv.push_back( 100*L/255 );
    luv.push_back( 354*U/255 - 134 );
    luv.push_back( 256*V/255 - 140 );

    return luv;
}

bool MeanShiftFilter::writeImgLuv(const IplImage* img, int i, int j, vector<float> luv)
{
    if(img==NULL)
    {
        return false;
    }

    float L = 255*luv[0]/100;
    float U = 255*(luv[1]+134)/354;
    float V = 255*(luv[2]+140)/256;

    ((uchar *)(img->imageData + j*img->widthStep))[i*img->nChannels + 0] = (uchar)L;
    ((uchar *)(img->imageData + j*img->widthStep))[i*img->nChannels + 1] = (uchar)U;
    ((uchar *)(img->imageData + j*img->widthStep))[i*img->nChannels + 2] = (uchar)V;

    return true;
}
