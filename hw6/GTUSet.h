/* 
 * File:   GTUSet.h
 * Author: Gökçe Demir
 * Student ID: 141044067
 * CSE241 - HW06
 * Created on December 10, 2017, 11:33 AM
 */

#ifndef GTUSET_H
#define GTUSET_H

#include <iostream>
#include "GTUSetBase.h"

using namespace std;

namespace GTU
{
    template<class T>
    class GTUSet : public GTUSetBase<T>  //derived class
    {
    public:
        
        GTUSet();  //no parameter constructor
        
        void sortedSet(T& mySet);  //sorted array 
        
        /*true if the container size is 0, false otherwise.*/
        virtual bool empty() const ;
        
        //Returns the number of elements in the set container.
        typename GTUSetBase<T>::GTUIterator::size_type size() const ;
        
        /*Returns the maximum number of elements
         *  that the set container can hold.*/
        virtual typename GTUSetBase<T>::GTUIterator::size_type max_size() const ;

        /*Insert element, throws exception if the element is already in the set*/
        std::pair<typename GTUSetBase<T>::GTUIterator,bool>
                insert (const typename GTUSetBase<T>::GTUIterator::value_type& val);
        
        /*Erase element*/
        virtual typename GTUSetBase<T>::GTUIterator::size_type 
        erase (const typename GTUSetBase<T>::GTUIterator::value_type& val);
        
        /*Clear all content.*/
        virtual void clear() ;
        
        /*Get iterator to element.*/
        virtual typename GTUSetBase<T>::GTUIterator 
        find (const typename GTUSetBase<T>::GTUIterator::value_type& val) ;
        
        /*Count elements with a specific value. */
        virtual typename GTUSetBase<T>::GTUIterator::size_type
        count(const typename GTUSetBase<T>::GTUIterator::value_type& val) const;

        /*Return iterator to beginning.*/
        virtual typename GTUSetBase<T>::GTUIterator begin() ;
       
        /*Return iterator to end.*/
        virtual typename GTUSetBase<T>::GTUIterator end();
        
    protected:
        std::shared_ptr<T> myPtr;   //shared_ptr dynamic memory
        const int MAX_SIZE = 1000;  //maximum set size
        int indexOf;  // setin indeksini tutar
        typename GTUSetBase<T>::GTUIterator iter;
        typename GTUSetBase<T>::GTUIterator currentIt;  //basşangıc itereatoru
        
    };
}

#endif /* GTUSET_H */

