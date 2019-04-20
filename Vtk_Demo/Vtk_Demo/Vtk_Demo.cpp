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
    //view.ShowDicomFile(".\\data\\slices3");
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

    //CTrianglePoints tp("triangle.vtk");
    //return 0;
#endif 
    vtkSmartPointer<vtkJPEGReader> reader =
        vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileName( ".\\data\\ct.jpg");
    reader->Update();

    vtkSmartPointer<vtkImageShrink3D> shrinkFilter = 
        vtkSmartPointer<vtkImageShrink3D>::New();
    shrinkFilter->SetInputConnection(reader->GetOutputPort());
    shrinkFilter->SetShrinkFactors(20,20,1);
    shrinkFilter->Update();

    int originalDims[3];
    reader->GetOutput()->GetDimensions(originalDims);

    double originalSpace[3];
    reader->GetOutput()->GetSpacing(originalSpace);

    int shrinkDims[3];
    shrinkFilter->GetOutput()->GetDimensions(shrinkDims);

    double shrinkSpace[3];
    shrinkFilter->GetOutput()->GetSpacing(shrinkSpace);

    std::cout<<"原图图像维数      ："<<originalDims[0] << " "<<originalDims[1]<<" "<<originalDims[2]<<std::endl;
    std::cout<<"原图图像像素间隔  ："<<originalSpace[0] << " "<<originalSpace[1]<<" "<<originalSpace[2]<<std::endl;
    std::cout<<"重采样图像维数    ："<<shrinkDims[0] << " "<<shrinkDims[1]<<" "<<shrinkDims[2]<<std::endl;
    std::cout<<"重采样图像像素间隔："<<shrinkSpace[0] << " "<<shrinkSpace[1]<<" "<<shrinkSpace[2]<<std::endl;

    vtkSmartPointer<vtkImageActor> originalActor =
        vtkSmartPointer<vtkImageActor>::New();
    originalActor->SetInput( reader->GetOutput());

    vtkSmartPointer<vtkImageActor> shrinkActor =
        vtkSmartPointer<vtkImageActor>::New();
    shrinkActor->SetInput(shrinkFilter->GetOutput());

    double originalViewport[4] = {0.0, 0.0, 0.5, 1.0};
    double shrinkViewport[4] = {0.5, 0.0, 1.0, 1.0};

    vtkSmartPointer<vtkRenderer> originalRenderer =
        vtkSmartPointer<vtkRenderer>::New();
    originalRenderer->SetViewport(originalViewport);
    originalRenderer->AddActor(originalActor);
    originalRenderer->ResetCamera();
    originalRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderer> shrinkRenderer =
        vtkSmartPointer<vtkRenderer>::New();
    shrinkRenderer->SetViewport(shrinkViewport);
    shrinkRenderer->AddActor(shrinkActor);
    shrinkRenderer->ResetCamera();
    shrinkRenderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(originalRenderer);
    renderWindow->AddRenderer(shrinkRenderer);
    renderWindow->SetSize(640, 480);
    renderWindow->Render();
    renderWindow->SetWindowName("ImageShrink3DExample");

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> style =
        vtkSmartPointer<vtkInteractorStyleImage>::New();

    renderWindowInteractor->SetInteractorStyle(style);
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();

	return 0;
}

