package mytree;

/**
 * 
 * MyTree class defines a recursive type called MyTree (for Binary Trees),
 * and provides constructor and getter methods.
 */

public class MyTree {

	/**
	 * Tree class defines a recursive type called Tree, and provides constructor and
	 * accessor methods.
	 */
	private boolean empty;
	private int value;
	private MyTree left, right;

	/**
	 * Creates a new MyTree whose root value is x and left and right subtrees are r
	 * and l
	 */
	public MyTree(int value, MyTree left, MyTree right) {
		this.empty = false;
		this.value = value;
		this.left = left;
		this.right = right;
	}

	/**
	 * Creates an empty tree
	 */
	public MyTree() {
		this.empty = true;
	}

	/**
	 * returns true if this tree is empty (e.g., nil)
	 */
	public boolean getEmpty() {
		return empty;
	}

	/**
	 * gets the root value of this tree
	 */
	public int getValue() {
		if (getEmpty()) {
			throw new IllegalStateException("Trying to access root of an empty tree");
		}
		return value;
	}

	/**
	 * gets the left subtree of this node
	 */
	public MyTree getLeft() {
		if (getEmpty()) {
			throw new IllegalStateException("Trying to access subtree of an empty tree");
		}
		return left;
	}

	/**
	 * gets the right subtree of this node
	 */
	public MyTree getRight() {
		if (getEmpty()) {
			throw new IllegalStateException("Trying to access subtree of an empty tree");
		}
		return right;
	}

	/**
	 * Showing the representation of the tree by the format as below:
	 * source (with modifications) http://www.connorgarvey.com/blog/?p=82 Creates a
	 * String representation of the given tree. The format looks like this
	<code>
	10
	   |
	   |- 15
	   |   |
	   |   |- 20
	   |   |
	   |   |- 14
	   |       |
	   |       | - [nil]
	   |       |
	   |       |- 11
	   |
	   |- 7
	</code>
 	 * Where the bottom child is the left sub tree and
 	 * the top child is the right sub tree.
 	 * If both children are nil or the empty tree, then they won't be printed.
 	 * If only a child is nil, then both of them will be printed so
 	 * it can be distinguished which one is right child and which
 	 * one is the left child.
 	 * @param tree the Tree, which may not be null.
 	 * @return A string containing the formatted tree
	 */
	@Override
	public String toString() {
		return toStringAux(0);
	}

	public String toStringAux(int n) {
		if (getEmpty()) {
			return Bar(n) + "emptyTree";
		} else {
			return String.format("%s%d\n%s\n%s", Bar(n), this.getValue(), this.getLeft().toStringAux(n + 1),
					this.getRight().toStringAux(n + 1));
		}
	}

	public String Bar(int n) {
		StringBuilder result = new StringBuilder();
		for (int i = 0; i < n; i++) {
			result.insert(i, '|');
		}
		return result.toString();
	}

	public final static MyTree emptyTree = new MyTree();

	public String toDot() {
		String result = "digraph g {\n";
		result += toDotAux("t");
		return result + "}";
	}

	private String toDotAux(String s) {
		String result = "";
		if (getEmpty()) {
			return result;
		} else {
			result += s + " [label=\"" + this.getValue() + "\"]\n";
			if (this.getLeft().getEmpty() && !this.getRight().getEmpty()) {
				result += s + "->" + s + "l [style=\"invis\"]\n";
				result += s + "l" + " [style=\"invis\"]\n";
				result += s + "->" + s + "r\n";
				result += this.getRight().toDotAux(s + "r");
			} else if (this.getRight().getEmpty() && !this.getLeft().getEmpty()) {
				result += s + "->" + s + "l\n";
				result += this.getLeft().toDotAux(s + "l");
				result += s + "->" + s + "r [style=\"invis\"]\n";
				result += s + "r" + " [style=\"invis\"]\n";
			} else if (!this.getRight().getEmpty() && !this.getLeft().getEmpty()) {
				result += s + "->" + s + "l\n";
				result += this.getLeft().toDotAux(s + "l");
				result += s + "->" + s + "r\n";
				result += this.getRight().toDotAux(s + "r");

			}
		}
		return result;
	}

	public static MyTree makeCompleteTree(int level) {
		return makeCompleteTreeAux(level, 1);
	}

	private static MyTree makeCompleteTreeAux(int level, int nextNodeNumber) {
		if (level == 0) {
			return new MyTree(nextNodeNumber, emptyTree, emptyTree);
		} else {
			return new MyTree(nextNodeNumber, makeCompleteTreeAux(level - 1, nextNodeNumber + 1),
					makeCompleteTreeAux(level - 1, nextNodeNumber + (int) Math.round(Math.pow(2, level))));
		}
	}

}
