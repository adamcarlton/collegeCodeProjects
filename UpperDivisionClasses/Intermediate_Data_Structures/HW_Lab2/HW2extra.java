import java.util.Scanner;

public class HW2extra {
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
 

        BST<Integer> bTree2 = new BST();
        int newIter = user_input.nextInt();
        for(int i = 0; i < newIter; i++){
            switch(user_input.next()){
                case "insert":
                    bTree2.insert(user_input.nextInt());
                    break;
                case "delete":
                    bTree2.delete(user_input.nextInt());
                    break;
                case "inorder":
                    bTree2.traverse("inorder", bTree2.getRoot());
                    break;
                case "preorder":
                    bTree2.traverse("preorder", bTree2.getRoot());
                    break;
                case "postorder":
                    bTree2.traverse("postorder", bTree2.getRoot());
                    break;
            }
        }

        boolean identical = bTree2.compareTree(bTree.getRoot(), bTree2.getRoot());
        System.out.println("Are they identical? " + identical);
        user_input.close();          
    }
}
