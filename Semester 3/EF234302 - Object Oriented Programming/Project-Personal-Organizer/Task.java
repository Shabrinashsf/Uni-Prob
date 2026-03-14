public class Task {
    private String title;
    private String description;
    
    public Task(String title, String description) {
        this.title = title;
        this.description = description;
    }
    
    public String getTitle() {
        return title;
    }
    
    public String getDescription() {
        return description;
    }
    
    @Override
    public String toString(){
        return "Judul " + title + "| Deskripsi: " + description;
    }
}