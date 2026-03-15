import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import javax.swing.*;

public abstract class BaseMatchCards {

    // ... (Class Card, cardList, variables lainnya tetap sama) ...
    class Card {
        String cardName;
        ImageIcon cardImageIcon;

        Card(String cardName, ImageIcon cardImageIcon) {
            this.cardName = cardName;
            this.cardImageIcon = cardImageIcon;
        }
    }

    String[] cardList = {
        "1_Fireball", "2_TrenchcoatMushrooms", "3_Monk", "4_Market", "5_Steal",
        "6_King", "7_StinkTrap", "8_LightningWizard", "9_Hypnosis", "10_Beehive"
    };

    int rows, columns;
    int cardWidth = 90, cardHeight = 128;

    ArrayList<Card> cardSet;
    ImageIcon cardBackImageIcon;

    int boardWidth, boardHeight;

    JFrame frame = new JFrame("Match Cards");
    JLabel textLabel = new JLabel();
    JPanel textPanel = new JPanel();
    JPanel boardPanel = new JPanel();
    JPanel controlPanel = new JPanel();
    
    JButton homeButton = new JButton("Home Menu");
    JButton restartButton = new JButton("Restart");

    int lives = 3;
    ArrayList<JButton> board;
    Timer hideCardTimer;
    boolean gameReady = false;
    boolean isGameOver = false;
    // Variabel baru untuk membedakan fase preview awal
    private boolean isPreviewPhase = true; 
    
    JButton card1Selected = null;
    JButton card2Selected = null;
    

    public BaseMatchCards(int rows, int columns) {
        this.rows = rows;
        this.columns = columns;

        boardWidth = columns * cardWidth + 50; 
        boardHeight = rows * cardHeight + 150; 

        setupCards();
        shuffleCards();
        initUI();
        startTimer();
    }

    void initUI() {
        frame.setLayout(new BorderLayout());
        frame.setSize(boardWidth, boardHeight);
        frame.setLocationRelativeTo(null);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // --- Panel Utara (Skor) ---
        textLabel.setFont(new Font("Arial", Font.BOLD, 20));
        textLabel.setHorizontalAlignment(JLabel.CENTER);

        textLabel.setText("Lives: " + lives);
        textPanel.setBorder(BorderFactory.createEmptyBorder(10, 0, 10, 0));
        textPanel.add(textLabel);
        frame.add(textPanel, BorderLayout.NORTH);

        // --- Panel Tengah (Board Permainan) ---
        board = new ArrayList<>();
        boardPanel.setLayout(new GridLayout(rows, columns, 5, 5)); 
        boardPanel.setBorder(BorderFactory.createEmptyBorder(5, 10, 5, 10));
        
        for (int i = 0; i < cardSet.size(); i++) {
            JButton tile = new JButton();
            tile.setPreferredSize(new Dimension(cardWidth, cardHeight));
            tile.setIcon(cardSet.get(i).cardImageIcon);
            tile.setFocusable(false);
            tile.setMargin(new Insets(0, 0, 0, 0));
            tile.addActionListener(e -> handleCardClick(tile));

            board.add(tile);
            boardPanel.add(tile);
        }

        frame.add(boardPanel, BorderLayout.CENTER);

        // --- Panel Selatan (Kontrol: Restart & Home) ---
        controlPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 20, 10));
        
        // 1. Tombol Restart
        restartButton.addActionListener(e -> restartGame());
        restartButton.setFont(new Font("Arial", Font.BOLD, 14));
        restartButton.setBackground(new Color(255, 100, 100));
        restartButton.setForeground(Color.WHITE);

        // 2. Tombol Home Menu
        homeButton.addActionListener(e -> backToHome());
        homeButton.setFont(new Font("Arial", Font.BOLD, 14));
        homeButton.setBackground(new Color(100, 150, 255));
        homeButton.setForeground(Color.WHITE);

        controlPanel.add(homeButton);
        controlPanel.add(restartButton);
        frame.add(controlPanel, BorderLayout.SOUTH);

        frame.pack();
        frame.setVisible(true);
    }
    
    void backToHome() {
        frame.dispose();
        SwingUtilities.invokeLater(() -> new App());
    }

    void handleCardClick(JButton tile) {
        if (!gameReady || isGameOver) return;
        if (tile.getIcon() == cardBackImageIcon) {

            if (card1Selected == null) {
                card1Selected = tile;
                int idx = board.indexOf(tile);
                tile.setIcon(cardSet.get(idx).cardImageIcon);

            } else if (card2Selected == null) {
                card2Selected = tile;
                int idx = board.indexOf(tile);
                tile.setIcon(cardSet.get(idx).cardImageIcon);

                if (card1Selected.getIcon() != card2Selected.getIcon()) {
                    lives--;
                    textLabel.setText("Lives: " + lives);

                    if (lives <= 0) {
                        endGame(false); // Game Over
                        return;
                    }

                    // PERBAIKAN: Mengatur delay Timer menjadi 1 detik (1000ms) saat salah tebak
                    hideCardTimer.setInitialDelay(1000); 
                    hideCardTimer.start();
                    
                    // Menonaktifkan sementara klik saat menunggu hideCardTimer
                    gameReady = false; 

                } else {
                    // KARTU COCOK
                    if (isGameWon()) {
                        endGame(true);
                        return;
                    }
                    card1Selected = null;
                    card2Selected = null;
                }
            }
        }
    }
    
    boolean isGameWon() {
        int matchedCount = 0;
        for (JButton button : board) {
            if (button.getIcon() != cardBackImageIcon) { 
                matchedCount++;
            }
        }
        return matchedCount == board.size(); 
    }

    void endGame(boolean won) {
        isGameOver = true;
        gameReady = false;
        
        String message;
        if (won) {
            message = "🎉 Selamat! Anda berhasil menyelesaikan level ini! 🎉";
        } else {
            message = "💔 Game Over! Nyawa Anda habis. Coba lagi?";
            for (JButton button : board) {
                int idx = board.indexOf(button);
                button.setIcon(cardSet.get(idx).cardImageIcon);
            }
        }
        
        JOptionPane.showMessageDialog(frame, message, "Game Selesai", JOptionPane.INFORMATION_MESSAGE);
        
        for (JButton button : board) {
            button.setEnabled(false);
        }
    }

    void restartGame() {
        lives = 3;
        isGameOver = false;
        gameReady = false;
        isPreviewPhase = true; // Reset fase preview
        card1Selected = null;
        card2Selected = null;

        shuffleCards();
        for (int i = 0; i < board.size(); i++) {
            board.get(i).setIcon(cardSet.get(i).cardImageIcon); 
            board.get(i).setEnabled(true);
        }

        textLabel.setText("Lives: " + lives);
        
        // Mengatur Timer Preview Awal/Restart menjadi 10 detik (10000ms)
        hideCardTimer.setInitialDelay(10000); 
        hideCardTimer.start();
    }

    void setupCards() {
        cardSet = new ArrayList<>();

        int totalCards = rows * columns;
        int uniqueCards = totalCards / 2;

        for (int i = 0; i < uniqueCards; i++) {
            String cardName = cardList[i];
            Image img = new ImageIcon(getClass().getResource("/img/" + cardName + ".png")).getImage();
            ImageIcon icon = new ImageIcon(img.getScaledInstance(cardWidth, cardHeight, Image.SCALE_SMOOTH));
            cardSet.add(new Card(cardName, icon));
        }

        cardSet.addAll(new ArrayList<>(cardSet));

        Image back = new ImageIcon(getClass().getResource("/img/0_CardBack.png")).getImage();
        cardBackImageIcon = new ImageIcon(back.getScaledInstance(cardWidth, cardHeight, Image.SCALE_SMOOTH));
    }


    void shuffleCards() {
        for (int i = 0; i < cardSet.size(); i++) {
            int j = (int) (Math.random() * cardSet.size());
            Card temp = cardSet.get(i);
            cardSet.set(i, cardSet.get(j));
            cardSet.set(j, temp);
        }
    }

    void startTimer() {
        // Mengatur Timer Preview Awal menjadi 10 detik (10000ms)
        hideCardTimer = new Timer(10000, e -> hideCards()); 
        hideCardTimer.setRepeats(false);
        hideCardTimer.start();
    }

    void hideCards() {
        // PERBAIKAN LOGIKA UTAMA DI SINI
        if (isPreviewPhase) {
            // FASE 1: Preview Awal (setelah 10 detik)
            for (JButton button : board) {
                button.setIcon(cardBackImageIcon);
            }
            isPreviewPhase = false; // Preview selesai
            gameReady = true;       // Aktifkan klik
            // Setel delay ke 1 detik untuk match timeout berikutnya
            hideCardTimer.setInitialDelay(1000); 

        } else {
            // FASE 2: Timeout Kartu Salah (setelah 1 detik)
            if (card1Selected != null && card2Selected != null) {
                card1Selected.setIcon(cardBackImageIcon);
                card2Selected.setIcon(cardBackImageIcon);
            }
            card1Selected = null;
            card2Selected = null;
            
            // Mengaktifkan kembali klik setelah kartu tertutup (jika tidak Game Over)
            if (!isGameOver) {
                gameReady = true; 
            }
        }
    }
}