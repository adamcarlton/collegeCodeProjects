public class ExtraCredit{

  public static boolean isBST(Node<Integer> root){
    return BST_Check(root, Integer.MIN_VALUE, Integer.MAX_VALUE);
  }

  public static boolean BST_Check(Node<Integer> root, Integer min, Integer max){
    if(root == null){
      return true;
    }
    if(root.getData() > max || root.getData() < min){
      return false;
    }

    return (BST_Check(root.getLeftChild(), min, root.getData() - 1) && BST_Check(root.getRightChild(), root.getData() + 1, max));
  }
  public static void main(String[] args){
       Node<Integer> one = new Node<Integer>(5);
       Node<Integer> two = new Node<Integer>(1);
       Node<Integer> three = new Node<Integer>(8);
       Node<Integer> four = new Node<Integer>(-1);
       Node<Integer> eight = new Node<Integer>(-5);
       one.setLeftChild(two);
       two.setParent(one);
       one.setRightChild(three);
       three.setParent(one);
       two.setLeftChild(four);
       four.setParent(two);
       four.setLeftChild(eight);
       eight.setParent(four);

       System.out.println(isBST(one));
       //preorderTraversal(one);
   }
}
