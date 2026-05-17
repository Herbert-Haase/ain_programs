// FakultaetContinuationExplizitSchleife.java
import java.util.function.LongConsumer;

public final class FakultaetContinuationExplizitSchleife {
    private FakultaetContinuationExplizitSchleife() { }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        fakultaet(new PrintClosure(), n);
    }

    private static void fakultaet(LongConsumer c, long n) {
        while (true) {
            if (n == 0) {
                c.accept(1);
                return;
            }

            c = new MultiplicationClosure(c, n);
            n = n - 1;
            // continue;
        }
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
            var c = this.c;
            var n = this.n;
            while (true) {
                if (!(c instanceof MultiplicationClosure)) {
                    c.accept(n * f);
                    return;
                }
                f = n * f;
                var mc = (MultiplicationClosure) c;
                c = mc.c;
                n = mc.n;
            }
        }
    }
}

