import java.util.*;

public class AlgorithmsSolutions 
{
    
    // PROBLEM 1: Median via Selection Sort Invariant
    
    public static int findMedian(int[] arr) 
    {
        int[] tempArr = arr.clone();
        int targetIndex = tempArr.length / 2;
    
        for (int i = 0; i <= targetIndex; i++) 
        {
            int minIdx = i;
            for (int j = i + 1; j < tempArr.length; j++) 
            {
                if (tempArr[j] < tempArr[minIdx]) 
                {
                    minIdx = j;
                }
            }
            int temp = tempArr[i];
            tempArr[i] = tempArr[minIdx];
            tempArr[minIdx] = temp;
        }
        
        return tempArr[targetIndex];
    }
    
    // PROBLEM 2: K-th Largest via Bubble Sort Invariant
    
    public static int findKthLargest(int[] arr, int k) 
    {
        int[] tempArr = arr.clone();
        int size = tempArr.length;
    
        for (int pass = 0; pass < k; pass++) 
        {
            for (int i = 0; i < size - pass - 1; i++) 
            {
                if (tempArr[i] > tempArr[i + 1]) 
                {
                    int temp = tempArr[i];
                    tempArr[i] = tempArr[i + 1];
                    tempArr[i + 1] = temp;
                }
            }
        }
        return tempArr[size - k];
    }
    
    // PROBLEM 3: Merge Two Arrays via Insertion Sort Logic
    
    public static int[] mergeSorted(int[] a, int[] b) 
    {
        int[] out = new int[a.length + b.length];
        int outCount = 0;
        
        for (int i = 0; i < a.length; i++) 
        {
            int pos = outCount;
            while (pos > 0 && out[pos - 1] > a[i]) 
            {
                out[pos] = out[pos - 1];
                pos--;
            }
            out[pos] = a[i];
            outCount++;
        }
        
        for (int i = 0; i < b.length; i++) 
        {
            int pos = outCount;
            while (pos > 0 && out[pos - 1] > b[i]) 
            {
                out[pos] = out[pos - 1];
                pos--;
            }
            out[pos] = b[i];
            outCount++;
        }
        
        return out;
    }
    
    // PROBLEM 4: Recursive Problems
    
    // 4.1: Factorial
    
    public static long factorial(int n) 
    {
        if (n == 0 || n == 1) 
        {
            return 1;
        }
        return n * factorial(n - 1);
    }
    
    // 4.2: Fibonacci
    
    public static long fibonacci(int n) 
    {
        if (n == 0) return 0;
        if (n == 1) return 1;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
    
    // 4.3: Count Digits
    
    public static int countDigits(int n) 
    {
        if (n < 10) 
        {
            return 1;
        }
        return 1 + countDigits(n / 10);
    }
    
    // 4.4: Power Function with fast exponentiation
    
    public static double power(double base, int exp) 
    {
        if (exp == 0) 
        {
            return 1.0;
        }
        
        if (exp < 0) 
        {
            return 1.0 / power(base, -exp);
        }
        
        if (exp % 2 == 0) 
        {
            double half = power(base, exp / 2);
            return half * half;
        } 
        else 
        {
            return base * power(base, exp - 1);
        }
    }
    
    // 4.5: Palindrome Check
    
    public static boolean isPalindrome(String str, int left, int right) 
    {
        if (left >= right) 
        {
            return true;
        }
        
        if (str.charAt(left) != str.charAt(right)) 
        {
            return false;
        }
        
        return isPalindrome(str, left + 1, right - 1);
    }
    
    // 4.6: Sum of Array
    
    public static int arraySum(int[] arr, int size) 
    {
        if (size == 0) 
        {
            return 0;
        }
        return arr[size - 1] + arraySum(arr, size - 1);
    }
    
    // 4.7: Maximum of Array
    
    public static int arrayMax(int[] arr, int size) 
    {
        if (size == 1) 
        {
            return arr[0];
        }
        
        int maxRest = arrayMax(arr, size - 1);
        return Math.max(arr[size - 1], maxRest);
    }
    
    // 4.8: Binary Search
    
    public static int binarySearch(int[] arr, int left, int right, int target) 
    {
        if (left > right) 
        {
            return -1;
        }
        
        int mid = (left + right) / 2;
        
        if (arr[mid] == target) 
        {
            return mid;
        } 
        else if (arr[mid] > target) 
        {
            return binarySearch(arr, left, mid - 1, target);
        } 
        else 
        {
            return binarySearch(arr, mid + 1, right, target);
        }
    }
    
    // PROBLEM 5: Merge Sort
    
    public static void mergeSort(int[] arr, int left, int right) 
    {
        if (left < right) 
        {
            int mid = left + (right - left) / 2;
            
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    
    private static void merge(int[] arr, int left, int mid, int right) 
    {
        int leftSize = mid - left + 1;
        int rightSize = right - mid;
        
        int[] leftArr = new int[leftSize];
        int[] rightArr = new int[rightSize];
        
        System.arraycopy(arr, left, leftArr, 0, leftSize);
        System.arraycopy(arr, mid + 1, rightArr, 0, rightSize);
        
        int i = 0, j = 0, k = left;
        
        while (i < leftSize && j < rightSize) 
        {
            if (leftArr[i] <= rightArr[j]) 
            {
                arr[k++] = leftArr[i++];
            } 
            else 
            {
                arr[k++] = rightArr[j++];
            }
        }
        
        while (i < leftSize) 
        {
            arr[k++] = leftArr[i++];
        }
        while (j < rightSize) 
        {
            arr[k++] = rightArr[j++];
        }
    }
    
    // PROBLEM 6: Quick Sort
    
    static long swapCount = 0;
    
    public static void quickSort(int[] arr, int low, int high) 
    {
        if (low < high) 
        {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    
    private static int partition(int[] arr, int low, int high) 
    {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) 
        {
            if (arr[j] < pivot) 
            {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                swapCount++;
            }
        }
        
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        swapCount++;
        
        return i + 1;
    }
    
    // PROBLEM 7: Fractional Knapsack
    
    static class Item implements Comparable<Item> 
    {
        int weight;
        int value;
        double ratio;
        
        Item(int weight, int value) 
        {
            this.weight = weight;
            this.value = value;
            this.ratio = (double) value / weight;
        }
        
        @Override
        public int compareTo(Item other) 
        {
            return Double.compare(other.ratio, this.ratio); 
        }
    }
    
    public static double fractionalKnapsack(Item[] items, int capacity) 
    {
        Arrays.sort(items);
        
        double totalValue = 0.0;
        int remainingCapacity = capacity;
        
        for (Item item : items) 
        {
            if (remainingCapacity <= 0) 
                break;
            
            if (item.weight <= remainingCapacity) 
            {
                totalValue += item.value;
                remainingCapacity -= item.weight;
            } 
            else 
            {
                double fraction = (double) remainingCapacity / item.weight;
                totalValue += fraction * item.value;
                remainingCapacity = 0;
            }
        }
        
        return totalValue;
    }
    
    // PROBLEM 8: Minimum Spanning Tree
    
    static class Edge implements Comparable<Edge> 
    {
        int u;
        int v;
        int weight;
        
        Edge(int u, int v, int weight) 
        {
            this.u = u;
            this.v = v;
            this.weight = weight;
        }
        
        @Override
        public int compareTo(Edge other) 
        {
            return this.weight - other.weight;
        }
    }
    
    static class UnionFind 
    {
        int[] parent;
        int[] rank;
        
        UnionFind(int n) 
        {
            parent = new int[n];
            rank = new int[n];
            for (int i = 0; i < n; i++) 
            {
                parent[i] = i;
                rank[i] = 0;
            }
        }
        
        int find(int x) 
        {
            if (parent[x] != x) 
            {
                parent[x] = find(parent[x]); 
            }
            return parent[x];
        }
        
        void unite(int x, int y) 
        {
            int rootX = find(x);
            int rootY = find(y);
            
            if (rootX != rootY) 
            {
                if (rank[rootX] < rank[rootY]) 
                {
                    parent[rootX] = rootY;
                } 
                else if (rank[rootX] > rank[rootY]) 
                {
                    parent[rootY] = rootX;
                } 
                else 
                {
                    parent[rootY] = rootX;
                    rank[rootX]++;
                }
            }
        }
    }
    
    // 8a: Prim's Algorithm
    
    public static void primsMST(int[][] graph) 
    {
        int V = graph.length;
        int[] minCost = new int[V];
        boolean[] inMST = new boolean[V];
        int[] parent = new int[V];
        
        Arrays.fill(minCost, Integer.MAX_VALUE);
        Arrays.fill(parent, -1);
        
        minCost[0] = 0;
        int totalCost = 0;
        
        System.out.println("\nPrim's Algorithm MST:");
        System.out.println("Edge\t\tWeight");
        
        for (int count = 0; count < V; count++) 
        {
            int u = -1;
            
            for (int i = 0; i < V; i++) 
            {
                if (!inMST[i] && (u == -1 || minCost[i] < minCost[u])) 
                {
                    u = i;
                }
            }
            
            inMST[u] = true;
            
            if (parent[u] != -1) 
            {
                System.out.println(parent[u] + " - " + u + "\t\t" + minCost[u]);
                totalCost += minCost[u];
            }
            
            for (int v = 0; v < V; v++) 
            {
                if (graph[u][v] != 0 && !inMST[v] && graph[u][v] < minCost[v]) 
                {
                    minCost[v] = graph[u][v];
                    parent[v] = u;
                }
            }
        }
        
        System.out.println("Total weight: " + totalCost);
    }
    
    // 8b: Kruskal's Algorithm
    
    public static void kruskalsMST(Edge[] edges, int V) 
    {
        Arrays.sort(edges);
        
        UnionFind uf = new UnionFind(V);
        int totalCost = 0;
        int edgeCount = 0;
        
        System.out.println("\nKruskal's Algorithm MST:");
        System.out.println("Edge\t\tWeight");
        
        for (Edge edge : edges) 
        {
            if (edgeCount >= V - 1) break;
            
            int u = edge.u;
            int v = edge.v;
            int w = edge.weight;
            
            if (uf.find(u) != uf.find(v)) 
            {
                System.out.println(u + " - " + v + "\t\t" + w);
                totalCost += w;
                edgeCount++;
                uf.unite(u, v);
            }
        }
        
        System.out.println("Total weight: " + totalCost);
    }
    
    // PROBLEM 9: Shortest Path Algorithms
    
    private static final int INF = 999999;
    
    // 9a: Dijkstra's Algorithm
    
    public static void dijkstra(int[][] graph, int src) 
    {
        int V = graph.length;
        int[] dist = new int[V];
        boolean[] visited = new boolean[V];
        
        Arrays.fill(dist, INF);
        dist[src] = 0;
        
        for (int count = 0; count < V - 1; count++) 
        {
            int u = -1;
            for (int i = 0; i < V; i++) 
            {
                if (!visited[i] && (u == -1 || dist[i] < dist[u])) 
                {
                    u = i;
                }
            }
            
            if (dist[u] == INF) break;
            
            visited[u] = true;
            
            for (int v = 0; v < V; v++) {
                if (graph[u][v] != 0 && !visited[v]) 
                {
                    if (dist[u] + graph[u][v] < dist[v]) 
                    {
                        dist[v] = dist[u] + graph[u][v];
                    }
                }
            }
        }
        
        System.out.println("\nDijkstra's Algorithm (Source: " + src + "):");
        System.out.println("Vertex\tDistance from Source");
        for (int i = 0; i < V; i++) 
        {
            if (dist[i] == INF) 
            {
                System.out.println(i + "\tINF");
            } 
            else 
            {
                System.out.println(i + "\t" + dist[i]);
            }
        }
    }
    
    // 9b: Bellman-Ford Algorithm
    
    public static void bellmanFord(int V, Edge[] edges, int src) 
    {
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE / 2);
        dist[src] = 0;
        
        for (int i = 0; i < V - 1; i++) 
        {
            for (Edge edge : edges) 
            {
                int u = edge.u;
                int v = edge.v;
                int w = edge.weight;
                
                if (dist[u] != Integer.MAX_VALUE / 2 && dist[u] + w < dist[v]) 
                {
                    dist[v] = dist[u] + w;
                }
            }
        }
        
        boolean hasNegativeCycle = false;
        for (Edge edge : edges) 
        {
            int u = edge.u;
            int v = edge.v;
            int w = edge.weight;
            
            if (dist[u] != Integer.MAX_VALUE / 2 && dist[u] + w < dist[v]) 
            {
                hasNegativeCycle = true;
                break;
            }
        }
        
        System.out.println("\nBellman-Ford Algorithm (Source: " + src + "):");
        
        if (hasNegativeCycle) 
        {
            System.out.println("Graph contains a negative-weight cycle");
        } 
        else 
        {
            System.out.println("Vertex\tDistance from Source");
            for (int i = 0; i < V; i++) 
            {
                if (dist[i] == Integer.MAX_VALUE / 2) 
                {
                    System.out.println(i + "\tINF");
                } 
                else 
                {
                    System.out.println(i + "\t" + dist[i]);
                }
            }
        }
    }
    
    // PROBLEM 10: Dynamic Programming
    
    // 10a: 0/1 Knapsack
    
    public static int knapsack01(int[] weights, int[] values, int W) 
    {
        int n = weights.length;
        int[][] dp = new int[n + 1][W + 1];
        
        for (int i = 1; i <= n; i++) 
        {
            for (int w = 1; w <= W; w++) 
            {
                if (weights[i - 1] <= w) 
                {
                    dp[i][w] = Math.max(
                        values[i - 1] + dp[i - 1][w - weights[i - 1]],
                        dp[i - 1][w]
                    );
                } 
                else 
                {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
        
        return dp[n][W];
    }
    
    // 10b: Minimum Coins
    
    public static int minCoins(int[] coins, int amount) 
    {
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;
        
        for (int i = 1; i <= amount; i++) 
        {
            for (int coin : coins) {
                if (coin <= i && dp[i - coin] != Integer.MAX_VALUE) 
                {
                    dp[i] = Math.min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        
        return dp[amount] == Integer.MAX_VALUE ? -1 : dp[amount];
    }
    
    // 10c: Count Coin Ways
    
    public static int countWays(int[] coins, int amount) 
    {
        int[] dp = new int[amount + 1];
        dp[0] = 1;
        
        for (int coin : coins) 
        {
            for (int a = coin; a <= amount; a++) 
            {
                dp[a] += dp[a - coin];
            }
        }
        return dp[amount];
    }
    
    // 10d: Longest Common Subsequence
    
    public static int lcs(String s1, String s2) 
    {
        int m = s1.length();
        int n = s2.length();
        int[][] dp = new int[m + 1][n + 1];
        
        for (int i = 1; i <= m; i++) 
        {
            for (int j = 1; j <= n; j++) 
            {
                if (s1.charAt(i - 1) == s2.charAt(j - 1)) 
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } 
                else 
                {
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[m][n];
    }
    
    // 10e: Longest Increasing Subsequence
    
    public static int lis(int[] arr) 
    {
        int n = arr.length;
        int[] dp = new int[n];
        Arrays.fill(dp, 1);
        
        for (int i = 1; i < n; i++) 
        {
            for (int j = 0; j < i; j++) 
            {
                if (arr[j] < arr[i]) 
                {
                    dp[i] = Math.max(dp[i], 1 + dp[j]);
                }
            }
        }
        
        int maxLis = 0;
        for (int val : dp) 
        {
            maxLis = Math.max(maxLis, val);
        }
        
        return maxLis;
    }
    
    public static void main(String[] args) 
    {
        System.out.println("====================================================================");
        System.out.println("           ALGORITHM PROBLEM SET - COMPLETE JAVA SOLUTIONS");
        System.out.println("====================================================================");
        
        // Problem 1: Median
        System.out.println("\n[PROBLEM 1] Median via Selection Sort Invariant");
        System.out.println("-------------------------------------------------");
        {
            int[] arr1 = {7, 2, 10, 9, 1};
            System.out.println("Input: {7, 2, 10, 9, 1}");
            System.out.println("Output: " + findMedian(arr1));
            
            int[] arr2 = {4, 1, 8, 3};
            System.out.println("Input: {4, 1, 8, 3}");
            System.out.println("Output: " + findMedian(arr2));
        }
        
        // Problem 2: K-th Largest
        System.out.println("\n[PROBLEM 2] K-th Largest via Bubble Sort Invariant");
        System.out.println("---------------------------------------------------");
        {
            int[] arr1 = {3, 1, 7, 4, 9, 2};
            System.out.println("Input: {3, 1, 7, 4, 9, 2}, k=2");
            System.out.println("Output: " + findKthLargest(arr1, 2));
            
            int[] arr2 = {10, 5, 8, 3};
            System.out.println("Input: {10, 5, 8, 3}, k=4");
            System.out.println("Output: " + findKthLargest(arr2, 4));
        }
        
        // Problem 3: Merge Two Arrays
        System.out.println("\n[PROBLEM 3] Merge Two Arrays via Insertion Sort Logic");
        System.out.println("------------------------------------------------------");
        {
            int[] a = {5, 1, 9};
            int[] b = {3, 7, 2, 6};
            System.out.println("Input A: {5, 1, 9}");
            System.out.println("Input B: {3, 7, 2, 6}");
            int[] result = mergeSorted(a, b);
            System.out.print("Output: {");
            for (int i = 0; i < result.length; i++) 
            {
                System.out.print(result[i]);
                if (i < result.length - 1) System.out.print(", ");
            }
            System.out.println("}");
        }
        
        // Problem 4: Recursive Problems
        System.out.println("\n[PROBLEM 4] Recursive Problems");
        System.out.println("------------------------------");
        {
            System.out.println("4.1 Factorial:");
            System.out.println("  factorial(0) = " + factorial(0));
            System.out.println("  factorial(5) = " + factorial(5));
            System.out.println("  factorial(10) = " + factorial(10));
            
            System.out.println("\n4.2 Fibonacci:");
            System.out.println("  fibonacci(0) = " + fibonacci(0));
            System.out.println("  fibonacci(7) = " + fibonacci(7));
            System.out.println("  fibonacci(10) = " + fibonacci(10));
            
            System.out.println("\n4.3 Count Digits:");
            System.out.println("  countDigits(0) = " + countDigits(0));
            System.out.println("  countDigits(100) = " + countDigits(100));
            System.out.println("  countDigits(98765) = " + countDigits(98765));
            
            System.out.println("\n4.4 Power:");
            System.out.println("  power(2.0, 0) = " + power(2.0, 0));
            System.out.println("  power(3.0, 4) = " + power(3.0, 4));
            System.out.println(String.format("  power(2.5, 3) = %.3f", power(2.5, 3)));
            
            System.out.println("\n4.5 Palindrome Check:");
            System.out.println("  isPalindrome(\"racecar\") = " + isPalindrome("racecar", 0, 6));
            System.out.println("  isPalindrome(\"hello\") = " + isPalindrome("hello", 0, 4));
            System.out.println("  isPalindrome(\"abba\") = " + isPalindrome("abba", 0, 3));
            
            System.out.println("\n4.6 Array Sum:");
            int[] arrSum = {1, 2, 3, 4, 5};
            System.out.println("  arraySum({1,2,3,4,5}, 5) = " + arraySum(arrSum, 5));
            
            System.out.println("\n4.7 Array Max:");
            int[] arrMax = {3, 1, 9, 2, 7};
            System.out.println("  arrayMax({3,1,9,2,7}, 5) = " + arrayMax(arrMax, 5));
            
            System.out.println("\n4.8 Binary Search:");
            int[] arrBs = {1, 3, 5, 7, 9};
            System.out.println("  binarySearch({1,3,5,7,9}, 0, 4, 7) = " + binarySearch(arrBs, 0, 4, 7));
            System.out.println("  binarySearch({1,3,5,7,9}, 0, 4, 4) = " + binarySearch(arrBs, 0, 4, 4));
        }
        
        // Problem 5: Merge Sort
        System.out.println("\n[PROBLEM 5] Merge Sort");
        System.out.println("---------------------");
        {
            int[] arr = {38, 27, 43, 3, 9, 82, 10};
            System.out.println("Input: {38, 27, 43, 3, 9, 82, 10}");
            mergeSort(arr, 0, arr.length - 1);
            System.out.print("Output: {");
            for (int i = 0; i < arr.length; i++) 
            {
                System.out.print(arr[i]);
                if (i < arr.length - 1) System.out.print(", ");
            }
            System.out.println("}");
        }
        
        // Problem 6: Quick Sort
        System.out.println("\n[PROBLEM 6] Quick Sort");
        System.out.println("---------------------");
        {
            int[] arr = {10, 7, 8, 9, 1, 5};
            System.out.println("Input: {10, 7, 8, 9, 1, 5}");
            swapCount = 0;
            quickSort(arr, 0, arr.length - 1);
            System.out.print("Output: {");
            for (int i = 0; i < arr.length; i++) 
            {
                System.out.print(arr[i]);
                if (i < arr.length - 1) System.out.print(", ");
            }
            System.out.println("}");
            System.out.println("Total Swaps: " + swapCount);
        }
        
        // Problem 7: Fractional Knapsack
        System.out.println("\n[PROBLEM 7] Fractional Knapsack");
        System.out.println("--------------------------------");
        {
            Item[] items = 
            {
                new Item(10, 60),
                new Item(20, 100),
                new Item(30, 120)
            };
            System.out.println("Input: weights={10,20,30}, values={60,100,120}, capacity=50");
            double result = fractionalKnapsack(items, 50);
            System.out.println(String.format("Output: %.2f", result));
        }
        
        // Problem 8: Minimum Spanning Tree
        System.out.println("\n[PROBLEM 8] Minimum Spanning Tree");
        System.out.println("----------------------------------");
        {
            int[][] graph = 
            {
                {0, 2, 0, 6, 0},
                {2, 0, 3, 8, 5},
                {0, 3, 0, 7, 0},
                {6, 8, 7, 0, 9},
                {0, 5, 0, 9, 0}
            };
            
            primsMST(graph);
            
            Edge[] edges = 
            {
                new Edge(0, 1, 2), new Edge(0, 3, 6), new Edge(1, 2, 3),
                new Edge(1, 3, 8), new Edge(1, 4, 5), new Edge(2, 3, 7),
                new Edge(2, 4, 7), new Edge(3, 4, 9)
            };
            
            kruskalsMST(edges, 5);
        }
        
        // Problem 9: Shortest Paths
        System.out.println("\n[PROBLEM 9] Shortest Path Algorithms");
        System.out.println("-------------------------------------");
        {
            int[][] graph = 
            {
                {0, 4, 0, 0, 8},
                {4, 0, 8, 0, 11},
                {0, 8, 0, 7, 0},
                {0, 0, 7, 0, 9},
                {8, 11, 0, 9, 0}
            };
            
            dijkstra(graph, 0);
            
            Edge[] edges = 
            {
                new Edge(0, 1, 6), new Edge(0, 2, 7), new Edge(1, 2, 8),
                new Edge(1, 3, 5), new Edge(1, 4, -4), new Edge(2, 3, -3),
                new Edge(2, 4, 9), new Edge(3, 1, -2), new Edge(4, 0, 2),
                new Edge(4, 3, 7)
            };
            
            bellmanFord(5, edges, 0);
        }
        
        // Problem 10: Dynamic Programming
        System.out.println("\n[PROBLEM 10] Dynamic Programming");
        System.out.println("----------------------------------");
        {
            System.out.println("10a. 0/1 Knapsack:");
            int[] weights = {2, 3, 4, 5};
            int[] values = {3, 4, 5, 6};
            int result = knapsack01(weights, values, 5);
            System.out.println("  Input: weights={2,3,4,5}, values={3,4,5,6}, W=5");
            System.out.println("  Output: " + result);
            
            System.out.println("\n10b. Minimum Coins:");
            int[] coins = {1, 5, 6, 9};
            result = minCoins(coins, 11);
            System.out.println("  Input: coins={1,5,6,9}, amount=11");
            System.out.println("  Output: " + result);
            
            System.out.println("\n10c. Count Coin Ways:");
            int[] coins2 = {1, 2, 3};
            result = countWays(coins2, 4);
            System.out.println("  Input: coins={1,2,3}, amount=4");
            System.out.println("  Output: " + result + " (combinations: {1,1,1,1}, {1,1,2}, {1,3}, {2,2})");
            
            System.out.println("\n10d. Longest Common Subsequence:");
            result = lcs("ABCBDAB", "BDCAB");
            System.out.println("  Input: s1=\"ABCBDAB\", s2=\"BDCAB\"");
            System.out.println("  Output: " + result);
            
            System.out.println("\n10e. Longest Increasing Subsequence:");
            int[] arr = {10, 9, 2, 5, 3, 7, 101, 18};
            result = lis(arr);
            System.out.println("  Input: {10,9,2,5,3,7,101,18}");
            System.out.println("  Output: " + result);
        }
        
        System.out.println("\n====================================================================");
        System.out.println("                    ALL TESTS COMPLETED");
        System.out.println("====================================================================");
    }
}
