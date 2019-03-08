#include "stdafx.h"
#include "TrianglePoints.h"



void Example_3_2_TrigangePoints(std::string &file_name)
{
    //创建点的坐标
    double X[3] = {1.0, 0.0, 0.0};
    double Y[3] = {0.0, 0.0, 1.0};
    double Z[3] = {0.0, 0.0, 0.0};

    //创建点数据以及在每个点坐标上加入(顶点)Vertex这种Cell
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();

    for (unsigned int i = 0; i < 3 ; i++) {
        //定义用于存储点索引的中间变量，vtkIdType就相当于int或long型
        vtkIdType pid[1];

        //把每个点坐标加入到vtkPoints中，InsertNextPoint()返回加入的点的索引号，
        //下面我们需要使用这个索引号来创建Vertex类型的Cell
        pid[0] = points->InsertNextPoint(X[i], Y[i], Z[i]);

        //在每个坐标点上分别创建一个Vertex，Vertex是Cell里的一种
        vertices->InsertNextCell(1, pid);
    }

    //创建vtkPolyData类型的数据，vtkPolyData派生自vtkPointSet，
    //vtkPointSet是vtkDataSet的子类。
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

    //指定数据集的几何(由points指定)，以及数据集的拓扑(由vertices指定)
    polydata->SetPoints(points);
    polydata->SetVerts(vertices);

    //将vtkPolyData类型的数据写入到一个vtk文件，保存位置是工程当前目录
    vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetFileName(file_name.c_str());
    writer->SetInput(polydata);
    writer->Write();
}

void Example_3_2_TrigangeGeometryLines(std::string &file_name)
{
    //创建三个坐标点
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint ( 1.0, 0.0, 0.0 ); //返回第一个点的ID：0
    points->InsertNextPoint ( 0.0, 0.0, 1.0 ); //返回第二个点的ID：1
    points->InsertNextPoint ( 0.0, 0.0, 0.0 ); //返回第三个点的ID：2
    
    //每两个坐标点之间分别创建一条线
    //SetId()的第一个参数是线段的端点ID，第二个参数是连接的点的ID
    vtkSmartPointer<vtkLine> line0 = vtkSmartPointer<vtkLine>::New();
    line0->GetPointIds()->SetId ( 0,0 ); 
    line0->GetPointIds()->SetId ( 1,1 );

    vtkSmartPointer<vtkLine> line1 = vtkSmartPointer<vtkLine>::New();
    line1->GetPointIds()->SetId ( 0,1 );
    line1->GetPointIds()->SetId ( 1,2 );

    vtkSmartPointer<vtkLine> line2 = vtkSmartPointer<vtkLine>::New();
    line2->GetPointIds()->SetId ( 0,2 );
    line2->GetPointIds()->SetId ( 1,0 );    

    //创建Cell数组，用于存储以上创建的线段
    vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
    lines->InsertNextCell(line0);
    lines->InsertNextCell(line1);
    lines->InsertNextCell(line2);

    //创建vtkPolyData类型的数据，vtkPolyData派生自vtkPointSet
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    
    //将点和线加入到数据集中，前者指定数据集的几何，后者指定其拓扑
    polydata->SetPoints(points);
    polydata->SetLines(lines);
   
    vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetFileName ( file_name.c_str() );
    writer->SetInput ( polydata );
    writer->Write();
}

void Example_3_4_ConceptScalars(std::string &file_name)
{
    //创建点集数据：包含两个坐标点。
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0,0,0);
    points->InsertNextPoint(1,0,0);

    //创建多边形数据。
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);

    //准备加入点数据的标量值，两个标量值分别为1和2。
    vtkSmartPointer<vtkDoubleArray> weights = vtkSmartPointer<vtkDoubleArray>::New();
    weights->SetNumberOfValues(2);
    weights->SetValue(0, 1);
    weights->SetValue(1, 2);

    //先获取多边形数据的点数据指针，然后设置该点数据的标量属性值。
    polydata->GetPointData()->SetScalars(weights);

    //输出索引号为0的点的标量值。
    double weight = vtkDoubleArray::SafeDownCast(polydata->GetPointData()->GetScalars())->GetValue(0);
    std::cout << "double weight: " << weight << std::endl;
}

CTrianglePoints::CTrianglePoints(std::string file_name)
{
    //Example_3_2_TrigangePoints(file_name);
    //Example_3_2_TrigangeGeometryLines(file_name);
    Example_3_4_ConceptScalars(file_name);
}


CTrianglePoints::~CTrianglePoints(void)
{
}
