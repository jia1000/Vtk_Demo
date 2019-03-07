#pragma once
#include "testwidgetsbase.h"
class CImageWidgetsTest :
    public CWidgetsBaseTest
{
public:
    CImageWidgetsTest(void);
    ~CImageWidgetsTest(void);

    virtual void SetMyInteractorStyle(vtkSmartPointer<vtkRenderWindowInteractor> interactor);

    virtual void StartWidgetsRender(vtkSmartPointer<vtkRenderer> renderer, 
        vtkSmartPointer<vtkRenderWindow> renderWindow, 
        vtkSmartPointer<vtkRenderWindowInteractor> interactor);
    virtual void CreatePipeline(vtkSmartPointer<vtkRenderer> renderer);
    virtual void AddMyActor(vtkSmartPointer<vtkRenderWindowInteractor> interactor);

private:
    vtkSmartPointer<vtkImagePlaneWidget> planeWidget;
};

