public class Plant extends LivingBeing {
    public Plant(String name) {
        super(name);
    }
    
    @Override
    public void grow(){
        System.out.println(getName() + " is growing as a plant.");
    }
    
    public void photosynthesize(){
        System.out.println(getName() + " is photosynthesizing.");
    }
}