Mat cameraMatrixL;
Mat distCoeffsL;
Mat cameraMatrixR;
Mat distCoeffsR;
Mat F, R, T, E;
Mat R1, R2, P1, P2, Q;

#include <cmath>
using namespace std;

#define linearEstimationOfX
//#define linearEstimationOfY

void setupParams()
{
	FileStorage fsL("C:\\Projects\\TennisBall 1\\x64\\intrinsicAndDistortionL.yml", FileStorage::READ);

	fsL["camera_matrix"] >> cameraMatrixL;
	fsL["distortion_coefficients"] >> distCoeffsL;
	fsL.release();
	FileStorage fsR("C:\\Projects\\TennisBall 1\\x64\\intrinsicAndDistortionR.yml", FileStorage::READ);

	fsR["camera_matrix"] >> cameraMatrixR;
	fsR["distortion_coefficients"] >> distCoeffsR;
	fsR.release();

	FileStorage fsS("C:\\Projects\\TennisBall 1\\x64\\stereoCalibration.yml", FileStorage::READ);
	fsS["f"] >> F;
	fsS["r"] >> R;
	fsS["t"] >> T;
	fsS["e"] >> E;
	fsS.release();

	FileStorage fsRec("C:\\Projects\\TennisBall 1\\x64\\stereoRectify.yml", FileStorage::READ);
	fsRec["r1"] >> R1;
	fsRec["r2"] >> R2;
	fsRec["p1"] >> P1;
	fsRec["p2"] >> P2;
	fsRec["q"] >> Q;
	fsRec.release();
}

Point3f findCoordinate(Mat &left, Mat &right)
{

	int xL = 265;
	int yL = 40; 
	int xWidthL = 150;
	int yWidthL = 115;
	Rect recL(xL, yL, xWidthL, yWidthL);
	Mat cloneL = left.clone();
	Mat frameL = left(recL);

	//cvWaitKey();

	int xR = 215;
	int yR = 30;
	int xWidthR = 150;
	int yWidthR = 115;
	Rect recR(xR, yR, xWidthR, yWidthR);
	Mat cloneR = right.clone();
	Mat frameR = right(recR);

	//cvWaitKey();

	//vector<Point2f> cornersL;
	int mthresh = 75;
	
	for (int k = 0; k < frameL.rows; k++){
		for (int j = 0; j < frameL.cols; j++){
			if (frameL.at<unsigned char>(k, j) > mthresh)
			{
				frameL.at<unsigned char>(k, j) = 255;
			}
			else
			{
				frameL.at<unsigned char>(k, j) = 0;
			}
			unsigned int r = (unsigned int)frameL.at<unsigned char>(k, j);
			//if (r < 100)
				//cout << "  ";
			//cout << r << " ";

		}
		//cout << "\n";
	}
	for (int k = 0; k < frameR.rows; k++){
		for (int j = 0; j < frameR.cols; j++){
			if (frameR.at<unsigned char>(k, j) > mthresh)
			{
				frameR.at<unsigned char>(k, j) = 255;
			}
			else
			{
				frameR.at<unsigned char>(k, j) = 0;
			}
			unsigned int r = (unsigned int)frameR.at<unsigned char>(k, j);
			//if (r < 100)
			//	cout << "  ";
			//cout << r << " ";

		}
		//cout << "\n";
	}

	// -----------Calculate the Center of Mass of the m on the M & M -----------------------
	int x_moment = 0;
	int x_area = 0;
	int y_moment = 0;
	int y_area = 0;

	for (int row = 0; row < frameL.rows; row++)
	{
		for (int column = 0; column < frameL.cols; column++)
		{
			if (frameL.at<unsigned char>(row, column) > mthresh)
			{
				x_moment += column;
				x_area++;
				y_moment += row;
				y_area++;
			}
		}
	}

	if (y_area <= 0)
		return Point3f(0,0,0);

	int y_cm = y_moment / y_area;
	int x_cm = x_moment / x_area;
	cvtColor(frameL, frameL, CV_GRAY2BGR);
	cvtColor(cloneL, cloneL, CV_GRAY2BGR);
	Point m_center(x_cm, y_cm);
	//center of mass
	circle(frameL, m_center, 3, Scalar(0, 255, 0), -1, 8, 0);

	int centerLx = x_cm + xL;
	int centerLy = y_cm + yL;
	Point centerL(centerLx, centerLy);
	std::cerr << "xcm+xl=" << centerLx << " y_cm+yL=" << centerLy << "\n";
	std::cerr << "centerl=" << centerL.x << "," << centerL.y << "\n";
	circle(cloneL, centerL, 3, Scalar(0, 255, 0), -1, 8, 0);


	// -----------Calculate the Center of Mass of the m on the M & M -----------------------
	x_moment = 0;
	x_area = 0;
	y_moment = 0;
	y_area = 0;

	for (int row = 0; row < frameR.rows; row++)
	{
		for (int column = 0; column < frameR.cols; column++)
		{
			if (frameR.at<unsigned char>(row, column) > mthresh)
			{
				x_moment += column;
				x_area++;
				y_moment += row;
				y_area++;
			}
		}
	}

	if (y_area <= 0)
		return Point3f(0,0,0);

	y_cm = y_moment / y_area;
	x_cm = x_moment / x_area;
	cvtColor(frameR, frameR, CV_GRAY2BGR);
	cvtColor(cloneR, cloneR, CV_GRAY2BGR);
	Point m_center1(x_cm, y_cm);
	Point centerR(x_cm + xR , y_cm + yR );
	//center of mass
	circle(frameR, m_center1, 3, Scalar(0, 255, 0), -1, 8, 0);
	circle(cloneR, centerR, 3, Scalar(0, 255, 0), -1, 8, 0);

	/*
	imshow("Ashcraft", frameL);
	cvWaitKey();
	imshow("Ashcraft", frameR);
	cvWaitKey();
	imshow("Ashcraft", cloneL);
	cvWaitKey();
	imshow("Ashcraft", cloneR);
	cvWaitKey();
	*/

	vector<Point2f> pointsL;
	pointsL.push_back(centerL);
	vector<Point2f> pointsR;
	pointsR.push_back(centerR);
	vector<Point2f> undistPointsL, undistPointsR;
	undistortPoints(pointsL, undistPointsL, cameraMatrixL, distCoeffsL, R1, P1);
	undistortPoints(pointsR, undistPointsR, cameraMatrixR, distCoeffsR, R2, P2);

	vector<Point3f> newPointsL;
	vector<Point3f> newPointsR;
	int disparity = undistPointsL.at(0).x - undistPointsR.at(0).x;
	newPointsL.push_back(Point3f(undistPointsL.at(0).x, undistPointsL.at(0).y, disparity));
	newPointsR.push_back(Point3f(undistPointsR.at(0).x, undistPointsR.at(0).y, disparity));
	
	vector<Point3f> newUndistPointsL;
	vector<Point3f> newUndistPointsR;

	perspectiveTransform(newPointsL, newUndistPointsL, Q);
	perspectiveTransform(newPointsR, newUndistPointsR, Q);
	//ofstream fout("xyzPoints.txt", ios::app);
	Point3f out;
	out.x = newUndistPointsL.at(0).x;
	out.y =  newUndistPointsL.at(0).y;
	out.z = newUndistPointsL.at(0).z;
	//fout << "Left (x,y,z) " << newUndistPointsL.at(0).x << ", " << newUndistPointsL.at(0).y << ", " << newUndistPointsL.at(0).z << "\n";
	//fout << "Right (x,y,z) " << newUndistPointsR.at(0).x << ", " << newUndistPointsR.at(0).y << ", " << newUndistPointsR.at(0).z << "\n\n";
	//fout.close();
	//imshow("Ashcraft", tmpL);
	return out;
}


Point2f catchPosition(Point3f coordinate, bool clearvals)
{
	float x = coordinate.x;
	float y = coordinate.y;
	float z = coordinate.z;

	// Declarations and Initializations
	static float s0=0,	 s1=0,	 s2=0,	 s3=0,	 s4=0;
	static float p11=0,	p21=0,	p31=0;
	static float q11=0,	q21=0,	q31=0;

	float c11=0, c12=0,	c13=0;
	float d=1;
	float xa=0,	  ya=0;

	// Clear the running sum variables if indicated that a new pitch is happening
	if (clearvals)
	{
		s0=0;   s1=0;	 s2=0;	 s3=0;	 s4=0;
		p11=0;	p21=0;	p31=0;
		q11=0;	q21=0;	q31=0;
	}

	// s_i = sum_{i=1}^n z_i^j
	s0+=1;		s1+=z;			s2+=z*z;		s3+=z*z*z;		s4+=z*z*z*z;
	// p_ij = element of A^T*x, where x is the n by 1 matrix of x coordinates (where A is n by 3)
	p11+=x;		p21+=z*x;		p31+=z*z*x;
	// q_ij = element of A^T*y, where y is the n by 1 matrix of y coordinates (where A is n by 3)
	q11+=y;		q21+=z*y;		q31+=z*z*y;
	if (s0 > 1) {
		// c_ij = cofactor of A^T*A, where A is the n by 3 Vandermode Matrix parameterized by z;
		c11=s2*s4-s3*s3;		c12=-(s1*s4-s2*s3);		c13=s1*s3-s2*s2;
		// d = det(A^T*A), where A is the n by 3 Vandermode Matrix parameterized by z;
		d = s0*c11+s1*c12+s2*c13;
		// xa and ya are the x and y coordinates when z=0.
		#ifdef linearEstimationOfX
			xa=(s2*p11-s1*p21)/(s2*s0-s1*s1); // linear		
		#else 
			xa=(c11*p11+c12*p21+c13*p31)/d;	// quadratic
		#endif
		if (s0 > 5)	
		#ifdef linearEstimationOfY
			ya=(s2*q11-s1*q21)/(s2*s0-s1*s1); // linear		
		#else 
			ya=(c11*q11+c12*q21+c13*q31)/d;	// quadratic
		#endif
		
			
	}

	if (cvIsNaN(xa))
		xa = 0;
	if (cvIsNaN(ya))
		ya = 0;

	// Output xa and ya.
	Point2f out(xa,ya);
	return out;

}
