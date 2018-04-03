public class pQueue<E extends Comparable> {
    private MinHeap myHeap;

    public pQueue (int s) {
        // Build the Constructor
        myHeap = new MinHeap(s);
    }

    public void insert(E data){
        myHeap.insert(data);
    }

    public Comparable<E> findMin(){
        return myHeap.findMin();
    }

    public Comparable<E> removeMin(){
        return myHeap.extract();
    }
    
    public boolean isEmpty(){
        if(myHeap.getLength() == 0){
            return true;
        }
        return false;
        // Return true when the priority queue is empty
        // Hint: Do the actual printing in your HW3.java
    }

    public void print(){
        System.out.print("Current Queue: ");
        for(int i = 1; i < myHeap.getLength(); i++){
            System.out.print(myHeap.getArray()[i] + ",");
        }
        System.out.println(myHeap.getArray()[myHeap.getLength()]);
        // print out ”Current Queue: ” 
        // followed by each element separated by a comma. 
        // Do not add spaces between your elements.
    }
}
