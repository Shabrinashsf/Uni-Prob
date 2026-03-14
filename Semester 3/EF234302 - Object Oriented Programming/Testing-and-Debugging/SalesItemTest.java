import junit.framework.TestCase;

public class SalesItemTest extends TestCase
{
    private SalesItem item1;
    private SalesItem item2;

    /**
     * Konstruktor: otomatis dipanggil sebelum setiap test
     */
    public SalesItemTest()
    {
        item1 = new SalesItem("Mechanical Keyboard", 8999);
        item2 = new SalesItem("Gaming Headset", 12999);
    }

    public void testAddCommentValid()
    {
        boolean ok1 = item1.addComment("Shab", "Feel-nya enak banget", 5);
        boolean ok2 = item1.addComment("Tono", "Lumayan tapi agak berisik", 3);
        assertTrue(ok1);
        assertTrue(ok2);
        assertEquals(2, item1.getNumberOfComments());
    }

    public void testAddCommentInvalidRating()
    {
        boolean ok = item1.addComment("Budi", "Rating out of range", 10);
        assertFalse(ok);
    }

    public void testDuplicateAuthor()
    {
        item1.addComment("Lina", "Bagus banget", 5);
        boolean ok = item1.addComment("Lina", "Mau nambah lagi nih", 4);
        assertFalse(ok);
    }

    public void testUpvoteAndDownvoteComment()
    {
        item1.addComment("Rian", "Worth it banget", 5);
        item1.upvoteComment(0);
        item1.upvoteComment(0);
        item1.downvoteComment(0);
        Comment c = item1.findMostHelpfulComment();
        assertEquals(1, c.getVoteCount());
    }

    public void testFindMostHelpfulComment()
    {
        item2.addComment("Shab", "Bass-nya mantap!", 5);
        item2.addComment("Mila", "Mikrofonnya kurang jelas", 3);
        item2.upvoteComment(0);
        item2.upvoteComment(0);
        item2.downvoteComment(1);
        Comment best = item2.findMostHelpfulComment();
        assertEquals("Shab", best.getAuthor());
    }

    public void testRemoveComment()
    {
        item1.addComment("Ayu", "Mau coba dulu", 4);
        item1.addComment("Budi", "Kurang cocok", 2);
        item1.removeComment(0);
        assertEquals(1, item1.getNumberOfComments());
    }

    public void testRemoveCommentInvalidIndex()
    {
        item1.addComment("Ayu", "Mau coba dulu", 4);
        item1.removeComment(5);
        assertEquals(1, item1.getNumberOfComments());
    }

    public void testGetNameAndPrice()
    {
        assertEquals("Mechanical Keyboard", item1.getName());
        assertEquals(8999, item1.getPrice());
    }

    public void testFindCommentByAuthor()
    {
        item1.addComment("Shab", "Feel-nya enak banget", 5);
        Comment found = item1.findMostHelpfulComment();
        assertNotNull(found);
    }

    public void testShowInfo()
    {
        item1.addComment("Lina", "Bagus banget", 5);
        item1.showInfo();
    }
}
