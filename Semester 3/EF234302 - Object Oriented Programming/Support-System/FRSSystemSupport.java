public class FRSSystemSupport {
    private InputReader reader;
    private Responder responder;
    
    public FRSSystemSupport(){
        reader = new InputReader();
        responder = new Responder();
    }
    
    public void start(){
        boolean finished = false;
        
        System.out.println("Selamat datang di FRS ITS Support System.");
        System.out.println("Silahkan beritahu kami kendala yang Anda miliki.");
        System.out.println("Kami siap membantu segala kendala yang anda miliki.");
        System.out.println("Anda bisa mengetikkan 'bye' untuk keluar dari sistem ini.");
        
        while (!finished) {
            String input = reader.getInput();
            if (input.toLowerCase().startsWith("bye")){
                finished = true;
            } else {
                String response = responder.getResponse(input);
                System.out.println(response);
            }
        }
        
        System.out.println("Senang telah membantu Anda. Bye...");
    }
    
    public static void main(String[] args) {
        FRSSystemSupport system = new FRSSystemSupport();
        system.start();
    }
}