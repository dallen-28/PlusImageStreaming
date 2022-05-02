#include "DataRepository.h"

DataRepository::DataRepository(std::string configFile)
{
    this->dataCollector = vtkSmartPointer<vtkPlusDataCollector>::New();
	this->trackerChannel = nullptr;
    this->configRootElement = vtkSmartPointer<vtkXMLDataElement>::New();


    this->ReadConfiguration(configFile);
}


void DataRepository::ReadConfiguration(std::string configFile)
{
    this->configFile = configFile;
    LOG_INFO("Connect using configuration file: " << this->configFile);
    this->configRootElement = vtkSmartPointer<vtkXMLDataElement>::Take(vtkXMLUtilities::ReadElementFromFile(this->configFile.c_str()));

    // Read configuration
    if (PlusXmlUtils::ReadDeviceSetConfigurationFromFile(this->configRootElement, this->configFile.c_str()) == PLUS_FAIL)
    {
        LOG_ERROR("Unable to read configuration from file" << configFile.c_str());
        exit;
    }

    vtkPlusConfig::GetInstance()->SetDeviceSetConfigurationData(this->configRootElement);

    if (dataCollector->ReadConfiguration(this->configRootElement) != PLUS_SUCCESS)
    {
        LOG_ERROR("Configuration incorrect for vtkPlusDataCollector.");
        exit;
    }
}

DataRepository::~DataRepository()
{

}


void DataRepository::StartDataCollection()
{
    
    vtkPlusDevice* plusVideoDevice;

    // Get VideoDevice
    if (dataCollector->GetDevice(plusVideoDevice, "VideoDevice") != PLUS_SUCCESS)
    {
        LOG_ERROR("Unable to locate the device with ID = \"VideoDevice\". Check config file.");
        exit(EXIT_FAILURE);
    }

    // For Linux replace line with commented code  
    //this->videoDevice = dynamic_cast<vtkPlusV4L2VideoSource*>(plusVideoDevice);
    this->videoDevice = dynamic_cast<vtkPlusMmfVideoSource*>(plusVideoDevice);


    // Connect to devices
    if (dataCollector->Connect() != PLUS_SUCCESS)
    {
        LOG_ERROR("Failed to connect to devices!");
		exit(EXIT_FAILURE);
    }

    LOG_INFO("Connection Successful");

    if (dataCollector->Start() != PLUS_SUCCESS)
    {
        LOG_ERROR("Failed to start Data collection!");
        exit(EXIT_FAILURE);
    }

    LOG_INFO("Data Collection Started Successfully");

    if (this->videoDevice->GetOutputChannelByName(trackerChannel, "VideoStream") != PLUS_SUCCESS)
    {
        LOG_ERROR("Unable to locate the channel with Id=\"VideoStream\". Check config file.");
        exit(EXIT_FAILURE);
    }
}

void DataRepository::StopDataCollection()
{
	LOG_DEBUG("Stopping Data Collection");

	if (this->dataCollector->Stop() != PLUS_SUCCESS)
	{
		LOG_ERROR("Failed to stop tracking");
		exit(EXIT_FAILURE);
	}
	if (this->dataCollector->Disconnect() != PLUS_SUCCESS)
	{
		LOG_ERROR("Failed to disconnect from devices");
		exit(EXIT_FAILURE);
	}
}

vtkImageData* DataRepository::GetFrames()
{
   
    // Get trackerFrame from trackerChannel
    if (this->trackerChannel->GetTrackedFrame(this->trackerFrame) != PLUS_SUCCESS)
    {
        LOG_DEBUG("Unable to get tracked frame");
    }

    return this->trackerFrame.GetImageData()->GetImage();

}