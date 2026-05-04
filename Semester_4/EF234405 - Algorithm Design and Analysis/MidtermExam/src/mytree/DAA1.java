package mytree;

public class DAA1 extends MyTree {

    // Binary Search Tree (BST)
    // 1. isBST() [20 points]
    public static boolean isBST(MyTree t) {
        return isBST(t, Integer.MIN_VALUE, Integer.MAX_VALUE);
    }

    // Helper function for isBST
    // Get a boolean value to know whether 't' is BST (Binary Search Tree)
    // whose values are within the range between lowerBound and upperBound
    private static boolean isBST(MyTree t, int lowerBound, int upperBound) {
        if (t.getEmpty()) {
            return true;
        }

        int value = t.getValue();
        if (value < lowerBound || value > upperBound) {
            return false;
        }

        return isBST(t.getLeft(), lowerBound, value) && isBST(t.getRight(), value, upperBound);
    }

    // 2. printDescending() [10 points]
    public static void printDescending(MyTree t) {
        if (t.getEmpty()) {
            return;
        }

        printDescending(t.getRight());
        System.out.println(t.getValue());
        printDescending(t.getLeft());
    }

    // 3. max() [10 points]   
    /**
     * You have to:
     * - handle empty trees
     * - never look at left
     * - never compares values, i.e., the value of t and the right,
     *   because it's not necessary if it's BST.
     * - returns the right value as soon as found
     *
     * @param t is the tree being searched for the max value
     * @return the max value of tree t
     */
    public static int max(MyTree t) {
        if (t.getEmpty()) {
            throw new IllegalStateException("Trying to get max of an empty tree");
        }

        if (t.getRight().getEmpty()) {
            return t.getValue();
        }

        return max(t.getRight());
    }

}