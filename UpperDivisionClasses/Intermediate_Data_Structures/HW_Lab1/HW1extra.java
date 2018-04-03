import java.util.Scanner;
public class HW1extra{ 
	public static void main(String[] args){	
		Scanner user_input = new Scanner(System.in);
        int numLoop = user_input.nextInt();
        for(int i = 0; i < numLoop; i++){
            String input = user_input.next();
            if(isPalindrome(input)){
                System.out.println("This is a Palindrome.");}
            else{
                System.out.println("Not a Palindrome.");}
            }   
		user_input.close();
	}
	
	public static boolean isPalindrome(String s){
        TwoStackQueue<Character> queue = new TwoStackQueue<Character>();
        Stack<Character> stack = new Stack<Character>();
        Node<Character> stackNode;
        Node<Character> queueNode;
        boolean isTrue = true;
        for(int i = 0; i < s.length(); i++){
            queue.enqueue(s.charAt(i));
            stack.push(s.charAt(i));}
        while(!stack.isEmpty()){
            stackNode = stack.pop();
            queueNode = queue.dequeue();
            //System.out.println(queueNode.getData());
            //System.out.println(stackNode.getData());
             if(stackNode.getData()!=queueNode.getData()){
                 return false;}
        }
        return isTrue;

		// Create a stack and a Queue of chars that represents the passed in string
		// Hint: While you loop through the given string, push the same char onto your stack
		//		 that you enqueue into your Queue. This way you can use dequeue to get 
		//       the string from left to right, but you pop the string from right to left
		
		// Compare your Queue and Stack to see if the input String was a Palindrome or not	

	}
}
