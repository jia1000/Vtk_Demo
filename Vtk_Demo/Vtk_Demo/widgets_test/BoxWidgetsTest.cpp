#include "stdafx.h"
#include "BoxWidgetsTest.h"


class vtkMyCallback : public vtkCommand
{
public:
    static vtkMyCallback *New()
    {
        return new vtkMyCallback;
    }
    virtual void Execute( vtkObject *caller, unsigned long, void* )
    {
        // Here we use the vtkBoxWidget to transform the underlying coneActor
        // (by manipulating its transformation matrix).
        vtkSmartPointer<vtkTransform> t =
            vtkSmartPointer<vtkTransform>::New();
        vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
        widget->GetTransform( t );
        widget->GetProp3D()->SetUserTransform( t );
    }
};

//////////////////////////////////////////////////////////////////////////
CBoxWidgetsTest::CBoxWidgetsTest(void)
{
}


CBoxWidgetsTest::~CBoxWidgetsTest(void)
{
}

void CBoxWidgetsTest::StartWidgetsRender(vtkSmartPointer<vtkRenderer> renderer, 
                                              vtkSmartPointer<vtkRenderWindow> renderWindow, 
                                              vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    m_renderWindow->Render();
    boxWidget->On();
    m_interactor->Start();
}

void CBoxWidgetsTest::SetMyInteractorStyle(vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    interactor->SetInteractorStyle( style );
}

void CBoxWidgetsTest::CreatePipeline(vtkSmartPointer<vtkRenderer> renderer)
{
    vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();

    vtkSmartPointer<vtkPolyDataMapper> coneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    coneMapper->SetInputConnection( cone->GetOutputPort() );

    /*vtkSmartPointer<vtkActor>*/ actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper( coneMapper );

    renderer->AddActor(actor);
}

void CBoxWidgetsTest::AddMyActor(vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    /*vtkSmartPointer<vtkBoxWidget> */boxWidget = vtkSmartPointer<vtkBoxWidget>::New();
    boxWidget->SetInteractor( interactor );

    boxWidget->SetProp3D( actor );
    boxWidget->SetPlaceFactor( 1.25 ); // Make the box 1.25x larger than the actor
    boxWidget->PlaceWidget();

    vtkSmartPointer<vtkMyCallback> callback = vtkSmartPointer<vtkMyCallback>::New();
    boxWidget->AddObserver( vtkCommand::InteractionEvent, callback );

    //boxWidget->On();
}