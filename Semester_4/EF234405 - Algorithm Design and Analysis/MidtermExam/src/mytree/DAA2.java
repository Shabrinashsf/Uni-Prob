package mytree;

// AVL Tree = Height-Balanced (HB) Tree

public class DAA2 extends DAA1 {

	// 4. isHeightBalanced() [10 points]
	public static boolean isHeightBalanced(MyTree t) {
		return heightIfBalanced(t) != -1;
	}

	// Returns subtree height if balanced; otherwise returns -1.
	private static int heightIfBalanced(MyTree t) {
		if (t.getEmpty()) {
			return 0;
		}

		int leftHeight = heightIfBalanced(t.getLeft());
		if (leftHeight == -1) {
			return -1;
		}

		int rightHeight = heightIfBalanced(t.getRight());
		if (rightHeight == -1) {
			return -1;
		}

		if (Math.abs(leftHeight - rightHeight) > 1) {
			return -1;
		}

		return Math.max(leftHeight, rightHeight) + 1;
	}

	// 5. insertHB() [10 points]
	public static MyTree insertHB(int n, MyTree t) {
		if (t.getEmpty()) {
			return new MyTree(n, new MyTree(), new MyTree());
		}

		if (n <= t.getValue()) {
			MyTree grownLeft = insertHB(n, t.getLeft());
			MyTree updated = new MyTree(t.getValue(), grownLeft, t.getRight());
			return rebalanceForLeft(updated);
		} else {
			MyTree grownRight = insertHB(n, t.getRight());
			MyTree updated = new MyTree(t.getValue(), t.getLeft(), grownRight);
			return rebalanceForRight(updated);
		}
	}

	// rebalanceForLeft is called when the left subtree of t may have
	// grown taller by one notch.
	// If it is indeed taller than the right subtree by two notches,
	// return a height-balanced version of t using single or double rotations.
	// The subtrees of t are assumed to be already height-balanced and
	// no effort is made to rebalance them.
	//
	// Likewise, for the case of the right subtree -> rebalanceForRight
	// Both rebalanceForLeft & rebalanceForRight will be used by insertHB() and deleteHB()
	// 6. rebalanceForLeft() [15 points]
	private static MyTree rebalanceForLeft(MyTree t) {
		if (MyTreeOps.height(t.getLeft()) - MyTreeOps.height(t.getRight()) < 2) {
			return t;
		}

		MyTree left = t.getLeft();
		if (MyTreeOps.height(left.getLeft()) >= MyTreeOps.height(left.getRight())) {
			MyTree newRight = new MyTree(t.getValue(), left.getRight(), t.getRight());
			return new MyTree(left.getValue(), left.getLeft(), newRight);
		} else {
			MyTree leftRight = left.getRight();
			MyTree newLeft = new MyTree(left.getValue(), left.getLeft(), leftRight.getLeft());
			MyTree newRight = new MyTree(t.getValue(), leftRight.getRight(), t.getRight());
			return new MyTree(leftRight.getValue(), newLeft, newRight);
		}
	}
	
	// 7. rebalanceForRight() [15 points]
	private static MyTree rebalanceForRight(MyTree t) {
		if (MyTreeOps.height(t.getRight()) - MyTreeOps.height(t.getLeft()) < 2) {
			return t;
		}

		MyTree right = t.getRight();
		if (MyTreeOps.height(right.getRight()) >= MyTreeOps.height(right.getLeft())) {
			MyTree newLeft = new MyTree(t.getValue(), t.getLeft(), right.getLeft());
			return new MyTree(right.getValue(), newLeft, right.getRight());
		} else {
			MyTree rightLeft = right.getLeft();
			MyTree newLeft = new MyTree(t.getValue(), t.getLeft(), rightLeft.getLeft());
			MyTree newRight = new MyTree(right.getValue(), rightLeft.getRight(), right.getRight());
			return new MyTree(rightLeft.getValue(), newLeft, newRight);
		}
	}
	
	// 8. deleteHB() [10 points]
	/**
	 * Deletes the value 'x' from the given tree, if it exists, and returns the new
	 * Tree.
	 *
	 * Otherwise, the original tree will be returned.
	 */
	public static MyTree deleteHB(MyTree t, int x) {
		if (t.getEmpty()) {
			return t;
		}

		if (x < t.getValue()) {
			MyTree newLeft = deleteHB(t.getLeft(), x);
			MyTree updated = new MyTree(t.getValue(), newLeft, t.getRight());
			return rebalanceForRight(updated);
		} else if (x > t.getValue()) {
			MyTree newRight = deleteHB(t.getRight(), x);
			MyTree updated = new MyTree(t.getValue(), t.getLeft(), newRight);
			return rebalanceForLeft(updated);
		} else {
			if (t.getLeft().getEmpty() && t.getRight().getEmpty()) {
				return new MyTree();
			} else if (t.getLeft().getEmpty()) {
				return t.getRight();
			} else if (t.getRight().getEmpty()) {
				return t.getLeft();
			} else {
				int predecessor = max(t.getLeft());
				MyTree newLeft = deleteHB(t.getLeft(), predecessor);
				MyTree updated = new MyTree(predecessor, newLeft, t.getRight());
				return rebalanceForRight(updated);
			}
		}
	}

}