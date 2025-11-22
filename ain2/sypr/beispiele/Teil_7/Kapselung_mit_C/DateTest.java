// DateTest.java

public final class DateTest {
    private DateTest() {}

    public static void main(final String[] args) {
        Date d;

        d = new Date();
        d.print();

        d = new Date(9, 7, 2011);
        d.print();
    }
}

