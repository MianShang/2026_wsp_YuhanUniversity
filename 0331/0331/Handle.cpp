#include "Handle.h"

//default 생성자, 인수 없이 이름만 사용하는 경우
Handle::Handle() 
{
	m_handle = INVALID_HANDLE_VALUE;

};

void Handle::HandleCheck(HANDLE handle__) 
{
	/// 혹시나 개발자가 실수로 전달하는 경우 방지를 위한 점검
	if (NULL == handle__)
		return;
	/// 개발자가 값을 확인하지 않고 전달하는 경우 방지를 위한 점검
	if (INVALID_HANDLE_VALUE == handle__)
		return;
	/// 문제가 없는 handle일경우 대입
	m_handle = handle__;
}

///HANDLE을 초기화 인수로 받는 생성자.
Handle::Handle(HANDLE handle__)
{ 
	HandleCheck(handle__);
	return;
}

/// = (대입 연산자)를 통해 핸들 값을 초기화하는 연산자 오버로딩.
void Handle::operator=(HANDLE handle__) 
{
	HandleCheck(handle__);
	return;
}

///핸들이 정상적인 값을 가지고 있는지 여부를 반환하는 메서드
BOOL Handle::isSetHandle() 
{
	///CheckHandle 중복값 발생
	return (INVALID_HANDLE_VALUE != m_handle) && (NULL != m_handle);

}

HANDLE Handle::getHandle() 
{
	return m_handle;
}

///핸들을 닫고 초기화하는 메서드
void Handle::closeHandle() 
{
	///중복 체크 필요
	CloseHandle(m_handle);
	m_handle = INVALID_HANDLE_VALUE;
}

Handle::~Handle() 
{
	//중복체크 필요
	CloseHandle(m_handle);
}