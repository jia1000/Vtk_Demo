// Vtk_Demo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "SplitView.h"
#include "DicomView.h"
#include "DicomSplitView.h"

int _tmain(int argc, _TCHAR* argv[])
{
    CDicomView view;
    view.ShowDicomFile(".\\data\\slices1");
    return 0;

    //CDicomSplitView view;
    //return 0;   
    
	return 0;
}

