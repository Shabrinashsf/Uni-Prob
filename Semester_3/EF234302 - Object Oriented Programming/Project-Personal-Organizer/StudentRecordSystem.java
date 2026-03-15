import java.util.ArrayList;
import java.util.Scanner;

public class StudentRecordSystem {
    public static void main(String[] args) {
        ArrayList<Student> records = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        int choice;
        
        do {
            System.out.println("\n=== Student Record System ===");
            System.out.println("1. Tambah Mahasiswa");
            System.out.println("2. Lihat Semua Mahasiswa");
            System.out.println("3. Cari Mahasiswa");
            System.out.println("4. Hapus Mahasiswa");
            System.out.println("5. Keluar");
            System.out.print("Pilih menu: ");
            choice = scanner.nextInt();
            scanner.nextLine();
        
            switch(choice){
                case 1:
                    System.out.print("Masukkan NIM: ");
                    String nim = scanner.nextLine();
                    System.out.print("Masukkan Nama: ");
                    String name = scanner.nextLine();
                    System.out.print("Masukkan Jurusan: ");
                    String major = scanner.nextLine();
                    records.add(new Student(nim, name, major));
                    System.out.println("Mahasiswa berhasil ditambahkan!");
                    break;
                case 2:
                    System.out.println("\nDaftar Mahasiswa:");
                    if (records.isEmpty()) {
                        System.out.println("Belum ada data mahasiswa.");
                    } else {
                        for (Student s : records) {
                            System.out.println(s);
                        }
                    }
                    break;
                case 3:
                    System.out.print("Masukkan NIM yang dicari: ");
                    String searchNim = scanner.nextLine();
                    boolean found = false;
                    for (Student s : records) {
                        if (s.getNim().equalsIgnoreCase(searchNim)) {
                            System.out.println("Data ditemukan: " + s);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        System.out.println("Mahasiswa dengan NIM " + searchNim + " tidak ditemukan.");
                    }
                    break;
                case 4:
                    System.out.print("Masukkan NIM mahasiswa yang akan dihapus: ");
                    String deleteNim = scanner.nextLine();
                    boolean removed = records.removeIf(s ->
                    s.getNim().equalsIgnoreCase(deleteNim));
                    if (removed) {
                        System.out.println("Data mahasiswa berhasil dihapus.");
                    } else {
                        System.out.println("Mahasiswa dengan NIM " + deleteNim + " tidak ditemukan.");
                    }
                    break;
                case 5:
                    System.out.println("Keluar dari sistem. Terima kasih!");
                    break;
                default:
                    System.out.println("Pilihan tidak valid, coba lagi.");
            }
        } while (choice != 5);

        scanner.close();    
    }
}