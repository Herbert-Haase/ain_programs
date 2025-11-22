// Date.java

import java.util.Calendar;

public final class Date {
    private final int day;
    private final int month;
    private final int year;

    public Date() {
        Calendar today = Calendar.getInstance();
        this.day = today.get(Calendar.DAY_OF_MONTH);
        this.month = today.get(Calendar.MONTH) + 1;
        this.year = today.get(Calendar.YEAR);
    }

    public Date(final int d, final int m, final int y) {
        if (d < 1 || d > 31 || m < 1 || m > 12) {
            throw new IllegalArgumentException("Falsches Datum");
        }

        this.day = d;
        this.month = m;
        this.year = y;
    }

    public void print() {
        System.out.printf("%d-%02d-%02d%n", this.year, this.month, this.day);
    }
}

