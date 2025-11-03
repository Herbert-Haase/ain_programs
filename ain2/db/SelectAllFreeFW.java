import java.sql.*;
import java.util.LinkedList;

public class SelectAllFreeFW {
  public static String[] get(String ausstattung, String land, String anreisetag, String abreisetag) {

    String name = "dbsys52";
    String passwd = "2002";
    Connection conn = null;
    Statement stmt = null;
    ResultSet rset = null;
    // final String ausstattung = "Sauna";
    // final String land = "Spanien";
    // final String anreisetag = "2024-05-01";
    // final String abreisetag = "2024-05-21";

    try {
      DriverManager.registerDriver(new oracle.jdbc.OracleDriver()); // Treiber laden
      String url = "jdbc:oracle:thin:@oracle19c.in.htwg-konstanz.de:1521:ora19c"; // String für DB-Connection
      conn = DriverManager.getConnection(url, name, passwd); // Verbindung erstellen

      conn.setTransactionIsolation(Connection.TRANSACTION_SERIALIZABLE); // Transaction Isolations-Level setzen
      conn.setAutoCommit(false); // Kein automatisches Commit

      stmt = conn.createStatement(); // Statement-Objekt erzeugen

      PreparedStatement sucheFW = conn.prepareStatement("SELECT f.name_ as name, AVG(bewertSterne) as anzahlSterne " +
          "FROM dbsys52.Adresse a JOIN dbsys52.Ferienwohnung f USING(adressNr) " +
          "LEFT JOIN dbsys52.Buchung b USING(feWoNr) " +
          "LEFT JOIN dbsys52.WohnungsAusstattung w USING(feWoNr) " +
          "WHERE w.ausstName = ? AND " +
          "a.landName = ? AND " +
          "f.name_ NOT IN (SELECT f2.name_ " +
          "FROM dbsys52.Buchung b2 JOIN dbsys52.Ferienwohnung f2 USING(feWoNr) " +
          "WHERE " +
          "(b2.startTag BETWEEN TO_DATE(?, 'YYYY-MM-DD') AND TO_DATE(?, 'YYYY-MM-DD')) " +
          "OR (b2.endTag BETWEEN TO_DATE(?, 'YYYY-MM-DD') AND TO_DATE(?, 'YYYY-MM-DD')) " +
          "OR (TO_DATE(?, 'YYYY-MM-DD') BETWEEN b2.startTag AND b2.endTag " +
          "OR (TO_DATE(?, 'YYYY-MM-DD') BETWEEN b2.startTag AND b2.endTag))) " +
          "GROUP BY f.name_ " +
          "ORDER BY AVG(bewertSterne) DESC");

      sucheFW.setString(1, ausstattung);
      sucheFW.setString(2, land);
      sucheFW.setString(3, anreisetag);
      sucheFW.setString(4, abreisetag);
      sucheFW.setString(5, abreisetag);
      sucheFW.setString(6, abreisetag);
      sucheFW.setString(7, anreisetag);
      sucheFW.setString(8, anreisetag);

      rset = sucheFW.executeQuery(); // Query ausführen

      LinkedList<String> fwList = new LinkedList<>();
      while (rset.next()) {
        fwList.add(rset.getString("name"));
        // System.out.println(
        // rset.getString("name") + " "
        // + rset.getInt("anzahlSterne"));
      }
      String[] fwArray = (String[]) fwList.toArray();

      stmt.close(); // Verbindung trennen
      conn.commit();
      conn.close();
      return fwArray;
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
