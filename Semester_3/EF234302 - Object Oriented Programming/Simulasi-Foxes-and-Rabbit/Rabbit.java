import java.util.List;

public class Rabbit extends Animal {
    private static final int MIN_REPRODUCTION_AGE = 5;  
    private static final int MAX_LIFESPAN = 50;  
    private static final double REPRODUCTION_PROBABILITY = 0.15;  
    private static final int MAX_OFFSPRING = 5;
    
    public Rabbit(boolean randomAge, Field field, Location location) {  
           super(randomAge, field, location);  
    }
    
    @Override  
    public void act(List<Animal> newRabbits) {  
        incrementAge();  
        if (isAlive()) {  
            giveBirth(newRabbits);  
            Location newLocation = field.getFreeNearbyLoc(location);  
            if (newLocation != null) {  
                setLocation(newLocation);  
            } 
            else {  
                setDead();  
            }  
        }  
    }
    
    public void setDead() {  
        isAlive = false;  
        if (location != null) {  
            field.clear(location);  
            location = null;  
            field = null;  
        }  
    }
    
    public void setLocation(Location newLocation) {  
        if (location != null) {  
            field.clear(location);  
            location = newLocation;  
        }  
    }
    
    protected int getBreedingAge() {  
        return MIN_REPRODUCTION_AGE;  
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
       
    @Override  
    protected Animal createOffspring(Field field, Location location) {  
        return new Rabbit(false, field, location);  
    }  
}