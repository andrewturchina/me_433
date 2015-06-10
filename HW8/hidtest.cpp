/*******************************************************
 Windows HID simplification
 Alan Ott
 Signal 11 Software
 8/22/2009
 Copyright 2009
 
 This contents of this file may be used by anyone
 for any reason without any conditions and may be
 used as a starting point for your own applications
 which use HIDAPI.
********************************************************/
#ifdef WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hidapi.h"

#define MAX_STR 255
#define DATA_POINTS 100

int main(int argc, char* argv[])
{
	int res;
	unsigned char buf[65];
	wchar_t wstr[MAX_STR];
	hid_device *handle;

	// Initialize the hidapi library
	res = hid_init();

	// Open the device using the VID, PID,
	// and optionally the Serial number.
	handle = hid_open(0x4d8, 0x3f, NULL);

	// Read the Manufacturer String
	res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	wprintf(L"Manufacturer String: %s\n", wstr);

	// Read the Product String
	res = hid_get_product_string(handle, wstr, MAX_STR);
	wprintf(L"Product String: %s\n", wstr);

	// Read the Serial Number String
	res = hid_get_serial_number_string(handle, wstr, MAX_STR);
	wprintf(L"Serial Number String: (%d) %s\n", wstr[0], wstr);

	// Read Indexed String 1
	res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
	wprintf(L"Indexed String 1: %s\n", wstr);

	wprintf(L"Please enter the row number: ");
	scanf("%s", &buf[1]);
	buf[0] = 0x80;
	res = hid_write(handle,buf,65);



	// Finalize the hidapi library
	res = hid_exit();

	return 0;
}
