public class Human extends LivingBeing {
    public Human(String name){
        super(name);
    }
    
    @Override
    public void grow(){
        System.out.println(getName() + " is growing as a human.");
    }
    
    public void speak (){
        System.out.println(getName() + " is talking.");
    }
}