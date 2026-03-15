public class Student {
    private String nim;
    private String name;
    private String major;
    
    public Student(String nim, String name, String major){
        this.nim = nim;
        this.name = name;
        this.major = major;
    }
    
    public String getNim(){
        return nim;
    }
    
    public String getName(){
        return name;
    }
    
    public String getMajor(){
        return major;
    }
    
    @Override 
    public String toString(){
        return "NIM: " + nim + " | Name: " + name + " | Jurusan: " + major;
    }
}