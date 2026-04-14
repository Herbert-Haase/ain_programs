package vhdl.ast;

public interface ExprVisitor {
    default void visitOperation(Operation operation) {
        operation.left.accept(this);
        operation.right.accept(this);
    }

    default void visitId(Id id) {
    }

    default void visitNot(Not not) {
        not.child.accept(this);
    }

    default void visitAssignment(Assignment assignment) {
        assignment.value.accept(this);
    }
}
