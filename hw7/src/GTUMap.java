import java.lang.reflect.Array;  
import java.security.InvalidParameterException;
import java.util.NoSuchElementException;
import javafx.util.Pair;  //for java pair

/**
 * @author Gökçe Demir
 * @param <K> pair_key
 * @param <V> pair_value
 * 
 * The class GTUMap extends from GTUSet 
 */
public class GTUMap<K, V> extends GTUSet< Pair <K, V> >
{
    private final Pair <K, V>[] mapArray;  //map pair array
    private final int MAX_SIZE = 1000;
    private int current=0;

    /*No parameter constructor for GTUMap*/
    GTUMap() 
    {
        this.mapArray = (Pair <K, V>[]) Array.newInstance(Pair.class, MAX_SIZE);
        setArray(mapArray);
        setCursor(current);
    }
   
    /**
     * @param val Value to be copied (or moved) to the inserted elements.
     * @return pair::first set to an iterator pointing to either the newly 
     * inserted element or to the equivalent element already in the set.
     * The pair::second element in the pair is set to true if a new element was 
     * inserted or false if an equivalent element already existed. 
     */
    @Override
    public Pair<GTUIteratorInt, Boolean > insert(Pair<K,V>  val)
    {
        for(int i=0; i<size(); ++i)
        {
            if(mapArray[i].getKey() == val.getKey())
            {  
                //aynı elemandan varsa exception fırlatır
                throw new InvalidParameterException("This value already exists!\n");  
            }
        }
        
        mapArray[getCursor()] = val;
        setArray(mapArray);
        setCursor(++current);
        
        printSet(mapArray);
        return null;
    }
    /*If k matches the key of an element in the set, 
                the method returns a reference to its mapped value.*/
    V at(K k)
    {
        for (int i = 0; i < size(); i++) 
        {
            if(mapArray[i].getKey() == k)
            {
                return mapArray[i].getValue();
            }
        }
        return null;
    }
    
    /**
    * @param pairVal Value to be searched for.
    * @return An iterator to the element, if val is found, or set::end otherwise.
    */
    @Override
    public GTUIteratorInt<Pair<K,V> > find(Pair pairVal)
    {
        setArray(mapArray);
        for(int i = 0; i< size(); ++i)
        {
            if(mapArray[i].getKey() == pairVal.getKey())
            {
                setFindIndex(i);
                return (GTUIteratorInt<Pair<K,V> >) iterator();
            }
        }
        return (GTUIteratorInt<Pair<K,V> >) end();
    }
    
    /**
    * @param other Another set .
    * @return The returned set is the intersection of this set and the given set.
    */
    @Override
    public GTUSetInt<Pair<K,V> > intersection(GTUSetInt<Pair<K,V> > other)
    {
        GTUMap< K,V > newSet = new GTUMap<> ();
        GTUMap<K,V> otherSet;  
        otherSet = (GTUMap<K,V>)other; // down casting
        
        for (int i = 0; i < this.size(); i++)
        {
            for (int j = 0; j < otherSet.size(); j++)
            {
                if(this.mapArray[i].getKey() == otherSet.getArray()[j].getKey())
                {
                    newSet.mapArray[i] = this.mapArray[i];
                }
            }
        }
        printSet(newSet.getArray());
        return newSet;
    }
    
    @Override
    public int erase(Pair val)
    {
        if(size() <= 0)
            throw new NoSuchElementException("No elements in the set!\n");
        for(int i=0; i< size(); i++)
        {
            if(mapArray[i].getKey() == val.getKey())
            {
                for(int j=i; j<=(size()-1); j++)
                {
                    mapArray[j]= mapArray[j+1];
                }
                break;
            }
        }
        printSet(mapArray);
        setCursor(getCursor() - 1);

        return 1;
    }
    
}
