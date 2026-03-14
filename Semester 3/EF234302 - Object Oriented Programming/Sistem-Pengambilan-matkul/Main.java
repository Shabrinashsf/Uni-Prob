import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        Dosen d1 = new Dosen("Misbakhul Munir Irfan Subakti, S.Kom., M.Sc.", "123424301");
        Dosen d2 = new Dosen("Fajar Baskoro, S.Kom., M.T.", "123424302");
        Dosen d3 = new Dosen("Dr. Baskoro Adi P., S.Kom.,M.Kom.", "123424303");
        Dosen d4 = new Dosen("Arya Yudhi Wijaya, S.Kom, M.Kom.", "123424304");
        Dosen d5 = new Dosen("Ilham Gurat Adillion, S.Kom., M.Kom.", "123424305");
        Dosen d6 = new Dosen("Dr. Sarwosri, S.Kom. M.T.", "123424307");
        Dosen d7 = new Dosen("Aldinata Rizky Revanda, S.Kom., M.Kom.", "123424201");
        
        MataKuliah[] daftarMK = new MataKuliah[7];
        daftarMK[0] = new MataKuliah("Pemrograman Web", "EF234301", 3, 5, "Kamis 07:00 - 08:50", "IF309", d1);
        daftarMK[1] = new MataKuliah("Pemrograman Berorientasi Objek", "EF234302", 3, 5, "Selasa 10:00 - 11:50", "TIF105", d2);
        daftarMK[2] = new MataKuliah("Jaringan Komputer", "EF234303", 4, 5, "Selasa 07:00 - 08:50", "TIF105", d3);
        daftarMK[3] = new MataKuliah("Teori Graf", "EF234304", 3, 5, "Senin 07:00 - 08:50", "TIF107", d4);
        daftarMK[4] = new MataKuliah("Matematika Diskrit", "EF234305", 3, 5, "Jumat 09:00 - 10:50", "TIF105", d5);
        daftarMK[5] = new MataKuliah("Konsep Pengembangan Perangkat Lunak", "EF234307", 2, 5, "Selasa 13:30 - 15:20", "IF305", d6);
        daftarMK[6] = new MataKuliah("Konsep Kecerdasan Artifisial", "EK234201", 3, 5, "Senin 10:00 - 11:50", "TIF103", d7);
        
        int menu = 0;
        while (menu != 4){
            System.out.println("\n===== SISTEM PENGAMBILAN MATA KULIAH SEMESTER 3 =====");
            System.out.println("1. Mendaftar Mata Kuliah");
            System.out.println("2. Lihat Daftar Mata Kuliah");
            System.out.println("3. Mata Kuliah Saya");
            System.out.println("4. Keluar");
            System.out.println("Pilih Menu: ");
            menu = sc.nextInt();
            sc.nextLine();
            
            if(menu == 1){
                System.out.println("Input Nama Mahasiswa: ");
                String nama = sc.nextLine();
                System.out.println("Input NRP Mahasiswa: ");
                String nrp = sc.nextLine();
                Mahasiswa mhs = new Mahasiswa(nama, nrp);
                
                System.out.println("\nDaftar Mata Kuliah: ");
                for (int i = 0; i < daftarMK.length; i++){
                    MataKuliah mk = daftarMK[i];
                    System.out.println((i+1) + ". [" + mk.getKode() + "] " + mk.getNama() + " " + mk.getSks() + " sks " + "[" + mk.getKelas() + "] " + mk.getJumlahMhsMengambil() + "/" + mk.getKapasitasKelas());
                }
                
                System.out.println("\nPilih Mata Kuliah (nomor): ");
                int opsi = sc.nextInt();
                sc.nextLine();
                
                if (opsi > 0 && opsi < daftarMK.length) {
                    MataKuliah mk = daftarMK[opsi - 1];
                    if (mk.registered(mhs)){
                        System.out.println("\nGagal Mengambil Mata Kuliah - Mahasiswa Telah Terdaftar");
                    } else {
                        boolean success = mk.daftarMhs(mhs);
                        if(success) {
                            System.out.println("\nBerhasil Mengambil Mata Kuliah");
                            System.out.println("Mahasiswa: " + mhs.getNama() + " (" + mhs.getNrp() + ")");
                            System.out.println("Mata Kuliah: " + mk.getNama() + " [" + mk.getKode() + "]");
                            System.out.println("Jadwal: " + mk.getJadwal() + " [" + mk.getKelas() + "]");
                            System.out.println("Dosen Pengajar: " + mk.getDosenPengajar().getNama());
                        } else {
                            System.out.println("\nGagal Mengambil Mata Kuliah - Kelas Sudah Penuh");
                        }
                    }
                } else {
                    System.out.println("\nOpsi Tidak Valid");
                }
            } else if (menu == 2){
                System.out.println("\nDaftar Mata Kuliah");
                for (int i = 0; i < daftarMK.length; i++){
                    MataKuliah mk = daftarMK[i];
                    System.out.println((i+1) + ". [" + mk.getKode() + "] " + mk.getNama() + " " + mk.getSks() + " sks " + "[" + mk.getKelas() + "] " + mk.getJumlahMhsMengambil() + "/" + mk.getKapasitasKelas());
                }
            } else if (menu == 3) {
                System.out.println("Input NRP: ");
                String target = sc.nextLine();
                System.out.println("\nDaftar Mata Kuliah Mahasiswa dengan NRP " + target + ":");
                boolean ada = false;
                
                for (int i = 0; i < daftarMK.length; i++){
                    MataKuliah mk = daftarMK[i];
                    
                    if(mk.registered(new Mahasiswa("", target))) {
                        System.out.println((i + 1) + ". " + mk.getNama() + " [" + mk.getKode() + "] " + mk.getJadwal() + " [" + mk.getKelas() + "] Dosen: " + mk.getDosenPengajar().getNama());
                        ada = true;
                    }
                }
                
                if (!ada){
                    System.out.println("Mahasiswa dengan NRP " + target + " belum mengambil mata kuliah");
                }
            } else if (menu == 4){
                System.out.println("Thankyou...");
            } else {
                System.out.println("Menu tidak valid");
            }
        }
    }
}