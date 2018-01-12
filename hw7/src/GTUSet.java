import java.lang.reflect.Array;
import java.security.InvalidParameterException;
import java.util.NoSuchElementException;
import javafx.util.Pair;  //for java pair

/**
 *
 * @author Gökçe Demir
 * Student ID: 141044067
 * CSE241 - HW07
 * @param <T>
 * The class GTUSet implements the GTUSetInt interface.It will keep its data using Java arrays.
 */
public class GTUSet<T> implements GTUSetInt<T>, GTUIteratorInt<T>
{
    private T[] array;    //template array seti tutmak icin kullanilir
    private final int MAX_SIZE = 1000;
    private int cursor =0;    //imlecin nerede oldugunu gosterir
    private int findIndex = 0;  //bulunan indeks tutulur

    /**
     *
     * @return  GTUIteratorInt
     */
    @Override
    public GTUIteratorInt<T> iterator()
    {	
        //currentIndex = cursor ;
        GTUIteratorInt<T> it = new GTUIteratorInt<T>()
        {
           /* Returns true if this list iterator has more elements when
            traversing the list in the reverse direction.  */
            @Override
            public boolean hasPrevious()
            {
                int temp = getCursor(); 
                if(temp -1 >=0 )
                    return true;   //eger setin baslangicini gecmiyorsa true
                else
                    return false;
            }

            /*Returns the previous element in the list and moves the cursor position backwards.*/
            @Override
            public T previous()
            {
                if(!this.hasPrevious())
                        throw new NoSuchElementException();
                return getArray()[--cursor];  //previosu element and cursor pos. backwards
            }

            @Override
            public boolean hasNext()
            {
                return ((getCursor() < MAX_SIZE) && (getArray()[getFindIndex()] !=null )) ;
            }
            /*Returns the next element in the list and advances the cursor position.*/
            @Override
            public T next()
            {
                if(!this.hasNext())
                {
                    throw new NoSuchElementException();
                }
                return getArray()[++findIndex];
            }

            @Override
            public GTUIteratorInt<T> iterator()
            {
                    // TODO Auto-generated method stub
                    return null;
            }	 
        };
        return it;
    }

    /**
    * @return Returns true if this list iterator has more elements when 
    *                traversing the list in the reverse direction.
    */
    @Override
    public boolean hasPrevious()
    {
        int temp = getCursor(); 
        return temp -1 >=0; //eger setin baslangicini gecmiyorsa true
    }

    /**
    * @return Returns the previous element in the list and moves the cursor position backwards.
    */
    @Override
    public T previous()
    {
        if(!this.hasPrevious())
                throw new NoSuchElementException();
        return getArray()[--cursor];  //previosu element and cursor pos. backwards
    }

    /**
    * @return Returns true if this list iterator has more elements when 
    * traversing the list in the forward direction. 
    */
    @Override
    public boolean hasNext()
    {
        return ((getCursor()< MAX_SIZE) && (getArray()[getFindIndex()]!=null)) ;
    }

    /**
    * @return Returns the next element in the list and advances the cursor position.
    */
    @Override
    public T next()
    {
        if(!this.hasNext())
        {
            throw new NoSuchElementException();
        }
        return getArray()[++findIndex];
    }

    /**
     * no parameter constructor
     */
    public GTUSet()
    {
        /*creates a new array with the specified type and length at runtime*/
        this.array = (T[]) Array.newInstance(Object.class, MAX_SIZE);
        cursor = 0; 	
    }

    /** 
     * Test whether container is empty
     * @return true or false. If container is not empty return false, otherwise 
     * return true.
     */
    @Override
    public boolean empty()
    {
        return getCursor() == 0;
    }

    /**
    * @return Return container size.
    */
    @Override
    public int size()
    {
        return getCursor();
    }

    /**
    * @return Return maximum size.
    */
    @Override
    public int max_size() 
    {
        return MAX_SIZE;
    }
    /* */

    /**
     * @param <T> generic array
     * @param arr Prints generic array 
     */
    public static <T> void printSet(T[] arr)
    {
        for(T element: arr)
        {
            if(element != null)
                System.out.printf("%s ",element);
        }
        System.out.println();
    }

    /**
    @param val Value to be copied (or moved) to the inserted elements.
    * @return pair::first set to an iterator pointing to either the newly 
    * inserted element or to the equivalent element already in the set.
    * The pair::second element in the pair is set to true if a new element was 
    * inserted or false if an equivalent element already existed. 
     */
    @Override
    public Pair<GTUIteratorInt, Boolean > insert(T val)
    {
        while(this.hasNext())
        {
            if(this.next() == val )
                throw new InvalidParameterException("This value already exists!\n");  //eger eleman varsa excepiton firlat
        }
        array[getCursor()] = val;  //yoksa elemani contaienera ekleme
        setCursor(getCursor() + 1);
        
        printSet(array);
        return null;
    }

    /**
     * @param val Value to be removed from the set.
     * @return  the function returns the number of elements erased.
     */
    @Override
    public int erase(T val)
    {
        if(size() <=0)
            throw new NoSuchElementException("No elements in the set!\n");
        for(int i=0; i< size(); i++)
        {
            if(getArray()[i] == val)
            {
                for(int j=i; j<=(size()-1); j++)
                {
                    array[j]= getArray()[j+1];
                }
                break;
            }
        }
        printSet(array);
        setCursor(getCursor() - 1);

        return 1;
    }

    /**
    * Clear all content
    */
    @Override
    public void clear()
    {
        setCursor(0);
        for (int i = 0; i < size(); i++)
        {
            getArray()[i] = null;
        }
    }

    /**
    * @param val Value to be searched for.
    * @return An iterator to the element, if val is found, or set::end otherwise.
    */
    @Override
    public GTUIteratorInt<T> find(T val)
    {
        for(int i = 0; i< size(); ++i)
        {
            if(array[i] == val)
            {
                setFindIndex(i) ;
                return iterator();
            }
        }
        return end();
    }

    /**
     * @param val Value to search for.
     * @return 1 if the container contains an element equivalent to val, or zero otherwise
     */
    @Override
    public int count(T val)
    {
        for (int i = 0; i < size(); ++i) 
        {
            if(getArray()[i] == val)
                    return 1;			
        }
        return 0;
    }

    /**
    * @return An iterator to the first element in the container.
    */
    @Override
    public GTUIteratorInt<T> begin()
    {
        setCursor(0);
        setFindIndex(0);
        return iterator();
    }

    /**
    * @return An iterator to the past-the-end element in the container.
    */
    @Override
    public GTUIteratorInt<T> end()
    {
        GTUSet<T> obj = new GTUSet<>();
        GTUIteratorInt<T> it = obj.iterator();
        
        return it;  //setin sonunu gosterir iterator
    }
    

    /**
    * @return Generic array
    */
    public T[] getArray()
    {
        return array;
    }

    /**
     *
     * @param other Another set .
     * @return The returned set is the intersection of this set and the given set.
     */
    @Override
    public GTUSetInt<T> intersection(GTUSetInt<T> other)
    {
        GTUSet<T> newSet = new GTUSet<>();
        GTUSet<T> otherSet = (GTUSet<T>)other;  // casting
        
        for (int i = 0; i < this.size(); i++)
        {
            for (int j = 0; j < otherSet.size(); j++)
            {
                if(this.array[i] == otherSet.getArray()[j])
                {
                    newSet.array[i] = this.array[i];
                }
            }
        }
        printSet(newSet.getArray());
        return newSet;
    }

    /**
     * @return the cursor
     */
    public int getCursor() {
        return cursor;
    }

    /**
     * @param cursor the cursor to set
     */
    public void setCursor(int cursor) {
        this.cursor = cursor;
    }

    /**
     * @return the findIndex
     */
    public int getFindIndex() {
        return findIndex;
    }

    /**
     * @param findIndex the findIndex to set
     */
    public void setFindIndex(int findIndex) {
        this.findIndex = findIndex;
    }

    /**
     * @param array the array to set
     */
    public void setArray(T[] array) {
        this.array = array;
    }
}