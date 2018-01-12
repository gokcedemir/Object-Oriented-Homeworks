//#include <iostream>
//#include "GTUIterator.h"
//
//using namespace std;
//
//namespace GTU
//{
//    /*no parameter construtor*/
//    template<class T>
//    GTUIterator<T>::GTUIterator() 
//    {
//        /*Body intentionally empty*/
//    }
//    /*constructor*/
//    template<class T>
//    GTUIterator<T>::GTUIterator(T* myptr): ptr(myptr)
//    {
//        /*Body intentionally empty.*/
//    }
//    /*Assignment operator */
//    template<class T>
//    GTUIterator<T>& GTUIterator<T>::operator=(const GTUIterator& rightside)
//    {
//        ptr = rightside.ptr;
//        return *this;
//    }
//    /*Referencing operator*/
//    template<class T>
//    T& GTUIterator<T>::operator*() 
//    {
//        return *ptr;
//    }
//
//    template<class T>
//    T* GTUIterator<T>::operator->()
//    {
//        return ptr;
//    }
//    /*Prefix increment operator*/
//    template<class T>
//    GTUIterator<T>& GTUIterator<T>::operator++() 
//    {
//        ++ptr;
//        return *this;
//    }
//    /*postfix increment operator*/
//    template<class T>
//    GTUIterator<T> GTUIterator<T>::operator++(int ignoreMe)
//    {
//        GTUIterator tmp(*this);  //calling constructor
//        operator ++();
//        return tmp;
//    }
//    /*prefix decrement operator*/
//    template<class T>
//    GTUIterator<T>& GTUIterator<T>::operator--()
//    {
//        --ptr;
//        return *this;
//    }
//    /*postfix decrement operator*/
//    template<class T>
//    GTUIterator<T> GTUIterator<T>::operator--(int ignoreMe)
//    {
//        GTUIterator tmp(*this); //calling constructor
//        operator --();
//        return tmp;
//    }
//    /*compare operator*/
//    template<class T>
//    bool GTUIterator<T>::operator==(const GTUIterator& obj1) const
//    {
//        return (this->ptr == obj1.ptr);
//    }
//} //GTU