public interface Animal {
    public void eat();
    public void sleep();
  }
  
  public class Dog implements Animal {
    public void eat() {
      System.out.println("Dog is eating");
    }
    
    public void sleep() {
      System.out.println("Dog is sleeping");
    }
  }
  
  public class AnimalTest {
    public static void main(String[] args) {
      Animal animal = new Dog();
      animal.eat();
      animal.sleep();
    }
  }
  