// Expr.java
package expr.ast;

public abstract class Expr {
    public abstract void accept(ExprVisitor visitor);
}

