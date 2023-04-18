#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include "MvCameraControl.h"
#include <string>
#include <iostream>
#include <ctime>
//����ʱ��ı���
//clock_t a, b;

std::string Trigger;//��ȡ�����Ƿ��£��������򴥷�һ��
int num = 1;//������Ƭ�����������ն�����ʾ
BOOL                    m_bThreadState;
BOOL                    m_bStartGrabbing;                     // ch:�Ƿ�ʼץͼ | en:Whether to start grabbing
int                     m_nTriggerMode;                       // ch:����ģʽ | en:Trigger Mode
int                     m_nTriggerSource;                     // ch:����Դ | en:Trigger Source
CRITICAL_SECTION        m_hSaveImageMux[2];
unsigned char*          m_pSaveImageBuf[2];
unsigned int            m_nSaveImageBufSize[2];
MV_FRAME_OUT_INFO_EX    m_stImageInfo[2];

bool g_bExit = false;

// ch:�ȴ��������� | en:Wait for key press
void WaitForKeyPress(void)
{
    while(!_kbhit())
    {
        Sleep(10);
    }
    _getch();
}

bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo)
{
    if (NULL == pstMVDevInfo)
    {
        printf("The Pointer of pstMVDevInfo is NULL!\n");
        return false;
    }
    if (pstMVDevInfo->nTLayerType == MV_GIGE_DEVICE)
    {
        int nIp1 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
        int nIp2 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
        int nIp3 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
        int nIp4 = (pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

        // ch:��ӡ��ǰ���ip���û��Զ������� | en:print current ip and user defined name
        printf("CurrentIp: %d.%d.%d.%d\n" , nIp1, nIp2, nIp3, nIp4);
        printf("UserDefinedName: %s\n\n" , pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName);
    }
    else if (pstMVDevInfo->nTLayerType == MV_USB_DEVICE)
    {
        printf("UserDefinedName: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName);
        printf("Serial Number: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
        printf("Device Number: %d\n\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.nDeviceNumber);
    }
    else
    {
        printf("Not support.\n");
    }

    return true;
}

static  unsigned int __stdcall WorkThread3(void* pUser)
{
    MV_FRAME_OUT stImageInfo = { 0 };
    MV_DISPLAY_FRAME_INFO stDisplayInfo = { 0 };
    int nRet = MV_OK;

    while (m_bStartGrabbing)//1
    {
        nRet = MV_CC_GetImageBuffer(pUser, &stImageInfo, 1000);//ͬMV_CC_GetImageBuffer()һ��
        if (nRet == MV_OK)
        {
            //EnterCriticalSection(&m_hSaveImageMux[1]);
            if (NULL == m_pSaveImageBuf[1] || stImageInfo.stFrameInfo.nFrameLen > m_nSaveImageBufSize[1])
            {
                if (m_pSaveImageBuf[1])
                {
                    free(m_pSaveImageBuf[1]);
                    m_pSaveImageBuf[1] = NULL;
                }

                m_pSaveImageBuf[1] = (unsigned char*)malloc(sizeof(unsigned char) * stImageInfo.stFrameInfo.nFrameLen);
                if (m_pSaveImageBuf[1] == NULL)
                {
                    LeaveCriticalSection(&m_hSaveImageMux[1]);
                    return 0;
                }
                m_nSaveImageBufSize[1] = stImageInfo.stFrameInfo.nFrameLen;
            }
            memcpy(m_pSaveImageBuf[1], stImageInfo.pBufAddr, stImageInfo.stFrameInfo.nFrameLen);
            memcpy(&m_stImageInfo[1], &(stImageInfo.stFrameInfo), sizeof(MV_FRAME_OUT_INFO_EX));
            //LeaveCriticalSection(&m_hSaveImageMux[1]);
            MV_CC_FreeImageBuffer(pUser, &stImageInfo);//ͬMV_CC_FreeImageBuffer()һ��
        }
        else
        {
            if (MV_TRIGGER_MODE_ON == m_nTriggerMode)
            {
                Sleep(5);
            }
        }
    }
    return MV_OK;
}

static  unsigned int __stdcall WorkThread2(void* pUser)
{
    MV_FRAME_OUT stImageInfo = { 0 };
    MV_DISPLAY_FRAME_INFO stDisplayInfo = { 0 };
    int nRet = MV_OK;

    while (m_bStartGrabbing)//1
    {
        nRet = MV_CC_GetImageBuffer(pUser, &stImageInfo, 1000);//ͬMV_CC_GetImageBuffer()һ��
        if (nRet == MV_OK)
        {
            //EnterCriticalSection(&m_hSaveImageMux[0]);
            if (NULL == m_pSaveImageBuf[0] || stImageInfo.stFrameInfo.nFrameLen > m_nSaveImageBufSize[0])
            {
                if (m_pSaveImageBuf[0])
                {
                    free(m_pSaveImageBuf[0]);
                    m_pSaveImageBuf[0] = NULL;
                }

                m_pSaveImageBuf[0] = (unsigned char*)malloc(sizeof(unsigned char) * stImageInfo.stFrameInfo.nFrameLen);
                if (m_pSaveImageBuf[0] == NULL)
                {
                    LeaveCriticalSection(&m_hSaveImageMux[0]);
                    return 0;
                }
                m_nSaveImageBufSize[0] = stImageInfo.stFrameInfo.nFrameLen;
            }
            memcpy(m_pSaveImageBuf[0], stImageInfo.pBufAddr, stImageInfo.stFrameInfo.nFrameLen);
            memcpy(&m_stImageInfo[0], &(stImageInfo.stFrameInfo), sizeof(MV_FRAME_OUT_INFO_EX));
            //LeaveCriticalSection(&m_hSaveImageMux[0]);
            MV_CC_FreeImageBuffer(pUser, &stImageInfo);//ͬMV_CC_FreeImageBuffer()һ��

        }
        else
        {
            if (MV_TRIGGER_MODE_ON == m_nTriggerMode)
            {
                Sleep(5);
            }
        }
    }
    return MV_OK;
}

static  unsigned int __stdcall WorkThread0(void* pUser)
{
    int nRet = MV_OK;
    MV_FRAME_OUT stOutFrame = {0};

    while(true)
    {
        nRet = MV_CC_GetImageBuffer(pUser, &stOutFrame, 1000);
        if (nRet == MV_OK)
        {
            printf("Device0 Get Image Buffer: Width[%d], Height[%d], FrameNum[%d]\n",
                stOutFrame.stFrameInfo.nWidth, stOutFrame.stFrameInfo.nHeight, stOutFrame.stFrameInfo.nFrameNum);

            nRet = MV_CC_FreeImageBuffer(pUser, &stOutFrame);
            if(nRet != MV_OK)
            {
                printf("Free Image Buffer fail! nRet [0x%x]\n", nRet);
            }
        }
        else
        {
            printf("Device0 Get Image fail! nRet [0x%x]\n", nRet);
        }
        if(g_bExit)
        {
            break;
        }
    }

    return 0;
}

static  unsigned int __stdcall WorkThread1(void* pUser)
{
    int nRet = MV_OK;
    MV_FRAME_OUT stOutFrame = { 0 };

    while (true)
    {
        nRet = MV_CC_GetImageBuffer(pUser, &stOutFrame, 1000);
        if (nRet == MV_OK)
        {
            printf("Device1 Get Image Buffer: Width[%d], Height[%d], FrameNum[%d]\n",
                stOutFrame.stFrameInfo.nWidth, stOutFrame.stFrameInfo.nHeight, stOutFrame.stFrameInfo.nFrameNum);

            nRet = MV_CC_FreeImageBuffer(pUser, &stOutFrame);
            if (nRet != MV_OK)
            {
                printf("Free Image Buffer fail! nRet [0x%x]\n", nRet);
            }
        }
        else
        {
            printf("Device1 Get Image fail! nRet [0x%x]\n", nRet);
        }
        if (g_bExit)
        {
            break;
        }
    }

    return 0;
}

int main()
{
    int nRet = MV_OK;
    void* handle[2] = { NULL,NULL };

    do 
    {
        // ch:ö���豸 | en:Enum device
        MV_CC_DEVICE_INFO_LIST stDeviceList;
        memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
        nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
        if (MV_OK != nRet)
        {
            printf("Enum Devices fail! nRet [0x%x]\n", nRet);
            break;
        }

        if (stDeviceList.nDeviceNum > 0)
        {
            for (unsigned int i = 0; i < stDeviceList.nDeviceNum; i++)
            {
                printf("[device %d]:\n", i);
                MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList.pDeviceInfo[i];
                if (NULL == pDeviceInfo)
                {
                    break;
                } 
                PrintDeviceInfo(pDeviceInfo);            
            }  
        } 
        else
        {
            printf("Find No Devices!\n");
            break;
        }

        // ch:ѡ���豸��������� | en:Select device and create handle
        for (int index = 0; index < stDeviceList.nDeviceNum; index++)
        {
            nRet = MV_CC_CreateHandle(&handle[index], stDeviceList.pDeviceInfo[index]);
            if (MV_OK != nRet)
            {
                printf("Create Handle fail! nRet [0x%x]\n", nRet);
                break;
            }
            // ch:���豸 | en:Open device
            nRet = MV_CC_OpenDevice(handle[index]);
            if (MV_OK != nRet)
            {
                printf("Open Device%d fail! nRet [0x%x]\n", index, nRet);
                break;
            }
            else
                printf("Open Device%d success! nRet [0x%x]\n", index, nRet);
        }

        // ch:̽��������Ѱ���С(ֻ��GigE�����Ч) | en:Detection network optimal package size(It only works for the GigE camera)
        for (int index = 0; index < stDeviceList.nDeviceNum; index++)
        {
            if (stDeviceList.pDeviceInfo[index]->nTLayerType == MV_GIGE_DEVICE)
            {
                int nPacketSize = MV_CC_GetOptimalPacketSize(handle[index]);
                if (nPacketSize > 0)
                {
                    nRet = MV_CC_SetIntValue(handle[index], "GevSCPSPacketSize", nPacketSize);
                    if (nRet != MV_OK)
                    {
                        printf("Warning: Device[%d] Set Packet Size fail nRet [0x%x]!", index, nRet);
                    }
                    else
                        printf("Device[%d] Set Packet Size success nRet [0x%x]\n", index, nRet);
                }
                else
                {
                    printf("Warning: Device[%d] Get Packet Size fail nRet [0x%x]!", index, nPacketSize);
                }
            }
        }

        // ch:���ô���ģʽΪon | en:Set trigger mode as on
        for (int index = 0; index < stDeviceList.nDeviceNum; index++)
        {
            nRet = MV_CC_SetEnumValue(handle[index], "TriggerMode", MV_TRIGGER_MODE_ON);
            if (MV_OK != nRet)
            {
                printf("Device[%d] Set Trigger Mode fail! nRet [0x%x]\n", index, nRet);
                break;
            }
            else
                printf("Device[%d] Set Trigger Mode success! nRet [0x%x]\n", index, nRet);
        }
        // ch:���ô���ԴΪ���� | en:Set trigger source as
        for (int index = 0; index < stDeviceList.nDeviceNum; index++)
        {
            nRet = MV_CC_SetEnumValue(handle[index], "TriggerSource", MV_TRIGGER_SOURCE_SOFTWARE);
            //nRet = MV_CC_SetEnumValue(handle[index], "TriggerMode", MV_TRIGGER_MODE_ON);
            if (MV_OK != nRet)
            {
                printf("Device[%d] Set Trigger Source fail! nRet [0x%x]\n", index, nRet);
                break;
            }
            else
                printf("Device[%d] Set Trigger Source success! nRet [0x%x]\n", index, nRet);
        }
        // ch:��������Ϊ�Զ����� | en:Set Gain as Auto Gain
        for (int index = 0; index < stDeviceList.nDeviceNum; index++)
        {
            nRet = MV_CC_SetEnumValue(handle[index], "GainAuto", MV_GAIN_MODE_CONTINUOUS);
            if (MV_OK != nRet)
            {
                printf("Device[%d] Set Auto Gain fail! nRet [0x%x]\n", index, nRet);
                break;
            }
            else
                printf("Device[%d] Set Auto Gain success! nRet [0x%x]\n", index, nRet);
        }
        // ch:�����ع�Ϊ�Զ��ع� | en:Set Exposure as Auto Exposure
        for (int index = 0; index < stDeviceList.nDeviceNum; index++)
        {
            nRet = MV_CC_SetEnumValue(handle[index], "ExposureAuto", MV_EXPOSURE_AUTO_MODE_CONTINUOUS);
            if (MV_OK != nRet)
            {
                printf("Device[%d] Set Auto ExposureAuto fail! nRet [0x%x]\n", index, nRet);
                break;
            }
            else
                printf("Device[%d] Set Auto ExposureAuto success! nRet [0x%x]\n", index, nRet);
        }
        // ch:����֡��Ϊ65 | en:Set Exposure as Auto Exposure
        for (int index = 0; index < stDeviceList.nDeviceNum; index++)
        {
            nRet = MV_CC_SetBoolValue(handle[index], "AcquisitionFrameRateEnable", true);
            if (MV_OK != nRet)
            {
                printf("Device[%d] Set Frame Rate as 65 fail! nRet [0x%x]\n", index, nRet);
                break;
            }
            else
            {
                MV_CC_SetFloatValue(handle[index], "AcquisitionFrameRate", 65);
                printf("Device[%d] Set Frame Rate as 65 success! nRet [0x%x]\n", index, nRet);
            }
        }
        // ch:��ʼȡ�� | en:Start grab image
        for (int index = 0; index < stDeviceList.nDeviceNum; index++)
        {
            memset(&(m_stImageInfo[index]), 0, sizeof(MV_FRAME_OUT_INFO_EX));

            nRet = MV_CC_StartGrabbing(handle[index]);
            if (MV_OK != nRet)
            {
                printf("Start grabbing fail! DevIndex[%d], nRet[%#x]\r\n", index, nRet);
            }
            else
                printf("Start grabbing success! DevIndex[%d], nRet[%#x]\r\n", index, nRet);
            m_bStartGrabbing = TRUE;

            // ch:��ʼ�ɼ�֮��Ŵ���workthread�߳�
            unsigned int nCount = 0;
            /*while (-1 != m_nCurCameraIndex)
            {
                nCount++;
                if (nCount > 50)
                {
                    return;
                }

                Sleep(2);
            }*/
            unsigned int nThreadID = 0;
            //m_nCurCameraIndex = index;
            void* hThreadHandle[2];
            if(index==0)
                hThreadHandle[index] = (void*)_beginthreadex(NULL, 0, WorkThread2, handle[index], 0, &nThreadID);
            else
                hThreadHandle[index] = (void*)_beginthreadex(NULL, 0, WorkThread3, handle[index], 0, &nThreadID);
            if (NULL == hThreadHandle[index])
            {
                printf("Create grab thread fail! DevIndex[%d]\r\n", index);
            }
            else
                printf("Create grab thread success! DevIndex[%d]\r\n", index);
        }
        
        // ch: ����һ�β���ͼ | en: Trigger once and save a image
        /**************************ģ��ߵ��ź�ʹ��**************************/
        //std::cin>>Trigger;
        while(1)
        /*********************************************************************/
        //for (int num = 0; num < 50; num++)//������10����Ƭ
        {
            //Trigger = " ";
            // ch:����һ�� | en: Software trigger once
            for (int index = 0; index < stDeviceList.nDeviceNum; index++)
            {
                /**********************����ʱ����*************************
                b = clock();
                printf("׼������ b = %d\r\n", b);
                a = clock();
                printf("trigger camera index = %d, a = %d\r\n", index, a);
                **********************************************************/
                nRet = MV_CC_SetCommandValue(handle[index], "TriggerSoftware");
                if (MV_OK != nRet)
                {
                    printf("Soft trigger onece fail! DevIndex[%d], nRet[%#x]\r\n", index, nRet);
                }
                else
                    printf("Soft trigger once success! DevIndex[%d], nRet[%#x]\r\n", index, nRet);
            }
            
            Sleep(50);//����Ӳ��ʱ�䣬Ϊ���������ͼ���ݴ浽����Ļ�����

            // ch:����ͼƬ | en: Save Image
            MV_SAVE_IMG_TO_FILE_PARAM stSaveFileParam;
            memset(&stSaveFileParam, 0, sizeof(MV_SAVE_IMG_TO_FILE_PARAM));

            for (int index = 0; index < stDeviceList.nDeviceNum; index++)
            {
                //EnterCriticalSection(&m_hSaveImageMux[index]);
                if (m_pSaveImageBuf[index] == NULL || m_stImageInfo[index].enPixelType == 0)
                {
                    printf("Save Image fail! No data! DevIndex[%d]\r\n", index);
                    LeaveCriticalSection(&m_hSaveImageMux[index]);
                    continue;
                }

                stSaveFileParam.enImageType = MV_Image_Bmp;                     // ch:��Ҫ�����ͼ������ | en:Image format to save
                //stSaveFileParam.enPixelType = PixelType_Gvsp_Mono8;          // ch:�����Ӧ�����ظ�ʽ | en:Camera pixel type
                stSaveFileParam.enPixelType = PixelType_Gvsp_BayerRG8;          // ch:�����Ӧ�����ظ�ʽ | en:Camera pixel type
                stSaveFileParam.nWidth = 1440;                                  // ch:�����Ӧ�Ŀ� | en:Width
                stSaveFileParam.nHeight = 1080;                                 // ch:�����Ӧ�ĸ� | en:Height
                stSaveFileParam.nDataLen = 1555200;
                stSaveFileParam.pData = m_pSaveImageBuf[index];
                stSaveFileParam.iMethodValue = 0;
                // ch:jpgͼ��������ΧΪ(50-99] | en:jpg image nQuality range is (50-99]
                if (MV_Image_Jpeg == stSaveFileParam.enImageType)
                {
                    stSaveFileParam.nQuality = 95;
                    if (index == 0)
                        sprintf_s(stSaveFileParam.pImagePath, 256, "e:/Photos/23_02_27/002/left/image%d_%04d.jpg", index, m_stImageInfo[0].nFrameNum);
                    //sprintf_s(stSaveFileParam.pImagePath, 256, "c:/VisionPhotos/0/image%d_%05d.jpg", index, m_stImageInfo[0].nFrameNum);
                    else if (index == 1)
                        sprintf_s(stSaveFileParam.pImagePath, 256, "e:/Photos//23_02_27/002/right/image%d_%04d.jpg", index, m_stImageInfo[1].nFrameNum);
                    //sprintf_s(stSaveFileParam.pImagePath, 256, "c:/VisionPhotos/1/image%d_%05d.jpg", index, m_stImageInfo[1].nFrameNum);
                }
                // ch: pngͼ��������ΧΪ[0-9] | en: png image nQuality range is [0-9]
                else if (MV_Image_Png == stSaveFileParam.enImageType)
                {
                    stSaveFileParam.nQuality = 9;
                    if (index == 0)
                        sprintf_s(stSaveFileParam.pImagePath, 256, "e:/Photos/23_02_27/001/left/image%d_%04d.png", index, m_stImageInfo[0].nFrameNum);
                    //sprintf_s(stSaveFileParam.pImagePath, 256, "c:/VisionPhotos/0/image%d_%05d.png", index, m_stImageInfo[0].nFrameNum);
                    else if (index == 1)
                        sprintf_s(stSaveFileParam.pImagePath, 256, "e:/Photos/23_02_27/001/right/image%d_%04d.png", index, m_stImageInfo[1].nFrameNum);
                    //sprintf_s(stSaveFileParam.pImagePath, 256, "c:/VisionPhotos/1/image%d_%05d.png", index, m_stImageInfo[1].nFrameNum);
                }

                else if (MV_Image_Bmp == stSaveFileParam.enImageType)
                {
                    if (index == 0)
                        sprintf_s(stSaveFileParam.pImagePath, 256, "c:/006/left/image%d_%04d.bmp", index, m_stImageInfo[0].nFrameNum);
                    //sprintf_s(stSaveFileParam.pImagePath, 256, "c:/VisionPhotos/0/image%d_%05d.bmp", index, m_stImageInfo[0].nFrameNum);
                    else if (index == 1)
                        sprintf_s(stSaveFileParam.pImagePath, 256, "c:/006/right/image%d_%04d.bmp", index, m_stImageInfo[1].nFrameNum);
                    //sprintf_s(stSaveFileParam.pImagePath, 256, "c:/VisionPhotos/1/image%d_%05d.bmp", index, m_stImageInfo[1].nFrameNum);
                }
                int nRet = MV_CC_SaveImageToFile(handle[index], &stSaveFileParam);
                //LeaveCriticalSection(&m_hSaveImageMux[index]);
                
                /**********************����ʱ����*************************
                b = clock();
                printf("�洢��� b = %d\r\n", b);
                a = clock();
                printf("save image index = %d, a = %d\r\n", index, a);
                *********************************************************/
                if (MV_OK != nRet)
                {
                    printf("Save Image fail! DevIndex[%d], nRet[%#x]\r\n", index, nRet);
                }
                else
                    printf("Save Image success! DevIndex[%d], Number[%5d]\r\n", index, num);
            }
                
            /***************************ģ��ߵ��ź�ʹ��*******************************/
            //scanf_s("%c", &Trigger);
            num++;
            //std::cin >> Trigger;
            /**************************************************************************/
            Sleep(10);
        }
        printf("Press a key to stop grabbing.\n");
        WaitForKeyPress();
        g_bExit = true;
        Sleep(1000);
        /***************************�����ɼ���Ĳ���********************************/
        for (int index = 0; index < stDeviceList.nDeviceNum; index++)
        {
            // ch:ֹͣȡ�� | en:Stop grab image
            nRet = MV_CC_StopGrabbing(handle[index]);
            if (MV_OK != nRet)
            {
                printf("Stop Grabbing fail! nRet [0x%x]\n", nRet);
                break;
            }
            // ch:�ر��豸 | Close device
            nRet = MV_CC_CloseDevice(handle[index]);
            if (MV_OK != nRet)
            {
                printf("ClosDevice fail! nRet [0x%x]\n", nRet);
                break;
            }
            // ch:���پ�� | Destroy handle
            nRet = MV_CC_DestroyHandle(handle[index]);
            if (MV_OK != nRet)
            {
                printf("Destroy Handle fail! nRet [0x%x]\n", nRet);
                break;
            }
        }
    } while (0);

    /****************************���پ��***************************/
    if (nRet != MV_OK)
    {
        for (int index = 0; index < 2; index++)
        {
            if (handle[index] != NULL)
            {
                MV_CC_DestroyHandle(handle[index]);
                handle[index] = NULL;
                printf("Destroiy Handle[%d] success", index);
            }
        }
    }

    printf("Press a key to exit.\n");
    WaitForKeyPress();
    
    return 0;
}
