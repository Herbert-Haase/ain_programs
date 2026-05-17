// Funktional.java
import java.util.Scanner;
import java.util.function.UnaryOperator;
import java.util.function.DoubleSupplier;

public final class Funktional {
    private Funktional() { }

    private static final Scanner EINGABE = new Scanner(System.in);

    public static void main(String[] args) {
        System.out.printf(
            "%.2f%n", brutto(EINGABE::nextDouble, steuerBerechnung(true)));
        System.out.printf(
            "%.2f%n", brutto(EINGABE::nextDouble, steuerBerechnung(false)));
    }

    // Funktion hoeherer Ordung: Funktion als Rueckgabewert
    private static
    UnaryOperator<Double> steuerBerechnung(boolean ermaessigt) {
        double steuer = ermaessigt ? 1.07 : 1.19;
        return (netto) -> netto * steuer;
    }

    // Funktion hoeherer Ordung: Funktionen als Parameter
    private static
    double brutto(DoubleSupplier netto, UnaryOperator<Double> versteuern) {
        return versteuern.apply(netto.getAsDouble());
    }
}

