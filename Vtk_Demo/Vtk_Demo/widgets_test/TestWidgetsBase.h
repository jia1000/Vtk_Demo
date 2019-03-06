#pragma once
class CWidgetsBaseTest
{
public:
    CWidgetsBaseTest(void);
    ~CWidgetsBaseTest(void);

    void ShowWidgets_Test();

    virtual vtkSmartPointer<vtkRenderer> CreateRenderer();
    virtual vtkSmartPointer<vtkRenderWindow> CreateRenderWindow(vtkSmartPointer<vtkRenderer> renderer);
    virtual vtkSmartPointer<vtkRenderWindowInteractor> CreateInteractor(vtkSmartPointer<vtkRenderWindow> renderWindow);

    virtual void CreatePipeline(vtkSmartPointer<vtkRenderer> renderer) 
    {
    }
    virtual void AddMyActor(vtkSmartPointer<vtkRenderWindowInteractor> interactor) 
    {
    }
    virtual void StartWidgetsRender(vtkSmartPointer<vtkRenderer> renderer, 
        vtkSmartPointer<vtkRenderWindow> renderWindow, 
        vtkSmartPointer<vtkRenderWindowInteractor> interactor)
    {
    }

protected:
    vtkSmartPointer<vtkRenderer> m_renderer;
    vtkSmartPointer<vtkRenderWindow> m_renderWindow;
    vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;
};

