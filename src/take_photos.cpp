#include<opencv2/opencv.hpp>
#include<string>
using namespace std;
using namespace cv;

#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

int main()
{	
	CascadeClassifier cascade;
	cascade.load("lbpcascade_frontalface.xml");
	VideoCapture cap;
	cap.open(0);
	Mat frame;
	int pic_num = 1;
	while (1)
	{		
		cap >> frame;
		
		std::vector<Rect> faces;
		Mat frame_gray;
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);

		cascade.detectMultiScale(frame_gray, faces, 1.1, 4, 0, Size(100, 100), Size(500, 500));
		
		for (size_t i = 0; i < faces.size(); i++)
		{
			rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);
		}
		
		if (faces.size() == 1)
		{
			Mat faceROI = frame_gray(faces[0]);
			Mat myFace;
			resize(faceROI, myFace, Size(92, 112));
			//putText(frame, patch::to_string(pic_num), faces[0].tl(),3, 1.2, (0, 0, 255), 2, LINE_AA);
			
			string filename = format("./pic/pic1_%d.jpg", pic_num);
			imwrite(filename, myFace);
			imshow(filename, myFace);
			waitKey(500);
			destroyWindow(filename);
			pic_num++;
			if (pic_num == 11)
			{				
				return 0;
			}
		}
		imshow("frame", frame);
		waitKey(100);
	}
	return 0;
}
