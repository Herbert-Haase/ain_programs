package expr.ast;

public final class Id extends Expr {
    public final String name;

    public Id(String name) {
        this.name = name;
    }

    @Override
    public void accept(ExprVisitor v) {
        v.visitId(this);
    }

    @Override
    public String toString() {
        return this.name;
    }
}
