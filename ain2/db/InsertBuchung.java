import java.sql.*;
import java.util.LinkedList;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class InsertBuchung {
  public static void insert(String fw, String email, String anreisetag, String abreisetag) {

    String name = "dbsys52";
    String passwd = "2002";
    Connection conn = null;
    Statement stmt = null;
    ResultSet rset = null;

    String feWoNr;
    LocalDate currentDate = LocalDate.now();
    DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
    String buchungsZeit = currentDate.format(formatter);

    try {
      DriverManager.registerDriver(new oracle.jdbc.OracleDriver()); // Treiber laden
      String url = "jdbc:oracle:thin:@oracle19c.in.htwg-konstanz.de:1521:ora19c"; // String für DB-Connection
      conn = DriverManager.getConnection(url, name, passwd); // Verbindung erstellen

      conn.setTransactionIsolation(Connection.TRANSACTION_SERIALIZABLE); // Transaction Isolations-Level setzen
      conn.setAutoCommit(false); // Kein automatisches Commit

      stmt = conn.createStatement(); // Statement-Objekt erzeugen
      //
      rset = stmt.executeQuery("Select feWoNr From Buchung Where name_ = '" + fw + "'");
      while (rset.next()) {
        feWoNr = rset.getString("feWoNr");
        break;
      }

      PreparedStatement sucheFW = conn.prepareStatement(
          "INSERT INTO Buchung (feWoNr, kundenEmail, buchungsZeit, startTag, endTag," +
              " betrag) " +

              "VALUES (?, ?, TO_DATE(?, 'YYYY-MM-DD'), " +
              "TO_DATE(?, 'YYYY-MM-DD'), TO_DATE(?, 'YYYY-MM-DD'), 1200);");

      sucheFW.setString(1, feWoNr);
      sucheFW.setString(2, email);
      sucheFW.setString(3, buchungsZeit);
      sucheFW.setString(4, anreisetag);
      sucheFW.setString(5, abreisetag);

      sucheFW.executeQuery(); // Query ausführen

      stmt.close(); // Verbindung trennen
      conn.commit();
      conn.close();
    } catch (SQLException se) { // SQL-Fehler abfangen
      System.out.println();
      System.out
          .println("SQL Exception occurred while establishing connection to DBS: "
              + se.getMessage());
      System.out.println("- SQL state  : " + se.getSQLState());
      System.out.println("- Message    : " + se.getMessage());
      System.out.println("- Vendor code: " + se.getErrorCode());
      System.out.println();
      System.out.println("EXITING WITH FAILURE ... !!!");
      System.out.println();
      try {
        conn.rollback(); // Rollback durchführen
      } catch (SQLException e) {
        e.printStackTrace();
      }

      // System.exit(-1);
    }
  }
}
