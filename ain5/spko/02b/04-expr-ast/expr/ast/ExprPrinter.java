// ExprPrinter
package expr.ast;

public final class ExprPrinter implements ExprVisitor {
    private StringBuilder result;

    public String print(Expr expr) {
        this.result = new StringBuilder();
        expr.accept(this);
        return this.result.toString();
    }

    @Override
    public void visitValue(Value value) {
        this.result.append(value);
    }

    @Override
    public void visitOperation(Operation operation) {
        this.result.append('(');
        operation.left.accept(this);
        this.result.append(operation);
        operation.right.accept(this);
        this.result.append(')');
    }
}

