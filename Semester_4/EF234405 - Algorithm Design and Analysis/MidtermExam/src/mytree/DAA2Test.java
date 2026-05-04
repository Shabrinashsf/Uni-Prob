package mytree;

public class DAA2Test extends DAA2 {
	public static void main(String args[]) {
		MyTree t = DAA1Test.array2Tree(new int[] { 10, 4, 5, 16, 15});

		DAA1Test.print("Original tree: Array to Tree", t);

		// 4. isHeightBalanced()
		System.out.println("Question 4: isHeightBalanced()");
		if (isHeightBalanced(t)) {
			System.out.println("The tree is Height-Balanced");
		} else {
			System.out.println("The tree is not Height-Balanced");
		}

		// 5. insertHB()
		System.out.println("Question 5: insertHB()");
		t = insertHB(7, t);
		DAA1Test.print("7 has been inserted", t);
		if (isHeightBalanced(t)) {
			System.out.println("The tree is Height-Balanced");
		} else {
			System.out.println("The tree is not Height-Balanced");
		}
		t = insertHB(12, t);
		DAA1Test.print("12 has been inserted", t);
		if (isHeightBalanced(t)) {
			System.out.println("The tree is Height-Balanced");
		} else {
			System.out.println("The tree is not Height-Balanced");
		}
		t = insertHB(9, t);
		DAA1Test.print("9 has been inserted", t);
		if (isHeightBalanced(t)) {
			System.out.println("The tree is Height-Balanced");
		} else {
			System.out.println("The tree is not Height-Balanced");
		}
		
		// 5. deleteHB()
		System.out.println("Question 6: deleteHB()");
		t = deleteHB(t, 7);
		DAA1Test.print("7 has been deleted", t);
		if (isHeightBalanced(t)) {
			System.out.println("The tree is Height-Balanced");
		} else {
			System.out.println("The tree is not Height-Balanced");
		}
		t = deleteHB(t, 12);
		DAA1Test.print("12 has been deleted", t);
		if (isHeightBalanced(t)) {
			System.out.println("The tree is Height-Balanced");
		} else {
			System.out.println("The tree is not Height-Balanced");
		}
		t = deleteHB(t, 9);
		DAA1Test.print("9 has been deleted", t);
		if (isHeightBalanced(t)) {
			System.out.println("The tree is Height-Balanced");
		} else {
			System.out.println("The tree is not Height-Balanced");
		}
		t = deleteHB(t, 10);
		DAA1Test.print("10 has been deleted", t);
		if (isHeightBalanced(t)) {
			System.out.println("The tree is Height-Balanced");
		} else {
			System.out.println("The tree is not Height-Balanced");
		}
		t = deleteHB(t, 15);
		DAA1Test.print("15 has been deleted", t);
		if (isHeightBalanced(t)) {
			System.out.println("The tree is Height-Balanced");
		} else {
			System.out.println("The tree is not Height-Balanced");
		}

	}
}