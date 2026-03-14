public class MataKuliah {
    private String nama;
    private String kode;
    private int sks;
    private int kapasitasKelas;
    private String jadwal;
    private String kelas;
    private Dosen dosenPengajar;
    private Mahasiswa[] mhsMengambil;
    private int jumlahMhsMengambil;
    
    public MataKuliah(String nama, String kode, int sks, int kapasitasKelas, String jadwal, String kelas, Dosen dosenPengajar){
        this.nama = nama;
        this.kode = kode;
        this.sks = sks;
        this.kapasitasKelas = kapasitasKelas;
        this.jadwal = jadwal;
        this.kelas = kelas;
        this.dosenPengajar = dosenPengajar;
        this.mhsMengambil = new Mahasiswa[kapasitasKelas];
        this.jumlahMhsMengambil = 0;
    }
    
    public String getNama(){
        return nama;
    }
    
    public String getKode(){
        return kode;
    }
    
    public int getSks(){
       return sks;
    }
    
    public int getKapasitasKelas(){
        return kapasitasKelas;
    }
    
    public String getJadwal(){
        return jadwal;
    }
    
    public String getKelas(){
        return kelas;
    }
    
    public Dosen getDosenPengajar(){
        return dosenPengajar;
    }
    
    public int getJumlahMhsMengambil(){
        return jumlahMhsMengambil;
    }
    
    public boolean registered(Mahasiswa mhs){
        for (int i = 0; i < jumlahMhsMengambil; i ++){
            if (mhsMengambil[i].getNrp().equals(mhs.getNrp())) {
                return true;
            }
        }
        return false;   
    }
    
    public boolean daftarMhs(Mahasiswa mhs) {
        if(registered(mhs)){
            return false;
        }
        if(jumlahMhsMengambil < kapasitasKelas){
            mhsMengambil[jumlahMhsMengambil] = mhs;
            jumlahMhsMengambil++;
            return true;
        }
        return false; 
    }
}