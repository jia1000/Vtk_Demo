
#pragma  once
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
class CSplitView{
public:
    CSplitView();
   ~CSplitView();
private:
    vtkSmartPointer<vtkRenderer> CreateVtkRender();

    vtkSmartPointer<vtkRenderer> m_render_left_down ;
    vtkSmartPointer<vtkRenderer> m_render_left_up   ;
    vtkSmartPointer<vtkRenderer> m_render_right_down;
    vtkSmartPointer<vtkRenderer> m_render_right_up  ;

};