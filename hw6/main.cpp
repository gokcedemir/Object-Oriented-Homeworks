/* 
 * File:   main.cpp
 * Author: Gökçe Demir
 * Student ID: 141044067
 * CSE241 - HW06
 * Created on December 4, 2017, 1:28 AM
 */

#include <iostream>
#include "GTUSet.h"
#include "GTUSet.cpp"
#include "GTUMap.h"
#include "GTUMap.cpp"
#include <string>


using namespace std;

using GTU::GTUSetBase;
using GTU::GTUSet;
using GTU::GTUMap;

const int MAX_SIZE = 1000 ; //const value

/*intersection of the two sets.*/
template <class T>
GTUSet<T> setIntersection (const GTUSetBase<T>& obj1, const GTUSetBase<T>& obj2)
{
    GTUSet<T> intersec;
    
    int firstSize = obj1.size();    //1. objenin size
    int secondSize = obj2.size();  //2. objenin size
    
    
    for (int i = 0; i < firstSize; i++)
    {
        for (int j = 0; j < secondSize; j++)
        {
            if(obj1.getMypoint()[i] == obj2.getMypoint()[j])
            {
                intersec.getMypoint()[i] = obj2.getMypoint()[j];
            }
        }
    }
   return intersec;
}

int main(int argc, char** argv)
{
    try{
        GTUSetBase<int> *base1;   //referans olsuturma base classdan
        GTUSetBase<int> *base2;
        GTUSet<int> obj;
        GTUSet<int> obj1;
        
        GTUSetBase<int>::GTUIterator mit,mit2;
       // obj.erase(1);   //throw exception
        obj.insert(2);
        obj.insert(5);
        obj.insert(13);
        obj.insert(1);
        obj.insert(8);
       //  obj.insert(5);  //throw exception
        obj.insert(7);
        mit2 = obj.find(7);
        mit = obj.begin();
        
        /************map testing******************/
        GTUMap<int, int> mymap;
        GTUMap<int, int> mymap2;
        mymap.insert(pair<int,int>(24,14));
        mymap.insert(pair<int,int>(23,14));
        mymap.insert(pair<int,int>(1,5));
       

        mymap2.insert(pair<int,int>(24,14));
		mymap2.insert(pair<int,int>(24,14));

        mymap.erase(24);
        mit = mymap.find(23);
        
        /************************/
       /*set obj1 oluşturma*/
        obj1.insert(5);
        obj1.insert(12);
        obj1.insert(13);
        obj1.insert(1);
        obj1.insert(15);
        
        base1= &obj;
        base2 = &obj1;
      
        setIntersection(*base1, *base2);  //calling function
        

    }
    catch(const char* msg)
    {
         // code to handle exception
        cout<<msg;
    }
       
        
    
    return 0;
}

