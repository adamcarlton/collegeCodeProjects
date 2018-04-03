public class Node<E extends Comparable<E>> {
    private E data;
    private Node<E> leftChild;
    private Node<E> rightChild;
    private Node<E> parent;

    private int height;

    public Node(E d) {
        data = d;
        leftChild = null;
        rightChild = null;
        parent = null;
        height = 1;
    }

    public void setData(E d) {
        data = d;
    }

    public void setLeftChild(Node<E> lc) {
        leftChild = lc;
    }

    public void setRightChild(Node<E> rc) {
        rightChild = rc;
    }

    public void setParent(Node<E> p) {
        parent = p;
    }

    public void setHeight(int h){
        height = h;
    }

    public E getData() {
        return data;
    }

    public Node<E> getLeftChild() {
        return leftChild;
    }

    public Node<E> getRightChild() {
        return rightChild;
    }

    public Node<E> getParent() {
        return parent;
    }

    public int getHeight(){
        return height;
    }


    public boolean isUnbalanced(){
        if(this.getLeftChild() == null && this.getRightChild() == null){
            return false;
        }
        if(this.getLeftChild() == null && this.getRightChild() != null){
            if(0 - this.getRightChild().getHeight() < -1){
                return true;
            }
            return false;
        }
        if(this.getRightChild() == null && this.getLeftChild() != null){
            if(this.getLeftChild().getHeight() - 0 > 1){
                return true;
            }
            return false;
        }
        else if(this.getLeftChild().getHeight() - this.getRightChild().getHeight() > 1 || this.getLeftChild().getHeight() - this.getRightChild().getHeight() < -1){
                return true;
            }
        return false;
    	// Return true when this node's children's heights differ by more than 1
        // Note: When a child is null, its height is 0
    }

}
