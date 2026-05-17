// Currying.java
import java.util.function.IntBinaryOperator;
import java.util.function.IntFunction;
import java.util.function.IntUnaryOperator;

public final class Currying {
    static IntBinaryOperator uncurriedAdd = (x, y) -> x + y;
    static IntFunction<IntUnaryOperator> curriedAdd = x -> y -> x + y;

    public static void main(String[] args) {
        System.out.println(uncurriedAdd.applyAsInt(3, 5)); // 8
        System.out.println(curriedAdd.apply(3).applyAsInt(5)); // 8

        var addThree = curriedAdd.apply(3);
        System.out.println(addThree.applyAsInt(5)); // 8
        System.out.println(addThree.applyAsInt(12)); // 15
    }
}
