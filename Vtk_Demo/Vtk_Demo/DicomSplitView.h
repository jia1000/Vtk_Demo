#pragma once
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>

class CDicomSplitView
{
public:
    CDicomSplitView(void);
    ~CDicomSplitView(void);

    void ShowDicomFile(std::string folder);
private:
    vtkSmartPointer<vtkTextMapper> SetLeftDownTextAnonationMapper(vtkSmartPointer<vtkImageViewer2> imageViewer);
    vtkSmartPointer<vtkTextMapper> SetLeftUpAnonationMapper();
    vtkSmartPointer<vtkTextMapper> SetRightDownTextAnonationMapper(vtkSmartPointer<vtkImageViewer2> imageViewer);

    void AddLeftDownSliceTextActor(vtkSmartPointer<vtkTextMapper> sliceTextMapper);
    void AddLeftUpTextActor(vtkSmartPointer<vtkTextMapper> usageTextMapper);
    void AddRightDownSliceTextActor(vtkSmartPointer<vtkTextMapper> sliceTextMapper);


    vtkSmartPointer< vtkImageViewer2 >           m_imageViewer;
    vtkSmartPointer<vtkDICOMImageReader> m_reader;
};

