public class Human {
    private String name;
    public int age;

    public Person(String n, int a) {
        name = n;
        age = a;
    }

    public void setName(String n) {
        name = n;
    }

    public String getName() {
        return name;
    }

    private void celebBirthday() {
        age++;
        System.out.println("Happy bday " + name + "! You are now " + age + " years old.");
    }

    public static void main(String[] args) {
        Human p = new Person("Border", 35);
        System.out.println("Name is " + p.getName());
        System.out.println("Age is " + p.age);
        p.setName("Barney");
        System.out.println("changed name is " + p.getName());
        p.celebBirthday(); 
    }
}