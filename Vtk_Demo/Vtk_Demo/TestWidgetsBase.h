#pragma once
class CTestWidgetsBase
{
public:
    CTestWidgetsBase(void);
    ~CTestWidgetsBase(void);

    void TextWidgets_Test();

    void StartRender(vtkSmartPointer<vtkRenderer> renderer, 
        vtkSmartPointer<vtkRenderWindow> renderWindow, 
        vtkSmartPointer<vtkRenderWindowInteractor> interactor);

    vtkSmartPointer<vtkRenderer> CreateRenderer();
    vtkSmartPointer<vtkRenderWindow> CreateRenderWindow(vtkSmartPointer<vtkRenderer> renderer);
    vtkSmartPointer<vtkRenderWindowInteractor> CreateInteractor(vtkSmartPointer<vtkRenderWindow> renderWindow);

    virtual void CreatePipeline(vtkSmartPointer<vtkRenderer> renderer);
    virtual void AddTextActor(vtkSmartPointer<vtkRenderWindowInteractor> interactor);

protected:
    vtkSmartPointer<vtkRenderer> m_renderer;
    vtkSmartPointer<vtkRenderWindow> m_renderWindow;
    vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;

    vtkSmartPointer<vtkTextWidget> textWidget;
};

