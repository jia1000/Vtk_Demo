#pragma once
#include "testwidgetsbase.h"
class Rib3DView :
    public CWidgetsBaseTest
{
public:
    Rib3DView(void);
    ~Rib3DView(void);

    void SetMyInteractorStyle(vtkSmartPointer<vtkRenderWindowInteractor> interactor);

    virtual void StartWidgetsRender(vtkSmartPointer<vtkRenderer> renderer, 
        vtkSmartPointer<vtkRenderWindow> renderWindow, 
        vtkSmartPointer<vtkRenderWindowInteractor> interactor);
    virtual void CreatePipeline(vtkSmartPointer<vtkRenderer> renderer);
    virtual void AddMyActor(vtkSmartPointer<vtkRenderWindowInteractor> interactor);

private:
    vtkSmartPointer<vtkTextWidget> textWidget;
};

