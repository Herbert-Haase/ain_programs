// Value.java
package expr.ast;

public final class Value extends Expr {
    public final String value;

    // Aufruf des Konstruktors nur in ast.ExprBuilder
    Value(String value) {
        this.value = value;
    }

    @Override
    public void accept(ExprVisitor v) {
        v.visitValue(this);
    }

    @Override
    public String toString() {
        return this.value;
    }
}

