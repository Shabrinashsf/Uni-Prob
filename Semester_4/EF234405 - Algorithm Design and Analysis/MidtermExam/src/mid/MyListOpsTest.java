package mid;

import static mid.MyList.cons;
import static mid.MyList.empty;

public class MyListOpsTest {
	/**
     * Transform array to MyList
     * @param array[] is input array
     * @param index is initial index of array
     * @return List is returning function type
     */
    public static MyList array2List(int array[], int index) {
        if (index == array.length) {
            return empty();
        } else {
            return cons(array[index], array2List(array, index + 1));
        }
    }
    public static void main(String args[]) {
        int a1[] = {5,2,-7,0};
        MyList list1 = array2List(a1, 0);
        System.out.println(list1);
        
        MyList e0 = new MyList(0, MyList.empty());
        MyList e8 = MyList.cons(8, e0);
        MyList e_5 = MyList.cons(-5, e8);
        MyList list2 = MyList.cons(2, e_5);
        System.out.println(list2);
        System.out.println("From @Override function toString(): " + list2.toString());
        
        int a2[] = {2,-5,8,0};
        MyList list3 = array2List(a2, 0);
        if (list2.toString().equals(list3.toString())) {
            System.out.println("list2 is equal with list3");
        } else {
            System.out.println("list2 is not equal with list3");
        }
        
        System.out.println("Element from list3, 1st index: " + MyListOps.select(1, list3));
        System.out.println("The last element from list3: " + MyListOps.last(list3));
    }
}