#include <iostream>
#include "DataRepository.h"


using namespace std;

int main()
{
	cout << "Hello World " << endl;


	// Change to path where config file is located
	DataRepository *dataRepository = new DataRepository("C:\\d\\Test\\VostarsImageStreaming\\ConfigFiles\\PlusDeviceSet_Server_WebcamTest.xml");


	dataRepository->StartDataCollection();


	vtkImageData* data;

	while (1)
	{
		data = dataRepository->GetFrames();
	}
	


}