public class Mahasiswa {
    private String nama;
    private String nrp;
    
    public Mahasiswa(String nama, String nrp){
        this.nama = nama;
        this.nrp = nrp; 
    }
    
    public String getNama(){
        return nama;
    }
    
    public String getNrp() {
        return nrp;
    }
}