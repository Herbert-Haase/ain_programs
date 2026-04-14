package vhdl.ast;

public final class Not extends Expr {
    public final Expr child;

    public Not(Expr child) {
        this.child = child;
    }

    @Override
    public void accept(ExprVisitor v) {
        v.visitNot(this);
    }
}
