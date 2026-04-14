// Operation.java
package expr.ast;

public final class Operation extends Expr {
    public final Expr left;
    public final String operator;
    public final Expr right;

    // Aufruf des Konstruktors nur in ast.ExprBuilder
    Operation(Expr left, String operator, Expr right) {
        this.left = left;
        this.operator = operator;
        this.right = right;
    }

    @Override
    public void accept(ExprVisitor v) {
        v.visitOperation(this);
    }

    @Override
    public String toString() {
        return this.operator;
    }
}

