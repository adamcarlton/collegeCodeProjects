
public class Stack<E> {
	private Node<E> top;
	
	public Stack(){
        this.top = null;	
		// We want to initialize our Stack to be empty
		// (ie) Set top as null
		
	}
	
	public void push(E newData){
        this.top = new Node(newData, this.top);
		// We want to create a node whose data is newData and next node is top
		// Push this new node onto the stack
		// Update top

	}
	
	public Node<E> pop(){
        if (this.isEmpty()){
            return null;}
	    Node<E> temp = this.top;
        this.top = temp.getNext();
        return temp;
		// Return the Node that currently represents the top of the stack
		// Update top
		// Hint: The order you implement the above 2 tasks matters, so use a temporary node
	 	//	     to hold important information
		// Hint: Return null on a empty stack

	}
	
	public boolean isEmpty(){
       return (this.top == null);
		//Check if the Stack is empty
		
	}
	
	public void printStack(){
        Node<E> temp = this.top;
        while(temp != null){
            System.out.println(temp.getData());
            temp = temp.getNext();}       
		// Loop through your stack and print each Node's data
		
	}
}
