// LEGO Robot.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
using namespace std;

// NXT++ 0.6
#include "nxtpp_07\include\NXT++.h"
#pragma comment (lib, "nxtpp_07/lib/fantom.lib" )

int main()
{

	printf("Searching for NXT devices... (please wait) \n\n");

	// Get list of NXT Devices
	// connected via Bluetooth or USB
	//
	// Note: This will only find Bluetooth devices that have
	// been paired using the Windows BT Control Panel.
	//
	std::vector<std::vector<std::string> > devicelist;
	devicelist = Comm::ListNXTDevices(true);
	// false = only USB devices will be listed.
	// true = list Bluetooth and USB devices.

	printf("Search complete! \n\n");

	// Iterate through NXT device list
	// and output Device Name and
	// MAC Address to console.
	for (unsigned int i = 0; i < devicelist.size(); i++)
	{
		cout << "NXT Device " << i << "   Name: " << devicelist[i][0] << "   MAC Address: " << devicelist[i][1] << endl;
	}
	cout << "\n\n\n" << endl;


	// Un-comment this to connect to an NXT Device

	Comm::NXTComm comm1;

	// Try to connect to specific NXT Device
	//
	// The string name should be the Device Name
	// or MAC Address without colon separators.
	//
	if ( NXT::OpenNXTDevice(&comm1, "GoGo", false) )
	// false = only USB devices will be listed.
	// true = list Bluetooth and USB devices.
	{
	printf( "\nConnected to brick... \n" );

	// Get NXT device information
	double protocol = NXT::GetProtocolVersion(&comm1);
	double version = NXT::GetFirmwareVersion(&comm1);
	int battery = NXT::BatteryLevel(&comm1);
	string name = NXT::GetName(&comm1);

	// Output information to console
	printf( "Protocol version: %f \n", protocol ); // e.g. 1.124000 or
	printf( "Firmware version: %f \n", version ); // e.g. 1.280000 or 1.310000
	printf( "Battery Level: %i \n", battery ); //e.g.  8198, or 6674 when battery low warning
	printf( "Name: %s \n", name.data() ); // NXT device name

	while (true)
	{
		NXT::Motor::SetForward(&comm1, OUT_A, 100);
		Wait(1000);
		NXT::Motor::Stop(&comm1, OUT_A, true);
		Wait(1000);
		NXT::Motor::SetReverse(&comm1, OUT_A, 100);
		Wait(1000);
		NXT::Motor::Stop(&comm1, OUT_A, true);
		Wait(1000);
	}
	
	//NXT::Motor::GoTo(&comm1, OUT_A, 100, 55, true);
	//Wait(1000);
	//NXT::PlayTone(&comm1, 300, 500); // Play high tone from NXT
	//Wait(500);
	//NXT::PlayTone(&comm1, 800, 500);
	//NXT::Motor::GoTo(&comm1, OUT_A, 50, 85, true); //Go forward with motor on port 1 with 100 power
	//Wait(1000);
	//NXT::Motor::GoTo(&comm1, OUT_A, 50, 55, true);
	//Wait(1000);
	//NXT::Motor::GoTo(&comm1, OUT_A, 50, 25, true); //Go forward with motor on port 1 with 100 power
	//Wait(1000);
	//NXT::Motor::GoTo(&comm1, OUT_A, 50, 55, true);
	}


	/*
	// Un-comment this to connect to a 2nd NXT Device

	Comm::NXTComm comm2;

	// This will establish a connection with a 2nd NXT device
	if ( NXT::OpenNXTDevice(&comm2, "NXT3", true) )
	{
	printf( "\nConnected to brick... \n" );

	double protocol = NXT::GetProtocolVersion(&comm2);
	double version = NXT::GetFirmwareVersion(&comm2);
	int battery = NXT::BatteryLevel(&comm2);
	string name = NXT::GetName(&comm2);

	printf( "Protocol version: %f \n", protocol );
	printf( "Firmware version: %f \n", version );
	printf( "Battery Level: %i \n", battery );
	printf( "Name: %s \n", name.c_str() );

	NXT::PlayTone  ( &comm2, 500, 100 ); // Play low tone from NXT
	}

	*/


	/*
	// Un-comment this to change NXT Device Name
	//
	// The safest is way is to connect one NXT via USB,
	// and this code will set the Device Name for the
	// first device that is found.

	Comm::NXTComm comm;

	// Connect to first available NXT Device via USB
	if( NXT::Open(&comm) )
	{
	printf( "\nConnected to brick... \n" );

	// Get NXT device information
	double version = NXT::GetFirmwareVersion(&comm);
	string name = NXT::GetName(&comm);

	// Output information to console
	printf( "Current Device Name is: %s \n", name.c_str() );
	printf( "Firmware version: %f \n", version );

	printf( "\nSetting new Device Name... \n" );

	// Change Device Name
	char *newname;
	newname = "NXT3";
	NXT::SetName(&comm, newname);

	name = NXT::GetName(&comm);
	printf( "New Device Name is: %s \n", name.c_str() );

	}

	*/


	
	// Tidy-up and close connect to NXT Device
	NXT::Close(&comm1); //close the NXT

	int t;
	cin >> t;

	return 0;
}

