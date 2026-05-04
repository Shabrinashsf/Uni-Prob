package mid;

/**
 * 
 * MyList class defines a recursive type called MyList, and provides constructor and
 * getter methods.
 */

public class MyList {

	private boolean empty;
	private int head;
	private MyList tail;

	/**
	 * The first constructor creates a list consisting of a head, that is, an
	 * integer and a tail, which is another list of integers.
	 * 
	 * @param head
	 * @param tail
	 */
	public MyList(int head, MyList tail) {
		this.empty = false;
		this.head = head;
		this.tail = tail;
	}

	/**
	 * The second constructor creates an empty list, i.e., a list with no elements.
	 * For this list, head and tail remain undefined, calls to the corresponding
	 * getters will have to result in an exception.
	 */
	public MyList() {
		this.empty = true;
	}

	/**
	 * Creates a new list from a given head element and a tail List
	 */
	public static MyList cons(int head, MyList tail) {
		return new MyList(head, tail);
	}

	/**
	 * Creates a new empty List
	 */
	public static MyList empty() {
		return new MyList();
	}

	public boolean getEmpty() {
		return this.empty;
	}

	public String toString() {
		return "[" + toStringAux() + "]";
	}

	public String toStringAux() {
		if (getEmpty()) {
			return "";
		} else if (getTail().isEmpty()) {
			return getHead() + "";
		} else {
			return getHead() + ", " + getTail().toStringAux();
		}
	}

	public static boolean equals(MyList l1, MyList l2) {
		if (l1.isEmpty() && l2.isEmpty()) {
			return true;
		} else if (l1.isEmpty() || l2.isEmpty()) {
			return false;
		} else if (l1.getHead() == l2.getHead()) {
			return equals(l1.getTail(), l2.getTail());
		} else {
			return false;
		}
	}

	/**
	 * returns true public static boolean equals(MyList l1, MyList l2) { if
	 * (l1.isEmpty() && l2.isEmpty()) { return true; } else if (l1.getHead() ==
	 * l2.getHead()) { return equals(l1.getTail(), l2.getTail()); } else { return
	 * false; } } if this list is empty
	 */
	public boolean isEmpty() {
		return empty;
	}

	/**
	 * returns the head of this list or throws an exception if the list is empty
	 * 
	 * @throws IllegalStateException if the list is empty
	 */
	public int getHead() {
		if (isEmpty()) {
			throw new IllegalStateException("Trying to access head of an empty list");
		}
		return head;
	}

	/**
	 * returns the tail of this list or throws an exception if the list is empty
	 * 
	 * @throws IllegalStateException if the list is empty
	 */
	public MyList getTail() {
		if (isEmpty()) {
			throw new IllegalStateException("Trying to access tail of an empty list");
		}
		return tail;
	}

}
