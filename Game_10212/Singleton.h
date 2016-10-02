#pragma once

template <class T>

class Singleton
{
protected:
	Singleton()
	{

	}

	virtual ~Singleton()
	{

	}

public:
	static T& Get()
	{
		static T instance;
		return instance;
	}
};