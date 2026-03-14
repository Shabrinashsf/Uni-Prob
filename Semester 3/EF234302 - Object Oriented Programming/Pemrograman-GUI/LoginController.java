public class LoginController {
    private final String USER = "shabrinashsf";
    private final String PASS = "shab";
    
    public boolean checkLogin(String username, String password){
        return username.equals(USER) && password.equals(PASS);
    }
}