#include "stdafx.h"
#include "DicomSplitView.h"


CDicomSplitView::CDicomSplitView(void)
{
    std::string folder = "./data/slices1";

    m_reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    m_reader->SetDirectoryName(folder.c_str());
    m_reader->Update();

    // 创建一个拆2*2布局的窗口
    m_render_left_down  = CreateDicomVtkRender();
    m_render_left_up    = CreateDicomVtkRender();
    m_render_right_down = CreateDicomVtkRender();//CreateDicomRibVtkRender();
    m_render_right_up   = CreateDicomVtkRender();

    // 左下图像
    m_render_left_down->SetBackground(0.3,0.3,0.3);
    m_render_left_down->SetViewport(0.0,0.0,0.5,0.5);
    // 右下图像
    m_render_right_down->SetBackground(0.4,0.4,0.4);
    m_render_right_down->SetViewport(0.5,0.0,1.0,0.5);
    // 左上图像
    m_render_left_up->SetBackground(0.5,0.5,0.5);
    m_render_left_up->SetViewport(0.0,0.5,0.5,1.0);
    // 右上图像
    m_render_right_up->SetBackground(0.6,0.6,0.6);
    m_render_right_up->SetViewport(0.5,0.5,1.0,1.0);


    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(m_render_left_down );
    renWin->AddRenderer(m_render_left_up   );
    renWin->AddRenderer(m_render_right_down);
    renWin->AddRenderer(m_render_right_up  );
    renWin->SetSize( 800, 600 );
    renWin->Render();
    renWin->SetWindowName("Viewport");

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renWin);

    // 设置交互器的风格为Image，会比默认的3D风格，缺少旋转等功能.
    vtkSmartPointer<vtkInteractorStyleImage> interactorStyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
    interactor->SetInteractorStyle(interactorStyle);


    renWin->Render();
    interactor->Initialize();
    interactor->Start();
}


CDicomSplitView::~CDicomSplitView(void)
{
}

vtkSmartPointer<vtkRenderer> CDicomSplitView::CreateVtkRender()
{
    // 这里可以创建其它的几何图形    
    vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();

    vtkSmartPointer<vtkPolyDataMapper> coneMapper = 	vtkSmartPointer<vtkPolyDataMapper>::New();
    coneMapper->SetInput(cone->GetOutput());

    vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
    coneActor->SetMapper(coneMapper);

    vtkSmartPointer<vtkRenderer> renderer1 = vtkSmartPointer<vtkRenderer>::New();
    renderer1->AddActor(coneActor);

    return renderer1;
}
vtkSmartPointer<vtkRenderer> CDicomSplitView::CreateDicomVtkRender()
{

    vtkSmartPointer<vtkImageMapToWindowLevelColors> WindowLevel = vtkSmartPointer<vtkImageMapToWindowLevelColors>::New();
    WindowLevel->SetInputConnection(m_reader->GetOutputPort());

    WindowLevel->SetWindow(380);
    WindowLevel->SetLevel(30);

    vtkSmartPointer<vtkImageActor> imageActor = vtkSmartPointer<vtkImageActor>::New();
    imageActor->SetInput(WindowLevel->GetOutput());

    vtkSmartPointer<vtkRenderer> renderer1 = vtkSmartPointer<vtkRenderer>::New();
    renderer1->AddActor(imageActor);

    /////////////////添加右下角注释，，但是没有起作用/////////////////////////////////////////////////////////
    //vtkSmartPointer<vtkTextProperty> sliceTextProp = vtkSmartPointer<vtkTextProperty>::New();
    //sliceTextProp->SetFontFam     ilyToCourier();
    //sliceTextProp->SetFontSize(10);
    //sliceTextProp->SetVerticalJustificationToBottom();
    //sliceTextProp->SetJustificationToRight();

    //vtkSmartPointer<vtkTextMapper> sliceTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    //std::string msg = "";
    //msg += "PatientName:";
    //msg += std::string(m_reader->GetPatientName());
    //msg += "\n";
    //msg += "StudyID:";
    //msg += std::string(m_reader->GetStudyID());
    ////msg += "\n";
    ////msg += "ImagePosition:";
    ////msg += std::string(*(m_reader->GetImagePositionPatient()));
    ////msg += "\n";
    ////msg += "Width:";
    ////msg += StatusMessage::TransferString(m_reader->GetWidth());
    //sliceTextMapper->SetInput(msg.c_str());
    //sliceTextMapper->SetTextProperty(sliceTextProp);

    //vtkSmartPointer<vtkActor2D> sliceTextActor = vtkSmartPointer<vtkActor2D>::New();
    //sliceTextActor->SetMapper(sliceTextMapper);
    //sliceTextActor->SetPosition(785, 10);

    //renderer1->AddActor2D(sliceTextActor);
    //////////////////////////////////////////////////////////////////////////

    return renderer1;
}
vtkSmartPointer<vtkRenderer> CDicomSplitView::CreateDicomRibVtkRender()
{
    vtkSmartPointer<vtkDICOMImageReader> v16=vtkSmartPointer<vtkDICOMImageReader>::New();
    v16->SetDataByteOrderToLittleEndian();
    v16->SetDirectoryName(".//data//slices1");// 文件目录path
    //v16->SetDataSpacing(3.2,3.2,1.5);
    v16->Update();


    vtkSmartPointer<vtkContourFilter> skinExtractor=vtkSmartPointer<vtkContourFilter>::New();
    skinExtractor->SetInputConnection(v16->GetOutputPort());
    skinExtractor->SetValue(0,500);

    vtkSmartPointer<vtkPolyDataNormals> skinNormals=vtkSmartPointer<vtkPolyDataNormals>::New();
    skinNormals->SetInputConnection(skinExtractor->GetOutputPort());
    skinNormals->SetFeatureAngle(60.0);

    vtkSmartPointer<vtkPolyDataMapper> coneMapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    coneMapper->SetInputConnection(skinNormals->GetOutputPort());

    vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
    coneActor->SetMapper(coneMapper);

    vtkSmartPointer<vtkRenderer> renderer1 = vtkSmartPointer<vtkRenderer>::New();
    renderer1->AddActor(coneActor);

    return renderer1;
}