// FakultaetEndrekursiv.java
public final class FakultaetEndrekursiv {
    private FakultaetEndrekursiv() { }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        System.out.println(fakultaet(n));
    }

    private static long fakultaet(long n) {
        return fakultaet(1, n);
    }

    private static long fakultaet(long f, long n) {
        if (n == 0) {
            return f;
        }

        return fakultaet(n * f, n - 1);
    }
}

