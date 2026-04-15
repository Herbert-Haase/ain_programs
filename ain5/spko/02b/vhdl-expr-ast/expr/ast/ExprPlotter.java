// expr/ast/ExprPlotter.java
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
    public void visitId(Id id) {
        this.result.append("*".repeat(this.nesting + 1))
                   .append(' ')
                   .append(id.name)
                   .append('\n');
    }

    @Override
    public void visitOperation(Operation operation) {
        ++this.nesting;
        this.result.append("*".repeat(this.nesting))
                   .append(' ')
                   .append(operation.operator)
                   .append('\n');
        operation.left.accept(this);
        operation.right.accept(this);
        --this.nesting;
    }

    @Override
    public void visitNot(Not not) {
        ++this.nesting;
        this.result.append("*".repeat(this.nesting))
                   .append(" NOT\n");
        not.child.accept(this);
        --this.nesting;
    }

    @Override
    public void visitAssignment(Assignment assignment) {
        ++this.nesting;
        this.result.append("*".repeat(this.nesting))
                   .append(" <=\n");
        
        // Linke Seite (Target ID)
        ++this.nesting;
        this.result.append("*".repeat(this.nesting))
                   .append(' ')
                   .append(assignment.target)
                   .append('\n');
        --this.nesting;
        
        // Rechte Seite (Expression)
        assignment.value.accept(this);
        
        --this.nesting;
    }
}
