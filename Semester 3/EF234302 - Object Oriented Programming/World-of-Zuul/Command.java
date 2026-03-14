public class Command {
   private String commandWord;
   private String secondWord;
   
   public Command(String firstWord, String secondWord){
       commandWord = firstWord;
       this.secondWord = secondWord;
   }
   
   public String getCommandWord(){
       return commandWord;
   }
   
   public String getSecondWord(){
       return secondWord;
   }
   
   public boolean hasSecondWord(){
       return (secondWord != null);
   }
   
   public boolean isUnknown(){
       return (commandWord == null);
   }
}