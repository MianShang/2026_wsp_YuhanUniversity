// 0331.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <Windows.h>
#include "Handle.h"

int main()
{

    Handle h;
    ///HANDLE 자료형은 OS가 정보를 가지고 있고,
    ///프로그램은 단순히 이름표 형식만 갖는다.
    /// 
    
    h = CreateFile(L"d:\\file1.txt",     //파일의 경로
        GENERIC_READ,           //읽기 쓰기 용도 지정 
        FILE_SHARE_READ,        //파일을 열었을때 다른사용자의 접근 권한 지정
        NULL,                   //보안속성, 지정하지 않으면 현재 나의 권한
        OPEN_EXISTING,          //파일을 열때의 수행할 동작 -> OPEN_EXISTING 있는놈을 열어라
        FILE_ATTRIBUTE_NORMAL,  //파일의 속성 정보 -> 파일을 열때 어떤 속성으로 할건지
        NULL);                  //그 파일이랑 똑같은 파일 만들기 설정


    if (FALSE == h.isSetHandle()) 
    {
        DWORD ret = 0;
        ret = GetLastError();
        printf("파일 개방 오류 : %d \n",ret);
    }
    else 
    {
        printf("파일 개방 성공!!!\n");
    }

    /*
    //오류 체크
    if (NULL == h) 
    {
        printf("파일 개방 오류\n");
    }
    // 오류 체크
    else if(INVALID_HANDLE_VALUE == h)
    {
        printf("파일 개방 오류!!!\n");

    }
    else 
    {
        printf("파일 개방 성공!!!\n");
    }

    */
    ///OS에서 보관하고 있는 내요청에 따라 작성된 정보를 OS가 해제하여 자원을 반환
    //CloseHandle(h);

    h.closeHandle();

    std::cout << "Hello World!\n";
}

