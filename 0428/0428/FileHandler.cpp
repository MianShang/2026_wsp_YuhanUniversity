#include "FileHandler.h"

#include<iostream>

BOOL FileHandler::real_file_open(
	WCHAR* path,
	DWORD dAccess,
	DWORD sMode,
	DWORD fAttribute
) {
	m_handle = CreateFile(path,
		dAccess,
		sMode,
		NULL,
		CREATE_ALWAYS,
		fAttribute,
		NULL
	);

	

	///파일 생성 점검
	if (FALSE == m_handle.isSetHandle())
	{
		printf("%s : %d error", __FUNCTION__, GetLastError());
		return FALSE;
	}

	return TRUE;
}

void FileHandler::CloseFile()
{
	m_handle.closeHandle();
}


BOOL FileHandler::FileOpenNormal(WCHAR* path)
{
	return real_file_open(
			path, 
			GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 
			FILE_ATTRIBUTE_NORMAL);
}


///선언부의 메서드를 구현부에 작성하는 방법
///1. 클래스의 선언부를 붙여넣기 한다.
///2. : 삭제, {} 를 넣어서 구현체임을 알림
///3. 누구의 메서드인지 소속을 입력
///  클래스 이름 :: 메서드 이름
/// 4. 내용 작성

BOOL FileHandler::check_rdwr_param(
	void* buf,
	DWORD len,
	DWORD* length 
) 
{
	do
	{
		if (nullptr == buf)
		{
			break;
		}

		if (0 >= len)
		{
			break;
		}

		if (nullptr == length)
		{
			break;
		}

		return TRUE;

	} while (FALSE);

	return FALSE;
	
}

BOOL FileHandler::FileRead(void* buf, DWORD len, DWORD* rlen) 
{
	////1. 그자리에서 바로 return 에러 처리를 할 수 없음
	///return ReadFile(m_handle.getHandle(), buf, len, rlen, NULL);

	///2. 에러처리후 return
	///	1) 전달된 인수가 모두 이상이 없는지 확인
	if(FALSE == check_rdwr_param(buf,len,rlen))
	{
		printf("s : Invailid param received\n", __FUNCTION__);
		return FALSE;
	}
	/// 2) 실제 요청인 파일 읽기를 수행
	if (FALSE == ReadFile(m_handle.getHandle(), buf, len, rlen, NULL)) 
	{
		printf("%s : %d", __FUNCTION__, GetLastError());
		return FALSE;
	}

	return TRUE;
}

BOOL FileHandler::FileWrite(void* buf, DWORD len, DWORD* wlen)
{
	if (FALSE == check_rdwr_param(buf, len, wlen))
	{
		printf("s : Invailid param received\n", __FUNCTION__);
		return FALSE;
	}

	if (FALSE == WriteFile(m_handle.getHandle(), buf, len, wlen, NULL))
	{
		printf("%s : %d", __FUNCTION__, GetLastError());
		return FALSE;
	}

	return TRUE;
}

BOOL FileHandler::FilePointerBegin() 
{
	/// 위치 지정 변수
	LARGE_INTEGER reqPos = {0, };
	/// 위치 변경 전 마지막 위치 값 반환 변수
	LARGE_INTEGER result = { 0, };

	if (FALSE == SetFilePointerEx(m_handle.getHandle(), reqPos, &result, FILE_BEGIN)) 
	{
		printf("%s : %d\b", __FUNCTION__, GetLastError());
		return FALSE;
	}

	return TRUE;
}
/// 파일 포인터를 처음으로 보내면서, 마지막 위치를 얻는 메서드
BOOL FileHandler::FilePointerBegin(LARGE_INTEGER* pos) 
{
	return TRUE;
}
/// 파일 포인터를 처음 위치로붜 지정된(pos) 위치로 보내는 메서드
BOOL FileHandler::FilePointerBegin(LARGE_INTEGER pos) 
{
	/// 위치 지정 변수
	LARGE_INTEGER reqPos = pos;
	/// 위치 변경 전 마지막 위치 값 반환 변수
	LARGE_INTEGER result = { 0, };

	if (FALSE == SetFilePointerEx(m_handle.getHandle(), reqPos, &result, FILE_BEGIN))
	{
		printf("%s : %d\b", __FUNCTION__, GetLastError());
		return FALSE;
	}

	return TRUE;
}

 /*
 BOOL FileHandler::FileOpenReadOnly(void*, DWORD len, DWORD* rilen)
{
	real_file_open(
		path,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		FILE_ATTRIBUTE_NORMAL);
}

BOOL FileHandler::FileOpenWriteOnly(void*, DWORD len, DWORD* wilen)
{
	real_file_open(
		path,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE,
		FILE_ATTRIBUTE_NORMAL);
}
*/
