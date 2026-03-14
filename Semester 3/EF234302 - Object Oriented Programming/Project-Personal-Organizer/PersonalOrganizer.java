import java.util.ArrayList;
import java.util.Scanner;

public class PersonalOrganizer {
    public static void main(String[] args) {
        ArrayList<Task>tasks = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        int choice;
        
        do {
            System.out.println("\n=== Personal Organizer ===");
            System.out.println("1. Tambah Tugas");
            System.out.println("2. Lihat Semua Tugas");
            System.out.println("3. Hapus Tugas");
            System.out.println("4. Keluar");
            System.out.print("Pilih menu: ");
            choice = scanner.nextInt();
            scanner.nextLine();
            
            switch(choice) {
                case 1:
                    System.out.print("Masukkan judul tugas: ");
                    String title = scanner.nextLine();
                    System.out.print("Masukkan deskripsi tugas: ");
                    String description = scanner.nextLine();
                    tasks.add(new Task(title, description));
                    System.out.println("Tugas berhasil ditambahkan!");
                    break;
                case 2:
                    System.out.println("\nDaftar Tugas:");
                    if (tasks.isEmpty()) {
                        System.out.println("Tidak ada tugas.");
                    } else {
                        for (int i = 0; i < tasks.size(); i++) {
                            System.out.println((i + 1) + ". " + tasks.get(i));
                        }
                    }
                    break;
                case 3:
                    System.out.print("Masukkan nomor tugas yang akan dihapus: ");
                    int index = scanner.nextInt();
                    if (index > 0 && index <= tasks.size()) {
                        tasks.remove(index - 1);
                        System.out.println("Tugas berhasil dihapus!");
                    } else {
                        System.out.println("Nomor tugas tidak valid.");
                    }
                    break;
                case 4:
                    System.out.println("Terima kasih! Keluar dari aplikasi.");
                    break;
                default:
                    System.out.println("Pilihan tidak valid, coba lagi.");
            }
        } while (choice != 4);
        
        scanner.close();
    }
}