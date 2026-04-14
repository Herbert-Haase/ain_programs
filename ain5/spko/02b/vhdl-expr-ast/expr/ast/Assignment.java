package vhdl.ast;

public final class Assignment extends Expr {
    public final String target;
    public final Expr value;

    public Assignment(String target, Expr value) {
        this.target = target;
        this.value = value;
    }

    @Override
    public void accept(ExprVisitor v) {
        v.visitAssignment(this);
    }
}
