import java.util.Scanner;

public class aCarltonHW0{
  public static void main(String[] args){
    Scanner scanner = new Scanner(System.in);
    int iterations = scanner.nextInt();
    for(int i = 0; i < iterations; i++){
      int a = scanner.nextInt();
      int b = scanner.nextInt();
      System.out.println(a+b + " " + a*b);
    }
  }
}
