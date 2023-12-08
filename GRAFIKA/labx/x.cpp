
#include <stdio.h>
using namespace std;

#include <iostream>

// OpenCV includes
#include <opencv2/opencv.hpp>
using namespace cv;

Mat srcImage; // input (source) image

void CreateWindow(const char* name, int x, int y) {
	namedWindow(name, WINDOW_AUTOSIZE);
	moveWindow(name,x,y);
}

void ShowImage(Mat img, const char* name, int x, int y) {
	CreateWindow(name, x, y);
	imshow(name, img);
}

Mat greyImage;

// timestamp 1

void Brightness(Mat src, Mat dst, int B) {
	for (int i = 0; i < src.cols; i++) {
		for (int j = 0; j < src.rows; j++) {
			Vec3b pixelColor;
			pixelColor = src.at<Vec3b>(i, j);

			for (int a = 0; a < 3; a++) {

				if (pixelColor[a] + B < 255) 
				{
					pixelColor[a] += B;
				} 
				else
				{
					pixelColor[a] = 255;
				}
					

			}
			dst.at<Vec3b>(i, j) = pixelColor;
		}
	}

	
}
// timestamp2

int threshold_value = 100;
const int max_value = 255;

Mat binarizedImage;

void Threshold(int pos, void* userdata) {
	threshold(greyImage, binarizedImage, threshold_value, max_value, THRESH_BINARY);

	imshow("Binarization", binarizedImage);
}
//timestamp 3

// timestamp 4



void DrawHistogramAt(Mat src, const char* name, int x, int y) {

	const int histSize = 256;
	const int hist_w = 256;
	const int hist_h = 256;
	float range[2] = { 0, 256 };
	const float* histRange{ range };

	Mat histogram;
	calcHist(&src, 1, 0, Mat(), histogram,1, &histSize, &histRange);
	normalize(histogram, histogram, range[0], range[1],NORM_MINMAX);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	for (int i = 1; i < histSize; i++) 
	{
		int value = cvRound(histogram.at<float>(i));
		line(histImage, Point(i, hist_h), Point(i, hist_h - value), Scalar(255, 255, 0), 1);

	}
	ShowImage(histImage,name, x, y);
}


int main()
{
	// reading source file srcImage
	srcImage = imread( "Samples/Fish.jpg" );
	if ( !srcImage.data )
	{
		cout << "Error! Cannot read source file. Press ENTER.";
		waitKey(); // wait for a key press
		return( -1 );
	}
	cvtColor(srcImage, greyImage, COLOR_BGR2GRAY);

	ShowImage(srcImage,"Damian Petta", 0,0);

	ShowImage(greyImage, "Grey image", 300, 0);

	imwrite("Samples/Grey image.jpg", greyImage);

	Mat resizedImage(200, 200, srcImage.type());

	resize(srcImage, resizedImage, resizedImage.size());

	ShowImage(resizedImage, "Resized image", 600, 0);
	Mat blurImage;

	blur(srcImage, blurImage, Size(5,5) );

	ShowImage(blurImage, "Blured image", 900, 0);

	Mat CannyImage;

	Canny(srcImage, CannyImage, 120, 28);

	ShowImage(CannyImage, "Canny edges", 1200, 0);

	Mat LaplacianImage;

	Laplacian(greyImage, LaplacianImage, CV_16S, 3);
	Mat scaledLaplacianImage;

	convertScaleAbs(LaplacianImage, scaledLaplacianImage);

	ShowImage(scaledLaplacianImage, "Laplacian Image", 1500, 0);

	Mat dilatedImage, erodedImage;

	int iterations = 2;
	Mat element = getStructuringElement(MORPH_RECT, Size(iterations * 2 + 1, iterations * 2 + 1),
		Point(iterations, iterations));

	dilate(CannyImage, dilatedImage, element);
	ShowImage(dilatedImage, "Dilated Image", 1200, 300);

	erode(dilatedImage, erodedImage, element);

	ShowImage(erodedImage, "Eroded Image", 1500, 300);
	// timestamp 1

	Mat brightImage;
	srcImage.copyTo(brightImage);

	Brightness(brightImage, brightImage, 100);

	ShowImage(brightImage, "Bright Image", 0, 300);
	// timestamp 2


	CreateWindow("Binarization", 300, 600);
	createTrackbar("Threshold value", "Binarization", &threshold_value,max_value, Threshold);
	Threshold(threshold_value, NULL);

	// timestamp 3
	CreateWindow("Src video", 600, 600);
	CreateWindow("Dst video", 1200, 600);
	Mat srcFrame, dstFrame;
	VideoCapture capture("Samples/Dino.avi");

	capture >> srcFrame;
	VideoWriter writer("Samples/Dino2.avi", -1, 25, srcFrame.size());

	int key = 2115;
	while (waitKey(25) != 27 && !srcFrame.empty()) {
		
		Canny(srcFrame, dstFrame, 15,200);
		writer << dstFrame;
		
			imshow("Src video", srcFrame);
			imshow("dst video", dstFrame);
			capture >> srcFrame;
	}
	// timestamp 4

	DrawHistogramAt(greyImage, "Gray image histogram", 300, 300);
	

	Mat equalizedImage; 
	equalizeHist(greyImage, equalizedImage);

	DrawHistogramAt(equalizedImage, "Equalized image histogram Image", 900, 300);
	ShowImage(equalizedImage, "Histogram Equalized", 900, 300);
	//timestamp 5

	Mat testImage;


	waitKey();
}
