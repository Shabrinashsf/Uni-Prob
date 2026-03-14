import java.util.Iterator;  
import java.util.List;

public class Fox extends Animal {
    private static final int RABBIT_ENERGY_VALUE = 10;  
      private static final int MAX_LIFESPAN = 70;  
      private static final double REPRODUCTION_PROBABILITY = 0.15;  
      private static final int MAX_OFFSPRING = 3;  
      private static final int INITIAL_ENERGY = 20;  
       
      private int energyLevel;  
       
      public Fox(boolean randomAge, Field field, Location location) {  
           super(randomAge, field, location);  
           energyLevel = INITIAL_ENERGY;  
      }
      
    @Override  
      public void act(List<Animal> newFoxes) {  
           incrementAge();  
           incrementHunger();  
           if (isAlive()) {   
                giveBirth(newFoxes);  
                Location newLocation = findFood();  
                if (newLocation == null) {  
                     newLocation = field.getFreeNearbyLoc(location);  
                }  
                if (newLocation != null) {  
                     setLocation(newLocation);  
                } 
                else {  
                     setDead();  
                }  
           }  
      }
      
    private Location findFood() {  
           List<Location> nearbyLocs = field.getNearbyLocs(location);  
           Iterator<Location> it = nearbyLocs.iterator();  
           while (it.hasNext()) {  
                Location loc = it.next();  
                Object animal = field.getObjectAt(loc);  
                if (animal instanceof Rabbit) {  
                     Rabbit rabbit = (Rabbit) animal;  
                     if (rabbit.isAlive()) {  
                          rabbit.setDead();  
                          energyLevel += RABBIT_ENERGY_VALUE;  
                          return loc;  
                     }  
                }  
           }  
           return null;  
      }  
       
      private void incrementHunger() {  
           energyLevel--;  
           if (energyLevel <= 0) {  
                setDead();  
           }  
      }  
       
      protected int getBreedingAge() {  
           return 10;  
      }  
       
      protected int getMaxLifespan() {  
           return MAX_LIFESPAN;  
      }  
       
      protected double getReproductionProbability() {  
           return REPRODUCTION_PROBABILITY;  
      }  
       
      protected int getMaxOffspring() {  
           return MAX_OFFSPRING;  
      }  
       
      protected Animal createOffspring(Field field, Location location) {  
           return new Fox(false, field, location);  
      }
}