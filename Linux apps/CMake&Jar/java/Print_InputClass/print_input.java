package lab3.java.Print_InputClass;
import java.util.Scanner;

public class print_input {
    public static void HandInput(final int n, int[][] A)
    {
        Scanner in = new Scanner(System.in);
        int val;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n ; j++)
            {
                System.out.printf("Input value for [%d][%d]:", i, j);
                val = in.nextInt();
                A[i][j] = val;
            }
        }
        //in.close();
    }

    public static void SortedInput(final int n, int[][] A)
    {
        int[][] matrix= {
        { 21, 34, 56, 22, 76, 90, 36, 47, 83, 14},
        { 45, 10, 17, 84, 62, 49, 58, 55, 13, 98},
        { 16, 26, 82, 67, 15, 65, 12, 24 , 15, 33},
        { 79, 13, 57, 44, 38, 94, 11, 47, 49, 86},
        { 46, 12, 64, 83, 47, 23, 10, 21, 30 ,66},
        { 34, 75, 14, 73, 52, 39, 27, 32, 11, 78},
        { 45, 27, 48, 18, 95, 60, 71, 76, 88 ,37},
        { 76, 10, 46, 83, 27, 18, 72, 92, 37, 58},
        { 14, 41, 62, 72, 17, 48, 39, 94, 93, 77},
        { 15, 67, 73, 45, 47, 37, 74, 59, 37, 28}
    };
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                A[i][j] = matrix[i][j];
            }
        }
    }

    public static void RandInput(int n, int[][] A)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                A[i][j] = (int)(Math.random() * 100);
            }
        }
    }

    public static void pretty_print(final int n, int[][] A)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                System.out.printf("%d\t", A[i][j]);
            }
            System.out.print("\n\n");
        }
    }
    public static void menu(final int n, int[][] A)
    {
        Scanner in = new Scanner(System.in);
        int var;
        System.out.print("Choose type of matrix filler:\n 1)Keyboard\n 2)Rand\n 3)Sorted\n Print number to choose:");
        var = in.nextInt();
        switch (var) {
            case 1:
                HandInput(n, A);
                pretty_print(n, A);
                break;
            case 2:
                RandInput(n, A);
                pretty_print(n, A);
                break;
            case 3:
                SortedInput(n, A);
                pretty_print(n, A);
                break;
            default:
                System.out.print("Wrong input");
                break;
        }
    }
}
