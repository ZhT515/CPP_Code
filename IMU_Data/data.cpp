#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi

using namespace std;

struct DataFrame
{
    double Lon1 = 0;
    double Lat1 = 0;
    double hMSL1 = 0;
    int yaw = 0;
    int VE1 = 0;
    int VN1 = 0;
    int VU1 = 0;
    int64_t UnixTime = -1;
}outData1;


int main()
{
    int count[8] = { 0 };
    FILE* fp;
    char str[3];
    char Datastr[90][3] = { 0 };
    int data[90] = { 0 };
    int ByteOrder = 2;
    double Lon1, Lat1, hMSL1;
    int yaw, VE1, VN1, VU1;
    int64_t UnixTime = -1;
    int64_t UnixTime2 = -1;
    fp = fopen("C:/Users/Tong/Desktop/0818_1.txt", "r");
    std::string path5 = "C:/GPSDATA0818.txt";
    char* path6 = const_cast<char*>(path5.c_str());
    std::cout << path6 << std::endl;
    FILE* outFile_2 = fopen(path6, "a");
    FILE* fp2;

    while (fscanf(fp, "%s", str) != EOF)
    {
        if (count[0] == 1 && count[1] == 1 && ByteOrder < 90)
        {
            //strcpy(Datastr[ByteOrder], str);
            data[ByteOrder] = stoi(str, 0, 16);
            //printf("num: %d %s ", ByteOrder,str);
            ByteOrder++;
        }
        else if (count[0] == 1 && count[1] == 0 && strcmp("61", str) == 0)
        {
            count[1] = 1;
           // printf("%s ", str);
        }
        else if (strcmp("DA", str) == 0)
        {
            ByteOrder = 2;
            count[0] = 1;
            count[1] = 0;

            //printf("\nTOP:%s ", str);
        }
        else
            printf("error: %s\n", str);



        if (count[0] == 1 && count[1] == 1 && ByteOrder == 89)
        {
            Lon1 = (16777216 * data[44] + 65536 * data[45] + 256 * data[46] + data[47]) * 0.0000001;
            Lat1 = (16777216 * data[48] + 65536 * data[49] + 256 * data[50] + data[51]) * 0.0000001;
            hMSL1 = (65536 * data[52] + 256 * data[53] + data[54]) * 0.01;
            yaw = 256 * data[33] + data[34];
            VE1 = 65536 * data[35] + 256 * data[36] + data[37];
            VN1 = 65536 * data[38] + 256 * data[39] + data[40];
            VU1 = 65536 * data[41] + 256 * data[42] + data[43];
            int TimeBit1 = data[62] & 0x01;
            UnixTime = (4294967296 * TimeBit1 + 16777216 * int64_t(data[63]) + 65536 * int64_t(data[64]) + 256 * int64_t(data[65]) + int64_t(data[66])) * 0.1;
            fprintf(outFile_2, "%.7f,%.7f,%.2f,%d,%d,%d,%d,%x,%x,%x,%x,%x,%I64d\n", \
                Lon1, Lat1, hMSL1, yaw, VE1, VN1, VU1, data[62], data[63], data[64], data[65], data[66], UnixTime);
           // printf("%.7f,%.7f,%.2f,%d,%d,%d,%d,%I64d\n", Lon1, Lat1, hMSL1, yaw, VE1, VN1, VU1, UnixTime);
        }
    }
    fclose(outFile_2);
    fclose(fp);

    return 0;
}
