#include "stdafx.h"

#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>

#include <vtkJPEGReader.h>
#include <vtkTexture.h>

#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>

#include <vtkImageViewer2.h>
#include <vtkMetaImageReader.h>


#include <vtkImageData.h>
#include <vtkMatrix4x4.h>
#include <vtkImageReslice.h>
#include <vtkLookupTable.h>
#include <vtkImageMapToColors.h>
#include <vtkImageActor.h>
#include <vtkInteractorStyleImage.h>

#include <vtkDICOMImageReader.h>



#include <sstream>
#include <vtkTextMapper.h>
#include <vtkObjectFactory.h>
#include <vtkTextProperty.h>
#include <vtkActor2D.h>

void Exmple_2_2()
{
    vtkSmartPointer< vtkJPEGReader > reader = 
        vtkSmartPointer< vtkJPEGReader >::New();
    reader->SetFileName("texture.jpg");

    vtkSmartPointer< vtkTexture > texture = 
        vtkSmartPointer< vtkTexture >::New();
    texture->SetInputConnection( reader->GetOutputPort() );
    texture->InterpolateOn();


    vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    cylinder->SetHeight( 3.0 );
    cylinder->SetRadius( 1.0 );
    cylinder->SetResolution( 10 ); 

    vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cylinderMapper->SetInputConnection( cylinder->GetOutputPort() ); 

    vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper( cylinderMapper );
    cylinderActor->GetProperty()->SetColor(1.0, 1.0, 1.0);
    cylinderActor->SetTexture(texture);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor( cylinderActor );
    renderer->SetBackground( 1.0, 1.0, 1.0 );

    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer( renderer );
    renWin->SetSize( 640, 480 );
    renWin->Render();
    renWin->SetWindowName("RenderCylinder");

    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(style);

    iren->Initialize();
    iren->Start();
}

void Example_2_3_ViewPort()
{
    vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
    vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
    vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();

    vtkSmartPointer<vtkPolyDataMapper> coneMapper = 	vtkSmartPointer<vtkPolyDataMapper>::New();
    coneMapper->SetInput(cone->GetOutput());
    vtkSmartPointer<vtkPolyDataMapper> cubeMapper = 	vtkSmartPointer<vtkPolyDataMapper>::New();
    cubeMapper->SetInput(cube->GetOutput());
    vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = 	vtkSmartPointer<vtkPolyDataMapper>::New();
    cylinderMapper->SetInput(cylinder->GetOutput());
    vtkSmartPointer<vtkPolyDataMapper> sphereMapper = 	vtkSmartPointer<vtkPolyDataMapper>::New();
    sphereMapper->SetInput(sphere->GetOutput());

    vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
    coneActor->SetMapper(coneMapper);
    vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
    cubeActor->SetMapper(cubeMapper);
    vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(cylinderMapper);
    vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
    sphereActor->SetMapper(sphereMapper);


    // ×óÏÂÍ¼Ïñ
    vtkSmartPointer<vtkRenderer> renderer1 = vtkSmartPointer<vtkRenderer>::New();
    renderer1->AddActor(coneActor);
    renderer1->SetBackground(1.0,0.0,0.0);
    renderer1->SetViewport(0.0,0.0,0.5,0.5);
    // ÓÒÏÂÍ¼Ïñ
    vtkSmartPointer<vtkRenderer> renderer2 = vtkSmartPointer<vtkRenderer>::New();
    renderer2->AddActor(cubeActor);
    renderer2->SetBackground(0.0,1.0,0.0);
    renderer2->SetViewport(0.5,0.0,1.0,0.5);
    // ×óÉÏÍ¼Ïñ
    vtkSmartPointer<vtkRenderer> renderer3 = vtkSmartPointer<vtkRenderer>::New();
    renderer3->AddActor(cylinderActor);
    renderer3->SetBackground(0.0,0.0,1.0);
    renderer3->SetViewport(0.0,0.5,0.5,1.0);
    // ÓÒÉÏÍ¼Ïñ
    vtkSmartPointer<vtkRenderer> renderer4 = vtkSmartPointer<vtkRenderer>::New();
    renderer4->AddActor(sphereActor);
    renderer4->SetBackground(1.0,1.0,0.0);
    renderer4->SetViewport(0.5,0.5,1.0,1.0);

    vtkSmartPointer<vtkRenderWindow> renWin=vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(renderer1);
    renWin->AddRenderer(renderer2);
    renWin->AddRenderer(renderer3);
    renWin->AddRenderer(renderer4);
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

void Example_5_2()
{
    vtkSmartPointer<vtkMetaImageReader> reader =
        vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(".\\data\\head.mhd");
    reader->Update();

    vtkSmartPointer<vtkImageViewer2> imageViewer =
        vtkSmartPointer<vtkImageViewer2>::New();
    imageViewer->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    imageViewer->SetupInteractor(renderWindowInteractor);

    imageViewer->SetColorLevel(500);
    imageViewer->SetColorWindow(2000);
    imageViewer->SetSlice(40);
    imageViewer->SetSliceOrientationToXY();
    imageViewer->Render();

    imageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
    imageViewer->SetSize(640, 480);
    imageViewer->GetRenderWindow()->SetWindowName("DisplayImageExample");

    renderWindowInteractor->Start();
}

void Example_5_3()
{
    vtkSmartPointer<vtkMetaImageReader> reader =
        vtkSmartPointer<vtkMetaImageReader>::New();
    reader->SetFileName(".\\data\\brain.mhd");
    reader->Update();

    int extent[6];
    double spacing[3];
    double origin[3];

    reader->GetOutput()->GetExtent(extent);
    reader->GetOutput()->GetSpacing(spacing);
    reader->GetOutput()->GetOrigin(origin);

    double center[3];
    center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
    center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
    center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);

    static double axialElements[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 
    };

    vtkSmartPointer<vtkMatrix4x4> resliceAxes =
        vtkSmartPointer<vtkMatrix4x4>::New();
    resliceAxes->DeepCopy(axialElements);
    resliceAxes->SetElement(0, 3, center[0]);
    resliceAxes->SetElement(1, 3, center[1]);
    resliceAxes->SetElement(2, 3, center[2]);

    vtkSmartPointer<vtkImageReslice> reslice =
        vtkSmartPointer<vtkImageReslice>::New();
    reslice->SetInputConnection(reader->GetOutputPort());
    reslice->SetOutputDimensionality(2);
    reslice->SetResliceAxes(resliceAxes);
    reslice->SetInterpolationModeToLinear();

    vtkSmartPointer<vtkLookupTable> colorTable =
        vtkSmartPointer<vtkLookupTable>::New();
    colorTable->SetRange(0, 1000); 
    colorTable->SetValueRange(0.0, 1.0);
    colorTable->SetSaturationRange(0.0, 0.0);
    colorTable->SetRampToLinear();
    colorTable->Build();

    vtkSmartPointer<vtkImageMapToColors> colorMap =
        vtkSmartPointer<vtkImageMapToColors>::New();
    colorMap->SetLookupTable(colorTable);
    colorMap->SetInputConnection(reslice->GetOutputPort());

    vtkSmartPointer<vtkImageActor> imgActor =
        vtkSmartPointer<vtkImageActor>::New();
    imgActor->SetInput(colorMap->GetOutput());

    vtkSmartPointer<vtkRenderer> renderer =
        vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(imgActor);
    renderer->SetBackground(1.0, 1.0, 1.0);

    vtkSmartPointer<vtkRenderWindow> renderWindow =
        vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->Render();
    renderWindow->SetSize(640, 480);
    renderWindow->SetWindowName("ImageResliceExample");

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> imagestyle =
        vtkSmartPointer<vtkInteractorStyleImage>::New();

    renderWindowInteractor->SetInteractorStyle(imagestyle);
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
}
