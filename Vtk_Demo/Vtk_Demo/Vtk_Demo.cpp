// Vtk_Demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "SplitView.h"
#include "DicomView.h"
#include "DicomSplitView.h"
#include "widgets_test//TestWidgetsBase.h"
#include "widgets_test/TextWidgetsTest.h"
#include "widgets_test/CaptionWidgetsTest.h"
#include "widgets_test/BoxWidgetsTest.h"
#include "widgets_test/ContourWidgetsTest.h"
#include "widgets_test/ImageWidgetsTest.h"
#include "widgets_test/Rib3DView.h"
#include "data_object_test/TrianglePoints.h"

int _tmain(int argc, _TCHAR* argv[])
{
#if 1
    //CDicomView view;
    //view.ShowDicomFile(".\\data\\slices1");
    //return 0;

    //CDicomSplitView view;
    //return 0;
    
    //CTextWidgetsTest widgets_test;
    //widgets_test.ShowWidgets_Test();
    //return 0;

    //CCaptionWidgetsTest widgets_test;
    //widgets_test.ShowWidgets_Test();
    //return 0;

    //CBoxWidgetsTest widgets_test;
    //widgets_test.ShowWidgets_Test();
    //return 0;

    //CContourWidgetsTest widgets_test;
    //widgets_test.ShowWidgets_Test();
    //return 0;

    //CImageWidgetsTest widgets_test;
    //widgets_test.ShowWidgets_Test();
    //return 0;

    //Rib3DView widgets_test;
    //widgets_test.ShowWidgets_Test();
    //return 0;

    CTrianglePoints tp("triangle.vtk");
    return 0;
#endif 
    

	return 0;
}

