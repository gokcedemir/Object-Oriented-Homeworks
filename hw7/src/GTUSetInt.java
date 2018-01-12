import javafx.util.Pair;

/**
 *
 * @author Gökçe Demir
 * Student ID: 141044067
 * CSE241 - HW07
 * @param <T>
 * GTUSetInt is a Java interface that extends GTUIteratorInt interface. 
 */
public interface GTUSetInt<T> extends GTUIteratorInt<T>
{
    /**
     * Test whether container is empty
     * @return true or false. If container is not empty return false, otherwise 
     * return true.
     */
    public boolean empty();

    /**
     * @return Return container size.
     */
    public int size();

    /**
     * @return Return maximum size.
     */
    public int max_size();

    /**
     * @param val Value to be copied (or moved) to the inserted elements.
     * @return pair::first set to an iterator pointing to either the newly 
     * inserted element or to the equivalent element already in the set.
     * The pair::second element in the pair is set to true if a new element was 
     * inserted or false if an equivalent element already existed. 
     */
    Pair<GTUIteratorInt, Boolean> insert(T val);

    /**
     * @param val Value to be removed from the set.
     * @return  the function returns the number of elements erased.
     */
    public int erase(T val);


    /**
     * Clear all content
    */
    public void clear();

    /**
     * @param val Value to be searched for.
     * @return An iterator to the element, if val is found, or set::end otherwise.
     */
    public GTUIteratorInt<T> find(T val);


    /**
     * @param val Value to search for.
     * @return 1 if the container contains an element equivalent to val, or zero otherwise
     */
    public int count(T val);


    /**
     * @return An iterator to the first element in the container.
     */
    public GTUIteratorInt<T> begin();

    /**
     * @return An iterator to the past-the-end element in the container.
     */
    public GTUIteratorInt<T> end();

    /**
     * @param other Another set .
     * @return The returned set is the intersection of this set and the given set.
     */
    public GTUSetInt<T> intersection(GTUSetInt<T> other);

}