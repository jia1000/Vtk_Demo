#include "stdafx.h"
#include "TestWidgetsBase.h"


CTestWidgetsBase::CTestWidgetsBase(void)
{
}


CTestWidgetsBase::~CTestWidgetsBase(void)
{
}

void CTestWidgetsBase::TextWidgets_Test()
{
    // Create the RenderWindow, Renderer and both Actors
    m_renderer        = CreateRenderer();
    m_renderWindow    = CreateRenderWindow(m_renderer);
    m_interactor      = CreateInteractor(m_renderWindow);
    // Create a test pipeline
    CreatePipeline(m_renderer);
    // Create the widget
    AddTextActor(m_interactor);
        
    StartRender(m_renderer, m_renderWindow, m_interactor);
}

void CTestWidgetsBase::CaptionWidgets_Test()
{
    // Create the RenderWindow, Renderer and both Actors
    m_renderer        = CreateRenderer();
    m_renderWindow    = CreateRenderWindow(m_renderer);
    m_interactor      = CreateInteractor(m_renderWindow);
    // Create a test pipeline
    CreateCaptionPipeline(m_renderer);
    // Create the widget
    AddCaptionActor(m_interactor);

    StartRenderCaption(m_renderer, m_renderWindow, m_interactor);

}

void CTestWidgetsBase::StartRender(vtkSmartPointer<vtkRenderer> renderer, 
                                   vtkSmartPointer<vtkRenderWindow> renderWindow, 
                                   vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    renderWindow->SetSize(600, 600);
    interactor->Initialize();
    renderWindow->Render();
    interactor->Start();
}

void CTestWidgetsBase::StartRenderCaption(vtkSmartPointer<vtkRenderer> renderer, 
                                   vtkSmartPointer<vtkRenderWindow> renderWindow, 
                                   vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    
    m_renderWindow->Render();
    captionWidget->On();
    m_interactor->Start();
}

vtkSmartPointer<vtkRenderer> CTestWidgetsBase::CreateRenderer()
{
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    
    renderer->SetBackground(0.1, 0.2, 0.4);

    return renderer;
}

vtkSmartPointer<vtkRenderWindow> CTestWidgetsBase::CreateRenderWindow(vtkSmartPointer<vtkRenderer> renderer)
{
    vtkSmartPointer< vtkRenderWindow > renderWindow = vtkSmartPointer< vtkRenderWindow >::New();

    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("AnnotationWidget");
    //renderWindow->SetSize(400, 400);

    return renderWindow;
}
vtkSmartPointer<vtkRenderWindowInteractor> CTestWidgetsBase::CreateInteractor(vtkSmartPointer<vtkRenderWindow> renderWindow)
{
    vtkSmartPointer< vtkRenderWindowInteractor > interactor = 
        vtkSmartPointer< vtkRenderWindowInteractor >::New();

    interactor->SetRenderWindow(renderWindow);

    return interactor;
}

void CTestWidgetsBase::CreatePipeline(vtkSmartPointer<vtkRenderer> renderer)
{
    //vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    //vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    //mapper->SetInputConnection(sphereSource->GetOutputPort());
    //vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    //actor->SetMapper(mapper);

    vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileName(".\\data\\test\\ct.jpg");
    reader->Update();

    vtkSmartPointer<vtkImageActor> actor = vtkSmartPointer<vtkImageActor>::New();
    actor->SetInput(reader->GetOutput());

    renderer->AddActor(actor);
}

void CTestWidgetsBase::CreateCaptionPipeline(vtkSmartPointer<vtkRenderer> renderer)
{
    // Sphere
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    //sphereSource->SetRadius(10);
    sphereSource->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    renderer->AddActor(actor);
}

void CTestWidgetsBase::AddTextActor(vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    // Create the widget
    vtkSmartPointer<vtkTextActor> textActor = vtkSmartPointer<vtkTextActor>::New();
    textActor->SetInput("This is a test");
    textActor->GetTextProperty()->SetColor( 0.1, 0.1, 0.1 );
    int font_size = textActor->GetTextProperty()->GetFontSize();
    // 没起效
    //textActor->GetTextProperty()->SetFontSize()

    // vtkTextWidget变量出了作用域，会失效，所以，在vtkRenderWindowInteractor的start同级作用域，一定要保证存在
    textWidget = vtkSmartPointer<vtkTextWidget>::New();

    vtkSmartPointer<vtkTextRepresentation> textRepresentation = vtkSmartPointer<vtkTextRepresentation>::New();
    textRepresentation->GetPositionCoordinate()->SetValue( .01, .01 );
    textRepresentation->GetPosition2Coordinate()->SetValue( .7, .2 );
    textWidget ->SetRepresentation( textRepresentation );

    textWidget->SetInteractor(interactor);
    textWidget->SetTextActor(textActor);
    textWidget->SelectableOff();

    textWidget->On();
}

void CTestWidgetsBase::AddCaptionActor(vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    // Create the widget and its representation
    vtkSmartPointer<vtkCaptionRepresentation> captionRepresentation = vtkSmartPointer<vtkCaptionRepresentation>::New();
    captionRepresentation->GetCaptionActor2D()->SetCaption("Test caption");
    captionRepresentation->GetCaptionActor2D()->GetTextActor()->GetTextProperty()->SetFontSize(100);

    double pos[3] = {.2,0,0};
    captionRepresentation->SetAnchorPosition(pos);

    // vtkCaptionWidget变量出了作用域，会失效，所以，在vtkRenderWindowInteractor的start同级作用域，一定要保证存在
    captionWidget = vtkSmartPointer<vtkCaptionWidget>::New();
    captionWidget->SetInteractor(interactor);
    captionWidget->SetRepresentation(captionRepresentation);

    // 需要放在Render之后
    //captionWidget->On();
}