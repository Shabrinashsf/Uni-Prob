import java.util.ArrayList;  
import java.util.Iterator;  
import java.util.List;  
import java.util.Random; 
/**
 * Write a description of class Simulator here.
 *
 * @author Isabella Sienna Sulisthio
 * @version 11 Nov 2025
 */
 
   
 public class Simulator {  
      private static final int DEFAULT_ROW = 30;  
      private static final int DEFAULT_COL = 30;  
      private List<Animal> animals;  
      private Field field;  
      private int step;  
      private SimulatorView view;  
       
      public Simulator(int row, int col) {  
           if (row <= 0 || col <= 0) {  
                System.out.println("The row and column must be greater than 0");  
                System.out.println("Using default row and column");  
                row = DEFAULT_ROW;  
                col = DEFAULT_COL;  
           }  
           animals = new ArrayList<Animal>();  
           field = new Field(row, col);  
           
           view = new SimulatorView(row, col, field);  
           view.setSymbol(Rabbit.class, 'R');  
           view.setSymbol(Fox.class, 'F');  
           
           reset();  
      }  
       
      public void simulate(int maxSteps) {  
           for (int i = 0; i < maxSteps; i++) {  
            simulateOneStep();  
           }  
      }  
       
      public void reset() {  
           step = 0;  
           animals.clear();  
           field.clearAll();  
           populate();  
           view.show(step, field);  
      }  
       
      public void simulateOneStep() {  
           step++;  
           
           List<Animal> newAnimals = new ArrayList<Animal>();  
           for (Iterator<Animal> it = animals.iterator(); it.hasNext();) {  
            Animal animal = it.next();  
            animal.act(newAnimals);  
           }  
           view.show(step, field);  
      }  
       
      private void populate() {  
           field.clearAll();  
           
           double foxProbability = 0.2;  
           double rabbitProbability = 0.3;  
           
           Random rand = new Random();  
           for (int i = 0; i < field.getRow(); i++) {  
                for (int j = 0; j < field.getCol(); j++) {  
                     Location location = new Location(i, j);  
                     if (rand.nextDouble() <= foxProbability) {  
                          Fox fox = new Fox(false, field, location);  
                          animals.add(fox);  
                          field.place(fox, location);  
                     }  
                     if (rand.nextDouble() <= rabbitProbability) {  
                          Rabbit rabbit = new Rabbit(true, field, location);  
                          animals.add(rabbit);  
                          field.place(rabbit, location);  
                     }  
                }  
           }  
      }  
       
      public static void main(String[] args) {  
           Simulator simulator = new Simulator(10, 10);  
           simulator.simulate(5);  
      }  
 } 