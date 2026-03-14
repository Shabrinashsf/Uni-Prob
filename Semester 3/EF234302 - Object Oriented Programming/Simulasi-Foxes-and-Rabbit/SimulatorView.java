import java.util.HashMap;  
import java.util.Map;
 public class SimulatorView {  
      private int row;  
      private int col;  
      private Map<Class<?>, Character> symbols;  
       
      public SimulatorView(int row, int col, Field field) {  
           this.row = row;  
           this.col = col;  
           symbols = new HashMap<Class<?>, Character>();  
      }  
       
      public void setSymbol(Class<?> animal, char symbol) {  
           symbols.put(animal, symbol);  
      }  
       
      public void show(int step, Field field) {  
           System.out.println("Simulation step " + step + ": ");  
           for (int i = 0; i < row; i++) {  
                for (int j = 0; j < col; j++) {  
                     Object animal = field.getObjectAt(new Location(i, j));  
                     if (animal == null) {  
                          System.out.print(". ");  
                     } else {  
                          Character symbol = symbols.get(animal.getClass());  
                          System.out.print((symbol != null ? symbol : '?') + " ");  
                     }  
                }  
                System.out.println();  
           }  
           System.out.println();  
      }  
 } 