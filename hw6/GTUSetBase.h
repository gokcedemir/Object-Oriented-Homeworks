/*The class GTUSetBase is an abstract class. This is header file.*/

/* 
 * File:   GTUSetBase.h
 * Author: Gökçe Demir
 * Student ID: 141044067
 * CSE241 - HW06
 * Created on December 4, 2017, 1:29 AM
 */

#ifndef GTUSETBASE_H
#define GTUSETBASE_H

#include <iostream>
#include <cstddef>
#include <regex>
using namespace std;  //standart namespace


namespace GTU
{
    template<class T>
    class GTUSetBase
    {
    public:
        typedef int size_type;
        typedef T value_type;

        class GTUIterator   //inner class
        {
        public:
            typedef T& reference;
            typedef T* pointer;
            typedef int size_type;
            typedef T value_type;
                
            GTUIterator();
            reference operator *();
            pointer operator -> ();

            GTUIterator(T* myptr);  //constructor

            /*Copy constructor*/
            GTUIterator(const GTUIterator& other); 

            /*assignment operator for iterator*/
            GTUIterator& operator =(const GTUIterator& rightside);

            /*prefix-increment operator*/
            GTUIterator& operator ++();

            /*postfix increment operator*/
            GTUIterator operator ++ (int ignoreMe);

            /*compare operator.*/
            bool operator == (const GTUIterator& obj1) const;

            /*prefix decrement operator*/
            GTUIterator& operator --();

            /*postfix decrement operator*/
            GTUIterator operator --(int ignoreMe);

        protected:
            pointer ptr;  //equals T* ptr
            pointer mydata;
            pair<T,T> mypair;
        };
        
        GTUSetBase();  //no parameter constructor

        /*true if the container size is 0, false otherwise.*/
        virtual bool empty() const = 0;
        
        //Returns the number of elements in the set container.
        virtual size_type size() const = 0;
        
        /*Returns the maximum number of elements
         *  that the set container can hold.*/
        virtual size_type max_size() const =0;

        /*Insert element,throws exception if the element is already in the set*/
        std::pair<GTUIterator,bool> insert (const value_type& val);
        
        /*Erase element*/
        virtual size_type erase (const value_type& val) =0;
        
        /*Clear all content.*/
        virtual void clear() =0;
        
        /*Get iterator to element.*/
        virtual GTUIterator find (const value_type& val)  = 0;
        
        /*Count elements with a specific value. */
        virtual size_type count (const value_type& val) const = 0;

        /*Return iterator to beginning.*/
        virtual GTUIterator begin() =0 ;
        
        /*Return iterator to end.*/
        virtual GTUIterator end() =0;
        
        void setData(T* data);
        T* getData() const;
        T* getMypoint() const;  //getter for shared_ptr pointeri 
        
    protected:
        T* data;
        size_type sizeOf = 0;    
        T* mypoint ;  //pointer for shared_ptr

    };
}//GTU


#endif /* GTUSETBASE_H */

