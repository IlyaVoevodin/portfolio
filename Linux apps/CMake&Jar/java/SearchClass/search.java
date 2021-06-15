package lab3.java.SearchClass;

public class search {
    public static void ReleaseSearch(int x, int row_x, int clmn_x, final int n, int[][] A)
    {
        for (int i = 0; i < n; i++)
        {
            int j = n - i - 1;
            if (A[i][j] == x)
            {
                row_x = i + 1;
                clmn_x = j + 1;
		System.out.printf("Row: %d, Clmn: %d",row_x, clmn_x);
                return;
            }
        else
            {
                if ((i == n - 1) && (j == 0))
                {
                    System.out.println("Value not found");
                }
            }
        }
    }

    public static void DebugSearch(int x, int row_x, int clmn_x, final int n, int[][] A)
    {
        for (int i = 0; i < n; i++)
        {
            int j = n - i - 1;

            System.out.printf("Searching...\n Current value: %d\n", A[i][j]);
            if (A[i][j] == x)
            {
                row_x = i + 1;
                clmn_x = j + 1;
                System.out.printf("Value %d was found at [%d][%d]", x, row_x, clmn_x);
                return;
            }
        else
            {
                if ((i == n - 1) && (j == 0))
                {
                    System.out.printf("Value %d was not found!", x);
                }
            }
        }
    }
}
