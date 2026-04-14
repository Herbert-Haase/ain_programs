// Value.java
public final class Value extends Expr {
    public final String value;

    // Aufruf des Konstruktors nur in ExprBuilder
    Value(String value) {
        this.value = value;
    }

    @Override
    public String toString() {
        return this.value;
    }
}

