// FakultaetContinuationExplizit.java
import java.util.function.LongConsumer;

public final class FakultaetContinuationExplizit {
    private FakultaetContinuationExplizit() { }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        fakultaet(new PrintClosure(), n);
    }

    private static void fakultaet(LongConsumer c, long n) {
        if (n == 0) {
            c.accept(1);
            return;
        }

        fakultaet(new MultiplicationClosure(c, n), n - 1);
    }

    private static class PrintClosure implements LongConsumer {
        @Override
        public void accept(long f) {
            System.out.println(f);
        }
    }

    private static class MultiplicationClosure implements LongConsumer {
        private final LongConsumer c;
        private final long n;
        
        public MultiplicationClosure(LongConsumer c, long n) {
            this.c = c;
            this.n = n;
        }

        @Override
        public void accept(long f) {
            this.c.accept(this.n * f);
        }
    }
}

