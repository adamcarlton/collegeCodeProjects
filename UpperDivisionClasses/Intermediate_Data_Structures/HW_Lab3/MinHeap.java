public class MinHeap<E extends Comparable> {
    private E[] myArray;
    private int maxSize;
    private int length;

    
    public MinHeap(int s){
    	// Build the constructor
        this.maxSize = s + 1;
        this.length = 0;
        myArray = (E[]) (new Comparable[maxSize]);
    }

    public E[] getArray(){
        return myArray;
    }

    public void setArray(E[] newArray){
        myArray = newArray;
    }

    public int getMaxSize(){
        return maxSize;
    }

    public void setMaxSize(int ms){
        maxSize = ms;
    }

    public int getLength(){
        return length;
    }

    public void setLength(int l){
        length = l;
    }

    public void swap(int index1, int index2, E[] array){
        E temp = array[index1];
        array[index1] = array[index2];
        array[index2] = temp;
    }
    public void heapify(){
        for(int i = myArray.length; i >= 1; i--){
            bubbleDown(i);
        }
    }
    // Other Methods
    public void insert(E data){
        length++;
        myArray[length] = data;
        int current = length;
        if(length == 1){
            return;
        }
        while(myArray[current].compareTo(myArray[current/2]) < 0){
            if(current == 0){
                return;
            }
            swap(current, current/2, myArray);
            current = current / 2;
            if(current == 1){
                return;
            }
        }
    	// Insert an element into your heap.
    	
    	// When adding a node to your heap, remember that for every node n, 
    	// the value in n is less than or equal to the values of its children, 
    	// but your heap must also maintain the correct shape.
		// (ie there is at most one node with one child, and that child is the left child.)
		// (Additionally, that child is farthest left possible.)
        
    }


    public Comparable<E> findMin(){
        // return the minimum value in the heap
        if(myArray[1] == null){
            return null;
        }
        E temp = myArray[1];
        return temp;
    }
    public void bubbleDown(int index){
        if(index > length || (index * 2) > length){
            return;
        }
        if(myArray[index].compareTo(myArray[index*2]) > 0 || myArray[index].compareTo(myArray[index*2+1]) > 0){
            if(myArray[index*2].compareTo(myArray[index*2+1]) < 0){
                swap(index, index*2, myArray);
                bubbleDown(index*2);
            }
            else{
                swap(index, index*2+1, myArray);
                bubbleDown(index*2+1);
            }
        }
    }
    public Comparable<E> extract(){
        // remove and return the minimum value in the heap
        E temp = myArray[1];
        myArray[1] = myArray[length];
        length--;
        if(length <= 1){
            return temp;
        }
        bubbleDown(1);
        return temp;
    }
}
