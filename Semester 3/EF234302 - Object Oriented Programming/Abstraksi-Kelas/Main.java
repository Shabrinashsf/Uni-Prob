public class Main {
    public static void main(String[] args) {
        LivingBeing human = new Human("Budi");
        LivingBeing animal = new Animal("cat");
        LivingBeing plant = new Plant("Rose");
        
        human.breathe();
        human.grow();
        
        animal.breathe();
        animal.grow();
        
        plant.breathe();
        plant.grow();
        
        ((Human) human).speak();
        ((Animal) animal).move();
        ((Plant) plant).photosynthesize();
    }
}