#include "stdafx.h"
#include "TextWidgetsTest.h"


CTextWidgetsTest::CTextWidgetsTest(void)
{
}


CTextWidgetsTest::~CTextWidgetsTest(void)
{
}

void CTextWidgetsTest::StartWidgetsRender(vtkSmartPointer<vtkRenderer> renderer, 
                                              vtkSmartPointer<vtkRenderWindow> renderWindow, 
                                              vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    renderWindow->SetSize(600, 600);
    interactor->Initialize();
    renderWindow->Render();
    interactor->Start();
}

void CTextWidgetsTest::CreatePipeline(vtkSmartPointer<vtkRenderer> renderer)
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

void CTextWidgetsTest::AddMyActor(vtkSmartPointer<vtkRenderWindowInteractor> interactor)
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