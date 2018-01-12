/* 
 * File:   GTUMap.h
 * Author: Gökçe Demir
 * Student Id: 141044067
 * CSE241 - HW06
 * Created on December 9, 2017, 12:46 AM
 */

#ifndef GTUMAP_H
#define GTUMAP_H
#include "GTUSet.h"
#include "GTUSetBase.h"
#include <iostream>
#include <utility>

using namespace std;

namespace GTU
{
    template<class K, class V>
    class GTUMap : public GTUSet< std::pair<K,V> >
    {
    public:
        GTUMap();  //no parameter constructor
        /*f k matches the key of an element in the set,
         *  the function returns a reference to its mapped value.*/
        V& operator[] (const K& k);
        
        std::pair<typename GTUSetBase<K>::GTUIterator,bool>
                insert (pair<K,V> val);

        /*Get iterator to element.*/
        typename GTUSetBase<K>::GTUIterator 
        find (K key)  ;
        
        /*Erase element*/
        typename GTUSetBase<K>::GTUIterator::size_type erase(K key);

        
        private:
            int index;   //mapin indeksi
            int theSize;
            std::shared_ptr< pair<K,V> > sharedPtr;   //shared_ptr dynamic memory
            const int MAX_SIZE = 1000;  //maximum set size
            pair<K,V>* shrpoint ;  //pointer for shared_ptr
        
    };
}


#endif /* GTUMAP */

