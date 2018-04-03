import java.util.Scanner;
import java.util.HashSet;
import java.util.Set;
import java.io.File;
import java.io.FileNotFoundException;

public class acarltonHW6{

    public static Set<String> dictionary = new HashSet<String>();
    public static String phrase;
    public static boolean[] SP;
    public static int[] Loc;

    public static void main(String[] args){
        String fileName = "diction10k.txt";
        loadDictionary(fileName);
        Scanner scanner = new Scanner(System.in);
        int iterations = scanner.nextInt();

        for(int i = 0; i < iterations; i++){
            phrase = scanner.next();
            System.out.println("Phrase: " + phrase);
            SP = new boolean[phrase.length()];
            Loc = new int[phrase.length()];
            for(int j = 0; j < phrase.length(); j++){
                SP[j] = false;
            }
            iterSplit();
            if(!SP[0]){
                System.out.println("NOPE! Iterative cannot split it :(\n");
            }
            else{
                System.out.println("YES! Iterative CAN split it :D");
                toSplit(0, Loc[0]);
            }
            memSplit(0);
            if(!SP[0]){
                System.out.println("NOPE! Memoized cannot split it :(\n");
            }
            else{
                System.out.println("YES! Memoized CAN split it :D");
                toSplit(0, Loc[0]);
            }
        }
    }

    public static void iterSplit(){
        for(int i = phrase.length() - 1; i >= 0; i--){
            if (SP[i] == false){
                for (int j = i; j < phrase.length(); j++){
                    if(dictionary.contains(phrase.substring(i, j + 1)) && ((j + 1 == phrase.length())?true:SP[j+1])){
                        SP[i] = true;
                        Loc[i] = j;
                    }
                }
            }
        }
        return;
    }

    public static void toSplit(int start, int end){
        if(end + 1 >= phrase.length() ){
            System.out.println(phrase.substring(start, end + 1) + "\n");
            return;
        }
        System.out.print(phrase.substring(start, end + 1) + " ");
        toSplit(end + 1, Loc[end + 1]);
        return;
    }

    public static boolean memSplit(int index){
        if(index == phrase.length()){
            return true;
        }
        if (SP[index] == false){
            for (int j = index; j < phrase.length(); j++){
                if(dictionary.contains(phrase.substring(index, j+1)) && memSplit(j+1)){
                    SP[index] = true;
                    Loc[index] = j;
                }
            }
        }
        return SP[index];
    }

    public static void loadDictionary(String dictionaryFileName){
        File inputFile = new File(dictionaryFileName);
        try {
            Scanner scan = new Scanner(inputFile);
            String line;
            while (scan.hasNext()) {
                line = scan.next();
                dictionary.add(line.trim());
            }
            scan.close();
        }
        catch (FileNotFoundException e){
            e.printStackTrace();
        }
    }
}
