#pragma once
#include "testwidgetsbase.h"
class CCaptionWidgetsTest :
    public CWidgetsBaseTest
{
public:
    CCaptionWidgetsTest(void);
    ~CCaptionWidgetsTest(void);

    virtual void StartWidgetsRender(vtkSmartPointer<vtkRenderer> renderer, 
        vtkSmartPointer<vtkRenderWindow> renderWindow, 
        vtkSmartPointer<vtkRenderWindowInteractor> interactor);
    virtual void CreatePipeline(vtkSmartPointer<vtkRenderer> renderer);
    virtual void AddMyActor(vtkSmartPointer<vtkRenderWindowInteractor> interactor);

private:
    vtkSmartPointer<vtkCaptionWidget> captionWidget;
};

