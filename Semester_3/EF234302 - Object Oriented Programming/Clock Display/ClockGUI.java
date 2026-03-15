import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.time.LocalTime;

class ClockGUI extends JFrame {
    private ClockDisplay clock;
    private JLabel timeLabel;
    private Timer timer;

    public ClockGUI(){
        LocalTime curTime = LocalTime.now();
        clock = new ClockDisplay(curTime.getHour(), curTime.getMinute(), curTime.getSecond());

        setTitle("What Time is it?");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        timeLabel = new JLabel(clock.getTime(), SwingConstants.CENTER);
        timeLabel.setFont(new Font("Serif", Font.BOLD, 40));
        add(timeLabel, BorderLayout.CENTER);

        startClock();

        setVisible(true);
    }

    private void startClock(){
        timer = new Timer(1000, new ActionListener() {
            public void actionPerformed(ActionEvent e){
                clock.timeTick();
                timeLabel.setText(clock.getTime());
            }
        });

        timer.start();
    }
}