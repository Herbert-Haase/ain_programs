// FakultaetContinuationSchleife.java
import java.util.function.LongConsumer;

public final class FakultaetContinuationSchleife {
    private FakultaetContinuationSchleife() { }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        fakultaet(System.out::println, n);
    }

    private static void fakultaet(LongConsumer c, long n) {
        while (true) {
            if (n == 0) {
                c.accept(1);
                return;
            }

            final var cc = c;
            final var nn = n;
            c = f -> cc.accept(nn * f);
            n = nn - 1;
        }
    }
}

