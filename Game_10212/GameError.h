/*
Copyright (c) 2011 by Chrles Kelly
C++와 DirectX로 게임 엔진을 제작하며 배우는 2D 게임 프로그래밍 참고
*/
#pragma once
#include <string>
#include <exception>
using namespace std;

namespace GameErrorDefine
{
	enum ErrorCode
	{
		FATAL_ERROR = -1,
		Caution = 1,
	};
}

class GameError : public exception
{
public:
	GameError() throw() : errorCode(GameErrorDefine::FATAL_ERROR), message("게임 엔진에 알 수 없는 오류가 발생했습니다.") { };
	GameError(const GameError &e) throw() : exception(e), errorCode(e.GetCode()), message(e.GetErrorMessage()) { }
	GameError(int code, const string &s) throw() : errorCode(code), message(s) { }
	GameError &operator= (const GameError &rhs) throw()
	{
		exception::operator=(rhs);
		this->errorCode = rhs.errorCode;
		this->message = rhs.message;
	}
	virtual ~GameError() throw() { };
	virtual const char* what() const throw() { return this->GetErrorMessage();  }
	const char* GetErrorMessage() const throw() { return message.c_str(); }
	int GetCode() const throw() { return errorCode;  }
private:
	int errorCode;
	string message;
};

