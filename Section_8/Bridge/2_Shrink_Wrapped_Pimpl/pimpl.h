// pimpl.h

#include <memory>

/*
* The idea is to have a library class (pimpl) that you wraps the pimpl pattern so it is easier to use later.
* 
* We first define a unique_ptr so we don't have to manually create and delete the pointer. Later, we define a variadic constructor so we can
* pass several arguments, and finally, we define the -> and * operator so the impl pointer can be accessed.
*/

template <typename T> 
class pimpl
{
private:
  std::unique_ptr<T> impl;
public:
  pimpl() : impl{ new T{} } {}
  ~pimpl() {}

  template <typename ...Args> pimpl
    (Args&& ...args) : impl{ new T{std::forward<Args>(args)... } }
    {}

  T* operator->() { return impl.get(); }
  T& operator*() { return *impl.get(); }
};

//template <typename T> 
//class pimpl
//{
//private:
//  std::unique_ptr<T> impl;
//public:
//  pimpl();
//  ~pimpl();
//
//  template <typename ...Args> pimpl
//    (Args&& ...args);
//
//  T* operator->();
//  T& operator*();
//};
//
//template<typename T>
//pimpl<T>::pimpl() : impl{ new T{} }
//{}
//
//template<typename T>
//pimpl<T>::~pimpl()
//{}
//
//template<typename T>
//template<typename... Args>
//pimpl<T>::pimpl(Args &&... args)
//  :impl{ new T{std::forward<Args>(args)... } }
//{}
//
//template<typename T>
//T* pimpl<T>::operator->()
//{
//  return impl.get();
//}
//
//template<typename T>
//T& pimpl<T>::operator*()
//{
//  return *impl.get();
//}



