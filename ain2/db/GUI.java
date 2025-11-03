import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GUI extends JFrame implements ActionListener {

  JTextField land;
  JTextField anreisetag;
  JTextField abreisetag;
  JTextField ausstattung;
  JTextField email;
  JPanel panel;

  public GUI() {
    this.setTitle("Ferienwohnung buchen");
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    // Select: Land, Anreisetag, Abreisetag, Austattung
    // Buchung: Ferienwohnung

    JLabel landLabel = new JLabel("Land");
    JLabel anreisetagLabel = new JLabel("Anreise");
    JLabel abreisetagLabel = new JLabel("Abreise");
    JLabel ausstattungLabel = new JLabel("Ausstattung");
    JLabel emailLabel = new JLabel("Email");
    land = new JTextField("Spanien", 10);
    anreisetag = new JTextField("2024-05-01", 10);
    abreisetag = new JTextField("2024-05-21", 10);
    ausstattung = new JTextField("Sauna", 10);
    email = new JTextField("schmidt.maria@example.com", 20);

    JButton button = new JButton("Submit");
    button.addActionListener(this);

    JPanel panel1 = new JPanel();
    JPanel panel2 = new JPanel();
    JPanel panel3 = new JPanel();
    JPanel panel4 = new JPanel();
    JPanel panel5 = new JPanel();
    panel = new JPanel();

    panel1.add(landLabel);
    panel1.add(land);
    panel2.add(anreisetagLabel);
    panel2.add(anreisetag);
    panel3.add(abreisetagLabel);
    panel3.add(abreisetag);
    panel4.add(ausstattungLabel);
    panel4.add(ausstattung);
    panel5.add(emailLabel);
    panel5.add(email);

    panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
    panel.add(panel1);
    panel.add(panel2);
    panel.add(panel3);
    panel.add(panel4);
    panel.add(panel5);
    panel.add(button);
    panel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
    setContentPane(panel);

    this.setLocationRelativeTo(null);
    this.pack();
    this.setVisible(true);
  }

  public void buchFW(String fw, String email, String anreisetag, String abreisetag) {
    // insert sql insertion buchung
    // anreisedatum, abreisedatum
  }

  public void seeFW(String[] options, String email, String anreisetag, String abreisetag) {

    String fw = (String) JOptionPane.showInputDialog(panel, "Tu was", "input dialog", JOptionPane.PLAIN_MESSAGE, null,
        options, options[0]);

    if ((fw != null) && (fw.length() > 0)) {
      buchFW(fw, email, anreisetag, abreisetag);
    }
  }

  public void actionPerformed(ActionEvent e) {
    String land_s = land.getText();
    String anreisetag_s = anreisetag.getText();
    String abreisetag_s = abreisetag.getText();
    String ausstattung_s = ausstattung.getText();
    String email_s = email.getText();

    seeFW(SelectAllFreeFW.get(ausstattung_s, land_s, anreisetag_s, abreisetag_s), email_s, anreisetag_s, abreisetag_s);
  }

  public static void main(String[] args) {
    JFrame myapp = new GUI();
  }
}
