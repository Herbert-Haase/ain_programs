// FakultaetRekursiv.java
public final class FakultaetRekursiv {
    private FakultaetRekursiv() { }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        System.out.println(fakultaet(n));
    }

    private static long fakultaet(long n) {
        if (n == 0) {
            return 1;
        }

        return  n * fakultaet(n - 1);
/*
        long f = fakultaet(n - 1);
        return n * f;
*/
    }
}

