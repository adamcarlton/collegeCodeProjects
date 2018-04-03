public class TestClass {
	public static void main(String[] args) {
        //insert tests
		AVL<Integer> myAVL1 = new AVL<Integer>();
		myAVL1.insert(10);
		myAVL1.insert(5);
		myAVL1.insert(20);
		myAVL1.insert(2);
		myAVL1.insert(1);
		myAVL1.traverse("preorder", myAVL1.getRoot());
		System.out.println("Should be: 10 2 1 5 20");
		
		AVL<Integer> myAVL2 = new AVL<Integer>();
		myAVL2.insert(10);
		myAVL2.insert(5);
		myAVL2.insert(20);
		myAVL2.insert(2);
		myAVL2.insert(3);
		myAVL2.traverse("preorder", myAVL2.getRoot());
		System.out.println("Should be: 10 3 2 5 20");
		
		AVL<Integer> myAVL3 = new AVL<Integer>();
		myAVL3.insert(10);
		myAVL3.insert(5);
		myAVL3.insert(20);
		myAVL3.insert(7);
		myAVL3.insert(6);
		myAVL3.traverse("preorder", myAVL3.getRoot());
		System.out.println("Should be: 10 6 5 7 20");
		
		AVL<Integer> myAVL4 = new AVL<Integer>();
		myAVL4.insert(10);
		myAVL4.insert(5);
		myAVL4.insert(20);
		myAVL4.insert(7);
		myAVL4.insert(8);
		myAVL4.traverse("preorder", myAVL4.getRoot());
		System.out.println("Should be: 10 7 5 8 20");		

		AVL<Integer> myAVL5 = new AVL<Integer>();
		myAVL5.insert(10);
		myAVL5.insert(5);
		myAVL5.insert(20);
		myAVL5.insert(30);
		myAVL5.insert(40);
		myAVL5.traverse("preorder", myAVL5.getRoot());
		System.out.println("Should be: 10 5 30 20 40");
		
		AVL<Integer> myAVL6 = new AVL<Integer>();
		myAVL6.insert(10);
		myAVL6.insert(5);
		myAVL6.insert(20);
		myAVL6.insert(30);
		myAVL6.insert(25);
		myAVL6.traverse("preorder", myAVL6.getRoot());
		System.out.println("Should be: 10 5 25 20 30");
		
		AVL<Integer> myAVL7 = new AVL<Integer>();
		myAVL7.insert(10);
		myAVL7.insert(5);
		myAVL7.insert(20);
		myAVL7.insert(15);
		myAVL7.insert(17);
		myAVL7.traverse("preorder", myAVL7.getRoot());
		System.out.println("Should be: 10 5 17 15 20");
		
		AVL<Integer> myAVL8 = new AVL<Integer>();
		myAVL8.insert(10);
		myAVL8.insert(5);
		myAVL8.insert(20);
		myAVL8.insert(15);
		myAVL8.insert(13);
		myAVL8.traverse("preorder", myAVL8.getRoot());
		System.out.println("Should be: 10 5 15 13 20");
		
		AVL<Integer> myAVL9 = new AVL<Integer>();
		myAVL9.insert(10);
		myAVL9.insert(5);
		myAVL9.insert(2);
		myAVL9.traverse("preorder", myAVL9.getRoot());
		System.out.println("Should be: 5 2 10");
		
		AVL<Integer> myAVL10 = new AVL<Integer>();
		myAVL10.insert(10);
		myAVL10.insert(20);
		myAVL10.insert(30);
		myAVL10.traverse("preorder", myAVL10.getRoot());
		System.out.println("Should be: 20 10 30");
		
		AVL<Integer> myAVL11 = new AVL<Integer>();
		myAVL11.insert(10);
		myAVL11.insert(5);
		myAVL11.insert(6);
		myAVL11.traverse("preorder", myAVL11.getRoot());
		System.out.println("Should be: 6 5 10");
		
		AVL<Integer> myAVL12 = new AVL<Integer>();
		myAVL12.insert(10);
		myAVL12.insert(20);
		myAVL12.insert(15);
		myAVL12.traverse("preorder", myAVL12.getRoot());
		System.out.println("Should be: 15 10 20");
		
		//delete tests
		AVL<Integer> myAVLdel1 = new AVL<Integer>();
		myAVLdel1.insert(44);
		myAVLdel1.insert(17);
		myAVLdel1.insert(78);
		myAVLdel1.insert(10);
		myAVLdel1.insert(32);
		myAVLdel1.insert(50);
		myAVLdel1.insert(88);
		myAVLdel1.insert(5);
		myAVLdel1.insert(12);
		myAVLdel1.insert(30);
		myAVLdel1.insert(90);
		myAVLdel1.insert(1);
		System.out.println("Base tree no deletions:");
		myAVLdel1.traverse("preorder", myAVLdel1.getRoot());
		System.out.println("Should be: 44 17 10 5 1 12 32 30 78 50 88 90");

		//node has 0 children
		AVL<Integer> myAVLdel2 = new AVL<Integer>();
		myAVLdel2.insert(44);
		myAVLdel2.insert(17);
		myAVLdel2.insert(78);
		myAVLdel2.insert(10);
		myAVLdel2.insert(32);
		myAVLdel2.insert(50);
		myAVLdel2.insert(88);
		myAVLdel2.insert(5);
		myAVLdel2.insert(12);
		myAVLdel2.insert(30);
		myAVLdel2.insert(90);
		myAVLdel2.insert(1);
		myAVLdel2.delete(90);
		myAVLdel2.traverse("preorder", myAVLdel2.getRoot());
		System.out.println("Should be: 17 10 5 1 12 44 32 30 78 50 88");
		
		//node has 1 child
		AVL<Integer> myAVLdel3 = new AVL<Integer>();
		myAVLdel3.insert(44);
		myAVLdel3.insert(17);
		myAVLdel3.insert(78);
		myAVLdel3.insert(10);
		myAVLdel3.insert(32);
		myAVLdel3.insert(50);
		myAVLdel3.insert(88);
		myAVLdel3.insert(5);
		myAVLdel3.insert(12);
		myAVLdel3.insert(30);
		myAVLdel3.insert(90);
		myAVLdel3.insert(1);
		myAVLdel3.delete(88);
		myAVLdel3.traverse("preorder", myAVLdel3.getRoot());
		System.out.println("Should be: 17 10 5 1 12 44 32 30 78 50 90");
		
		//node has 2 children
		AVL<Integer> myAVLdel4 = new AVL<Integer>();
		myAVLdel4.insert(44);
		myAVLdel4.insert(17);
		myAVLdel4.insert(78);
		myAVLdel4.insert(10);
		myAVLdel4.insert(32);
		myAVLdel4.insert(50);
		myAVLdel4.insert(88);
		myAVLdel4.insert(5);
		myAVLdel4.insert(12);
		myAVLdel4.insert(30);
		myAVLdel4.insert(90);
		myAVLdel4.insert(1);
		myAVLdel4.delete(78);
		myAVLdel4.traverse("preorder", myAVLdel4.getRoot());
		System.out.println("Should be: 17 10 5 1 12 44 32 30 88 50 90");
		
	}

}
