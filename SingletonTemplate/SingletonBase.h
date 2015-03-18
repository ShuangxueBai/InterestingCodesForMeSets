/**
 *	这里使用一种单例模板来为使用“单例模式”的类提供方便的创建继承
 * 继承这种单例模板，需要实例化一次继承的子类。
 *	之后就可以使用类方法来调用以创建的单例。--by bshx
 */
#ifndef   SINGLETON_BASE_H_
#define  SINGLETON_BASE_H_
#include <assert.h>

/**
 *	SingletonBase
 */
template<class T>
class SingletonBase
{
public:
	SingletonBase(){
		assert(!m_pSingleClass);
		long offset = (long)(T*)(long)1 - (long)(SingletonBase<T>*)(T*)(long)1; //计算继承指针偏移
		m_pSingleClass = (T*)((long)this + offset);
	}
	~SingletonBase(){
		assert(m_pSingleClass);
		m_pSingleClass = NULL;
	}

	/**
	 *	获取单例的指针
	 */
	static T*  GetInstancePointer() 
	{
		return m_pSingleClass;
	}

	/**
	 *	获取单例的引用
	 */
	static T& GetInstanceRefer()
	{
		assert(m_pSingleClass);
		return *m_pSingleClass;
	}
private:
	static T* m_pSingleClass; //!< 单例类
};

template<class T> 
T* SingletonBase<T>::m_pSingleClass = NULL;

#endif






