import java.util.*;

public class Coffee{
    private Scanner input = new Scanner(System.in);
    private Map<String, Integer> coffeeMenu = new LinkedHashMap<>();
    private List<String> transactionLog = new ArrayList<>();
    private Inventory inventory = new Inventory();

    public Coffee() {
        coffeeMenu.put("Espresso", 15000);
        coffeeMenu.put("Americano", 12000);
        coffeeMenu.put("Latte", 18000);
        coffeeMenu.put("Cappuccino", 20000);
    }
    
    public void start(){
        boolean running = true;
        while(running){
           System.out.println("\n=== VENDING COFFEE MACHINE ===");
           System.out.println("1. Beli Kopi");
           System.out.println("2. Lihat Stok");
           System.out.println("3. Refill Stok (Admin)");
           System.out.println("4. Lihat Log Transaksi");
           System.out.println("5. Keluar");
           System.out.print("Pilih menu: ");
           int menu = input.nextInt();
        
           switch(menu){
               case 1 -> beliKopi();
               case 2 -> inventory.tampilkanStok();
               case 3 -> refillAdmin();
               case 4 -> lihatLog();
               case 5 -> {
                 running = false;
                    System.out.println("Mesin dimatikan... sampai jumpa, Shab!");
                }
               default -> System.out.println("Pilihan tidak valid!");
           }
        }
    }
    
    public void beliKopi(){
        System.out.println("\n=== PILIH JENIS KOPI ===");
        int i = 1;
        for (String kopi : coffeeMenu.keySet()) {
            System.out.println(i + ". " + kopi + " - Rp" + coffeeMenu.get(kopi));
            i++;
        }
        System.out.print("Masukkan pilihan: ");
        int pilihan = input.nextInt();
        input.nextLine();

        if (pilihan < 1 || pilihan > coffeeMenu.size()) {
            System.out.println("Pilihan tidak valid!");
            return;
        }
        
        String selectedCoffee = coffeeMenu.keySet().toArray(new String[0])[pilihan - 1];
        int harga = coffeeMenu.get(selectedCoffee);

        System.out.print("Pilih ukuran (S/M/L): ");
        String size = input.next().toUpperCase();
        switch (size) {
            case "M" -> harga += 3000;
            case "L" -> harga += 5000;
        }

        System.out.print("Tambah gula? (y/n): ");
        boolean tambahGula = input.next().equalsIgnoreCase("y");
        if (tambahGula) harga += 1000;
        
        System.out.print("Tambah susu? (y/n): ");
        boolean tambahSusu = input.next().equalsIgnoreCase("y");
        if (tambahSusu) harga += 2000;

        System.out.println("Total harga: Rp" + harga);
        System.out.print("Masukkan jumlah uang: Rp");
        int bayar = input.nextInt();

        if (bayar < harga) {
            System.out.println("Uang tidak cukup, transaksi dibatalkan!");
            return;
        }

        if (!inventory.cekStock(tambahGula, tambahSusu)) {
            System.out.println("⚠️  Stok bahan tidak cukup! Hubungi admin untuk refill.");
            return;
        }

        inventory.kurangiStock(tambahGula, tambahSusu);

        System.out.println("☕ Sedang membuat " + selectedCoffee + "...");
        System.out.println("Kopi " + selectedCoffee + " siap! Kembalian: Rp" + (bayar - harga));

        String log = String.format("[%s] %s (%s) - Rp%d", 
                                   new Date(), selectedCoffee, size, harga);
        transactionLog.add(log);
    }
    
    private void refillAdmin() {
        System.out.print("\nMasukkan password admin: ");
        String password = input.next();
        if (!password.equals("admin123")) {
            System.out.println("❌ Password salah! Akses ditolak.");
            return;
        }

        System.out.println("\n=== REFILL STOK ===");
        System.out.print("Tambah stok kopi: ");
        int kopi = input.nextInt();
        System.out.print("Tambah stok susu: ");
        int susu = input.nextInt();
        System.out.print("Tambah stok gula: ");
        int gula = input.nextInt();
        System.out.print("Tambah stok air: ");
        int air = input.nextInt();

    }
    
    private void lihatLog(){
        System.out.println("\n=== LOG TRANSAKSI ===");
        if (transactionLog.isEmpty()) {
            System.out.println("Belum ada transaksi.");
        } else {
            for (String log : transactionLog) {
                System.out.println(log);
            }
        }
    }
}