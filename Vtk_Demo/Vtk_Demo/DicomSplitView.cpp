#include "stdafx.h"
#include "DicomSplitView.h"

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
CDicomSplitView::CDicomSplitView(void)
{
    m_imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
}


CDicomSplitView::~CDicomSplitView(void)
{
}


vtkSmartPointer<vtkTextMapper> CDicomSplitView::SetLeftDownTextAnonationMapper(vtkSmartPointer<vtkImageViewer2> imageViewer)
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

vtkSmartPointer<vtkTextMapper> CDicomSplitView::SetRightDownTextAnonationMapper(vtkSmartPointer<vtkImageViewer2> imageViewer)
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

void CDicomSplitView::AddLeftDownSliceTextActor(vtkSmartPointer<vtkTextMapper> sliceTextMapper)
{
    vtkSmartPointer<vtkActor2D> sliceTextActor = vtkSmartPointer<vtkActor2D>::New();
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    m_imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
}
void CDicomSplitView::AddRightDownSliceTextActor(vtkSmartPointer<vtkTextMapper> sliceTextMapper)
{
    vtkSmartPointer<vtkActor2D> sliceTextActor = vtkSmartPointer<vtkActor2D>::New();
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(785, 10);

    m_imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
}
void CDicomSplitView::AddLeftUpTextActor(vtkSmartPointer<vtkTextMapper> usageTextMapper)
{
    vtkSmartPointer<vtkActor2D> usageTextActor = vtkSmartPointer<vtkActor2D>::New();
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    m_imageViewer->GetRenderer()->AddActor2D(usageTextActor);
}

void CDicomSplitView::ShowDicomFile(std::string folder)
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

    
    m_imageViewer->GetRenderWindow()->SetSize(800, 600);
    m_imageViewer->SetColorWindow(380);
    m_imageViewer->SetColorLevel(30);

    //////////////////////////////////////////////////////////////////////////
    m_imageViewer->SetSlice(4);
    m_imageViewer->SetSliceOrientationToXY();


    m_imageViewer->Render();
    m_imageViewer->GetRenderer()->ResetCamera();

    renderWindowInteractor->Start();
}