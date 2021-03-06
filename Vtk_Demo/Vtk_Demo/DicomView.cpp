#include "stdafx.h"
#include "DicomView.h"
#include "vtk_command/vtkDicomInfoCallback.h"

class vtkBiDimensionalCallback: public vtkCommand
{
public:
    static	vtkBiDimensionalCallback*  New()
    {
        return new vtkBiDimensionalCallback;
    }

    virtual void Execute(vtkObject* caller, unsigned long, void*)
    {
        vtkBiDimensionalWidget* biDimensionalWidget = reinterpret_cast<vtkBiDimensionalWidget*> (caller);
        vtkBiDimensionalRepresentation2D* representation = static_cast<vtkBiDimensionalRepresentation2D*> (biDimensionalWidget->GetRepresentation());

        double p1[3];
        representation->GetPoint1DisplayPosition(p1);
        double p2[3];
        representation->GetPoint2DisplayPosition(p2);
        double p3[3];
        representation->GetPoint3DisplayPosition(p3);
        double p4[3];
        representation->GetPoint4DisplayPosition(p4);

        //显示四个点的屏幕坐标(px)
        std::cout << "Point: " 
            << "(" << p1[0] << " " << p1[1] << " " << p1[2] << ")" 
            << "(" << p2[0] << " " << p2[1] << " " << p2[2] << ")" 
            << "(" << p3[0] << " " << p3[1] << " " << p3[2] << ")" 
            << "(" << p4[0] << " " << p4[1] << " " << p4[2] << ")" 
            << std::endl;
    }
    vtkBiDimensionalCallback() { }
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class  StatusMessage
{
public:
    static std::string Format(int slice, int maxSlice)
    {
        std::stringstream tmp;
        tmp << "Slice Number " << slice + 1 << "/" << maxSlice + 1;
        return tmp.str();
    }
    static std::string TransferString(int value)
    {
        std::stringstream tmp;
        tmp << value;
        return tmp.str();
    }
    static std::string TransferString(float value)
    {
        std::stringstream tmp;
        tmp << value;
        return tmp.str();
    }

};

class myvtkInteractorStyleImage: public vtkInteractorStyleImage
{
public:
    static myvtkInteractorStyleImage* New();
    vtkTypeMacro(myvtkInteractorStyleImage, vtkInteractorStyleImage);

protected:
    vtkImageViewer2* _ImageViewer;
    vtkTextMapper* _StatusMapper;
    vtkDICOMImageReader* _DicomReader;
    int _Slice;
    int _MinSlice;
    int _MaxSlice;

public:
    void SetImageViewer(vtkImageViewer2* imageViewer) {
        _ImageViewer = imageViewer;
        _MinSlice = imageViewer->GetSliceMin();
        _MaxSlice = imageViewer->GetSliceMax();
        _Slice = _MinSlice;
        cout << "Slice: Min = " << _MinSlice << ", Max = " << _MaxSlice << endl;
    }

    void SetStatusMapper(vtkTextMapper* statusMapper)
    {
        _StatusMapper = statusMapper;
    }
    void SetDicomImageReader(vtkDICOMImageReader* dicomReader)
    {
        _DicomReader = dicomReader;
    }

protected:
    void MoveSliceForward()
    {
        if (_Slice < _MaxSlice)
        {
            _Slice += 1;
            cout << "MoveSliceForward::Slice = " << _Slice << endl;
            _ImageViewer->SetSlice(_Slice);
            std::string msg = StatusMessage::Format(_Slice, _MaxSlice);
            _StatusMapper->SetInput(msg.c_str());
            _ImageViewer->Render();
            float* f = _DicomReader->GetImagePositionPatient();
            //printf("Image Position Patient :%.6f\n", *f);
        }
    }

    void MoveSliceBackward()
    {
        if (_Slice > _MinSlice)
        {
            _Slice -= 1;
            cout << "MoveSliceBackward::Slice = " << _Slice << endl;
            _ImageViewer->SetSlice(_Slice);
            std::string msg = StatusMessage::Format(_Slice, _MaxSlice);
            _StatusMapper->SetInput(msg.c_str());
            _ImageViewer->Render();
        }
    }

    virtual void OnKeyDown()
    {
        std::string key = this->GetInteractor()->GetKeySym();
        if (key.compare("Up") == 0)
            MoveSliceForward();
        else if (key.compare("Down")==0)
        {
            MoveSliceBackward();
        }

        vtkInteractorStyleImage::OnKeyDown();
    }

    virtual void OnMouseWheelForward()
    {
        MoveSliceForward();
    }

    virtual void OnMouseWheelBackward()
    {
        if (_Slice > _MinSlice)
            MoveSliceBackward();
    }
};

vtkStandardNewMacro(myvtkInteractorStyleImage);
//////////////////////////////////////////////////////////////////////////
CDicomView::CDicomView(void)
{
    m_imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
}


CDicomView::~CDicomView(void)
{
}


vtkSmartPointer<vtkTextMapper> CDicomView::SetLeftDownTextAnonationMapper(vtkSmartPointer<vtkImageViewer2> imageViewer)
{
    vtkSmartPointer<vtkTextProperty> sliceTextProp = vtkSmartPointer<vtkTextProperty>::New();
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(20);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkSmartPointer<vtkTextMapper> sliceTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(), imageViewer->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    return sliceTextMapper;
}


vtkSmartPointer<vtkTextMapper> SetLeftUpTextAnonationMapper()
{
    vtkSmartPointer<vtkTextProperty> usageTextProp = vtkSmartPointer<vtkTextProperty>::New();
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkSmartPointer<vtkTextMapper> usageTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    usageTextMapper->SetInput("- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n  mouse button while dragging");
    usageTextMapper->SetTextProperty(usageTextProp);

    return usageTextMapper;
}

vtkSmartPointer<vtkTextMapper> CDicomView::SetRightDownTextAnonationMapper(vtkSmartPointer<vtkImageViewer2> imageViewer)
{
    vtkSmartPointer<vtkTextProperty> sliceTextProp = vtkSmartPointer<vtkTextProperty>::New();
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(10);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToRight();

    vtkSmartPointer<vtkTextMapper> sliceTextMapper = vtkSmartPointer<vtkTextMapper>::New();
    std::string msg = "";
    msg += "PatientName:";
    msg += std::string(m_reader->GetPatientName());
    msg += "\n";
    msg += "StudyID:";
    msg += std::string(m_reader->GetStudyID());
    msg += "\n";
    msg += "ImagePosition:";
    msg += StatusMessage::TransferString(*(m_reader->GetImagePositionPatient()));
    msg += "\n";
    msg += "Width:";
    msg += StatusMessage::TransferString(m_reader->GetWidth());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    return sliceTextMapper;
}

void CDicomView::AddLeftDownSliceTextActor(vtkSmartPointer<vtkTextMapper> sliceTextMapper)
{
    vtkSmartPointer<vtkActor2D> sliceTextActor = vtkSmartPointer<vtkActor2D>::New();
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    m_imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
}
void CDicomView::AddRightDownSliceTextActor(vtkSmartPointer<vtkTextMapper> sliceTextMapper)
{
    vtkSmartPointer<vtkActor2D> sliceTextActor = vtkSmartPointer<vtkActor2D>::New();
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(785, 10);

    m_imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
}
void CDicomView::AddLeftUpTextActor(vtkSmartPointer<vtkTextMapper> usageTextMapper)
{
    vtkSmartPointer<vtkActor2D> usageTextActor = vtkSmartPointer<vtkActor2D>::New();
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    m_imageViewer->GetRenderer()->AddActor2D(usageTextActor);
}

// 事件回调Comand的处理函数
// 第一个参数：obj：是调用事件的对象，本例中，即为interactor
// 第二个参数：eid：所要监听的事件ID
// 第三个参数：是与vtkCallbackCommand实例相关联的数据。可以通过vtkCallbackCommand::SetClientData函数设置
void MyCallbackFunc(vtkObject* obj, unsigned long eid, void* clientdata, void* calldata)
{
    std::string client_data  = *(std::string*)(clientdata);
    //int client_data = *((int*)(clientdata));
    static int pressCount = 0;
    pressCount++;
    printf("Clicked: %4d-%s\n", pressCount, client_data.c_str());;
} 

void CDicomView::ShowDicomFile(std::string folder)
{
    //std::string folder = ".\\data\\slices";
    m_reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    m_reader->SetDirectoryName(folder.c_str());
    m_reader->Update();
    
    m_imageViewer->SetInputConnection(m_reader->GetOutputPort());

    // 创建左下角的切片数量相关注释信息
    vtkSmartPointer<vtkTextMapper> sliceTextMapper = SetLeftDownTextAnonationMapper(m_imageViewer);
    AddLeftDownSliceTextActor(sliceTextMapper);

    // 创建右下角的切片数量相关注释信息
    vtkSmartPointer<vtkTextMapper> sliceTextMapper2 = SetRightDownTextAnonationMapper(m_imageViewer);
    AddRightDownSliceTextActor(sliceTextMapper2);


    // 创建左上角的相关注释信息
    vtkSmartPointer<vtkTextMapper> usageTextMapper = SetLeftUpTextAnonationMapper();

    AddLeftUpTextActor(usageTextMapper);    

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
        vtkSmartPointer<vtkRenderWindowInteractor>::New();

    vtkSmartPointer<myvtkInteractorStyleImage> myInteractorStyle =
        vtkSmartPointer<myvtkInteractorStyleImage>::New();

    myInteractorStyle->SetImageViewer(m_imageViewer);
    myInteractorStyle->SetStatusMapper(sliceTextMapper);
    myInteractorStyle->SetDicomImageReader(m_reader);

    m_imageViewer->SetupInteractor(renderWindowInteractor);
    renderWindowInteractor->SetInteractorStyle(myInteractorStyle);

    // 添加类似于大小径的Widget
    {
	    vtkSmartPointer<vtkBiDimensionalWidget> bidimensionalWidget =
	        vtkSmartPointer<vtkBiDimensionalWidget>::New();
	    bidimensionalWidget->SetInteractor(renderWindowInteractor);
	    //采用默认的图标
	    bidimensionalWidget->CreateDefaultRepresentation();
	    //添加“观察者-命令模式（命令子类方案）”
	    vtkSmartPointer<vtkBiDimensionalCallback> bidiCallback =
	        vtkSmartPointer<vtkBiDimensionalCallback>::New();
	    bidimensionalWidget->AddObserver(vtkCommand::InteractionEvent, bidiCallback);
	    bidimensionalWidget->On();
    }


    // 添加事件回调Command--第一种方式
    //vtkSmartPointer<vtkCallbackCommand> mouseCallback = vtkSmartPointer<vtkCallbackCommand>::New();
    //mouseCallback->SetCallback(MyCallbackFunc);
    //std::string client_data = "haha";
    ////int client_data = 111111;
    //mouseCallback->SetClientData((void*)&client_data);
    //renderWindowInteractor->AddObserver(vtkCommand::LeftButtonPressEvent, mouseCallback);

    // 添加事件回调Command--第二种方式
    vtkSmartPointer<vtkDicomInfoCallback> mouseCallback = vtkSmartPointer<vtkDicomInfoCallback>::New();    
    renderWindowInteractor->AddObserver(vtkCommand::LeftButtonPressEvent, mouseCallback);

    m_imageViewer->GetRenderWindow()->SetSize(800, 600);
    m_imageViewer->SetColorWindow(380);
    m_imageViewer->SetColorLevel(30);

    //////////////////////////////////////////////////////////////////////////
    static int use_orientation = 2;
    if (1 == use_orientation) {
	    m_imageViewer->SetSliceOrientationToXY();	    
    } else if(2 == use_orientation){
        m_imageViewer->SetSliceOrientationToXZ();
    } else if(3 == use_orientation){
        m_imageViewer->SetSliceOrientationToYZ();
    }
    // 主要是设置下slice的range
    myInteractorStyle->SetImageViewer(m_imageViewer);

    m_imageViewer->Render();
    m_imageViewer->GetRenderer()->ResetCamera();

    renderWindowInteractor->Start();
}

