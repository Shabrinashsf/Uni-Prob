import java.util.*;

public class Inventory {
    private int stockCoffee = 10;
    private int stockMilk = 10;
    private int stockSugar = 10;
    private int stockWater = 10;
    
    public boolean cekStock(boolean sugar, boolean milk) {
        if(stockCoffee <= 0 || stockWater <= 0){
            return false;
        }
        if (sugar && stockSugar <= 0) {
            return false;
        }
        if (milk && stockMilk <= 0) {
            return false;
        }
        return true;
    }
    
    public void kurangiStock(boolean sugar, boolean milk){
        stockCoffee--;
        stockWater--;
        if (sugar) {
            stockSugar--;
        }
        if (milk) {
            stockMilk--;
        }
        cekPeringatanStok();
    }
    
    public void refill(int coffee, int milk, int sugar, int water){
        stockCoffee += coffee;
        stockMilk += milk;
        stockSugar += sugar;
        stockWater += water;
        System.out.println("Stok berhasil diisi ulang!");
        tampilkanStok();
    }
    
    public void tampilkanStok(){
        System.out.println("\n=== STATUS STOK ===");
        System.out.println("Kopi  : " + stockCoffee);
        System.out.println("Susu  : " + stockMilk);
        System.out.println("Gula  : " + stockSugar);
        System.out.println("Air   : " + stockWater);
    }
    
    public boolean stockHabis() {
        return (stockCoffee <= 0 || stockMilk <= 0 || stockSugar <= 0 || stockWater <= 0);
    }
    
    public void cekPeringatanStok(){
        if(stockHabis()){
            System.out.println("\n⚠️  PERINGATAN: Salah satu stok bahan habis!");
            System.out.println("Silakan hubungi admin untuk melakukan refill bahan!");
        }
    }
}