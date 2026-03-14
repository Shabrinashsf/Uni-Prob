public abstract class LivingBeing {
    private String name;
    
    public LivingBeing(String name){
        this.name = name;
    }
    
    public String getName(){
        return name;
    }
    
    // common method
    public void breathe(){
        System.out.println(name + " is breathing");
    }
    
    // abstract method
    public abstract void grow();
}