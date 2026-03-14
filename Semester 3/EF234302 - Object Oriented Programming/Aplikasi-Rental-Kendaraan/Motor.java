public class Motor extends Kendaraan {
    private int jumlahRoda;
    
    public Motor(String merk, String model, int tahunProduksi, int jumlahRoda) {
    super(merk, model, tahunProduksi);
    this.jumlahRoda = jumlahRoda;
    }
    
    public String tampilInfo(){
        return "Motor: " + super.tampilInfo() + " - " + jumlahRoda + "roda";
    }
}