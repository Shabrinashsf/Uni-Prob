import java.util.List;  
import java.util.Random;    
 public abstract class Animal {  
  protected int age;  
  protected boolean isAlive;  
  protected Location location;  
  protected Field field;  
  protected static final Random rand = new Random();  
   
  public Animal(boolean randomAge, Field field, Location location) {  
       if (randomAge) {  
            this.age = rand.nextInt(getMaxLifespan());  
       } 
       else {  
            this.age = 0;  
       }  
       this.isAlive = true;  
       this.field = field;  
       setLocation(location);  
  }  
   
  public int age() {  
   return age;  
  }  
   
  public boolean isAlive() {  
   return isAlive;  
  }  
   
  public Location getLocation() {  
   return location;  
  }  
   
  public void setLocation(Location newLocation) {  
       if (location != null) {  
            field.clear(location);  
       }  
       location = newLocation;  
       field.place(this, newLocation);  
  }  
   
  public String printLocation(Location location) {  
   return String.format("(" + (location.getRow() + 1) + ", " + (location.getCol() + 1) + ")");  
  }  
   
  public void setDead() {  
       isAlive = false;  
       if (location != null) {  
            field.clear(location);  
            location = null;  
       }  
       field = null;  
  }  
   
  public boolean canReproduce() {  
       return age >= getBreedingAge();  
  }  
   
  protected void incrementAge() {  
       age++;  
       if (age > getMaxLifespan()) {  
            setDead();  
       }  
  }  
   
  protected void giveBirth(List<Animal> newAnimals) {  
       if (location == null){  
            return;
        }
   
       List<Location> freeLocs = field.getAllFreeNearbyLocs(location);  
       int totalOffspring = reproduce();  
       
       for (int i = 0; i < totalOffspring && freeLocs.size() > 0; i++) {  
            Location loc = freeLocs.remove(0);  
            Animal offspring = createOffspring(field, loc);  
            newAnimals.add(offspring);  
       }  
  }  
   
  protected int reproduce() {  
       int totalOffspring = 0;  
       if (canReproduce() && rand.nextDouble() <= getReproductionProbability()) {  
            totalOffspring = rand.nextInt(getMaxOffspring()) + 1;  
       }  
       return totalOffspring;  
  }  
   
  public abstract void act(List<Animal> newAnimals);  
   
  abstract protected int getBreedingAge();  
   
  abstract protected int getMaxLifespan();  
   
  abstract protected double getReproductionProbability();  
   
  abstract protected int getMaxOffspring();  
   
  abstract protected Animal createOffspring(Field field, Location location);  
 }