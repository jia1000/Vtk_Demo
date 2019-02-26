#pragma once
class CDicomSplitView
{
public:
    CDicomSplitView(void);
    ~CDicomSplitView(void);

private:
    vtkSmartPointer<vtkRenderer> CreateVtkRender();

    vtkSmartPointer<vtkRenderer> CreateDicomVtkRender();
    // ������һ����ʾ��ά�߹ǵ�VTK
    vtkSmartPointer<vtkRenderer> CreateDicomRibVtkRender();

    vtkSmartPointer<vtkRenderer> m_render_left_down ;
    vtkSmartPointer<vtkRenderer> m_render_left_up   ;
    vtkSmartPointer<vtkRenderer> m_render_right_down;
    vtkSmartPointer<vtkRenderer> m_render_right_up  ;

    vtkSmartPointer<vtkDICOMImageReader> m_reader;


};

