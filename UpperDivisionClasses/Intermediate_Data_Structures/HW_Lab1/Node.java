
public class Node<E> {
	private E data;
	private Node<E> next;
	
	public Node(E c, Node<E> n){
        this.data = c;
        this.next = n;    
		// Set the data and next fields to the corresponding input
		
	}
	
	public void setData(E d){
		this.data = d;
		// Set the "data" data field to the corresponding input

	}
	
	public void setNext(Node<E> n){
        this.next = n;
		// Set the "next" data field to the corresponding input

	}
	public E getData(){
        return this.data;
		// Return the "data" data field
		
	}
	
	public Node<E> getNext(){
	    return this.next;
		// return the "next" data field
		
	}
	
}
