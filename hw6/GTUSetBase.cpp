/* Author: Gökçe Demir
   Sudent ID: 141044067
   CSE241 - HW06
 */

#include "GTUSetBase.h"
#include <iostream>

using namespace std;

namespace GTU
{
    /*no parameter constructor for base class*/
    template<class T>
    GTUSetBase<T>::GTUSetBase() 
    {
        /*Body intentionally empty*/
    }
    
    template<class T>
    void GTUSetBase<T>::setData(T* data) {
        this->data = data;
    }
    template<class T>
    T* GTUSetBase<T>::getData() const {
        return data;
    }
    template<class T>
    T* GTUSetBase<T>::getMypoint() const
    {
        return mypoint;
    }

    /*no parameter constructor for GTuIterator class*/
    template<class T>
    GTUSetBase<T>::GTUIterator::GTUIterator()
    {
        /*Body intentionally empty..*/
    }
    
    /*copy constructor for Iterator class*/
    template<class T>
    GTUSetBase<T>::GTUIterator::GTUIterator(const GTUIterator& other):ptr(other.ptr)
    {
        /*body intentionally empty*/
    }
    
    template<class T>
    GTUSetBase<T>::GTUIterator::GTUIterator(T* Myptr): ptr(Myptr)
    {
        /*body intentionally empty*/
    }
    /*compare operator*/
    template<class T>
    bool GTUSetBase<T>::GTUIterator::operator ==(const GTUIterator& obj1) const
    {
        return (this->ptr == obj1.ptr);
    }
    /*assignment operator for iterator class*/
    template<class T>
    typename GTUSetBase<T>::GTUIterator& GTUSetBase<T>::GTUIterator::operator =(const GTUIterator& rightside)
    {
        ptr = rightside.ptr;
        return *this;
    }
    /*Referencing operator*/
    template<class T>
    T& GTUSetBase<T>::GTUIterator::operator*()
    {
        return *ptr;
    }
    /*pointer operator for iterator*/
    template<class T>
    T* GTUSetBase<T>::GTUIterator::operator ->()
    {
        return ptr;
    }
    /*Prefix increment operator*/
    template<class T>
    typename GTUSetBase<T>::GTUIterator& GTUSetBase<T>::GTUIterator::operator ++()
    {
        ++ptr;
        return *this;
    }
    /*postfix increment operator*/
    template<class T>
    typename GTUSetBase<T>::GTUIterator GTUSetBase<T>::GTUIterator::operator ++(int ignoreMe)
    {
        GTUIterator tmp(*this);  //calling constructor
        operator ++();
        return tmp;
    }
    /*prefix decrement operator*/
    template<class T>
    typename GTUSetBase<T>::GTUIterator& GTUSetBase<T>::GTUIterator::operator --()
    {
        --ptr;
        return *this;
    }
    /*postfix decrement operator*/
    template<class T>
    typename GTUSetBase<T>::GTUIterator GTUSetBase<T>::GTUIterator::operator --(int ignoreMe)
    {
        GTUIterator tmp(*this); //calling constructor
        operator --();
        return tmp;
    }

}