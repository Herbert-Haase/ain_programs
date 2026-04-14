// ExprVisitor.java
package expr.ast;

public interface ExprVisitor {
    default void visitOperation(Operation operation) {
        operation.left.accept(this);
        operation.right.accept(this);
    }
    
    default void visitValue(Value value) { }
}

