import java.util.Scanner;

public class HW0 {
        static Scanner scanner = new Scanner(System.in);
        public static void main (String[] args){
        int numProblem = scanner.nextInt();
        for(int i = 0; i < numProblem; i++){
            int a = scanner.nextInt();
            int b = scanner.nextInt();                                  
            int g = Euclid(a,b);
            int l = Lcm(a,b);
            System.out.println(g + " " + l);
            }
        }
        public static int Euclid(int a, int b){
            if (b == 0){
                return a;}
            else{ 
                return Euclid(b, a % b);}
            }
        public static int Lcm(int a, int b){
            return a * (b / Euclid(a, b));
            }
}
