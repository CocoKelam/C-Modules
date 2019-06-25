#ifndef _SINGLETON_H
#define _SINGLETON_H
#include <mutex>

namespace  coco
{

	template <class T>
	class Singleton
	{
	public:
		~Singleton();
		template<class... Args>
		static T* GetInstance(Args... args);

	protected:
		Singleton() {};
		Singleton& operator=(const Singleton&) {}
		Singleton(const Singleton&) {};

	private:
		static  T*  m_pInstance;
		static std::mutex m_Mtx;
	};

	template <class T>
	Singleton<T>::~Singleton()
	{
		std::lock_guard<std::mutex> lk(m_Mtx);
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	template<class T>
	template<class ...Args>
	T* Singleton<T>::GetInstance(Args ...args)
	{
		if (m_pInstance == nullptr)
		{
			std::lock_guard<std::mutex> lk(m_Mtx);
			if (m_pInstance == nullptr)
			{
				m_pInstance = new T(args...);
			}
		}

		return m_pInstance;
	}

	template <class T>
	T* Singleton<T>::m_pInstance = nullptr;

	template <class T>
	std::mutex Singleton<T>::m_Mtx;

}
#endif