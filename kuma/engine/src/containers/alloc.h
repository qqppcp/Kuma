#pragma once
#include "core/kmemory.h"


template <typename T>  
class MyAllc : public std::allocator<T>  
 {  
 public:  
  
     T* allocate(size_t _Count, const void* _Hint = NULL)  
     {  
         void *rtn = nullptr;  
         rtn = KMemory::allocate(sizeof(T) * _Count, memory_tag::MEMORY_TAG_DARRAY);
         return (T*)rtn;
     }  
  
     void deallocate(T* _Ptr, size_t _Count)  
     {  
         KMemory::free(_Ptr, sizeof(T) * _Count, memory_tag::MEMORY_TAG_DARRAY);
     }  
  
     template<class _Other>  
     struct rebind  
     {   // convert this type to allocator<_Other>  
         typedef MyAllc<_Other> other;  
     };  
  
     MyAllc() throw()   
     {}   
  
     MyAllc(const MyAllc& __a) throw()   
         : std::allocator<T>(__a)   
     {}  
  
     template<typename _Tp1>  
     MyAllc(const MyAllc<_Tp1>&) throw()   
     {}   
  
     ~MyAllc() throw()   
     {}  
 };