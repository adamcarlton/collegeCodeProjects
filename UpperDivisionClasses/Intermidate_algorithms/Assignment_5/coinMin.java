import java.util.*;
import java.io.*;


public class coinMin
{


	public static Scanner scan = new Scanner(System.in);
	public static ArrayList<Integer> denom = new ArrayList<Integer>();
	public static HashMap<Integer, Integer> mapCoins = new HashMap<Integer, Integer>();
	public static int[] numCoins;


//-----------------------------------------------------------

	public static int recCoins(int t)  // pure recursion
	{
		int curCoin, prevNum, curNum;

//		if (t<0) return Integer.MAX_VALUE-1;
		if (t==0) return 0;

		curNum = Integer.MAX_VALUE-1;
		for (int i=0; i<denom.size(); i++)
			{
				curCoin = denom.get(i);
				if (t>=curCoin)
				{
					prevNum=recCoins(t-curCoin); // recursively determine #coins
					if (1+prevNum<curNum)
						curNum = 1+prevNum;
				}
			}

		return curNum;
	}
//-----------------------------------------------------------

	public static int memoCoins(int t)
	// recursive but memoized (results cached in hashmap, tho array would be fine also)
	{
		int curCoin, prevNum, curNum;
		if (t==0) return 0;
		if (mapCoins.containsKey(t))
			return mapCoins.get(t);	// return if already known

		curNum = Integer.MAX_VALUE-1;
		for (int i=0; i<denom.size(); i++)
		{
			curCoin = denom.get(i);
			if (t>=curCoin)
			{
				prevNum=memoCoins(t-curCoin);  // recursive call to memoized routine
				if (1+prevNum<curNum)
					curNum = 1+prevNum;
			}
		}

		mapCoins.put(t,curNum);	// save computed value
		return curNum;

	}

//-----------------------------------------------------------

	public static int iterCoins(int T)
	// iterative, results in array, calculated from smallest to largest
	{
		int curCoin;
		numCoins = new int[T+1];

		numCoins[0]=0;
		for(int t=1; t<=T; t++)
		{
			numCoins[t] = Integer.MAX_VALUE-1;  //hack to avoid wrap-around
			for (int i=0; i<denom.size(); i++)
			{
				curCoin = (Integer)denom.get(i);
				if (curCoin<=t && 1+numCoins[t-curCoin]<numCoins[t])
					numCoins[t]= 1+numCoins[t-curCoin];

			}
		}
        coinCheck((Integer)numCoins[T], T);
		return numCoins[T];

	}

//-----------------------------------------------------------
//-----------------------------------------------------------
    public static void coinCheck(int coins, int T){
        if (T % coins == 0){
            System.out.println("The only coin you need is: " + T/coins);
        }
        else{
            System.out.println("The coins needed are: " + ((T/coins) + 1) + " and " + T%coins);
        }
    }

    public static void main (String[] args)
    {

		int T, dval;
		System.out.println("Please enter coin denominations (stop input with 0)");

		dval = scan.nextInt();
		while (dval>0)
		{
			denom.add(dval);
			dval = scan.nextInt();
		}


		System.out.println("Enter the target");
		T = scan.nextInt();

		System.out.println("Minimum Coins (iter):"+iterCoins(T));

		System.out.print("press return to continue");
		scan.nextLine();
		scan.nextLine();

		System.out.println("Minimum Coins (memo):"+memoCoins(T));

		System.out.print("press return to continue");
		scan.nextLine();

		System.out.println("Minimum Coins (pure rec):"+recCoins(T));

    }//end-main

}//end-class
