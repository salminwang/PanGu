#ifndef __SINGLETON_H__
#define __SINGLETON_H__

namespace PanGu
{

template <class T, const bool IS_THREAD_SINGLETON = false>
class Singleton 
{
public:
    //返回单件句柄
    static inline T* instance()
    {
        T** pPtr = NULL;

        if(IS_THREAD_SINGLETON)
        {
            static __thread  T* ptr = 0;   
            pPtr = &ptr;
        }
        else
        {
            //局部静态变量
            static T* ptr = 0;   
            pPtr = &ptr;
        }

        if (*pPtr == NULL)
        {
            if (((*pPtr) = new T()) == NULL)
            {
                return NULL;
            }
        }

        return const_cast<T*>(*pPtr);
    }
}
}

#endif