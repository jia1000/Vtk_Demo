// Vtk_Demo.cpp : �������̨Ӧ�ó������ڵ㡣
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

