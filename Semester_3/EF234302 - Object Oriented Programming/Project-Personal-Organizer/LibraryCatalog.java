import java.util.ArrayList;
import java.util.Scanner;

public class LibraryCatalog {
    public static void main(String[] args){
        ArrayList<Book> catalog = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        int choice;
        
        do {
            System.out.println("\n=== Library Catalog ===");
            System.out.println("1. Tambah Buku");
            System.out.println("2. Lihat Semua Buku");
            System.out.println("3. Cari Buku");
            System.out.println("4. Hapus Buku");
            System.out.println("5. Keluar");
            System.out.print("Pilih menu: ");
            choice = scanner.nextInt();
            scanner.nextLine();
            
            switch(choice) {
                case 1:
                    System.out.print("Masukkan judul buku: ");
                    String title = scanner.nextLine();
                    System.out.print("Masukkan nama penulis: ");
                    String author = scanner.nextLine();
                    System.out.print("Masukkan tahun terbit: ");
                    int year = scanner.nextInt();
                    catalog.add(new Book(title, author, year));
                    System.out.println("Buku berhasil ditambahkan!");
                    break;
                case 2:
                    System.out.println("\nDaftar Buku:");
                    if (catalog.isEmpty()) {
                        System.out.println("Tidak ada buku dalam katalog.");
                    } else {
                        for (int i = 0; i < catalog.size(); i++) {
                            System.out.println((i + 1) + ". " + catalog.get(i));
                        }
                    }
                    break;
                case 3:
                    System.out.print("Masukkan judul buku yang dicari: ");
                    String searchTitle = scanner.nextLine().toLowerCase();
                    boolean found = false;
                    for (Book book : catalog) {
                        if (book.getTitle().toLowerCase().contains(searchTitle)) {
                            System.out.println(book);
                            found = true;
                        }
                    }
                    if (!found) {
                        System.out.println("Buku tidak ditemukan.");
                    }
                    break;
                case 4:
                    System.out.print("Masukkan nomor buku yang akan dihapus: ");
                    int index = scanner.nextInt();
                    if (index > 0 && index <= catalog.size()) {
                        catalog.remove(index - 1);
                        System.out.println("Buku berhasil dihapus!");
                    } else {
                        System.out.println("Nomor buku tidak valid.");
                    }
                    break;
                case 5:
                    System.out.println("Keluar dari katalog. Terima kasih!");
                    break;
                default:
                    System.out.println("Pilihan tidak valid, coba lagi.");
            }
        } while (choice != 5);
        
        scanner.close();
    }
}