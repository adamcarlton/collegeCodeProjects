public class AVL<E extends Comparable<E>> {
    private Node<E> root;

    public AVL(){
        root = null;
    }

    public Node<E> getRoot(){
        return root;
    }

    public void insert(E data){
        boolean done = false;
        Node<E> temp = root;
        Node<E> newTemp = new Node<E>(data);

        while(!done){
            if(root == null){
               root = newTemp;
               done = true;
            }
            else if(temp.getData().compareTo(data) > 0){
                if(temp.getLeftChild() == null){
                    temp.setLeftChild(newTemp);
                    temp.getLeftChild().setParent(temp);
                    done = true;
                }
                temp = temp.getLeftChild();
            }
            else if(temp.getData().compareTo(data) <= 0){
                if(temp.getRightChild() == null){
                    temp.setRightChild(newTemp);
                    temp.getRightChild().setParent(temp);
                    done = true;
                }
                temp = temp.getRightChild();
            }
        }
        rebalance(newTemp);
        // Preform a regular insert
        // Check to make sure the tree remains an AVL tree
    }

    public Node<E> search(E data){
        // Return the node that corresponds with the given data
        // Note: No need to worry about duplicate values added to the tree
        boolean done = false;
        Node<E> temp = root;

        while(!done){
            if(temp == null){
                return null;
            }
            if(temp.getData().compareTo(data) == 0){
                done = true;
            }
            else if(temp.getData().compareTo(data) > 0){
                temp = temp.getLeftChild();
            }
            else{
                temp = temp.getRightChild();
            }
        }
        return temp;
    }

    public void delete(E data){
      Node<E> temp = search(data);
      if (temp == null){
          return;
      }
      Node<E> parent = temp.getParent();
      Node<E> replacement = new Node(null);

      boolean isRight;
      boolean isLeft;
      boolean isRoot;

      boolean hasChildren;
      boolean hasLeft;
      boolean hasRight;
      boolean hasBoth;

      // Find out if the node to be deleted is the root or if it is a left/right child
      if (temp == root){
          isRoot = true;
          isLeft = false;
          isRight = false;
      } else if (temp == temp.getParent().getLeftChild()){
          isRoot = false;
          isLeft = true;
          isRight = false;
      } else {
          isRoot = false;
          isLeft = false;
          isRight = true;
      }

      // Find out if the node to be deleted has children
      // If it does, find out if it has a Right/Left Child or both
      if (temp.getLeftChild() == null && temp.getRightChild() == null){
          hasChildren = false;
          hasBoth = false;
          hasLeft = false;
          hasRight = false;
      } else if (temp.getLeftChild() != null && temp.getRightChild() != null){
          hasChildren = true;
          hasBoth = true;
          hasLeft = true;
          hasRight = true;
      } else if (temp.getLeftChild() == null){
          hasChildren = true;
          hasBoth = false;
          hasRight = true;
          hasLeft = false;
      } else {
          hasChildren = true;
          hasBoth = false;
          hasRight = false;
          hasLeft = true;
      }

      // Seperate cases if the node to be deleted is the root of the tree
      if (isRoot){
          // Seperate cases depending on the number of children the node to be deleted has
          if (!hasChildren){
              root = null;
          } else if (hasBoth){
              replacement = getMin(temp.getRightChild());
              if (replacement == temp.getRightChild()){
                  replacement.setLeftChild(temp.getLeftChild());
                  replacement.setParent(temp.getParent());
                  replacement.getLeftChild().setParent(replacement);
                  root = replacement;
              } else {
                  if (replacement.getParent().getLeftChild() == replacement){
                      replacement.getParent().setLeftChild(null);
                  } else if (replacement.getParent().getRightChild() == replacement){
                      replacement.getParent().setRightChild(null);
                  }
                  replacement.setParent(temp.getParent());
                  replacement.setLeftChild(temp.getLeftChild());
                  replacement.setRightChild(temp.getRightChild());
                  temp.getLeftChild().setParent(replacement);
                  temp.getRightChild().setParent(replacement);
                  root = replacement;
              }

          } else if (hasLeft && !hasRight){
              temp.getLeftChild().setParent(null);
              root = temp.getLeftChild();
          } else if (hasRight && !hasLeft) {
              temp.getRightChild().setParent(null);
              root = temp.getRightChild();
          }
      } else {
          // This is the case where it isn't the root node
          if (!hasChildren){
              if (isLeft){
                  temp.getParent().setLeftChild(null);
              } else if (isRight){
                  temp.getParent().setRightChild(null);
              }
          } else if (hasBoth){
              replacement = getMin(temp.getRightChild());
              if (replacement == temp.getRightChild()){
                  replacement.setLeftChild(temp.getLeftChild());
                  replacement.setParent(temp.getParent());
                  replacement.getLeftChild().setParent(replacement);
              } else {
                  if (replacement.getParent().getLeftChild() == replacement){
                      replacement.getParent().setLeftChild(null);
                  } else if (replacement.getParent().getRightChild() == replacement){
                      replacement.getParent().setRightChild(null);
                  }
                  replacement.setParent(temp.getParent());
                  replacement.setLeftChild(temp.getLeftChild());
                  replacement.setRightChild(temp.getRightChild());
                  temp.getLeftChild().setParent(replacement);
                  temp.getRightChild().setParent(replacement);
              }
              if(isLeft){
                  temp.getParent().setLeftChild(replacement);
              } else if (isRight){
                  temp.getParent().setRightChild(replacement);
              }

          } else if (hasLeft && !hasRight){
              temp.getLeftChild().setParent(temp.getParent());
              temp.getParent().setLeftChild(temp.getLeftChild());
          } else if (hasRight && !hasLeft) {
              temp.getRightChild().setParent(temp.getParent());
              temp.getParent().setRightChild(temp.getRightChild());
          }
      }
      while(parent!=null){
        updateHeight(parent);
        if(parent.isUnbalanced()){
          rebalance(gitGud(parent));
          updateHeight(parent);
          //break;
        }
        parent = parent.getParent();
      }

    }

    private Node<E> getMaxChild(Node<E> node){
      if(node.getLeftChild() == null && node.getRightChild() == null){
        return null;
      }
      else if(node.getLeftChild() == null && node.getRightChild() != null){
        return node.getRightChild();
      }
      else if(node.getLeftChild() != null && node.getRightChild() == null){
        return node.getLeftChild();
      }
      else if(node.getLeftChild().getHeight() >= node.getRightChild().getHeight()){
        return node.getLeftChild();
      }
      else{
        return node.getRightChild();
      }
    }

    private Node<E> gitGud(Node<E> node){
      return getMaxChild(getMaxChild(node));
    }
    public void traverse(String order, Node<E> top) {
        // Preform a preorder traversal of the tree
        if(top != null){
            if(top.getData() != null){
                System.out.print(top.getData().toString() + " ");
                System.out.println(" height " + top.getHeight());
                traverse(order, top.getLeftChild());
                traverse(order, top.getRightChild());
            }
        }
    }


    public void rightRotate(Node<E> y){

    	/*
    	If x is the root of the tree to rotate with left child subtree T1 and right child y,
    	where T2 and T3 are the left and right children of y:
			x becomes left child of y and T3 as its right child of y
			T1 becomes left child of x and T2 becomes right child of x
		*/
    }

    public void leftRotate(Node<E> x){

    	/*
    	If y is the root of the tree to rotate with right child subtree T3 and left child x,
    	where T1 and T2 are the left and right children of x:
			y becomes right child of x and T1 as its left child of x
			T2 becomes left child of y and T3 becomes right child of y
		*/

    }
    private void rebalance(Node<E> node){
        Node<E> x = null;
        Node<E> y = null;
        Node<E> z = node;

        while(node != null){
          if(node.isUnbalanced()){
            rotateCheck(x, y, z);
            break;
          }
          else{
            updateHeight(node);
            node = node.getParent();
            x = y;
            y = z;
            z = node;
        }
      }
    }

    private void updateHeight(Node<E> node){
      if(node.getLeftChild() == null && node.getRightChild() == null){
        node.setHeight(1);
      }
      else if (node.getLeftChild() == null && node.getRightChild() != null){
          node.setHeight(node.getRightChild().getHeight() + 1);
      }
      else if(node.getRightChild() == null && node.getLeftChild() != null){
          node.setHeight(node.getLeftChild().getHeight() + 1);
      }
      else if(node.getLeftChild().getHeight() >= node.getRightChild().getHeight()){
          node.setHeight(node.getLeftChild().getHeight() + 1);
      }
      else{
          node.setHeight(node.getRightChild().getHeight() + 1);
      }
    }

    // HINT: You may want to create extra methods such as trinode reorder, or update heights, etc
    public Node<E> getMin(Node<E> top){
        boolean done = false;
        Node<E> temp = top;
        while(!done) {
            if (temp.getLeftChild() == null) {
                done = true;
            } else {
                temp = temp.getLeftChild();
            }
        }
        return temp;
    }

    private void rotateCheck(Node<E> x, Node<E> y, Node<E> z){
        if(z.getLeftChild() == y && y.getLeftChild() == x){
          leftLeftRotate(x, y, z);
        }
        else if(z.getLeftChild() == y && y.getRightChild() == x){
          leftRightRotate(x, y, z);
        }
        else if(z.getRightChild() == y && y.getRightChild() == x){
          rightRightRotate(x, y, z);
        }
        else{
          rightLeftRotate(x, y, z);
        }
    }

    private void leftLeftRotate(Node<E> x, Node<E> y, Node<E> z){
        if(z == this.getRoot()){
          root = y;
        }
        else{
          if(z.getParent().getRightChild() == z){
            z.getParent().setRightChild(y);
          }
          else{
            z.getParent().setLeftChild(y);
          }
        }
        Node<E> holder = y.getRightChild();
        y.setParent(z.getParent());
        y.setRightChild(z);
        z.setParent(y);
        z.setLeftChild(holder);
        if(holder != null){
          holder.setParent(z);
        }
        updateHeight(x);
        updateHeight(z);
        updateHeight(y);
    }

    private void rightRightRotate(Node<E> x, Node<E> y, Node<E> z){
      if(z == this.getRoot()){
        root = y;
      }
      else{
        if(z.getParent().getRightChild() == z){
          z.getParent().setRightChild(y);
        }
        else{
          z.getParent().setLeftChild(y);
        }
      }
      Node<E> holder = y.getLeftChild();
      y.setParent(z.getParent());
      y.setLeftChild(z);
      z.setParent(y);
      z.setRightChild(holder);
      if(holder != null){
        holder.setParent(z);
      }
      updateHeight(x);
      updateHeight(z);
      updateHeight(y);
    }

    private void leftRightRotate(Node<E> x, Node<E> y, Node<E> z){
      if(z == this.getRoot()){
        root = x;
      }
      else{
        if(z.getParent().getRightChild() == z){
          z.getParent().setRightChild(x);
        }
        else{
          z.getParent().setLeftChild(x);
        }
      }
        Node<E> leftHolder = x.getLeftChild();
        Node<E> rightHolder = x.getRightChild();
        x.setParent(z.getParent());
        x.setRightChild(z);
        z.setParent(x);
        z.setLeftChild(rightHolder);
        x.setLeftChild(y);
        y.setParent(x);
        y.setRightChild(leftHolder);
        if(leftHolder != null){
          leftHolder.setParent(y);
        }
        if(rightHolder != null){
          rightHolder.setParent(z);
        }
        updateHeight(z);
        updateHeight(y);
        updateHeight(x);
    }

    private void rightLeftRotate(Node<E> x, Node<E> y, Node<E> z){
      if(z == this.getRoot()){
        root = x;
      }
      else{
        if(z.getParent().getRightChild() == z){
          z.getParent().setRightChild(x);
        }
        else{
          z.getParent().setLeftChild(x);
        }
      }
        Node<E> leftHolder = x.getLeftChild();
        Node<E> rightHolder = x.getRightChild();
        x.setParent(z.getParent());
        x.setLeftChild(z);
        z.setParent(x);
        z.setRightChild(leftHolder);
        x.setRightChild(y);
        y.setParent(x);
        y.setLeftChild(rightHolder);
        if(leftHolder != null){
          leftHolder.setParent(z);
        }
        if(rightHolder != null){
          rightHolder.setParent(y);
        }
        updateHeight(z);
        updateHeight(y);
        updateHeight(x);
    }
}
