package mid;

/**
 * The class MyListOps defines a number of static methods to work with lists using
 * the MyList class.
 */
public class MyListOps extends MyList {

	/**
	 * Select and return the n-th element of a list a. Assume that the n-th element
	 * exists.
	 */

	public static int select(int n, MyList a) {
		if (a.isEmpty())
			throw new IllegalStateException("select - list does not have enough elements.");
		else if (n == 0)
			return a.getHead();
		else
			return select(n - 1, a.getTail());
	}

	/**
	 * Return the last element of list a. Assume that there is an element.
	 */

	public static int last(MyList a) {
		if (a.isEmpty())
			throw new IllegalStateException("list does not have any elements.");
		else if (a.getTail().isEmpty())
			return a.getHead();
		else
			return last(a.getTail());
	}

	/**
	 * Add an element x to the end of a list a. Return the extended list.
	 */

	public static MyList addToEnd(MyList a, int x) {
		if (a.isEmpty()) {
			return cons(x, empty());
		} else {
			return cons(a.getHead(), addToEnd(a.getTail(), x));
		}
	}

	/**
	 * Creates a MyList which is the result of MyList b appended to the end of MyList a
	 */
	public static MyList append(MyList a, MyList b) {
		if (a.isEmpty()) {
			return b;
		} else {
			return cons(a.getHead(), append(a.getTail(), b));
		}
	}

	/**
	 * addToEnd can also be defined using append without any further recursion.
	 * 
	 * public static MyList addToEnd(List a, int x) { return append(a, cons(x,
	 * empty())); }
	 * 
	 */

	/**
	 * A naive implementation of reversing a MyList. Can take quite long on large
	 * lists
	 */
	public static MyList naiveReverse(MyList a) {
		if (a.isEmpty()) {
			return empty();
		} else {
			return addToEnd(naiveReverse(a.getTail()), a.getHead());
		}
	}

	/**
	 * An efficient (tail recursive) implementation to reverse a MyList that uses a
	 * helper method and an accumulator
	 */
	public static MyList reverse(MyList list) {
		return reverseAccumulate(list, empty());
	}

	private static MyList reverseAccumulate(MyList original, MyList reversed) {
		if (original.isEmpty()) {
			return reversed;
		} else {
			return reverseAccumulate(original.getTail(), cons(original.getHead(), reversed));
		}
	}

	public static int max(MyList list) {
		if (list.isEmpty())
			throw new IllegalStateException("list does not have any elements.");
		else if (list.getTail().isEmpty()) {
			return list.getHead();
		} else {
			return Math.max(list.getHead(), max(list.getTail()));
		}
	}
}
