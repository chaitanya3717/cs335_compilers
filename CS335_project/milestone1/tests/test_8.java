public class ByteExample {
    public static void main(String[] args) {
      byte a = 100;
      byte b = -50;
      byte c = (byte)(a + b); // need to cast to byte since addition of two bytes results in an int
      
      System.out.println("a: " + a);
      System.out.println("b: " + b);
      System.out.println("c: " + c);
    }
  }
  