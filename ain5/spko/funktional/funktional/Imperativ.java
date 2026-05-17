// Imperativ.java
import java.util.Scanner;

public final class Imperativ {
    private Imperativ() { }

    private static final Scanner EINGABE = new Scanner(System.in);

    public static void main(String[] args) {
        double netto = EINGABE.nextDouble();
        double bruttoErmaessigt = netto * 1.07;
        System.out.printf("%.2f%n", bruttoErmaessigt);
        double bruttoNormal = netto * 1.19;
        System.out.printf("%.2f%n", bruttoNormal);
    }
}

