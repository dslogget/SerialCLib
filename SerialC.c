#include "SerialC.h"


void SerialC_Init(HANDLE *hComm, const uint16_t ComID, const DWORD baudrate,
                               const BYTE bits, const BYTE stopBits, const BYTE parity){
    if(*hComm == INVALID_HANDLE_VALUE){
        char buf[100];
        sprintf(buf, "\\\\.\\COM%d", ComID);
        *hComm = CreateFileA(buf, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

        if (hComm == INVALID_HANDLE_VALUE){
            MessageBoxA(0, "Port Failed to Open", "DLL Message", MB_OK | MB_ICONINFORMATION);
        }else{
            //MessageBoxA(0, "Port Opened", "DLL Message", MB_OK | MB_ICONINFORMATION);
        }

        DCB dcbSerialParams = { 0 }; // Initializing DCB structure
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
        GetCommState(*hComm, &dcbSerialParams);
        dcbSerialParams.BaudRate = baudrate;  // Setting BaudRate = 9600
        dcbSerialParams.ByteSize = bits;         // Setting ByteSize = 8
        dcbSerialParams.StopBits = stopBits;// Setting StopBits = 1
        dcbSerialParams.Parity   = parity;  // Setting Parity = None
        SetCommState(*hComm, &dcbSerialParams);

        COMMTIMEOUTS timeouts = { 0 };
        timeouts.ReadIntervalTimeout         = 50; // in milliseconds
        timeouts.ReadTotalTimeoutConstant    = 50; // in milliseconds
        timeouts.ReadTotalTimeoutMultiplier  = 10; // in milliseconds
        timeouts.WriteTotalTimeoutConstant   = 50; // in milliseconds
        timeouts.WriteTotalTimeoutMultiplier = 10; // in milliseconds

        SetCommTimeouts(*hComm, &timeouts);
    }


}

void SerialC_Read(HANDLE hComm, uint8_t** arr, DWORD* readSize){
    char byte[1000] = {0};
    ReadFile(hComm, byte, 999, readSize, NULL);
    *arr = malloc(sizeof(char) * (*readSize));
    memcpy(*arr, byte, *readSize);
}


DWORD SerialC_Write(HANDLE hComm, uint8_t* arr, DWORD toSend){
    DWORD bytesWritten = 0;

    WriteFile(hComm, arr, toSend, &bytesWritten, NULL);
    return bytesWritten;
}

void SerialC_Free(HANDLE *hComm){
    CloseHandle(*hComm);
}

