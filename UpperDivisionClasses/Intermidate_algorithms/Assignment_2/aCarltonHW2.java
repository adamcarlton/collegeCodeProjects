import java.util.Scanner;
import java.util.Stack;
public class aCarltonHW2{

    static String[] nodes;
    static Stack<String> topSort = new Stack<>();
    static boolean[] isVisited;
    static int nodeIter;

    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        nodeIter = scanner.nextInt();
        nodes = new String[nodeIter + 1];
        isVisited = new boolean[nodeIter + 1];
        int edgeNum = scanner.nextInt();
        int[][] adjMatrix = new int[nodeIter + 1][nodeIter + 1];

        for(int i = 1; i < isVisited.length; i++){
            isVisited[i] = false;
        }

        for(int i = 1; i <= nodeIter; i++){
            for(int j = 1; j <= nodeIter; j++){
                adjMatrix[i][j] = 0;
            }
        }

        for(int i = 1; i <= nodeIter + edgeNum; i++){
            if(i <= nodeIter){
                String node = scanner.next();
                nodes[i] = node;
            }
            else{
                int node1 = scanner.nextInt();
                int node2 = scanner.nextInt();
                int weight = scanner.nextInt();
                adjMatrix[node1][node2] = 1;
            }
        }

        for(int i = 1; i <= nodeIter; i++){
            if(isVisited[i] == false){
                dfs(adjMatrix, i);
            }
        }

        for(int i = 0; i < nodeIter; i++){
            System.out.println(topSort.pop());
        }
    }

    public static void dfs(int[][] adjMatrix, int index){
        isVisited[index] = true;
        for(int j = 1; j <= nodeIter; j++){
            if(!(isVisited[j]) && adjMatrix[index][j] == 1){
                dfs(adjMatrix, j);
            }
        }
        topSort.push(index + " " + nodes[index]);
    }
}
