#include <iostream>
#include "GTUMap.h"
#include <utility>
#include <string>

using namespace std;

namespace GTU
{
    template<class K, class V>
    GTUMap<K,V>::GTUMap()
    {
        index =0 ;  //set index zero
        theSize = 0;
        sharedPtr = std::shared_ptr<std::pair<K,V> >(new std::pair<K,V>[MAX_SIZE]); //create shared_pointer dynamic memory
        shrpoint = sharedPtr.get(); // returns the raw pointer

        GTUSetBase<std::pair<K,V>>::data = &(sharedPtr.get()[0]); 
        
    }
    
    template<class K, class V>
    V& GTUMap<K,V>::operator [](const K& k)
    {
        for(int i=0; i< theSize; ++i)
        {
            if(shrpoint[i].first == k)
            {
                return shrpoint[i].second;
            }
        }
    }
    
    /*Get iterator to element.*/
    template<class K, class V>
    typename GTUSetBase<K>::GTUIterator GTUMap<K,V>::find(K key) 
    {
        typename GTUSetBase<K>::GTUIterator myit;
        for(int i=0; i<theSize; ++i)
        {
            if(shrpoint[i].first == key)
            {
                myit = &i;
                return myit;
            }
        }
    }
    
    template<class K, class V>
    std::pair<typename GTUSetBase<K>::GTUIterator,bool>
    GTUMap<K,V>::insert(pair<K,V>  val)
    {
        
        for(int i=0; i<theSize; ++i)
        {
            if(shrpoint[i].first == val.first)
            {  
                //aynı elemandan varsa exception fırlatır
                throw "This value already exists!\n";
            }
        }
        shrpoint[index]= val;  //insert a value
        
        ++index;  //indeksi arttırma
        ++theSize;
       
    }
    /*mapten keye göre pair silme*/
    template<class K, class V>
    typename GTUSetBase<K>::GTUIterator::size_type GTUMap<K,V>::erase(K key)
    {
        for(int i=0; i<theSize; i++)
	{
            if(shrpoint[i].first == key)
            {
                for(int j=i; j<theSize-1; j++)
                {
                    shrpoint[j]=shrpoint[j+1];
                }
                break;
            }
	}
        --theSize;  //eleman saiyisi azalır erase isleminden sonra
        --index;   //indeks azaltma set icin
    }
} //GTU namespace