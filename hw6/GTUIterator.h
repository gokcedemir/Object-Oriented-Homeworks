///* 
// * File:   GTUIterator.h
// * Author: Gökçe Demir
// * Student ID: 141044067
// * CSE241 - Hw06
// * Created on December 10, 2017, 12:38 AM
// */
//
//#ifndef GTUITERATOR_H
//#define GTUITERATOR_H
//
//#include <iostream>
//
//using namespace std;
//
//namespace GTU
//{
//    template<class T>
//    class GTUIterator
//    {
//    public:
//        
//        typedef T& reference;
//        typedef T* pointer;
//        typedef int size_type;
//        typedef T value_type;
//        
//        GTUIterator();
//        reference operator *();
//        pointer operator -> ();
//        
//        GTUIterator(T* myptr);  //constructor
//        
//        /*Copy constructor*/
//        GTUIterator(const GTUIterator& other); 
//        
//        /*assignment operator for iterator*/
//        GTUIterator& operator =(const GTUIterator& rightside);
//        
//        /*prefix-increment operator*/
//        GTUIterator& operator ++();
//        
//        /*postfix increment operator*/
//        GTUIterator operator ++ (int ignoreMe);
//        
//        /*compare operator.*/
//        bool operator == (const GTUIterator& obj1) const;
//        
//        /*prefix decrement operator*/
//        GTUIterator& operator --();
//        
//        /*postfix decrement operator*/
//        GTUIterator operator --(int ignoreMe);
//        
//    private:
//        pointer ptr;  //equals T* ptr
//    };
//}// GTU
//
//
//#endif /* GTUITERATOR_H */
//
