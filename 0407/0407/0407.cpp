// 0407.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <Windows.h>

int main()
{
    DWORD error = 0;
    /// 파일 처리 예제
    HANDLE h = INVALID_HANDLE_VALUE;
    h = CreateFile(
                L"d:\\test.txt",
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ | FILE_SHARE_DELETE,
                NULL,
                CREATE_ALWAYS,
                FILE_ATTRIBUTE_NORMAL,
                NULL
                );

    /// 모든 프로그램은 반드시 함수 호출 후에 동작에 대한 결과 확인
    if (INVALID_HANDLE_VALUE == h) 
    {
        /// 항상 바로 직전에 발생한 오류를 숫자 값으로 획득하는 API
        error = GetLastError();
        printf("Error = %d\n", error);
        return -9;
    }

    printf("File Open Succees : %d\n",GetLastError());
    ///getchar();
    /// 기록할 버퍼를 생성
    char buf[128] = "File Create Read Write and etc ...";
    /// 실제 기록한 길이 획득을 위한 변수
    DWORD write_len = 0;
    /// 파일에 내용을 입력하자
    
    ///파일 쓰기
    if (FALSE == WriteFile(h, buf, strlen(buf), &write_len, NULL)) 
    {
        error = GetLastError();
        printf("Write Error : %d\n", error);
        /// 오류 발생으로 더 이상 처리하지 못할때,
        /// 핸들 누수가 발생하는 경우가 매우 많음!!!
        CloseHandle(h);
        return -9;      ///강제 종료
    }

    printf("GLE[ %d ] length[ %d ]\n", GetLastError(), write_len);

    ///버퍼 초기화
    memset(buf, 0x00, 128);

    ///파일 읽기
    if (FALSE == ReadFile(h, buf, 128, &write_len, NULL)) 
    {
        error = GetLastError();
        printf("Read Error : %d\n", error);
        /// 오류 발생으로 더 이상 처리하지 못할때,
        /// 핸들 누수가 발생하는 경우가 매우 많음!!!
        CloseHandle(h);
        return -9;      ///강제 종료
    }
    ///파일이 안읽어진게 보임 이유는 파일포인트가 존재하는데 파일포인터는 썼을때 이동함으로 읽을때 다시 파일 포인터 처음으로 보내줘야 하기 때문
    printf("GLE[ %d ] length[ %d ]\n", GetLastError(), write_len);

    printf("READ : %s\n", buf);

    if (FALSE == CloseHandle(h)) 
    {
        printf("CloseHandle Error : %d", GetLastError());
    }

    /// 단순 예제 : 따라하지 마시오. 참고만 하시오.
    /// 만약 핸들이 닫히지 않았다면, 닫힐때 까지 지속적으로 시도해야 한다.
    //while (!CloseHandle(h)) {}

    std::cout << "Hello World!\n";
}