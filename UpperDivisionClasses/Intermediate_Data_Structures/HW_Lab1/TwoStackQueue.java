
public class TwoStackQueue<E> {
    private Stack<E> stack1;
    private Stack<E> stack2;

    public TwoStackQueue(){
        stack1 = new Stack<E>();  
        stack2 = new Stack<E>();}

    public void enqueue(E newData){
        stack2.push(newData);}
    
    public Node<E> dequeue(){
        if( stack1.isEmpty()){
            while(!stack2.isEmpty()){
                stack1.push(stack2.pop().getData());}
        }
        return stack1.pop();}

    public boolean isEmpty(){
        if(stack1 == null){
            return true;}
        else if(stack2 == null){
            return true;}
        return false;}
    
    public void printQueue(){
        if(stack1.isEmpty() && stack2.isEmpty()){
            System.out.println("Queue's are null");
            return;}
        TwoStackQueue<E> nTwoStack = new TwoStackQueue();
        while(!this.isEmpty()){
            E newData = this.dequeue().getData();
            nTwoStack.enqueue(newData);
            System.out.println(newData);}
        while(!nTwoStack.isEmpty()){
            this.enqueue(nTwoStack.dequeue().getData());}
    }

}
