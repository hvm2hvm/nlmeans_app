
#ifndef _COMMON_H
#define _COMMON_H
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/legacy/compat.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <windows.h>
//#include <string>

using namespace cv;

#define PI 3.14159265
#define POS_INFINITY 1e30
#define NEG_INFINITY -1e30
#define max_(x,y) ((x) > (y) ? (x) : (y))
#define min_(x,y) ((x) < (y) ? (x) : (y))
#define isNan(x) ((x) != (x) ? 1 : 0)

#define OBJECT 0
#define BACKGROUND 255

#define RED 2
#define GREEN 1
#define BLUE 0

#define HUE 0
#define SATURATION 1
#define VALUE 2

class FileGetter{
	WIN32_FIND_DATAA found;	
	HANDLE hfind;
	char folder[MAX_PATH];			
	int chk;
	bool first;
	bool hasFiles;
public:
	FileGetter(char* folderin,char* ext);
	int getNextFile(char* fname);
	int getNextAbsFile(char* fname);
	char* getFoundFileName();
};


int openFileDlg(char* fname);

int openFolderDlg(char* folderName);

void resizeImg(Mat src, Mat &dst, int maxSize, bool interpolate);

#endif