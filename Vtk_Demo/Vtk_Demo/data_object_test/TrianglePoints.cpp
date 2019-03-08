#include "stdafx.h"
#include "TrianglePoints.h"



void Example_3_2_TrigangePoints(std::string &file_name)
{
    //�����������
    double X[3] = {1.0, 0.0, 0.0};
    double Y[3] = {0.0, 0.0, 1.0};
    double Z[3] = {0.0, 0.0, 0.0};

    //�����������Լ���ÿ���������ϼ���(����)Vertex����Cell
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();

    for (unsigned int i = 0; i < 3 ; i++) {
        //�������ڴ洢���������м������vtkIdType���൱��int��long��
        vtkIdType pid[1];

        //��ÿ����������뵽vtkPoints�У�InsertNextPoint()���ؼ���ĵ�������ţ�
        //����������Ҫʹ�����������������Vertex���͵�Cell
        pid[0] = points->InsertNextPoint(X[i], Y[i], Z[i]);

        //��ÿ��������Ϸֱ𴴽�һ��Vertex��Vertex��Cell���һ��
        vertices->InsertNextCell(1, pid);
    }

    //����vtkPolyData���͵����ݣ�vtkPolyData������vtkPointSet��
    //vtkPointSet��vtkDataSet�����ࡣ
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();

    //ָ�����ݼ��ļ���(��pointsָ��)���Լ����ݼ�������(��verticesָ��)
    polydata->SetPoints(points);
    polydata->SetVerts(vertices);

    //��vtkPolyData���͵�����д�뵽һ��vtk�ļ�������λ���ǹ��̵�ǰĿ¼
    vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetFileName(file_name.c_str());
    writer->SetInput(polydata);
    writer->Write();
}

void Example_3_2_TrigangeGeometryLines(std::string &file_name)
{
    //�������������
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint ( 1.0, 0.0, 0.0 ); //���ص�һ�����ID��0
    points->InsertNextPoint ( 0.0, 0.0, 1.0 ); //���صڶ������ID��1
    points->InsertNextPoint ( 0.0, 0.0, 0.0 ); //���ص��������ID��2
    
    //ÿ���������֮��ֱ𴴽�һ����
    //SetId()�ĵ�һ���������߶εĶ˵�ID���ڶ������������ӵĵ��ID
    vtkSmartPointer<vtkLine> line0 = vtkSmartPointer<vtkLine>::New();
    line0->GetPointIds()->SetId ( 0,0 ); 
    line0->GetPointIds()->SetId ( 1,1 );

    vtkSmartPointer<vtkLine> line1 = vtkSmartPointer<vtkLine>::New();
    line1->GetPointIds()->SetId ( 0,1 );
    line1->GetPointIds()->SetId ( 1,2 );

    vtkSmartPointer<vtkLine> line2 = vtkSmartPointer<vtkLine>::New();
    line2->GetPointIds()->SetId ( 0,2 );
    line2->GetPointIds()->SetId ( 1,0 );    

    //����Cell���飬���ڴ洢���ϴ������߶�
    vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
    lines->InsertNextCell(line0);
    lines->InsertNextCell(line1);
    lines->InsertNextCell(line2);

    //����vtkPolyData���͵����ݣ�vtkPolyData������vtkPointSet
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    
    //������߼��뵽���ݼ��У�ǰ��ָ�����ݼ��ļ��Σ�����ָ��������
    polydata->SetPoints(points);
    polydata->SetLines(lines);
   
    vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
    writer->SetFileName ( file_name.c_str() );
    writer->SetInput ( polydata );
    writer->Write();
}

void Example_3_4_ConceptScalars(std::string &file_name)
{
    //�����㼯���ݣ�������������㡣
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    points->InsertNextPoint(0,0,0);
    points->InsertNextPoint(1,0,0);

    //������������ݡ�
    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);

    //׼����������ݵı���ֵ����������ֵ�ֱ�Ϊ1��2��
    vtkSmartPointer<vtkDoubleArray> weights = vtkSmartPointer<vtkDoubleArray>::New();
    weights->SetNumberOfValues(2);
    weights->SetValue(0, 1);
    weights->SetValue(1, 2);

    //�Ȼ�ȡ��������ݵĵ�����ָ�룬Ȼ�����øõ����ݵı�������ֵ��
    polydata->GetPointData()->SetScalars(weights);

    //���������Ϊ0�ĵ�ı���ֵ��
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
