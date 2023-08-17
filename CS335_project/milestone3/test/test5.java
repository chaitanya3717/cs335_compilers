public class Rec {
    public static void main(String[] args) {
        int n = 100;
        int res = rec(n);
        System.out.println("The " + n + "th Fb no is " + res);
    }

    public static int rec(int n) {
        if (n <= 1) {
            return n;
        } else {
            return rec(n - 1) + rec(n - 2);
        }
    }
}