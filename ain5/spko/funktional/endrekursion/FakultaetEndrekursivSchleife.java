// FakultaetEndrekursivSchleife.java
public final class FakultaetEndrekursivSchleife {
    private FakultaetEndrekursivSchleife() { }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        System.out.println(fakultaet(n));
    }

    private static long fakultaet(long n) {
        return fakultaet(1, n);
    }

    private static long fakultaet(long f, long n) {
        while (true) {
            if (n == 0) {
                return f;
            }

            f = n * f;
            n = n - 1;
            // continue;
        }
    }
}

