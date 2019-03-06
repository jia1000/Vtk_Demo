#pragma once
#include "testwidgetsbase.h"
class CTextWidgetsTest :
    public CWidgetsBaseTest
{
public:
    CTextWidgetsTest(void);
    ~CTextWidgetsTest(void);

    virtual void StartWidgetsRender(vtkSmartPointer<vtkRenderer> renderer, 
        vtkSmartPointer<vtkRenderWindow> renderWindow, 
        vtkSmartPointer<vtkRenderWindowInteractor> interactor);
    virtual void CreatePipeline(vtkSmartPointer<vtkRenderer> renderer);
    virtual void AddMyActor(vtkSmartPointer<vtkRenderWindowInteractor> interactor);

private:
    vtkSmartPointer<vtkTextWidget> textWidget;
};

