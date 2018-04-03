
public class BST<E extends Comparable<E>> {
    private Node<E> root;

    public BST(){
        root = null;
    }

    public Node<E> getRoot(){
        return root;
    }

    public void insert(E data){
        Node<E> insertion = new Node<E>(data);
        if(this.root == null){
            root = insertion;
            return;
        }
        Node<E> parent = null;
        Node<E> temp = this.root;
        boolean check = false;
        while(temp != null){
            if(data.compareTo(temp.getData()) < 0){
                parent = temp;
                temp = temp.getLeftChild();
                check = true;
            }
            else{
                parent = temp;
                temp = temp.getRightChild();
                check = false;
            }
        }
        insertion.setParent(parent);
        if(check == true){
            parent.setLeftChild(insertion);
        }
        else{
            parent.setRightChild(insertion);
        }
        // Find the right spot in the tree for the new node
        // Make sure to check if anything is in the tree
        // Hint: if a node n is null, calling n.getData() will cause an error
        
    }

    public Node<E> find(E data){
        if(this.root == null){
            return null;
        }
        if(this.root.getData() == data){
            return this.root;
        }
        Node<E> temp = this.root;
        while(temp != null){
            if(temp.getData().compareTo(data) == 0){
                return temp;
            }
            if(data.compareTo(temp.getData()) < 0){
                temp = temp.getLeftChild();
            }
            else{
                temp = temp.getRightChild();
            }
        }
        return null;
        // Search the tree for a node whose data field is equal to data
    }

    public void delete(E data){
        Node<E> foundNode = this.find(data);
        if(foundNode == null){
            return;}
        if(this.root == foundNode){
            if(foundNode.getLeftChild() == null && foundNode.getRightChild() == null){
                root = null;
                return;
            }
        }
        if(foundNode.getLeftChild() == null && foundNode.getRightChild() != null){
            foundNode.getRightChild().setParent(foundNode.getParent());
            if(foundNode.getParent().getLeftChild() != foundNode){
                foundNode.getParent().setRightChild(foundNode.getRightChild());
            }
            else{
                foundNode.getParent().setLeftChild(foundNode.getRightChild());
            }
        }
        else if(foundNode.getLeftChild() != null && foundNode.getRightChild() == null){
            foundNode.getLeftChild().setParent(foundNode.getParent());
            if(foundNode.getParent().getRightChild() != foundNode){
                foundNode.getParent().setLeftChild(foundNode.getLeftChild());
            }
            else{
                foundNode.getParent().setRightChild(foundNode.getLeftChild());
            }
        }
        
        else if(foundNode.getLeftChild() == null && foundNode.getRightChild() == null){
            if(foundNode.getParent().getRightChild() == foundNode){
                foundNode.getParent().setRightChild(null);
            }
            else{
                foundNode.getParent().setLeftChild(null);
            }
        }
        else{
            Node<E> holder = this.findMin(foundNode.getRightChild());
            E newData = holder.getData();
            this.delete(holder.getData());
            foundNode.setData(newData);
        }

            

        // Find the right node to be deleted

        // If said node has no children, simply remove it by setting its parent to point to null instead of it.
        // If said node has one child, delete it by making its parent point to its child.
        // If said node has two children, then replace it with its successor,
        //          and remove the successor from its previous location in the tree.
        // The successor of a node is the left-most node in the node's right subtree.
        // If the value specified by delete does not exist in the tree, then the structure is left unchanged.

        // Hint: You may want to implement a findMin() method to find the successor when there are two children

    }

    public void traverse(String order, Node<E> top) {
        if (top != null){
            switch (order) {
                case "preorder":
                    // Your Code here
                    preorder(top);
                    System.out.println("");
                    break;
                case "inorder":
                    // Your Code here
                    inorder(top);
                    System.out.println("");
                    break;
                case "postorder":
                    // Your Code here
                    postorder(top);
                    System.out.println("");
                    break;
            }
        }
    }
    public void preorder(Node<E> node){
        if(node!=null){
            System.out.print(node.getData() + " ");
            preorder(node.getLeftChild());
            preorder(node.getRightChild());
        }
    }
    public void inorder(Node<E> node){
        if(node!=null){
            inorder(node.getLeftChild());
            System.out.print(node.getData()+ " ");
            inorder(node.getRightChild());
        }
    }
    public void postorder(Node<E> node){
        if(node!=null){
            postorder(node.getLeftChild());
            postorder(node.getRightChild());
            System.out.print(node.getData()+ " ");
        }
    }
    public Node<E> findMin(Node<E> node){
        while(node.getLeftChild() != null){
            node = node.getLeftChild();
        }
        return node;
    }
    public boolean compareTree(Node<E> tree1, Node<E> tree2){
        if(tree1 == null && tree2 == null){
            return true;
        }
        if(tree1.getData() != tree2.getData()){
           return false;
        }
        if(tree1.getData() == tree2.getData()){
            boolean rightCheck = compareTree(tree1.getRightChild(), tree2.getRightChild());
            boolean leftCheck = compareTree(tree1.getLeftChild(), tree2.getLeftChild());        
            return (rightCheck && leftCheck);         
        }
        return false;
    }
}
