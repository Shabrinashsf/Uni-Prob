package mytree;

import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;

import mid.MyList;
import mid.MyListOps;

/**
 * provides a few utility methods and examples of how to manipulate trees,
 * including a useful print method.
 */
class MyTreeOps extends MyTree {

	/**
	 * This was done in the Lecture
	 * 
	 * @return the height of the tree
	 */
	public static int height(MyTree t) {
		if (t.getEmpty())
			return 0;
		else {
			int leftHeight = height(t.getLeft());
			int rightHeight = height(t.getRight());

			return Math.max(leftHeight, rightHeight) + 1;
		}
	}

	/**
	 * Returns an entirely new tree whose elements are triple that of the input MyTree
	 */
	public static MyTree triple(MyTree t) {
		if (t.getEmpty())
			return new MyTree();
		else
			return new MyTree(3 * t.getValue(), triple(t.getLeft()), triple(t.getRight()));
	}

	/**
	 * Returns a List of values obtained by visiting the MyTree in in-order. e.g. left
	 * branch, then current root, then right branch.
	 */
	public static MyList inorder(MyTree t) {
		if (t.getEmpty())
			return MyList.empty();
		else {
			return MyListOps.append(inorder(t.getLeft()), MyList.cons(t.getValue(), inorder(t.getRight())));
		}
	}

	/**
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
	</code> Where the bottom child is the left sub tree and the top child is the
	 * right sub tree. If both children are nil or the empty tree then they will not
	 * be printed. If only one child is nil then both children are printed to so it
	 * can be known which was the right child and which was the left child.
	 * 
	 * @param tree The tree, which may not be null
	 * @return A string containing the formatted tree
	 */

	public static void print(MyTree t) {
		System.out.println(toString(t));
	}

	public static String toString(MyTree tree) {
		final StringBuilder buffer = new StringBuilder();
		return toStringTreeHelper(tree, buffer, new LinkedList<Iterator<MyTree>>()).toString();
	}

	private static String toStringTreeDrawLines(java.util.List<Iterator<MyTree>> parentIterators, boolean amLast) {
		StringBuilder result = new StringBuilder();
		Iterator<Iterator<MyTree>> it = parentIterators.iterator();
		while (it.hasNext()) {
			Iterator<MyTree> anIt = it.next();
			if (anIt.hasNext() || (!it.hasNext() && amLast)) {
				result.append("   |");
			} else {
				result.append("    ");
			}
		}
		return result.toString();
	}

	private static StringBuilder toStringTreeHelper(MyTree node, StringBuilder buffer,
			java.util.List<Iterator<MyTree>> parentIterators) {

		if (!parentIterators.isEmpty()) {
			boolean amLast = !parentIterators.get(parentIterators.size() - 1).hasNext();
			String lines = toStringTreeDrawLines(parentIterators, amLast);
			buffer.append("\n").append(lines).append("\n").append(lines).append("- ");
		}

		if (node.getEmpty()) {
			buffer.append("[nil]");
			return buffer;
		} else {
			buffer.append(node.getValue());
		}

		if (!(node.getLeft().getEmpty() && node.getRight().getEmpty())) {
			Iterator<MyTree> it = getChildrenIterator(node);
			parentIterators.add(it);
			while (it.hasNext()) {
				MyTree child = it.next();
				toStringTreeHelper(child, buffer, parentIterators);
			}
			parentIterators.remove(it);
		}

		return buffer;
	}

	private static Iterator<MyTree> getChildrenIterator(MyTree t) {
		if (t.getEmpty())
			return Collections.<MyTree>emptyList().iterator();
		else
			return Arrays.asList(new MyTree[] { t.getRight(), t.getLeft() }).iterator();
	}

}