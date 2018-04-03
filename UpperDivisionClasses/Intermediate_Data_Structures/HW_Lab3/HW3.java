import java.util.Scanner;
public class HW3 {
    public static void main(String[] args) {
        Scanner user_input = new Scanner(System.in);
        int iterations = user_input.nextInt();
        pQueue<Integer> queue = new pQueue<Integer>(iterations);
        for(int i = 0; i < iterations; i++){
            switch(user_input.next()){
                case "insert":
                    queue.insert(user_input.nextInt());
                    break;
                case "print":
                    queue.print();
                    break;
                case "isEmpty":
                    if(!queue.isEmpty()){
                        System.out.println("Not Empty");
                    }
                    else{
                        System.out.println("Empty");
                    }
                    break;
                case "findMin":
                    System.out.println(queue.findMin());
                    break;
                case "removeMin":
                    System.out.println(queue.removeMin());
                    break;
            }
        }
        user_input.close();
    	// Loop over the Scanner
        // Split each line into the task and the corresponding number (if one exists)
        // Depending on what the input task was, preform the corresponding function
        //      (ie) insert, findMin, removeMin, isEmpty, or print
        // Hint: Use a switch-case statement

        // Don't forget to close your Scanner!
        
    }
}
