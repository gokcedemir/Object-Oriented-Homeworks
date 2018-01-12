/**
 *
 * @author Gokce Demir 
 * Student Id: 141044067
 * CSE 241 - HW07
 * GTUIteratorInt is a Java interface that includes iterator methods.
 * 
 */
public interface GTUIteratorInt<T>
{
    /**
    * @return Returns true if this list iterator has more
        elements when traversing the list in the forward direction.
    */
    public boolean hasNext();
  
    
    /**
     * @return Returns true if this list iterator has more elements when 
     * traversing the list in the reverse direction.
     */
    public boolean hasPrevious();

    /**
     * @return Returns the next element in the list and advances the cursor position.
     */
    public T next();

    /**
     * @return Returns the previous element in the list and moves the cursor
     *  position backwards.
     */
    public T previous();

    /**
     *
     * @return GTUIteratorInt
     */
    public GTUIteratorInt<T> iterator();

}

