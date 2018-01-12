/* Author: Gökçe Demir
   Sudent ID: 141044067
   CSE241 - HW06
 */

#include "GTUSetBase.h"
#include "GTUSetBase.cpp"
#include "GTUSet.h"
#include <iostream>

using namespace std;

namespace GTU
{
    /*no parameter constructor*/
    template<class T>
    GTUSet<T>::GTUSet()
    {
        indexOf=0;  //set index zero
        GTUSetBase<T>::sizeOf = 0;
        myPtr = std::shared_ptr<T>(new T[MAX_SIZE]); //create shared_pointer dynamic memory
        GTUSetBase<T>::mypoint = myPtr.get(); // returns the raw pointer

        GTUSetBase<T>::data = &(myPtr.get()[0]);  
        currentIt =&(myPtr.get()[0]);  //baslangıc iterratoru
        iter =&(myPtr.get()[0]);
    }
    /*Return iterator to beginning.*/
    template<class T>
    typename GTUSetBase<T>::GTUIterator GTUSet<T>::begin()
    {
        return currentIt;
    }
    /*Return iterator to end.*/
    template<class T>
    typename GTUSetBase<T>::GTUIterator GTUSet<T>::end()
    {
        return  typename GTUSetBase<T>::GTUIterator(GTUSetBase<T>::data
                + GTUSetBase<T>::sizeOf);
    }

    //Returns the number of elements in the set container.
    template<class T>
    typename GTUSetBase<T>::GTUIterator::size_type GTUSet<T>::size() const
    {
        return GTUSetBase<T>::sizeOf;
    }
    /*Returns the maximum number of elements
         *  that the set container can hold.*/
    template<class T>
    typename GTUSetBase<T>::GTUIterator::size_type GTUSet<T>::max_size() const
    {
        return MAX_SIZE;
    }
    /*Insert element, throws exception std::bad_pafram 
         *                      if the element is already in the set*/
    template<class T>
    std::pair<typename GTUSetBase<T>::GTUIterator,bool> GTUSet<T>::insert(const typename GTUSetBase<T>::GTUIterator::value_type& val)
    {
      
        for(int i=0; i< GTUSetBase<T>::sizeOf; ++i)
        {
            if(GTUSetBase<T>::mypoint[i]==val)
            {  //aynı elemandan varsa exception fırlatır
                throw "This value already exists!\n";
            }
        }
        GTUSetBase<T>::mypoint[indexOf] = val;  //insert a value
         ++indexOf;  //indeksi arttırma
        ++GTUSetBase<T>::sizeOf;  //size i arttırma
        T temp;   //temp 
        T tempArr[GTUSetBase<T>::sizeOf];
        
        for (int i = 0; i <= GTUSetBase<T>::sizeOf; i++)
            tempArr[i] = GTUSetBase<T>::mypoint[i];

        for(int i=0;i<GTUSetBase<T>::sizeOf;i++)
	{		
            for(int j=i+1; j<GTUSetBase<T>::sizeOf; j++)
            {
                if(tempArr[i]>tempArr[j])
                {   /*swap islemi  */
                    temp  = tempArr[i];
                    tempArr[i] = tempArr[j];
                    tempArr[j] = temp;
                }
            }
	}
        for(int i = 0; i < GTUSetBase<T>::sizeOf; i++)
            GTUSetBase<T>::mypoint[i] = tempArr[i];
    }
     /*true if the container size is 0, false otherwise.*/
    template<class T>
    bool GTUSet<T>::empty() const  
    { 
        return GTUSetBase<T>::sizeOf == 0;  //eleman yoksa true return eder
    }
     /*Erase element*/
    template<class T>
    typename GTUSetBase<T>::GTUIterator::size_type 
    GTUSet<T>::erase(const typename GTUSetBase<T>::GTUIterator::value_type& val)
    {
        if(GTUSetBase<T>::sizeOf <=0)
            throw "No elements in the set!\n";
        for(int i=0; i<GTUSetBase<T>::sizeOf; i++)
	{
            if(GTUSetBase<T>::mypoint[i] == val)
            {
                for(int j=i; j<(GTUSetBase<T>::sizeOf-1); j++)
                {
                        GTUSetBase<T>::mypoint[j]=GTUSetBase<T>::mypoint[j+1];
                }
                break;
            }
	}
        --GTUSetBase<T>::sizeOf;  //eleman saiyisi azalır erase isleminden sonra
        --indexOf;   //indeks azaltma set icin
    }
     /*Clear all content.*/
    template<class T>
    void GTUSet<T>::clear()
    {
        myPtr.reset(new T);
        GTUSetBase<T>::sizeOf = 0;  // number of elements in set equals zero
    }
    /*Get iterator to element.*/
    template<class T>
    typename GTUSetBase<T>::GTUIterator GTUSet<T>::
    find(const typename GTUSetBase<T>::GTUIterator::value_type& val) 
    {
        for (int i = 0; i < GTUSetBase<T>::sizeOf; i++)
        {
            ++iter;
            if(GTUSetBase<T>::mypoint[i] == val)  //eger deger bulunursa
            {
                return iter;  //iterator objesi
            }
        }
    }
    /*Count elements with a specific value. */
    template<class T>
    typename GTUSetBase<T>::GTUIterator::size_type GTUSet<T>::
    count(const typename GTUSetBase<T>::GTUIterator::value_type& val) const
    {
        int counter;   //aranan eleman sayisi 
        for (int i = 0; i < GTUSetBase<T>::sizeOf; i++)
        {
            if(GTUSetBase<T>::mypoint[i]== val)  //eger eleman sette varsa
                ++counter; 
        }
        return counter;
    }
    
    template<class T>
    void GTUSet<T>::sortedSet(T& mySet)
    {
        T temp;   //temp value
        for(int i=0; i<= GTUSetBase<T>::sizeOf; i++)
        {
            for(int j=0; j<=GTUSetBase<T>::sizeOf-i; j++)
            {
                if(mySet[j]>mySet[j+1])
                {    /*swap işlemi gercekleşir */
                    temp = mySet[j];
                    mySet[j]=mySet[j+1];
                    mySet[j+1]=temp;
                }
            }
        }
    }
}