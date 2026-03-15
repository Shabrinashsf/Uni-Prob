public class Penyewa {
    private String nama;
    private Kendaraan kendaraan;
    
    public Penyewa(String nama, Kendaraan kendaraan) {
        this.nama = nama;
        this.kendaraan = kendaraan;
    }
    
    public String tampilInfoSewa() {
        return "Penyewa: " + nama + " | " + kendaraan.tampilInfo();
    }
}