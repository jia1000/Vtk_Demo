#include "stdafx.h"

#include "SplitView.h"





//////////////////////////////////////////////////////////////////////////
CSplitView::CSplitView()
{
    // ����һ����2*2���ֵĴ���
    m_render_left_down  = CreateVtkRender();
    m_render_left_up    = CreateVtkRender();
    m_render_right_down = CreateVtkRender();
    m_render_right_up   = CreateVtkRender();

    // ����ͼ��
    m_render_left_down->SetBackground(1.0,0.0,0.0);
    m_render_left_down->SetViewport(0.0,0.0,0.5,0.5);
    // ����ͼ��
    m_render_right_down->SetBackground(0.0,1.0,0.0);
    m_render_right_down->SetViewport(0.5,0.0,1.0,0.5);
    // ����ͼ��
    m_render_left_up->SetBackground(0.0,0.0,1.0);
    m_render_left_up->SetViewport(0.0,0.5,0.5,1.0);
    // ����ͼ��
    m_render_right_up->SetBackground(1.0,1.0,0.0);
    m_render_right_up->SetViewport(0.5,0.5,1.0,1.0);


    vtkSmartPointer<vtkRenderWindow> renWin=vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(m_render_left_down );
    renWin->AddRenderer(m_render_left_up   );
    renWin->AddRenderer(m_render_right_down);
    renWin->AddRenderer(m_render_right_up  );
    renWin->SetSize( 640, 480 );
    renWin->Render();
    renWin->SetWindowName("Viewport");

    vtkSmartPointer<vtkRenderWindowInteractor> interactor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renWin);

    renWin->Render();
    interactor->Initialize();
    interactor->Start();
}

CSplitView::~CSplitView()
{

}

vtkSmartPointer<vtkRenderer> CSplitView::CreateVtkRender()
{
    // ������Դ��������ļ���ͼ��
    //vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
    //vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
    //vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    //vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();

    vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();

    vtkSmartPointer<vtkPolyDataMapper> coneMapper = 	vtkSmartPointer<vtkPolyDataMapper>::New();
    coneMapper->SetInput(cone->GetOutput());

    vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
    coneActor->SetMapper(coneMapper);

    vtkSmartPointer<vtkRenderer> renderer1 = vtkSmartPointer<vtkRenderer>::New();
    renderer1->AddActor(coneActor);

    return renderer1;
}

