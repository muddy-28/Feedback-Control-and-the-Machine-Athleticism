#include<opencv/cvaux.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv/cxcore.h>
#include <time.h>

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
using namespace std;

//------Constants------
#define PI 3.14159265;
//------Constants------

int main()
{
    
    //---------------------Veriables------------------
    
    CvSize size640x480=cvSize(640,480);
    
    CvCapture* p_capWebcam;
    
    IplImage* p_imgOriginal;
    
    IplImage* p_imgProcessed;
    
    CvMemStorage* p_strStorage;
    
    CvSeq* p_seqCircles;
    float* p_fltxyRadius;
    float* p_fltxy;
    int i;
    char charCheckForEscKey;
    //---------------------Veriables------------------
    
    //-------------Capture Cam Vid Stream--------------
    p_capWebcam=cvCaptureFromCAM(0);
    
    //to serr cam frame size
    cvSetCaptureProperty( p_capWebcam, CV_CAP_PROP_FRAME_WIDTH, 640 );
    cvSetCaptureProperty( p_capWebcam, CV_CAP_PROP_FRAME_HEIGHT, 480 );
    
    //-------------Stream Checking--------------
    if(p_capWebcam==NULL)
    {
        printf("Error:Capture is NULL\n");
        getchar();
        return(-1);
    }
    //-------------CV Processing and Orignal Win Defination--------------
    cvNamedWindow("Original",CV_WINDOW_AUTOSIZE);
    cv::moveWindow("Original", 700, 20);
    cvNamedWindow("Processed",CV_WINDOW_AUTOSIZE);
    cv::moveWindow("Processed", 20, 350);
    
    p_imgProcessed=cvCreateImage(size640x480,IPL_DEPTH_8U,1);
    while(1)
    {
        p_imgOriginal=cvQueryFrame(p_capWebcam);
        if(p_imgOriginal==NULL)
        {
            printf("Error: Frame is NULL\n");
            getchar();
            break;
            
        }
        cvInRangeS(p_imgOriginal,CV_RGB(175,0,0),CV_RGB(256,100,100),p_imgProcessed);
        //cvInRangeS(p_imgOriginal,CV_RGB(0,0,175),CV_RGB(100,100,256),p_imgProcessed);
        p_strStorage=cvCreateMemStorage(0);
        cvSmooth(p_imgProcessed,p_imgProcessed,CV_GAUSSIAN,9,9);
        
        p_seqCircles=cvHoughCircles(p_imgProcessed,p_strStorage,CV_HOUGH_GRADIENT,2,p_imgProcessed->height/4,100,50,10,400);
        
        for(i=0; i<p_seqCircles->total;i++)
        {
            p_fltxyRadius=(float*)cvGetSeqElem(p_seqCircles,i);
            printf("Position x=%f | y=%f | r=%f", p_fltxyRadius[0],p_fltxyRadius[1],p_fltxyRadius[2]);
            cvCircle(p_imgOriginal,cvPoint(cvRound(p_fltxyRadius[0]),cvRound(p_fltxyRadius[1])),3,CV_RGB(0,255,0),CV_FILLED);
            cvCircle(p_imgOriginal, cvPoint(cvRound(p_fltxyRadius[0]),cvRound(p_fltxyRadius[1])), cvRound(p_fltxyRadius[2]), CV_RGB(0,255,0),3);
        }
        ////////////////////////////////////////////////////////////////////////////////////
        
        //cvInRangeS(p_imgOriginal,CV_RGB(140,0,0),CV_RGB(256,100,100),p_imgProcessed);
        cvInRangeS(p_imgOriginal,CV_RGB(0,0,150),CV_RGB(100,100,256),p_imgProcessed);
        p_strStorage=cvCreateMemStorage(0);
        cvSmooth(p_imgProcessed,p_imgProcessed,CV_GAUSSIAN,9,9);
        
        p_seqCircles=cvHoughCircles(p_imgProcessed,p_strStorage,CV_HOUGH_GRADIENT,2,p_imgProcessed->height/4,100,50,10,400);
        
        for(i=0; i<p_seqCircles->total;i++)
        {
            p_fltxy=(float*)cvGetSeqElem(p_seqCircles,i);
            printf("blue: Position x=%f | y=%f | r=%f", p_fltxy[0],p_fltxy[1],p_fltxy[2]);
            cvCircle(p_imgOriginal,cvPoint(cvRound(p_fltxy[0]),cvRound(p_fltxy[1])),3,CV_RGB(0,255,0),CV_FILLED);
            
            cvCircle(p_imgOriginal, cvPoint(cvRound(p_fltxy[0]),cvRound(p_fltxy[1])), cvRound(p_fltxy[2]), CV_RGB(0,255,0),3);
        }
        
        
        
        
        cvShowImage("Original",p_imgOriginal);
        cvShowImage("Processed",p_imgProcessed);
        cvReleaseMemStorage(&p_strStorage);
        charCheckForEscKey=cvWaitKey(10);
        if(charCheckForEscKey==27)
            break;
    }
    cvReleaseCapture(&p_capWebcam);
    cvDestroyWindow("Original");
    cvDestroyWindow("Processed");
    return(0);
}

