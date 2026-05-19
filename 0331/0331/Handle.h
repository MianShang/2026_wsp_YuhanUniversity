#pragma once

#include <Windows.h>

/**

**/

class Handle
{
///접근 권한 설정
/// C++은 별도로 설정하지 않으면 private 권한
/// JAVA에서는 별도로 설정하지 않으면 public 권한
private:

	///내부에서 관리하는 실제 핸들 객체
	HANDLE m_handle;
	///내부에서 핸들 값이 정상 값인지 확인하는 메서드
	void HandleCheck(HANDLE);

public :
	//default 생성자, 인수 없이 이름만 사용하는 경우
	Handle();

	///HANDLE을 초기화 인수로 받는 생성자.
	Handle(HANDLE);
	/// = (대입 연산자)를 통해 핸들 값을 초기화하는 연산자 오버로딩.
	void operator=(HANDLE);
	
	///핸들이 정상적인 값을 가지고 있는지 여부를 반환하는 메서드
	BOOL isSetHandle();
	
	HANDLE getHandle();

	///핸들을 닫고 초기화하는 메서드
	void closeHandle();

	~Handle();

};

