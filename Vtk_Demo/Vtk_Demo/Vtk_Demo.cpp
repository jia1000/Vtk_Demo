// Vtk_Demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "SplitView.h"
#include "DicomSplitView.h"

int _tmain(int argc, _TCHAR* argv[])
{
    CDicomSplitView view;
    view.ShowDicomFile(".\\data\\slices1");
    
    
	return 0;
}

