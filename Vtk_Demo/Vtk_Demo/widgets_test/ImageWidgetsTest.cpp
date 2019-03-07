#include "stdafx.h"
#include "ImageWidgetsTest.h"

CImageWidgetsTest::CImageWidgetsTest(void)
{
}


CImageWidgetsTest::~CImageWidgetsTest(void)
{
}

void CImageWidgetsTest::StartWidgetsRender(vtkSmartPointer<vtkRenderer> renderer, 
                                              vtkSmartPointer<vtkRenderWindow> renderWindow, 
                                              vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    m_interactor->Initialize();
    m_renderWindow->Render();
    planeWidget->On();
    m_interactor->Start();
}

void CImageWidgetsTest::SetMyInteractorStyle(vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    interactor->SetInteractorStyle( style );
}

void CImageWidgetsTest::CreatePipeline(vtkSmartPointer<vtkRenderer> renderer)
{
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->Update();

    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    renderer->AddActor(actor);
}

void CImageWidgetsTest::AddMyActor(vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    /*vtkSmartPointer<vtkImagePlaneWidget>*/ planeWidget = vtkSmartPointer<vtkImagePlaneWidget>::New();
    planeWidget->SetInteractor(interactor);
    planeWidget->TextureVisibilityOff();

    double origin[3] = {1, 0,0};
    planeWidget->SetOrigin(origin);
    planeWidget->UpdatePlacement();

}