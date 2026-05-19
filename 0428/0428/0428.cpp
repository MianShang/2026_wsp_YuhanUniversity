#include <iostream>
#include <windows.h>
#include "FileHandler.h"

int main()
{

    //파일 처리 객체 생성
    FileHandler fh;
    WCHAR filePath[] = L"test.txt";
    if(FALSE == fh.FileOpenNormal(filePath))
    {
        printf("파일 개방 실패\n");
        return -9;
    }

#define BUFFER_LEN 64
    ///읽기/쓰기....
    char buf[BUFFER_LEN] = { 0, };
    DWORD reqLen = 0;       ///읽기/쓰기 요청 길이
    DWORD reqResult = 0;    ///읽기/쓰기 실제 길이
    LARGE_INTEGER pos = { 0, };

    pos.QuadPart = 50;
    /// 파일 포인터를 50정도 offset 위치로 이동
    if (FALSE == fh.FilePointerBegin(pos)) 
    {
        return -9;
    }
    
    /// 파일의 내용을 기록 ==> 기록후 마지막위치로 이동
    memcpy(buf, "wikim", strlen("wikim"));
    ///길이 값을 sizeof()로 전달하면 , 전체 메모리 할당 크기가 전달
    reqLen = strlen(buf); ///들어가있는 buf에 길이만 전달 하는 방법
    if(FALSE == fh.FileWrite(buf, reqLen, &reqResult))
    {
        return -9;
    }

    ///2번째 기록
    /// 파일 포인터를 100 위치로 보낸다.
    pos.QuadPart = 100;
    memcpy(buf, "asdfasdf", strlen("asdfasdf"));
    if(FALSE == fh.FilePointerBegin(pos))
    {
        return -9;
    }
    if (FALSE == fh.FileWrite(buf, strlen(buf), &reqResult))
    {
        return -9;
    }

    /// 파일 포인터를 처음 위치로  보낸다.
    if (FALSE == fh.FilePointerBegin())
    {
        return -9;
    }

    ///버퍼 초기화
    memset(buf, 0x00, BUFFER_LEN);

    /// 기록한 내용을 다시 읽어서 확인
    if (FALSE == fh.FileRead(buf, reqLen, &reqResult)) 
    {
        return -9;
    }

    printf("READ : %s\n", buf);

    ///닫기
    fh.CloseFile();
    std::cout << "Hello World!\n";

}

