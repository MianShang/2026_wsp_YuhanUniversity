// 0519_search.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <windows.h>

int main()
{
    /// 파일/디렉터리 정보 획득을 위한 구조체

    /*
    * typedef struct _WIN32_FIND_DATAW {
    DWORD dwFileAttributes;                                             /// 속성 정보
    FILETIME ftCreationTime;                                            /// 생성 일자 시간 정보
    FILETIME ftLastAccessTime;                                          /// 마지막 접근 시간
    FILETIME ftLastWriteTime;                                           /// 마지막 수정 시간
    DWORD nFileSizeHigh;                                                /// 파일 크기의 상위 32bit
    DWORD nFileSizeLow;                                                 /// 파일 크기의 하위 32bit
    DWORD dwReserved0;                                                  /// 나중에 추가될 수 있는
    DWORD dwReserved1;                                                  /// 예약된/준비된 정보
    _Field_z_ WCHAR  cFileName[ MAX_PATH ];                             /// 파일 이름
    _Field_z_ WCHAR  cAlternateFileName[ 14 ];                          /// 축약된 파일 이름
                            /// 8 + 1(.) + 3 + NULL*2
    } WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;        /// 
    */
    WIN32_FIND_DATA ffd;
    /// 파일 탐색을 위한 경로와 핸들을 갖는 핸들 선언
    HANDLE hFind = INVALID_HANDLE_VALUE;

    /// 첫번째 파일 반환 요청 API => HANDLE이 반환
    hFind = FindFirstFile(L"D:\\VM\\4grade chapture\\*", &ffd);
    /// 오류 체크
    if (INVALID_HANDLE_VALUE == hFind) 
    {
        printf("Find First File Error : %d\n", GetLastError());
        return -9;
    }


    do 
    {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            printf("DR : %ws <- %ws\n", ffd.cFileName, ffd.cAlternateFileName);
        }
        else 
        {
            printf("Object : %ws <- %ws\n", ffd.cFileName, ffd.cAlternateFileName);
        }

    } while (0 != FindNextFile(hFind, &ffd));

    FindClose(hFind);

    std::cout << "Hello World!\n";
}

