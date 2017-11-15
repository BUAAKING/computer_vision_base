#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;

using namespace cv;


int main()
{
Mat src;
src=imread("108.jpg");
//namedWindow("src_image");
//imshow("src_image",src);
//waitKey(0);
int w,h;
h=src.rows;
w=src.cols;

Mat samples(w*h,1,CV_32FC3);
Mat labels(w*h,1,CV_32FC1);
int k=0;
for(int i=0;i<h;i++)
{
	uchar* data=src.ptr<uchar>(i);
		for(int j=0;j<w;j++)
		{
			samples.at<Vec3f>(k,0)[0]=float(data[j*3]);
			samples.at<Vec3f>(k,0)[1]=float(data[j*3+1]);
		    samples.at<Vec3f>(k,0)[2]=float(data[j*3+2]);
		k++;
		}

}
int clusterCount=3;
Mat centers(clusterCount,1,samples.type());
kmeans(samples,clusterCount,labels,TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,10,1.0),3,KMEANS_PP_CENTERS,centers);

Mat dst_img(src.rows,src.cols,CV_8UC1);
float step=255/(clusterCount-1);
k=0;
for(int i=0;i<src.rows;i++)
{
	uchar *data1=dst_img.ptr<uchar>(i);
	for(int j=0;j<dst_img.cols;j++)
	{
	int tt= labels.at<int>(k,0);
	k++;
	data1[j]=255-tt*step;
	
	}



}
namedWindow("[dst_image]");
imshow("[dst_image]",dst_img);

while((char(waitKey(1))!='q'))
{};
return 0;
}