#pragma once


// StdLib includes
#include <stdio.h>
#include <stdlib.h>

// Plus includes
#include <vtkPlusDevice.h>
#include <vtkIGSIOTransformRepository.h>
#include <igsioTrackedFrame.h>
#include <vtkPlusDataCollector.h>
#include <vtkPlusMmfVideoSource.h>
#include <vtkPlusChannel.h>

// For Linux umcomment below and comment out line 13 (vtkPlusMmfVideoSource.h)
//#include <V4L2/vtkPlusV4L2VideoSource.h>

// VTK includes
#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>
#include <vtkXMLDataElement.h>
#include <vtkXMLDataParser.h>
#include <vtkTransform.h>



class DataRepository
{

public:

    DataRepository(std::string);
    ~DataRepository();

    void StartDataCollection();
	void StopDataCollection();
    vtkImageData* GetFrames();
    void ReadConfiguration(std::string);


private:


    // Config File Name 
    std::string                                         configFile;

    // Config root element 
    vtkSmartPointer<vtkXMLDataElement>                  configRootElement;

    vtkSmartPointer<vtkPlusMmfVideoSource>				videoDevice;

    vtkSmartPointer<vtkPlusVirtualMixer>                mixerDevice;

    // Tracker Related Objects 
    vtkSmartPointer<vtkPlusDataCollector>               dataCollector;
    vtkPlusChannel                                      *trackerChannel;
    igsioTrackedFrame                                   trackerFrame;
       
};