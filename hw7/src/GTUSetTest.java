import javafx.util.Pair;  //for java pair

/**
 *
 * @author Gökçe Demir
 * Student ID: 141044067
 * CSE241 - HW07
 */
public class GTUSetTest
{
    private static GTUSet<String> myobj;  //create object
    private static GTUSet<String> myobj2;

    public static void main(String[] args)
    {
        // TODO Auto-generated method stub
        try {
                /*seti arrayde tuttugum icin lenght aliyorum*/
                /*no parameter constructorla object olusturulmuyor, 
                cunku generic array olusturmak icin type bilgisine ihtiyac duyuluyor.  */
                myobj = new GTUSet<>();
                myobj2 = new GTUSet<>();
                
                GTUMap<Integer, Integer> mapObj; //create object of map
                mapObj = new GTUMap<> ();
                
                GTUMap<Integer, Integer> mapObj2;  //another map object
                mapObj2 = new GTUMap<>();
                Pair mypair = new Pair<>(23,3);
                mapObj2.insert(mypair);
                
                Pair p1 = new Pair<>(1,10);
                /*create pair object and that objects insert map*/
                mapObj.insert(p1);
                Pair p2 = new Pair<>(13,5);
                mapObj.insert(p2);
                Pair p3 = new Pair<>(23,3);
                mapObj.insert(p3);
                Pair p4 = new Pair<>(29,5);
                mapObj.insert(p4);
                
               // System.out.println("is empty: "+ mapObj.empty());
               // mapObj.erase(p3);
              //  System.out.println("is empty: "+ mapObj.empty());
                
                /****************************************************/
                System.out.print("Intersection map: ");
                mapObj.intersection(mapObj2);
                
                System.out.println("count pair in map : " + mapObj2.count(mypair));
                
                System.out.printf("size: %d \n",myobj.size());
                System.out.printf("max_size: %d \n",myobj.max_size());
                /*Insert element container..*/
                myobj.insert("1");
               // System.out.printf("New size: %d \n",myobj.size());

               /*Erase element container*/
                myobj.erase("1");
               // System.out.printf("New size after erase operation: %d \n",myobj.size());
                myobj.insert("1");
                myobj.insert("5");
                myobj.insert("8");
                myobj.insert("4");
                
                System.out.printf("New size: %d \n",myobj.size());
                
                myobj2.insert("10");
                myobj2.insert("1");
                myobj2.insert("8");
                myobj2.insert("gokce");
                //myobj2.end();
                
                /*iki kumenin kesisimi*/
                System.out.print("Intersection set: ");
                myobj2.intersection(myobj); 
                
                GTUIteratorInt<String> a = myobj.find("1");
                // 1'den sonra gelen elemani next ile bulma
                System.out.println("1'den sonra gelen eleman: " + a.next());
  
                System.out.print("Set bos mu: " + myobj.empty());
                System.out.println();
                myobj.clear();
                System.out.print("Clear isleminden sonra set bos mu: " +myobj.empty());
                System.out.println();
                
                /*Access element in map */
                System.out.println("value 13 olan key: " +  mapObj.at(13));
                GTUIteratorInt<Pair< Integer, Integer> > temp;
                temp = mapObj.find(p2);
                mapObj.erase(p2);
                System.out.println("<13,5> pair iteratoru : " + temp);
                System.out.println("next element in map: "+ temp.next());
                System.out.println("has previous ? " + temp.hasPrevious());
                System.out.println("previous element in map: " + temp.previous());

        } 
        /*Exception handling*/
        catch (Exception e)
        {
                // TODO: handle exception
                System.out.printf("Exception thrown : %s", e.getMessage());
        }
    }
}