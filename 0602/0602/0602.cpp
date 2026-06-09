// 0602.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <windows.h>

int main()
{
    /// 파일 개방 -> 파일의 정보(타입, 시간정보)
    HANDLE hFile = CreateFile(L"D:\\test.txt",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );

    /// 오류 체크
    if (INVALID_HANDLE_VALUE == hFile)
    {
        printf("error : %s - %d\n", __FUNCTION__, GetLastError());
        return -9;
    }

    DWORD type = GetFileType(hFile);
    switch(type)
    {
    case FILE_TYPE_DISK:
        printf("Disk Type\n");
        break;
    case FILE_TYPE_PIPE:
        printf("Pipe Type\n");
        break;
    case FILE_TYPE_UNKNOWN:
        printf("Unknown Type\n");
        break;
    default:
        printf("Default Type\n");
        break;
    }

    /// 파일의 시간 정보 획득
    /// FILETIME 구조체 형식으로 시간/날짜 정보가 반환됨.
    /// FILETIME은 기록을 쉽게하기 위해서 작성된 구조체다. -> 직접 사용자가 볼려면 정보변경이 필요하다.
    FILETIME createTime, accessTime, writeTime;
    if (FALSE == GetFileTime(hFile, &createTime, &accessTime, &writeTime))
    {
        printf("error : %s - %d\n", __FUNCTION__, GetLastError());
        CloseHandle(hFile);
        return -9;
    }
    printf("CreateTime : %d - %d\n", createTime.dwLowDateTime, createTime.dwHighDateTime);
    printf("AccessTime : %d - %d\n", accessTime.dwLowDateTime, accessTime.dwHighDateTime);
    printf("WriteTime : %d - %d\n", writeTime.dwLowDateTime, writeTime.dwHighDateTime);

    /// 시간기준은 국제 시간 기준으로 우라나라시간으로 출력할려면 +9 해줘야함
    SYSTEMTIME systime;
    if (FALSE != FileTimeToSystemTime(&createTime, &systime))
    {
        printf("createTime : %d.%d.%d. %d:%d:%d\n", 
            systime.wYear, systime.wMonth, systime.wDay, 
            systime.wHour, systime.wMinute, systime.wSecond);
    }
    if (FALSE != FileTimeToSystemTime(&accessTime, &systime))
    {
        printf("accessTime : %d.%d.%d. %d:%d:%d\n",
            systime.wYear, systime.wMonth, systime.wDay,
            systime.wHour, systime.wMinute, systime.wSecond);
    }
    if (FALSE != FileTimeToSystemTime(&writeTime, &systime))
    {
        printf("writeTime : %d.%d.%d. %d:%d:%d\n",
            systime.wYear, systime.wMonth, systime.wDay,
            systime.wHour, systime.wMinute, systime.wSecond);
    }

    /// 파일의 생성 시간을 변경
    systime.wYear = 2030;
    systime.wMonth = 11;
    systime.wDay = 11;
    if (FALSE != SystemTimeToFileTime(&systime, &createTime))
    {
        /// createTime만 바꿀예정
        if (FALSE == SetFileTime(hFile ,&createTime, NULL, NULL))
        {
            printf("SetFileTIme Error : %d\n", GetLastError());
        }
    }
    

    CloseHandle(hFile);

    std::cout << "Hello World!\n";
}

