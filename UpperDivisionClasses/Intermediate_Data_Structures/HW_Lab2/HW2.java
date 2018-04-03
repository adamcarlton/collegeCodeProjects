import java.util.Scanner;

public class HW2 {
    public static void main(String[] args) {
        BST<Integer> bTree = new BST();
        Scanner user_input = new Scanner(System.in);
        int iterations = user_input.nextInt();
        for(int i = 0; i < iterations; i++){
            switch(user_input.next()){
                case "insert":
                    bTree.insert(user_input.nextInt());
                    break;
                case "delete":
                    bTree.delete(user_input.nextInt());
                    break;
                case "inorder":
                    bTree.traverse("inorder", bTree.getRoot());
                    break;
                case "preorder":
                    bTree.traverse("preorder", bTree.getRoot());
                    break;
                case "postorder":
                    bTree.traverse("postorder", bTree.getRoot());
                    break;
            }
        }
        user_input.close();          
        // Split each line into the task and the corresponding number (if one exists)
        // Depending on what the input task was, preform the corresponding function
        //      (ie) insert, delete, find, inoder, preorder, or postorder
        // Hint: Use a switch-case statement

        // Don't forget to close your Scanner!

    }
}
