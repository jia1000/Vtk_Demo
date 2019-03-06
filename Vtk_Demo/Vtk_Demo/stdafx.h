// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

//////////////////////////////////////////////////////////////////////////
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


#include <vtkImageCanvasSource2D.h>
#include <vtkContourFilter.h>
#include <vtkPolyDataNormals.h>
#include <vtkImageMapToWindowLevelColors.h>
#include <vtkTextMapper.h>
#include <vtkCommand.h>
#include <vtkCallbackCommand.h>


#include <vtkBiDimensionalWidget.h>
#include <vtkBiDimensionalRepresentation2D.h>
#include <vtkImageActor.h>
#include <vtkDistanceWidget.h>
#include <vtkDistanceRepresentation.h>
#include <vtkAngleWidget.h>
#include <vtkAngleRepresentation2D.h>
#include <vtkLeaderActor2D.h>
#include <vtkProperty2D.h>

#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkDataSetMapper.h>
#include <vtkScalarBarActor.h>
#include <vtkScalarBarWidget.h>
#include <vtkTextActor.h>
#include <vtkTextWidget.h>
#include <vtkTextRepresentation.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkBalloonWidget.h>
#include <vtkBalloonRepresentation.h>
#include <vtkCaptionWidget.h>
#include <vtkCaptionRepresentation.h>
#include <vtkCaptionActor2D.h>

// TODO: 在此处引用程序需要的其他头文件
