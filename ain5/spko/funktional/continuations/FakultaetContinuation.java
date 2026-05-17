// FakultaetContinuation.java
import java.util.function.LongConsumer;

public final class FakultaetContinuation {
    private FakultaetContinuation() { }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        fakultaet(System.out::println, n);
    }

    private static void fakultaet(LongConsumer c, long n) {
        if (n == 0) {
            c.accept(1);
            return;
        }

        fakultaet(f -> c.accept(n * f), n - 1);
    }
}

