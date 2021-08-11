#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "tchar.h"
#include <sstream>
#include <chrono>
#include <thread>

HANDLE hCom;

int main()
{
    hCom = CreateFile(_T("COM3"),//COM2��
        GENERIC_READ | GENERIC_WRITE,//�������д
        0,//��ռ��ʽ
        NULL,
        OPEN_EXISTING,//�򿪶����Ǵ���
        0,//ͬ����ʽ
        NULL);
    if (hCom == (HANDLE)-1)
    {
        printf("��COMʧ��!\n");
        return FALSE;
    }
    else
    {
        printf("COM�򿪳ɹ���\n");
    }
    SetupComm(hCom, 20480, 20480);//���뻺����������������Ĵ�С����1024

    COMMTIMEOUTS TimeOuts;//�趨����ʱ    
    TimeOuts.ReadIntervalTimeout = 100;
    TimeOuts.ReadTotalTimeoutMultiplier = 500;
    TimeOuts.ReadTotalTimeoutConstant = 5000;
    TimeOuts.WriteTotalTimeoutMultiplier = 500;//�趨д��ʱ
    TimeOuts.WriteTotalTimeoutConstant = 2000;
    SetCommTimeouts(hCom, &TimeOuts);//���ó�ʱ

    DCB dcb1;
    GetCommState(hCom, &dcb1);
    dcb1.BaudRate = 460800;//������Ϊ9600
    dcb1.ByteSize = 8;//ÿ���ֽ���8λ
    dcb1.Parity = NOPARITY;//����żУ��λ
    dcb1.StopBits = ONE5STOPBITS;//1��ֹͣλ
    dcb1.fParity = FALSE;
    dcb1.fNull = FALSE;
    PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//��ջ�����

    DWORD wCount = 400;//��ȡ���ֽ���
    DWORD wCount1;
    int i = 0;
    unsigned char buf[400];
    if (!ReadFile(hCom, buf, wCount, &wCount1, NULL))
    {
        printf("������ʧ��!");
    }
    if (wCount1 > 0)
    {
        printf("wCount1:%d\n", wCount1);
    }
    printf("�����ڳɹ�!��ȡ����Ϊ:\n");
    for (i = 0; i < wCount1; i++)
    {
        printf("%02X ", buf[i]);
    }


    buf[399] = '*';
    for (int i = 0; buf[i] != '*'; i++)
    {
        if ((buf[i] == 0xDA) && (buf[i + 1] == 0x61))
        {

            unsigned char data[92] = { 0 };
            for (int j = 0; j < 92; j++)
            {
                data[j] = buf[i + j];
            }
            double Lon1, Lat1, hMSL1;
            int yaw, VE1, VN1, VU1;
            int64_t UnixTime = -1;
            int64_t UnixTime2 = -1;
            Lon1 = (16777216 * data[44] + 65536 * data[45] + 256 * data[46] + data[47]) * 0.0000001;
            Lat1 = (16777216 * data[48] + 65536 * data[49] + 256 * data[50] + data[51]) * 0.0000001;
            hMSL1 = (65536 * data[52] + 256 * data[53] + data[54]) * 0.01;
            yaw = 256 * data[33] + data[34];
            VE1 = 65536 * data[35] + 256 * data[36] + data[37];
            VN1 = 65536 * data[38] + 256 * data[39] + data[40];
            VU1 = 65536 * data[41] + 256 * data[42] + data[43];
            int TimeBit1 = data[62] & 0x01;
            UnixTime = (4294967296 * TimeBit1 + 16777216 * int64_t(data[63]) + 65536 * int64_t(data[64]) + 256 * int64_t(data[65]) + int64_t(data[66])) * 0.1;
            UnixTime2 = UnixTime + 1628380800000;       //+ �������ϰ˵��ʱ���
            printf("%.7f,%.7f,%.2f,%d,%d,%d,%d,%I64d,%I64d\n", Lon1, Lat1, hMSL1, yaw, VE1, VN1, VU1, UnixTime, UnixTime2);

            //if (lat_1 == 0 && lng_1 == 0 && lat_2 == 0 && lng_2 == 0) {
            //    lat_1 = Lat1;
            //    lng_1 = Lon1;
            //    lat_2 = Lat1;
            //    lng_2 = Lon1;
            //}
            //else {
            //    lat_2 = Lat1;
            //    lng_2 = Lon1;
            //    num_0++;
            //}
            //printf("%.7f,%.7f,%.7f,%.7f\n", lat_1, lng_1, lat_2, lng_2);
            //double radlon1 = PI * lng_1 / 180.0;
            //double radlat1 = PI * lat_1 / 180.0;
            //double radlon2 = PI * lng_2 / 180.0;
            //double radlat2 = PI * lat_2 / 180.0;
            //double a = fabs(radlat1 - radlat2);
            //double b = fabs(radlon1 - radlon2);
            //double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(radlat1) * cos(radlat2) * pow(sin(b / 2), 2)));
            //s = s * 6371.004 * 1000;
            //if (s > 100) {
            //    for (int ii = 0; ii < 92; ii++)
            //    {
            //        printf("%02X ", data[ii]);
            //    }
            //}
            //printf("2���룺%f \n", s);

            std::string path5 = "D:/NEWDATA/DEP/DATA.txt";
            char* path6 = const_cast<char*>(path5.c_str());
            std::cout << path6 << std::endl;
            FILE* outFile_2 = fopen(path6, "a");

            fprintf(outFile_2, "%.7f,%.7f,%.2f,%d,%d,%d,%d,%d,%x,%x,%x,%x,%x,%I64d,%I64d\n", \
                Lon1, Lat1, hMSL1, yaw, VE1, VN1, VU1, data[62], data[63], data[64], data[65], data[66], UnixTime, UnixTime);
            fclose(outFile_2);

            break;
        }
    }
}