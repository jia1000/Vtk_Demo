#pragma once
#include "testwidgetsbase.h"
class CBoxWidgetsTest :
    public CWidgetsBaseTest
{
public:
    CBoxWidgetsTest(void);
    ~CBoxWidgetsTest(void);

    virtual void SetMyInteractorStyle(vtkSmartPointer<vtkRenderWindowInteractor> interactor);

    virtual void StartWidgetsRender(vtkSmartPointer<vtkRenderer> renderer, 
        vtkSmartPointer<vtkRenderWindow> renderWindow, 
        vtkSmartPointer<vtkRenderWindowInteractor> interactor);
    virtual void CreatePipeline(vtkSmartPointer<vtkRenderer> renderer);
    virtual void AddMyActor(vtkSmartPointer<vtkRenderWindowInteractor> interactor);

private:
    vtkSmartPointer<vtkBoxWidget> boxWidget;
    vtkSmartPointer<vtkActor> actor;
};

