public class OprExle {
    public static void main(String[] args) {
        int a = 25;
        int b = 33;
        int c = 42;

        // arithmetic operators
        int sum = a + b;
        int diff = a - b;
        int prod = a * b;
        int div = a / b;
        int mod = a % c;

        // relational operators
        boolean equals = a == b;
        boolean notEquals = a != b;
        boolean greaterThan = a > b;
        boolean lessThan = a < b;
        boolean greaterOrEquals = a >= b;
        boolean lessOrEquals = a <= b;

        // logical operators
        boolean and = (a > b) && (a > c);
        boolean or = (a > b) || (a < c);
        boolean not = !(a == b);

        // bitwise operators
        int bitwiseAnd = a & b;
        int bitwiseOr = a | b;
        int bitwiseXor = a ^ b;
        int bitwiseComplement = ~a;
        int leftShift = a << 1;
        int rightShift = a >> 1;
        int zeroFillRightShift = a >>> 1;

        System.out.println("Sum: " + sum);
        System.out.println("Difference: " + diff);
        System.out.println("Product: " + prod);
        System.out.println("Division: " + div);
        System.out.println("Modulus: " + mod);

        System.out.println("Equals: " + equals);
        System.out.println("Not equals: " + notEquals);
        System.out.println("Greater than: " + greaterThan);
        System.out.println("Less than: " + lessThan);
        System.out.println("Greater or equals: " + greaterOrEquals);
        System.out.println("Less or equals: " + lessOrEquals);

        System.out.println("Logical AND: " + and);
        System.out.println("Logical OR: " + or);
        System.out.println("Logical NOT: " + not);

        System.out.println("Bitwise AND: " + bitwiseAnd);
        System.out.println("Bitwise OR: " + bitwiseOr);
        System.out.println("Bitwise XOR: " + bitwiseXor);
        System.out.println("Bitwise complement: " + bitwiseComplement);
        System.out.println("Left shift: " + leftShift);
        System.out.println("Right shift: " + rightShift);
        System.out.println("Zero-fill right shift: " + zeroFillRightShift);
    }
}