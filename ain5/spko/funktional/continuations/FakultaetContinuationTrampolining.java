// FakultaetContinuationTrampolining.java
import java.util.function.LongFunction;

public final class FakultaetContinuationTrampolining {
    private FakultaetContinuationTrampolining() { }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        for (var t = fakultaet(f -> () -> { System.out.println(f); return null; }, n);
             t != null;
             t = t.next())
        { }
    }

    private static Trampolining fakultaet(LongFunction<Trampolining> c, long n) {
        if (n == 0) {
            return () -> c.apply(1);
        }

        return () -> fakultaet(f -> () -> c.apply(n * f), n - 1);
    }
    
    @FunctionalInterface
    private interface Trampolining {
        Trampolining next();
    }
}

