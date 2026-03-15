import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class LoginFrame extends JFrame {
    private final JTextField txtUsername;
    private final JPasswordField txtPassword;
    private final LoginController controller;
    
    public LoginFrame(){
        super("Login Form");
        
        controller = new LoginController();

        JLabel lblUsername = new JLabel("Username:");
        JLabel lblPassword = new JLabel("Password:");

        txtUsername = new JTextField(15);
        txtPassword = new JPasswordField(15);

        JButton btnLogin = new JButton("Login");
        JButton btnCancel = new JButton("Cancel");

        btnLogin.addActionListener(new LoginAction());
        btnCancel.addActionListener(new CancelAction());

        JPanel panel = new JPanel(new GridLayout(3, 2, 10, 10));
        panel.add(lblUsername);
        panel.add(txtUsername);
        panel.add(lblPassword);
        panel.add(txtPassword);
        panel.add(btnLogin);
        panel.add(btnCancel);

        add(panel);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(300, 180);
        setLocationRelativeTo(null);
        setVisible(true);
    }
    
    private class LoginAction implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String user = txtUsername.getText();
            String pass = new String(txtPassword.getPassword());

            if (controller.checkLogin(user, pass)) {
                JOptionPane.showMessageDialog(null, "Login Granted!");
            } else {
                JOptionPane.showMessageDialog(null, "Login Denied!");
            }
        }
    }
    
    private class CancelAction implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            txtUsername.setText("");
            txtPassword.setText("");
            txtUsername.requestFocus();
        }
    }
}