#include "stdafx.h"
#include "CaptionWidgetsTest.h"


CCaptionWidgetsTest::CCaptionWidgetsTest(void)
{
}


CCaptionWidgetsTest::~CCaptionWidgetsTest(void)
{
}

void CCaptionWidgetsTest::StartWidgetsRender(vtkSmartPointer<vtkRenderer> renderer, 
                                              vtkSmartPointer<vtkRenderWindow> renderWindow, 
                                              vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    m_renderWindow->Render();
    captionWidget->On();
    m_interactor->Start();
}

void CCaptionWidgetsTest::CreatePipeline(vtkSmartPointer<vtkRenderer> renderer)
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

void CCaptionWidgetsTest::AddMyActor(vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    // Create the widget and its representation
    vtkSmartPointer<vtkCaptionRepresentation> captionRepresentation = vtkSmartPointer<vtkCaptionRepresentation>::New();
    captionRepresentation->GetCaptionActor2D()->SetCaption("Test caption");
    captionRepresentation->GetCaptionActor2D()->GetTextActor()->GetTextProperty()->SetFontSize(100);

    double pos[3] = {.2,0,0};
    captionRepresentation->SetAnchorPosition(pos);

    // vtkCaptionWidget�������������򣬻�ʧЧ�����ԣ���vtkRenderWindowInteractor��startͬ��������һ��Ҫ��֤����
    captionWidget = vtkSmartPointer<vtkCaptionWidget>::New();
    captionWidget->SetInteractor(interactor);
    captionWidget->SetRepresentation(captionRepresentation);

    // ��Ҫ����Render֮��
    //captionWidget->On();
}