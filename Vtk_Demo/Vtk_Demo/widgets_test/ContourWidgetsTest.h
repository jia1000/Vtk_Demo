#pragma once
#include "testwidgetsbase.h"
class CContourWidgetsTest :
    public CWidgetsBaseTest
{
public:
    CContourWidgetsTest(void);
    ~CContourWidgetsTest(void);

    virtual void SetMyInteractorStyle(vtkSmartPointer<vtkRenderWindowInteractor> interactor);

    virtual void StartWidgetsRender(vtkSmartPointer<vtkRenderer> renderer, 
        vtkSmartPointer<vtkRenderWindow> renderWindow, 
        vtkSmartPointer<vtkRenderWindowInteractor> interactor);
    virtual void CreatePipeline(vtkSmartPointer<vtkRenderer> renderer);
    virtual void AddMyActor(vtkSmartPointer<vtkRenderWindowInteractor> interactor);

private:
    vtkSmartPointer<vtkContourWidget> contourWidget;
    vtkSmartPointer<vtkPolyData> polydata;
};

