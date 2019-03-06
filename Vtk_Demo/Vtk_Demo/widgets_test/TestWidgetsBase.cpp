#include "stdafx.h"
#include "TestWidgetsBase.h"


CWidgetsBaseTest::CWidgetsBaseTest(void)
{
}


CWidgetsBaseTest::~CWidgetsBaseTest(void)
{
}

void CWidgetsBaseTest::ShowWidgets_Test()
{
    // Create the RenderWindow, Renderer and both Actors
    m_renderer        = CreateRenderer();
    m_renderWindow    = CreateRenderWindow(m_renderer);
    m_interactor      = CreateInteractor(m_renderWindow);
    // Create a test pipeline
    CreatePipeline(m_renderer);
    // Create the widget
    AddMyActor(m_interactor);

    StartWidgetsRender(m_renderer, m_renderWindow, m_interactor);
}

//void CWidgetsBaseTest::TextWidgets_Test()
//{
//    // Create the RenderWindow, Renderer and both Actors
//    m_renderer        = CreateRenderer();
//    m_renderWindow    = CreateRenderWindow(m_renderer);
//    m_interactor      = CreateInteractor(m_renderWindow);
//    // Create a test pipeline
//    CreateTextPipeline(m_renderer);
//    // Create the widget
//    AddTextActor(m_interactor);
//        
//    StartTextWidgetsRender(m_renderer, m_renderWindow, m_interactor);
//}

//void CWidgetsBaseTest::CaptionWidgets_Test()
//{
//    // Create the RenderWindow, Renderer and both Actors
//    m_renderer        = CreateRenderer();
//    m_renderWindow    = CreateRenderWindow(m_renderer);
//    m_interactor      = CreateInteractor(m_renderWindow);
//    // Create a test pipeline
//    CreateCaptionPipeline(m_renderer);
//    // Create the widget
//    AddCaptionActor(m_interactor);
//
//    StartCaptionWidgetsRender(m_renderer, m_renderWindow, m_interactor);
//
//}





vtkSmartPointer<vtkRenderer> CWidgetsBaseTest::CreateRenderer()
{
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    
    renderer->SetBackground(0.1, 0.2, 0.4);

    return renderer;
}

vtkSmartPointer<vtkRenderWindow> CWidgetsBaseTest::CreateRenderWindow(vtkSmartPointer<vtkRenderer> renderer)
{
    vtkSmartPointer< vtkRenderWindow > renderWindow = vtkSmartPointer< vtkRenderWindow >::New();

    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("AnnotationWidget");
    //renderWindow->SetSize(400, 400);

    return renderWindow;
}
vtkSmartPointer<vtkRenderWindowInteractor> CWidgetsBaseTest::CreateInteractor(vtkSmartPointer<vtkRenderWindow> renderWindow)
{
    vtkSmartPointer< vtkRenderWindowInteractor > interactor = 
        vtkSmartPointer< vtkRenderWindowInteractor >::New();

    interactor->SetRenderWindow(renderWindow);

    return interactor;
}