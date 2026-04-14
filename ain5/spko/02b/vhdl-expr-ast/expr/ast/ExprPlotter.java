// ExprPlotter
package expr.ast;

public final class ExprPlotter implements ExprVisitor {
    private int nesting;
    private StringBuilder result;

    public String plot(Expr expr) {
        this.nesting = 0;
        this.result = new StringBuilder();
        this.result.append("""
                           @startmindmap
                           top to bottom direction
                           <style>
                           node {
                               LineColor white
                               BackgroundColor white
                           }
                           </style>
                           """);
        expr.accept(this);
        this.result.append("@endmindmap\n");
        return this.result.toString();
    }

    @Override
    public void visitValue(Value value) {
        this.result.append("*".repeat(this.nesting + 1))
                   .append(' ')
                   .append(value)
                   .append('\n');
    }

    @Override
    public void visitOperation(Operation operation) {
        ++this.nesting;
        this.result.append("*".repeat(this.nesting))
                   .append(' ')
                   .append(operation)
                   .append('\n');
        operation.left.accept(this);
        operation.right.accept(this);
        --this.nesting;
    }
}

