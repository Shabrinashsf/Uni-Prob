import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class App extends JFrame {

    public App() {
        // 1. Pengaturan Dasar Frame
        setTitle("🃏 Match Cards - Pilih Kesulitan");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(400, 350);
        setResizable(false);
        setLocationRelativeTo(null);

        // 2. Panel Utama untuk Konten
        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS)); 
        mainPanel.setBorder(BorderFactory.createEmptyBorder(30, 30, 30, 30));
        mainPanel.setBackground(new Color(240, 240, 240));

        // 3. Judul Game
        JLabel titleLabel = new JLabel("🃏 Match Cards Game 🃏");
        titleLabel.setFont(new Font("Segoe UI", Font.BOLD, 28)); 
        titleLabel.setAlignmentX(Component.CENTER_ALIGNMENT);  
        titleLabel.setForeground(new Color(0, 102, 204));    

        // 4. Label Instruksi
        JLabel instructionLabel = new JLabel("Pilih Tingkat Kesulitan untuk Mulai:");
        instructionLabel.setFont(new Font("Segoe UI", Font.PLAIN, 16));
        instructionLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        instructionLabel.setBorder(BorderFactory.createEmptyBorder(15, 0, 25, 0));  

        // 5. Panel untuk Tombol
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 20, 10)); 
        buttonPanel.setBackground(new Color(240, 240, 240));

        // 6. Membuat Tombol-Tombol Kesulitan dengan action listener
        JButton easyButton = createDifficultyButton("EASY", new Color(100, 200, 100), new Color(255, 255, 255));
        easyButton.addActionListener(e -> startGame(0));

        JButton mediumButton = createDifficultyButton("MEDIUM", new Color(255, 180, 50), new Color(0, 0, 0));
        mediumButton.addActionListener(e -> startGame(1));

        JButton hardButton = createDifficultyButton("HARD", new Color(220, 50, 50), new Color(255, 255, 255));
        hardButton.addActionListener(e -> startGame(2));
        
        // 7. Menambahkan komponen ke Panel Tombol
        buttonPanel.add(easyButton);
        buttonPanel.add(mediumButton);
        buttonPanel.add(hardButton);

        // 8. Menambahkan semua komponen ke Panel Utama
        mainPanel.add(titleLabel);
        mainPanel.add(instructionLabel);
        mainPanel.add(buttonPanel);

        // 9. Menambahkan Panel Utama ke Frame
        add(mainPanel);

        // 10. Menampilkan Frame
        setVisible(true);
    }

    /**
     * Metode pembantu untuk membuat JButton dengan gaya kustom
     */
    private JButton createDifficultyButton(String text, Color bgColor, Color fgColor) {
        JButton button = new JButton(text);
        button.setFont(new Font("Segoe UI", Font.BOLD, 15));
        button.setBackground(bgColor);
        button.setForeground(fgColor);
        button.setFocusPainted(false); 
        button.setPreferredSize(new Dimension(100, 45));
        return button;
    }

    /**
     * Metode untuk memulai game sesuai pilihan dan memanggil class level yang sesuai
     */
    private void startGame(int choice) {
        this.dispose(); 
        
        if (choice == 0) {
            System.out.println("Memulai MatchCardsLevel1 (Easy)");
            new MatchCardsLevel1(); 
        } else if (choice == 1) {
            System.out.println("Memulai MatchCardsLevel2 (Medium)");
            new MatchCardsLevel2();
        } else if (choice == 2) {
            System.out.println("Memulai MatchCardsLevel3 (Hard)");
            new MatchCardsLevel3();
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new App());
    }
}