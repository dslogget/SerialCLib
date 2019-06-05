#ifndef SERIALC_H_INCLUDED
#define SERIALC_H_INCLUDED

#include <windows.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>

void SerialC_Init(HANDLE *hComm, const uint16_t ComID, const DWORD baudrate,
                               const BYTE bits, const BYTE stopBits, const BYTE parity);

void SerialC_Read(HANDLE hComm, uint8_t** arr, DWORD* readSize);

DWORD SerialC_Write(HANDLE hComm, uint8_t* arr, DWORD toSend);

void SerialC_Free(HANDLE *hComm);

#endif // SERIALC_H_INCLUDED
