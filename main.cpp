#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<iostream>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include<string.h>
#include<fstream>
using namespace cv;
using namespace std;

CascadeClassifier car_cascade;
ofstream out;

/* Function Headers */
void detectAndDisplay( Mat image1, int index );


/* @function main */
int main( )
{
    Mat image1, image_truth, frame;
    namedWindow("result",2);

    out.open("foundLocations_Scale.txt");

    //-- 1. Load the cascades
    if( !car_cascade.load("D:/ToDo/research_santa_cruz/car_classifier/casscade5/cascade.xml"))// car_cascade_name ) )
    {
        printf("--(!)Error loading\n");
        return -1;
    }

    //-- 2. Read the input image (modify the address to load from your system)


    string address = "D:/ToDo/research_santa_cruz/car_classifier/CarData/TestImages_Scale/test-";
    string filename, cas, converted;
    string correctImage;
    string to = "D:/ToDo/research_santa_cruz/car_classifier/upload2/2_";

    string correct = "D:/ToDo/research_santa_cruz/car_classifier/CarData/LabeledImages/result-";
    //namedWindow("Truth",2);

    for(int i =0; i<108; i++)
    {
        cout<<i<<endl;
        ostringstream ss;
        ss<<i;
        //cout<<"address : "<<address<<endl;
        filename = address + ss.str() + ".pgm";
        correctImage = correct + ss.str() + ".pgm";
       // converted = to + ss.str() + ".jpg";


        //image_truth = imread(correctImage,1);
        //imshow("Truth", image_truth);
        //cout<<"filename : "<<filename<<endl;

        //{"taskID":"1","taskCount":0,"cost":"1.7","blocks":[[]],"type":"jpg"}
        //out<<"{\"taskID\":\"2\",\"taskCount\":"<<i<<",\"cost\":\"1.7\",\"blocks\"";
        out<<i<<":";

        image1 = imread(filename,1);
        //imwrite(converted,image1);
        detectAndDisplay( image1,i );
        //out<<",\"type\":\"jpg\"}\n";
        out<<"\n";

        int c = waitKey(0);
        if( (char)c == 27 )
        {
            destroyAllWindows();
            break;
        }

    }

    out.close();
    return 0;
}

/* @function detectAndDisplay */
void detectAndDisplay( Mat image1, int index=0 )
{

    std::vector<Rect> cars;

    car_cascade.detectMultiScale( image1, cars, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, Size(25, 10), Size(400,100) );
    cout<<"cars detected: "<<cars.size()<<endl;
    //out<<" "<<cars.size();
    //out<<"[";
    for( size_t i = 0; i < cars.size(); i++ )
    {
        //out<<"{\"taskID\":\"2\",\"taskCount\":"<<index<<",\"cost\":\"1.7\",\"blocks\"";
        rectangle(image1, cars[i].tl(),cars[i].br(), Scalar(255), 3, 8, 0);
        /* printing results in format for our HPU
        *out<<"["<<cars[i].y<<","<<cars[i].x<<","<<cars[i].width<<","<<cars[i].height<<"],\"type\":\"jpg\"}\n";
        *out<<"["<<cars[i].y<<","<<cars[i].x<<","<<cars[i].width<<","<<cars[i].height<<"]";//,\"type\":\"jpg\"}\n";
        */
        
        out<<" ("<<cars[i].y<<","<<cars[i].x<<","<<cars[i].width<<")";//for multi Scale
        //out<<" ("<<cars[i].y<<","<<cars[i].x<<")";//for fixed Scale
        
        //if(i!=(cars.size()-1))
        //    out<<",";

    }
    //out<<"]";
    //-- Show what you got
    imshow("result", image1 );
}
