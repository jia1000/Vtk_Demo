
#include "stdafx.h"

#include "vtkDicomInfoCallback.h"


vtkDicomInfoCallback::vtkDicomInfoCallback(void) : vtkCommand()
{
}


vtkDicomInfoCallback::~vtkDicomInfoCallback(void)
{
}

vtkDicomInfoCallback* vtkDicomInfoCallback::New()
{
    return new vtkDicomInfoCallback;
}

void vtkDicomInfoCallback::Execute(vtkObject* caller, unsigned long eventid, void* callData)
{    
    static int pressCount = 0;
    pressCount++;
    printf("Clicked: %4d\n", pressCount);
}