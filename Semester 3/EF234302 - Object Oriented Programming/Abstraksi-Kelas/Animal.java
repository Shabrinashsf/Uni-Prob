public class Animal extends LivingBeing {
    public Animal (String name) {
        super(name);
    }
    
    @Override
    public void grow(){
        System.out.println(getName() + " is growing as an animal.");
    }
    
    public void move(){
        System.out.println(getName() + " is moving.");
    }
}