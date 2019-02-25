// Vtk_Demo.cpp : 定义控制台应用程序的入口点。
//

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
int _tmain(int argc, _TCHAR* argv[])
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
	return 0;
}

