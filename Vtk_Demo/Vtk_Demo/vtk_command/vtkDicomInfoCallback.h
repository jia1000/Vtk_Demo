#pragma once
class vtkDicomInfoCallback : public vtkCommand
{
public:
    vtkDicomInfoCallback(void);
    ~vtkDicomInfoCallback(void);

    static vtkDicomInfoCallback* New();

    virtual void Execute(vtkObject* caller, unsigned long eventid, void* callData);

};

