package expr.ast;

public final class ExprPrinter implements ExprVisitor {
    private StringBuilder result;

    public String print(Expr expr) {
        this.result = new StringBuilder();
        expr.accept(this);
        return this.result.toString();
    }

    @Override
    public void visitId(Id id) {
        this.result.append(id.name);
    }

    @Override
    public void visitOperation(Operation operation) {
        this.result.append("(");
        operation.left.accept(this);
        this.result.append(" ").append(operation.operator).append(" ");
        operation.right.accept(this);
        this.result.append(")");
    }

    @Override
    public void visitNot(Not not) {
        this.result.append("NOT ");
        not.child.accept(this);
    }

    @Override
    public void visitAssignment(Assignment assignment) {
        this.result.append(assignment.target).append(" <= ");
        assignment.value.accept(this);
        this.result.append(";");
    }
}
