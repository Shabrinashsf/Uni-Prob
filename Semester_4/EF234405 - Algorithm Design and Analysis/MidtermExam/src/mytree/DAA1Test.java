package mytree;

import mid.MyList;

public class DAA1Test extends DAA1 {
	public static void main(String args[]) {
		MyTree t = array2Tree(new int[] { 1, 9, 2, 4, 0, 2, 9, 3, 0, 2, 4, 5, 6 });

		print("Original tree: Array to Tree", t);

		// 1. isBST()
		System.out.println("Question 1: Binary Search Tree (BST) -> isBST()");
		if (isBST(t)) {
			System.out.println("The tree is BST");
		} else {
			System.out.println("The tree is not BST");
		}

		// 2. printDescending()
		System.out.println("Question 2: printDescending()");
		printDescending(t);

		// 3. max()
		System.out.println("Question 3: max()");
		System.out.println("Max value of the tree: " + max(t));
	}

	static void print(String title) {
		System.out.println("-----------------------------");
		System.out.println("# " + title+ " #");
		System.out.println();
	}

	public static void print(String title, MyTree t) {
		print(title);
		print(t);

		System.out.println();
	}

	static void print(String title, MyList list) {
		print(title);
		print(list);

		System.out.println();
	}

	static void print(MyTree t) {
		MyTreeOps.print(t);
		System.out.println();
	}

	static void print(MyList list) {
		for (MyList l = list; !l.getEmpty(); l = l.getTail()) {
			System.out.println("- " + l.getHead());
		}
	}

	public static MyTree array2Tree(int a[]) {
		MyTree t = new MyTree();
		for (int i = 0; i < a.length; i++) {
			t = insertValue(a[i], t);
		}
		return t;
	}

	private static MyTree insertValue(int n, MyTree t) {
		if (t.getEmpty()) {
			return new MyTree(n, new MyTree(), new MyTree());
		} else if (n <= t.getValue()) {
			return new MyTree(t.getValue(), insertValue(n, t.getLeft()), t.getRight());
		} else {
			return new MyTree(t.getValue(), t.getLeft(), insertValue(n, t.getRight()));
		}
	}

}