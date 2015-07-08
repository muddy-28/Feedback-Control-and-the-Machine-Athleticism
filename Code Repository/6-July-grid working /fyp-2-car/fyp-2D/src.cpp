#include<opencv/cvaux.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv/cxcore.h>
#include <time.h>
#include<windows.h>

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>

#include<Windows.h>
using namespace std;

//------Constants------
#define PI 3.14159265;

int angle_bule=0;
int angle_red=0;

bool checkBufferFlag = false;
bool checkBufferFlagAfterTurn = false;
int atTurnY_axis;
bool URCFlag = false;
bool LRCFlag = false;
	
//char outputChars[];
char outputChars[] = "c";
DWORD btsIO;
//------Constants------
HANDLE hSerial;

void wait ( int seconds ) 
{ 
  clock_t endwait; 
  endwait = clock () + seconds * CLOCKS_PER_SEC ; 
  while (clock() < endwait) {} 
}

void delay(char action)
{
	for(int i=1;i>0;i--)
	{
	outputChars[0] = action;
	WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
	wait(0);
	}
}

void serialPortWrite()
{
	hSerial = CreateFile(L"COM3", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial !=INVALID_HANDLE_VALUE)
    {
        printf("Port opened! \n");
        DCB dcbSerialParams;
        GetCommState(hSerial,&dcbSerialParams);
        dcbSerialParams.BaudRate = CBR_9600;
        dcbSerialParams.ByteSize = 8;
        dcbSerialParams.Parity = NOPARITY;
        dcbSerialParams.StopBits = ONESTOPBIT;
        SetCommState(hSerial, &dcbSerialParams);
	}
	else
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			printf("Serial port doesn't exist! \n");
		}
		printf("Error while setting up serial port! \n");
		//system("PAUSE");
	}
	
}

void URCturnLeft(int p_fltxyRadius0, int p_fltxy0,int p_fltxyRadius1)
{
	if(p_fltxyRadius0 <= p_fltxy0)
				{
					cout<<"After Turn Left";
					cout<<"Move Forward";
					delay('F');
					
					if(checkBufferFlagAfterTurn == false)
					{
						atTurnY_axis = p_fltxyRadius1;
						checkBufferFlagAfterTurn = true;
					}
					if(p_fltxyRadius1 > atTurnY_axis)
					{
						cout<<"Move Left (After turn)";
						delay('L');
					}else if(p_fltxyRadius1 < atTurnY_axis)
					{
						cout<<"Move Right (After turn)";
						delay('R');
					}
				}/*else if(p_fltxyRadius0 >= p_fltxy0)
				{
					cout<<"Turn Right";
					if(checkBufferFlagAfterTurn == false)
					{
						atTurnY_axis = p_fltxyRadius1;
						checkBufferFlagAfterTurn = true;
					}
					if(p_fltxyRadius1 < atTurnY_axis)
					{
						cout<<"Move Left (After turn)";
					}else if(p_fltxyRadius1 > atTurnY_axis)
					{
						cout<<"Move Right (After turn)";
					}
				}*/else
	{
		delay('S');
		exit(0);}
}

void URCcarRight_BallLeft(int p_fltxyRadius0, int initialX_axis, int p_fltxyRadius1,int p_fltxy1, int p_fltxy0)
{
		//if(p_fltxyRadius1 >= p_fltxy1-20)
		//{
		//	delay('S');
		//	
		//	//outputChars[0] = 'S';
		//	//WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
		//	cout<<"Achieved";
		//}
		if(p_fltxyRadius0 < initialX_axis-5 )
		{

			cout<<"Move Left"<<initialX_axis<<" & "<<initialX_axis-10;
			delay('L');
		}else if(p_fltxyRadius0 > 5+initialX_axis)
		{
			cout<<"Move Right";
			delay('R');
		}

		if((p_fltxyRadius1 >= p_fltxy1 && p_fltxyRadius1 <= 20+p_fltxy1))
		{
			//outputChars[0] = 'S';
			//WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
			//delay('S');
			cout<<"In Buffer";
		}
}

void URCMoveBackward(int p_fltxyRadius0, int initialX_axis, int p_fltxyRadius1,int p_fltxy1, int p_fltxy0)
{
	// 
	//outputChars[0] = 'F';
		//cout<<"Move Backward.";
		//if(p_fltxyRadius0 < initialX_axis )
		//{
		//	cout<<"Move Left";
		//}else if(p_fltxyRadius0 > initialX_axis)
		//{
		//	cout<<"Move Right";
		//}
		////WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
		//if((p_fltxyRadius1 >= p_fltxy1 && p_fltxyRadius1 <= 20+p_fltxy1))
		//{
		//	//outputChars[0] = 'S';
		//	//WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
		//	cout<<"In Buffer";
		//}
}
/*---------------------- LRC ------------------------*/

void LRCturnLeft(int p_fltxyRadius0, int p_fltxy0,int p_fltxyRadius1)
{
	/*if(p_fltxyRadius0 <= p_fltxy0)
				{
					cout<<"Turn Right & Move Forward";
					if(checkBufferFlagAfterTurn == false)
					{
						atTurnY_axis = p_fltxyRadius1;
						checkBufferFlagAfterTurn = true;
					}
					if(p_fltxyRadius1 > atTurnY_axis)
					{
						cout<<"Move Left (After turn)";
					}else if(p_fltxyRadius1 < atTurnY_axis)
					{
						cout<<"Move Right (After turn)";
					}
				}else if(p_fltxyRadius0 >= p_fltxy0)
				{
					cout<<"Turn Left";
					if(checkBufferFlagAfterTurn == false)
					{
						atTurnY_axis = p_fltxyRadius1;
						checkBufferFlagAfterTurn = true;
					}
					if(p_fltxyRadius1 < atTurnY_axis)
					{
						cout<<"Move Left (After turn)";
					}else if(p_fltxyRadius1 > atTurnY_axis)
					{
						cout<<"Move Right (After turn)";
					}
				}*/
}

void LRCcarRight_BallLeft(int p_fltxyRadius0, int initialX_axis, int p_fltxyRadius1,int p_fltxy1, int p_fltxy0)
{
		 
		//outputChars[0] = 'F';
		//cout<<"Move forward.";
		//if(p_fltxyRadius0 >= 10- p_fltxy0)
		//{
		//	 
		//	outputChars[0] = 'S';
		//}

		//if(p_fltxyRadius0 < initialX_axis )
		//{
		//	cout<<"Move Right";
		//	//outputChars[0] = 'L';
		//	//WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
		//}else if(p_fltxyRadius0 > initialX_axis)
		//{
		//	cout<<"Move Left";
		//	//outputChars[0] = 'R';
		//	//WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
		//}
		///*WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);*/
		//if((p_fltxyRadius1 <= p_fltxy1 && p_fltxyRadius1 >= 20-p_fltxy1))
		//{
		//	//outputChars[0] = 'S';
		//	//WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
		//	cout<<"In Buffer";
		//}
}

void LRCMoveBackward(int p_fltxyRadius0, int initialX_axis, int p_fltxyRadius1,int p_fltxy1, int p_fltxy0)
{
	// 
	//outputChars[0] = 'F';
		//cout<<"Move Backward.";
		//if(p_fltxyRadius0 < initialX_axis )
		//{
		//	cout<<"Move Right";
		//}else if(p_fltxyRadius0 > initialX_axis)
		//{
		//	cout<<"Move Left";
		//}
		////WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
		//if((p_fltxyRadius1 <= p_fltxy1 && p_fltxyRadius1 >= 20-p_fltxy1))
		//{
		//	//outputChars[0] = 'S';
		//	//WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
		//	cout<<"In Buffer";
		//}
}



int main()
{
    //---------------------Veriables------------------    
    CvSize size640x480=cvSize(640,480);
    CvSize size640x480_v1=cvSize(640,480);
    CvCapture* p_capWebcam;
    IplImage* p_imgOriginal;
    IplImage* p_imgProcessed;
    IplImage* p_imgProcessed_v1;
    CvMemStorage* p_strStorage;
    CvMemStorage* p_strStorage_v1;
    CvSeq* p_seqCircles;
    CvSeq* p_seqCircles_v1;
    float* p_fltxyRadius;
    float* p_fltxy;
    int i,j;
	int dest=0;
	int src=0;
    char charCheckForEscKey;
	delay('S');
	serialPortWrite();
	
	int temp = 0;
	
    //---------------------Veriables------------------
    
	//-------------------communication------------------
	
	//-------------------communication------------------
	
	// Setup serial port connection and needed variables.
	 
	
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
	else
	{
		cout<<"Camera Opened... n working...";
	//-------------CV Processing and Orignal Win Defination--------------
    cvNamedWindow("Original",CV_WINDOW_AUTOSIZE);
    cv::moveWindow("Original", 700, 20);
   // cvNamedWindow("Processed Red",CV_WINDOW_AUTOSIZE);
    //cv::moveWindow("Processed Red", 20, 20);
    //cvNamedWindow("Processed Blue",CV_WINDOW_AUTOSIZE);
    //cv::moveWindow("Processed Blue", 20, 350);

	//bool checkBufferFlag = false;
	int initialX_axisCar;
	int initialY_axisCar;
	
	/*bool checkBufferFlagAfterTurn = false;
	int atTurnY_axis;
*/
	clock_t diffTime;
	clock_t initTime=clock(); 
	clock_t t=clock();
	initTime=((float)t)/CLOCKS_PER_SEC;
	double x1=0;
	double y1=0;
    double x2=0;
	double y2=0;


	clock_t diffTime_bule;
	clock_t initTime_bule=clock(); 
	clock_t t_bule=clock();
	initTime_bule=((float)t_bule)/CLOCKS_PER_SEC;
	double x1_bule=0;
	double y1_bule=0;
    double x2_bule=0;
	double y2_bule=0;
    
    p_imgProcessed=cvCreateImage(size640x480,IPL_DEPTH_8U,1);
    p_imgProcessed_v1=cvCreateImage(size640x480_v1,IPL_DEPTH_8U,1);
    while(1)
    {
        p_imgOriginal=cvQueryFrame(p_capWebcam);
        if(p_imgOriginal==NULL)
        {
            printf("Error: Frame is NULL\n");
            getchar();
            break;
            
        }
        //red rgb ;-)
        cvInRangeS(p_imgOriginal,CV_RGB(140,0,0),CV_RGB(255,120,110),p_imgProcessed);
        p_strStorage=cvCreateMemStorage(0);
        cvSmooth(p_imgProcessed,p_imgProcessed,CV_GAUSSIAN,9,9);
        
        p_seqCircles=cvHoughCircles(p_imgProcessed,p_strStorage,CV_HOUGH_GRADIENT,2,p_imgProcessed->height/4,100,50,10,400);
        
        //blue rgb :-)
        cvInRangeS(p_imgOriginal,CV_RGB(0,0,120),CV_RGB(110,120,255),p_imgProcessed_v1);
        p_strStorage_v1=cvCreateMemStorage(0);
        cvSmooth(p_imgProcessed_v1,p_imgProcessed_v1,CV_GAUSSIAN,9,9);
        
        p_seqCircles_v1=cvHoughCircles(p_imgProcessed_v1,p_strStorage_v1,CV_HOUGH_GRADIENT,2,p_imgProcessed_v1->height/4,100,50,10,400);
        
		//ttribute creation for red ball
        for(i=0; i<p_seqCircles->total;i++)
        {
            p_fltxyRadius=(float*)cvGetSeqElem(p_seqCircles,i);
            printf("\n red: Position x=%f | y=%f | r=%f", p_fltxyRadius[0],p_fltxyRadius[1],p_fltxyRadius[2]);
            cvCircle(p_imgOriginal,cvPoint(cvRound(p_fltxyRadius[0]),cvRound(p_fltxyRadius[1])),3,CV_RGB(0,255,0),CV_FILLED);
            cvCircle(p_imgOriginal, cvPoint(cvRound(p_fltxyRadius[0]),cvRound(p_fltxyRadius[1])), cvRound(p_fltxyRadius[2]), CV_RGB(0,255,0),3);
			double result;
			double param = p_fltxyRadius[1]/p_fltxyRadius[0];
			result = atan(param) * 180 / PI;
			angle_red=result;
			//cout<<" | Angle "<<result;
			//---------------------------------
			x2 = p_fltxyRadius[0];
			y2 = p_fltxyRadius[1];

			if(checkBufferFlag == false)
			{
				initialX_axisCar = x2;
				initialY_axisCar = y2;
				checkBufferFlag = true;
			}

			clock_t t;
			t = clock();
			diffTime = ((float)t)/CLOCKS_PER_SEC;
			if(diffTime-initTime >= 5)
			{
	 			float resultingDistance = ((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));
				float result;
				result = sqrt (resultingDistance);
				//printf ("| Distance = %f", result );

				//cout<<" | Speed"<<1000*result/diffTime<<endl;
				x1 = p_fltxyRadius[0];
				y1 = p_fltxyRadius[1];
			}
		}
        
        //conture creation for blue ball
        for(j=0; j<p_seqCircles_v1->total;j++)
        {
            p_fltxy=(float*)cvGetSeqElem(p_seqCircles_v1,j);
            printf("\n blue: Position x=%f | y=%f | r=%f", p_fltxy[0],p_fltxy[1],p_fltxy[2]);
            cvCircle(p_imgOriginal,cvPoint(cvRound(p_fltxy[0]),cvRound(p_fltxy[1])),3,CV_RGB(0,255,0),CV_FILLED);
            cvCircle(p_imgOriginal, cvPoint(cvRound(p_fltxy[0]),cvRound(p_fltxy[1])), cvRound(p_fltxy[2]), CV_RGB(0,255,0),3);

			
			double param_bule = p_fltxy[1]/p_fltxy[0];
			double result_bule = atan(param_bule) * 180 / PI;
			angle_bule=result_bule;
			//cout<<" | Angle "<<result_bule;
			//---------------------------------
			x2_bule = p_fltxy[0];
			y2_bule = p_fltxy[1];
			clock_t t_bule;
			t_bule = clock();
			diffTime_bule = ((float)t_bule)/CLOCKS_PER_SEC;
			if(diffTime_bule-initTime_bule >= 5)
			{
	 			float resultingDistance_bule = ((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));
				float result_bule;
				result_bule = sqrt (resultingDistance_bule);
				//printf ("| Distance = %f", result_bule );
				//cout<<" | Speed"<<1000*result_bule/diffTime_bule<<endl;
				x1_bule = p_fltxy[0];
				y1_bule = p_fltxy[1];
			}
        }
        cvShowImage("Original",p_imgOriginal);
       // cvShowImage("Processed Red",p_imgProcessed);
       // cvShowImage("Processed Blue",p_imgProcessed_v1);
		if(p_seqCircles_v1->total==1 && p_seqCircles->total==1)
		{
			p_fltxy=(float*)cvGetSeqElem(p_seqCircles_v1,1);
			p_fltxyRadius=(float*)cvGetSeqElem(p_seqCircles,1);
			dest=p_fltxy[0];
			src=p_fltxyRadius[0];
			//cout<<"\a";
		}
		
		if(dest!=0 && src!=0)
		{
			/*if (angle_red < angle_bule)
			{
				cout<<"Red is less. Move left tyre.";
			}*/
			if(p_fltxyRadius[1] < p_fltxy[1] && URCFlag == false && LRCFlag == false)
			{
				URCFlag = true;
			}else if(p_fltxyRadius[1] > p_fltxy[1] && URCFlag == false && LRCFlag == false)
			{
				LRCFlag = true;
			}
			if(URCFlag == true)
			{
				if (p_fltxyRadius[1] <= p_fltxy[1]-120 && p_fltxyRadius[1] > 0)
				{
					//Move Forward
					delay('F');	
					cout<<"Move forward.";
					URCcarRight_BallLeft(p_fltxyRadius[0],initialX_axisCar,p_fltxyRadius[1],p_fltxy[1],p_fltxy[0]);
					
					// temp = p_fltxy[1] - 100;
				}else if((p_fltxyRadius[1] >= (p_fltxy[1]-120)) && p_fltxyRadius[1] > 0)
				{
					cout<<"agge";
					if(p_fltxyRadius[1] <= p_fltxy[1] && p_fltxyRadius[1] > 0)
					{
						//Stop Car and turn left
						cout<<"Turn Left";
						delay('T');
						URCturnLeft(p_fltxyRadius[0],p_fltxy[0],p_fltxyRadius[1]);
					}else
					{
						//Move Backward
						URCMoveBackward(p_fltxyRadius[0],initialX_axisCar,p_fltxyRadius[1],p_fltxy[1],p_fltxy[0]);
						//cout<<"Move Backward";
					}
				}
			}
			if(LRCFlag == true)
			{
				cout<<"LRC";
				delay('F');
				if (p_fltxyRadius[1] >= p_fltxy[1] && p_fltxyRadius[1] > 0)
				{
					//Move Forward
					LRCcarRight_BallLeft(p_fltxyRadius[0],initialX_axisCar,p_fltxyRadius[1],p_fltxy[1],p_fltxy[0]);
				}else if(p_fltxyRadius[1] <= p_fltxy[1] && p_fltxyRadius[1] > 0)
				{
					if(p_fltxyRadius[1] >= 20-p_fltxy[1] && p_fltxyRadius[1] > 0)
					{
						//Stop Car and turn left
						LRCturnLeft(p_fltxyRadius[0],p_fltxy[0],p_fltxyRadius[1]);
					}else
					{
						//Move Backward
						LRCMoveBackward(p_fltxyRadius[0],initialX_axisCar,p_fltxyRadius[1],p_fltxy[1],p_fltxy[0]);
						//cout<<"Move Backward";
					}
				}
			}
			/*if (p_fltxyRadius[1] <= p_fltxy[1] && p_fltxyRadius[1] > 0)
			{*/
				//URCcarRight_BallLeft(p_fltxyRadius[0],initialX_axisCar,p_fltxyRadius[1],p_fltxy[1],p_fltxy[0]);
			//}/*else if(p_fltxyRadius[1] >= p_fltxy[1] && p_fltxyRadius[1] > 0)
			//{
				//URCturnLeft(p_fltxyRadius[0],p_fltxy[0],p_fltxyRadius[1]);
			//}
			/*else if((src>=dest && p_fltxy[1]>p_fltxyRadius[1]))
			{
				outputChars[0] = 'R';
				WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
			}
			else if((src>=dest && p_fltxy[1]<p_fltxyRadius[1]))
			{
				outputChars[0] = 'L';
				WriteFile(hSerial, outputChars, strlen(outputChars), &btsIO, NULL);
			}*/
		}
		cout<<"\n Destination"<<dest<<"\n";
        
        cvReleaseMemStorage(&p_strStorage);
        charCheckForEscKey=cvWaitKey(10);
        if(charCheckForEscKey==27)
            break;
    }
    cvReleaseCapture(&p_capWebcam);
    cvDestroyWindow("Original");
    cvDestroyWindow("Processed");
	checkBufferFlag = false;
	}
    return(0);
}
