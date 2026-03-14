import java.util.ArrayList;
import java.util.Scanner;

public class Main{
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        ArrayList<Kendaraan> kendaraanList = new ArrayList<>();
        ArrayList<Penyewa> penyewaList = new ArrayList<>();
        
        System.out.println("=== Sistem Manajemen Rental Kendaraan ===");
        
        System.out.print("Masukkan jumlah kendaraan yang ingin ditambahkan: ");
        int jumlahKendaraan = input.nextInt();
        input.nextLine();
        
        for (int i = 0; i < jumlahKendaraan; i++) {
            System.out.println("\nKendaraan ke-" + (i + 1));
            System.out.print("Jenis kendaraan (mobil/motor/sepeda): ");
            String jenis = input.nextLine().toLowerCase();

            System.out.print("Merk: ");
            String merk = input.nextLine();

            System.out.print("Model: ");
            String model = input.nextLine();

            System.out.print("Tahun produksi: ");
            int tahun = input.nextInt();
            input.nextLine(); // buang newline

            switch (jenis) {
                case "mobil":
                    kendaraanList.add(new Mobil(merk, model, tahun, 4));
                    break;
                case "motor":
                    kendaraanList.add(new Motor(merk, model, tahun, 2));
                    break;
                case "sepeda":
                    System.out.print("Jenis sepeda (BMX/Balap/Lipat/etc): ");
                    String jenisSepeda = input.nextLine();
                    kendaraanList.add(new Sepeda(merk, model, tahun, jenisSepeda));
                    break;
                default:
                    System.out.println("Jenis kendaraan tidak dikenal, dilewati!");
            }
        }
        
        System.out.print("\nMasukkan jumlah penyewa: ");
        int jumlahPenyewa = input.nextInt();
        input.nextLine();
        
        for (int i = 0; i < jumlahPenyewa; i++) {
            System.out.println("\nPenyewa ke-" + (i + 1));
            System.out.print("Nama penyewa: ");
            String nama = input.nextLine();

            // tampilkan list kendaraan
            System.out.println("Pilih kendaraan yang disewa:");
            for (int j = 0; j < kendaraanList.size(); j++) {
                System.out.println((j + 1) + ". " + kendaraanList.get(j).tampilInfo());
            }
            System.out.print("Masukkan nomor kendaraan: ");
            int pilihan = input.nextInt();
            input.nextLine();

            if (pilihan > 0 && pilihan <= kendaraanList.size()) {
                penyewaList.add(new Penyewa(nama, kendaraanList.get(pilihan - 1)));
            } else {
                System.out.println("Pilihan tidak valid, dilewati!");
            }
        }
        
        System.out.println("\n=== Daftar Kendaraan Tersedia ===");
        for (Kendaraan k : kendaraanList) {
            System.out.println("- " + k.tampilInfo());
        }
        
        System.out.println("\n=== Daftar Penyewa dan Kendaraan ===");
        for (Penyewa p : penyewaList) {
            System.out.println("- " + p.tampilInfoSewa());
        }
        
        input.close();
    }
}