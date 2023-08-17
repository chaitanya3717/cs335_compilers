public class CFExample {
    public static void main(String[] args) {
        double age = 18;
        String gender = "male";

     
        if (age >= 18) {
            System.out.println("You are an adult.");
        } else {
            System.out.println("You are a minor.");
        }


        for (int i = 0; i < 5; i++) {
            System.out.println("The value of i is " + i);
        }


        int j = 0;
        while (j < 5) {
            System.out.println("The value of j is " + j);
            j++;
        }
    }
}