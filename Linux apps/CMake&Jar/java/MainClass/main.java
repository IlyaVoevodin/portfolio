package lab3.java.MainClass;
import java.util.Scanner;
import lab3.java.SearchClass.search;
import lab3.java.Print_InputClass.print_input;

public class main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = Integer.parseInt(args[0]);
        if(n == 0)
        {
                System.out.println("Input matrix size!");
                return;
         }
         int[][] A = new int[n][n];

          int row = 0, clmn = 0,x;
          print_input.menu(n,A);

          System.out.print("Input value to search:");
          x = in.nextInt();
	 in.close();
          System.out.print("\n");

            String opt = args[1];
                switch (opt) {
                    case "-d":
                        search.DebugSearch(x, row, clmn, n, A);
                        break;
                    case "-r":
                        search.ReleaseSearch(x, row, clmn, n, A);
                        break;
                    default:
                        System.out.print("Wrong option input!");
                        break;
                }
        }
}