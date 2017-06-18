//this is a basic class 
//its inside structure is similiar to cocos2d::Director
//you can see the similiar code in functions: `getInstance` and `autorelease`

#pragma once
using namespace std;
template<class T>
class Singleton {
public:
	static inline T* instance();
	void release();
protected:
	Singleton() {}
	~Singleton() {}
	static T* _instance;
};

template <class T>
inline T*Singleton<T>::instance()
{
	if (NULL == _instance)
	{
		_instance = new T;
	}
	return _instance;
}

template<class T>
void Singleton<T>::release()
{
	if (!_instance)
		return;
	else
	{
		delete _instance;
		_instance = NULL;
	}
}
//what 's this???
#define DECLARE_SINGLETON_MEMBER(_Ty)   \
    template <> _Ty* Singleton<_Ty>::_instance = NULL;
