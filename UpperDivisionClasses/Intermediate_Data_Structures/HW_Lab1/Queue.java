
public class Queue<E> {
	private Node<E> head;
	private Node<E> tail;
	
	public Queue(){
	    this.head = null;
        this.tail = null;    
		// We want to initialize our Queue to be empty
		// (ie) set head and tail to be null
		
	}
	
	public void enqueue(E newData){
	    Node<E> temp = new Node(newData, null);
        if(this.isEmpty()){
               this.head = temp;}
        else{
            this.tail.setNext(temp);}
        this.tail = temp;
		// Create a new node whose data is newData and whose next node is null
		// Update head and tail
		// Hint: Think about what's different for the first node added to the Queue

	}
	
	public Node<E> dequeue(){
	    if (this.isEmpty()){
                return null;}
        Node<E> temp;
        temp = this.head;
        this.head = temp.getNext();
        return temp;
		// Return the head of the Queue
		// Update head
		// Hint: The order you implement the above 2 tasks matters, so use a temporary node
	 	//	     to hold important information
		// Hint: Return null on a empty Queue

	}
	
	public boolean isEmpty(){
	    return (this.head == null);
        // Check if the Queue is empty
		
	}
	
	public void printQueue(){
        Node<E> temp = this.head;
        while(temp != null){
            System.out.println(temp.getData());
            temp = temp.getNext();}
		// Loop through your queue and print each Node's data
		
	}
}
