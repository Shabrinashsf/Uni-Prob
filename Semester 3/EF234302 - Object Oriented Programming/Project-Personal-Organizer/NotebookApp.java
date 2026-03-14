import java.util.ArrayList;
import java.util.Scanner;

public class NotebookApp {
    public static void main(String[] args){
        ArrayList<Note> notes = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        int choice;
        
        do {
            System.out.println("\n=== Personal Notebook ===");
            System.out.println("1. Tambah Catatan");
            System.out.println("2. Lihat Semua Catatan");
            System.out.println("3. Cari Catatan");
            System.out.println("4. Hapus Catatan");
            System.out.println("5. Keluar");
            System.out.print("Pilih menu: ");
            choice = scanner.nextInt();
            scanner.nextLine();
            
            switch(choice){
                case 1:
                    System.out.print("Masukkan judul catatan: ");
                    String title = scanner.nextLine();
                    System.out.print("Masukkan isi catatan: ");
                    String content = scanner.nextLine();
                    notes.add(new Note(title, content));
                    System.out.println("Catatan berhasil ditambahkan!");
                    break;
                case 2:
                    System.out.println("\nDaftar Catatan:");
                    if (notes.isEmpty()) {
                        System.out.println("Belum ada catatan.");
                    } else {
                        for (int i = 0; i < notes.size(); i++) {
                            System.out.println((i + 1) + ". " + notes.get(i).getTitle());
                        }
                    }
                    break;
                case 3:
                     System.out.print("Masukkan judul catatan yang dicari: ");
                    String searchTitle = scanner.nextLine().toLowerCase();
                    boolean found = false;
                    for (Note note : notes) {
                        if (note.getTitle().toLowerCase().contains(searchTitle)) {
                            System.out.println("\nCatatan ditemukan:\n" + note);
                            found = true;
                        }
                    }
                    if (!found) {
                        System.out.println("Catatan tidak ditemukan.");
                    }
                    break;
                case 4:
                    System.out.print("Masukkan judul catatan yang akan dihapus: ");
                    String deleteTitle = scanner.nextLine().toLowerCase();
                    boolean removed = notes.removeIf(note ->
                    note.getTitle().toLowerCase().equals(deleteTitle));
                    if (removed) {
                        System.out.println("Catatan berhasil dihapus.");
                    } else {
                        System.out.println("Catatan dengan judul tersebut tidak ditemukan.");
                    }
                    break;
                case 5:
                    System.out.println("Keluar dari Notebook. Sampai jumpa!");
                    break;
                default:
                    System.out.println("Pilihan tidak valid, coba lagi.");
            }
        } while (choice != 5);
        
        scanner.close();
    }
}