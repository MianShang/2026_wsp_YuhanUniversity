// 0324.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
//표준 이름공간
using namespace std;

#define __TESTMODE__

/// 로깅 함수
/// 메시지를 직접 받아서 처리하는 로킹함수
void logFuncMsg(
    const char*         fmt__,
    const char*         file__,
    const char*         func__,
    int                 line__
) 
{
    printf("%s[ %s : %d ] %s\n", file__, func__, line__, fmt__);
}

///파일 오류 메시지는 1000번이 시작 번호
#define FILE_OPEN_ERROR                     1000
#define FILE_PERM_ERROR                     1001

///네트워크 오류 메시지는 2000번이 시작 번호
#define NETWORK_ACCESS_ERROR                2000
#define NETWORK_READ_ERROR                  2001

const char logNetworkMsg[][128] =
{
    "소켓 생성 오류",
    "connection 오류",
};

const char logFileMsg[][128] =
{
    "파일을 열지 못했다 : 파일이 존재하지 않음...",        ///0
    "파일을 열지 못했다 : 파일 권한이 없음...",            ///1
    "파일에 대한 경로가 잘못 되었습니다.",
    "파일을 열지 못했다 : 뭔지 모른다..."                  ///2
};

///번호를 받아서 처리하는 로깅함수
void logFuncNum(
    int                 num__,
    const char*         file__,
    const char*         func__,
    int                 line__
)
{


    ///번호의 유효성 검사
    if ((0 > num__) || (8000 <= num__)) 
    {
        return;
    }

    int cat = num__ / 1000;             ///3004 => 3
    int index = num__ - (cat * 1000);   ///3004 - 3000 => 4

    
    if (1 == cat) 
    {
#ifdef __TESTMODE__
        /// 1번 카테고리에 맞는 오류 메시지
        printf("%s[ %s : %d ] %s\n", file__, func__, line__, logFileMsg[index]);
#else 
        // real - printf();

#endif
    }

    else if (2 == cat) 
    {
        printf("%s[ %s : %d ] %s\n", file__, func__, line__, logNetworkMsg[index]);
    }
   
}



/// #define A B ==> A는 B로 사용된다
/// 메시지를 직접 작성해서 전달하는 최초의 매크로 형태
#define LOGMACROMSG(fmt) logFuncMsg(fmt, __FILE__, __FUNCTION__, __LINE__)
///     A             B
/// LOGMACRO가 받는 인자는 하나인데 logfunc()는 4개를 받는다 어떻게 해결해야할까?
/// 매크로를 사용해서 처리한다 로그쓸때 편함 이렇게 사용하면 컴파일 엔지니어링 당할 수 이씀

///번호를 전달해서 로그를 작성하는 매크로
#define LOGMACRONUM(n) logFuncNum(n, __FILE__, __FUNCTION__, __LINE__)

int main()
{
    int a = 3;

    if(3 == a)
    {
        /// __LINE__ : 항상 현재 라인 번호를 가리키는 매크로 C++부터 적용
        /// __FUNCTION__ : 항상 현재 함수의 이름을 가르키는 포인터
        /// __FILE__ : 현재 위치의 파일 이름을 가리키는 포인터
        //logFunc("a == 3!", __FILE__, __FUNCTION__, __LINE__);
        LOGMACROMSG("a가 3이 되어버렸어...");
        LOGMACRONUM(FILE_PERM_ERROR);
        //printf("%s[ %s ] %d\n", __FILE__, __FUNCTION__, __LINE__);
    }
    cout << "Hello World!\n";
}