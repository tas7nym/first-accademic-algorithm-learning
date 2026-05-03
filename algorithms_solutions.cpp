#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <float.h>

// ============================================================================
// PROBLEM 1: Median via Selection Sort Invariant
// ============================================================================

int find_median(int *arr, int size) {
    int target_index = size / 2;
    
    // Run selection sort only until we reach the median index
    for (int i = 0; i <= target_index; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
    
    return arr[target_index];
}

// ============================================================================
// PROBLEM 2: K-th Largest via Bubble Sort Invariant
// ============================================================================

int find_kth_largest(int *arr, int size, int k) {
    // Run k passes of bubble sort
    for (int pass = 0; pass < k; pass++) {
        for (int i = 0; i < size - pass - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    }
    
    // k-th largest is at index size - k
    return arr[size - k];
}

// ============================================================================
// PROBLEM 3: Merge Two Arrays via Insertion Sort Logic
// ============================================================================

void merge_sorted(int *a, int n, int *b, int m, int *out) {
    // Combine all elements into output using insertion sort logic
    int out_count = 0;
    
    // Process all elements from a
    for (int i = 0; i < n; i++) {
        // Find correct position to insert a[i]
        int pos = out_count;
        while (pos > 0 && out[pos - 1] > a[i]) {
            out[pos] = out[pos - 1];
            pos--;
        }
        out[pos] = a[i];
        out_count++;
    }
    
    // Process all elements from b
    for (int i = 0; i < m; i++) {
        // Find correct position to insert b[i]
        int pos = out_count;
        while (pos > 0 && out[pos - 1] > b[i]) {
            out[pos] = out[pos - 1];
            pos--;
        }
        out[pos] = b[i];
        out_count++;
    }
}

// ============================================================================
// PROBLEM 4: Recursive Problems
// ============================================================================

// 4.1: Factorial
long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// 4.2: Fibonacci
long long fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 4.3: Count Digits
int count_digits(int n) {
    if (n < 10) {
        return 1;
    }
    return 1 + count_digits(n / 10);
}

// 4.4: Power Function
double power(double base, int exp) {
    // Base case
    if (exp == 0) {
        return 1.0;
    }
    
    // For fast exponentiation (O(log exp))
    if (exp < 0) {
        return 1.0 / power(base, -exp);
    }
    
    if (exp % 2 == 0) {
        double half = power(base, exp / 2);
        return half * half;
    } else {
        return base * power(base, exp - 1);
    }
}

// 4.5: Palindrome Check
int is_palindrome(char *str, int left, int right) {
    if (left >= right) {
        return 1;
    }
    
    if (str[left] != str[right]) {
        return 0;
    }
    
    return is_palindrome(str, left + 1, right - 1);
}

// 4.6: Sum of Array
int array_sum(int *arr, int size) {
    if (size == 0) {
        return 0;
    }
    return arr[size - 1] + array_sum(arr, size - 1);
}

// 4.7: Maximum of Array
int array_max(int *arr, int size) {
    if (size == 1) {
        return arr[0];
    }
    
    int max_rest = array_max(arr, size - 1);
    return arr[size - 1] > max_rest ? arr[size - 1] : max_rest;
}

// 4.8: Binary Search
int binary_search(int *arr, int left, int right, int target) {
    if (left > right) {
        return -1;
    }
    
    int mid = (left + right) / 2;
    
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] > target) {
        return binary_search(arr, left, mid - 1, target);
    } else {
        return binary_search(arr, mid + 1, right, target);
    }
}

// ============================================================================
// PROBLEM 5: Merge Sort
// ============================================================================

void merge(int *arr, int left, int mid, int right) {
    int left_size = mid - left + 1;
    int right_size = right - mid;
    
    // Create temporary arrays
    int *left_arr = (int *)malloc(left_size * sizeof(int));
    int *right_arr = (int *)malloc(right_size * sizeof(int));
    
    // Copy data to temporary arrays
    for (int i = 0; i < left_size; i++) {
        left_arr[i] = arr[left + i];
    }
    for (int i = 0; i < right_size; i++) {
        right_arr[i] = arr[mid + 1 + i];
    }
    
    // Merge the temporary arrays back
    int i = 0, j = 0, k = left;
    
    while (i < left_size && j < right_size) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k++] = left_arr[i++];
        } else {
            arr[k++] = right_arr[j++];
        }
    }
    
    // Copy remaining elements
    while (i < left_size) {
        arr[k++] = left_arr[i++];
    }
    while (j < right_size) {
        arr[k++] = right_arr[j++];
    }
    
    free(left_arr);
    free(right_arr);
}

void merge_sort(int *arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ============================================================================
// PROBLEM 6: Quick Sort
// ============================================================================

long long swap_count = 0;

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            swap_count++;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    swap_count++;
    
    return i + 1;
}

void quick_sort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// ============================================================================
// PROBLEM 7: Fractional Knapsack
// ============================================================================

typedef struct {
    int weight;
    int value;
    double ratio;
    int index;
} Item;

int compare_items(const void *a, const void *b) {
    Item *item_a = (Item *)a;
    Item *item_b = (Item *)b;
    
    if (item_b->ratio > item_a->ratio) return 1;
    if (item_b->ratio < item_a->ratio) return -1;
    return 0;
}

double fractional_knapsack(Item *items, int n, int capacity) {
    // Calculate ratios
    for (int i = 0; i < n; i++) {
        items[i].ratio = (double)items[i].value / items[i].weight;
        items[i].index = i;
    }
    
    // Sort by ratio in descending order
    qsort(items, n, sizeof(Item), compare_items);
    
    double total_value = 0.0;
    int remaining_capacity = capacity;
    
    for (int i = 0; i < n && remaining_capacity > 0; i++) {
        if (items[i].weight <= remaining_capacity) {
            // Take the whole item
            total_value += items[i].value;
            remaining_capacity -= items[i].weight;
        } else {
            // Take fraction of the item
            double fraction = (double)remaining_capacity / items[i].weight;
            total_value += fraction * items[i].value;
            remaining_capacity = 0;
        }
    }
    
    return total_value;
}

// ============================================================================
// PROBLEM 8: Minimum Spanning Tree
// ============================================================================

#define V 5
#define INF 999999

typedef struct {
    int u;
    int v;
    int weight;
} Edge;

// Union-Find structure
typedef struct {
    int parent[V];
    int rank[V];
} UnionFind;

void make_set(UnionFind *uf) {
    for (int i = 0; i < V; i++) {
        uf->parent[i] = i;
        uf->rank[i] = 0;
    }
}

int find(UnionFind *uf, int x) {
    if (uf->parent[x] != x) {
        uf->parent[x] = find(uf, uf->parent[x]); // Path compression
    }
    return uf->parent[x];
}

void unite(UnionFind *uf, int x, int y) {
    int root_x = find(uf, x);
    int root_y = find(uf, y);
    
    if (root_x != root_y) {
        // Union by rank
        if (uf->rank[root_x] < uf->rank[root_y]) {
            uf->parent[root_x] = root_y;
        } else if (uf->rank[root_x] > uf->rank[root_y]) {
            uf->parent[root_y] = root_x;
        } else {
            uf->parent[root_y] = root_x;
            uf->rank[root_x]++;
        }
    }
}

// 8a: Prim's Algorithm
void prims_mst(int graph[V][V]) {
    int in_mst[V];
    int min_cost[V];
    int parent[V];
    
    memset(in_mst, 0, sizeof(in_mst));
    memset(parent, -1, sizeof(parent));
    
    for (int i = 0; i < V; i++) {
        min_cost[i] = INF;
    }
    
    min_cost[0] = 0;
    int total_cost = 0;
    
    printf("\nPrim's Algorithm MST:\n");
    printf("Edge\t\tWeight\n");
    
    for (int count = 0; count < V; count++) {
        int u = -1;
        
        // Find minimum cost vertex not in MST
        for (int i = 0; i < V; i++) {
            if (!in_mst[i] && (u == -1 || min_cost[i] < min_cost[u])) {
                u = i;
            }
        }
        
        in_mst[u] = 1;
        
        if (parent[u] != -1) {
            printf("%d - %d\t\t%d\n", parent[u], u, min_cost[u]);
            total_cost += min_cost[u];
        }
        
        // Update costs of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && !in_mst[v] && graph[u][v] < min_cost[v]) {
                min_cost[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }
    
    printf("Total weight: %d\n", total_cost);
}

int compare_edges(const void *a, const void *b) {
    Edge *edge_a = (Edge *)a;
    Edge *edge_b = (Edge *)b;
    return edge_a->weight - edge_b->weight;
}

// 8b: Kruskal's Algorithm
void kruskals_mst(Edge *edges, int E) {
    qsort(edges, E, sizeof(Edge), compare_edges);
    
    UnionFind uf;
    make_set(&uf);
    
    int total_cost = 0;
    int edge_count = 0;
    
    printf("\nKruskal's Algorithm MST:\n");
    printf("Edge\t\tWeight\n");
    
    for (int i = 0; i < E && edge_count < V - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;
        
        if (find(&uf, u) != find(&uf, v)) {
            printf("%d - %d\t\t%d\n", u, v, w);
            total_cost += w;
            edge_count++;
            unite(&uf, u, v);
        }
    }
    
    printf("Total weight: %d\n", total_cost);
}

// ============================================================================
// PROBLEM 9a: Dijkstra's Algorithm
// ============================================================================

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    int visited[V];
    
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    
    dist[src] = 0;
    
    for (int count = 0; count < V - 1; count++) {
        int u = -1;
        
        // Find unvisited vertex with minimum distance
        for (int i = 0; i < V; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }
        
        if (dist[u] == INF) break;
        
        visited[u] = 1;
        
        // Relax edges
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && !visited[v]) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }
    
    printf("\nDijkstra's Algorithm (Source: %d):\n", src);
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF) {
            printf("%d\tINF\n", i);
        } else {
            printf("%d\t%d\n", i, dist[i]);
        }
    }
}

// ============================================================================
// PROBLEM 9b: Bellman-Ford Algorithm
// ============================================================================

void bellman_ford(int V_count, int E_count, Edge *edges, int src) {
    int dist[V];
    
    for (int i = 0; i < V_count; i++) {
        dist[i] = INT_MAX / 2;
    }
    
    dist[src] = 0;
    
    // Relax edges V-1 times
    for (int i = 0; i < V_count - 1; i++) {
        for (int j = 0; j < E_count; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].weight;
            
            if (dist[u] != INT_MAX / 2 && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    // Check for negative cycles
    int has_negative_cycle = 0;
    for (int i = 0; i < E_count; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;
        
        if (dist[u] != INT_MAX / 2 && dist[u] + w < dist[v]) {
            has_negative_cycle = 1;
            break;
        }
    }
    
    printf("\nBellman-Ford Algorithm (Source: %d):\n", src);
    
    if (has_negative_cycle) {
        printf("Graph contains a negative-weight cycle\n");
    } else {
        printf("Vertex\tDistance from Source\n");
        for (int i = 0; i < V_count; i++) {
            if (dist[i] == INT_MAX / 2) {
                printf("%d\tINF\n", i);
            } else {
                printf("%d\t%d\n", i, dist[i]);
            }
        }
    }
}

// ============================================================================
// PROBLEM 10: Dynamic Programming
// ============================================================================

// 10a: 0/1 Knapsack
int knapsack_01(int *weights, int *values, int n, int W) {
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((W + 1) * sizeof(int));
        memset(dp[i], 0, (W + 1) * sizeof(int));
    }
    
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = (values[i - 1] + dp[i - 1][w - weights[i - 1]]) > dp[i - 1][w] 
                           ? (values[i - 1] + dp[i - 1][w - weights[i - 1]]) : dp[i - 1][w];
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    
    int result = dp[n][W];
    
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

// 10b: Minimum Coins
int min_coins(int *coins, int n, int amount) {
    int *dp = (int *)malloc((amount + 1) * sizeof(int));
    
    for (int i = 0; i <= amount; i++) {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;
    
    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                dp[i] = (dp[i - coins[j]] + 1) < dp[i] ? (dp[i - coins[j]] + 1) : dp[i];
            }
        }
    }
    
    int result = (dp[amount] == INT_MAX) ? -1 : dp[amount];
    free(dp);
    return result;
}

// 10c: Count Ways - Coin Combinations
int count_ways(int *coins, int n, int amount) {
    int *dp = (int *)malloc((amount + 1) * sizeof(int));
    memset(dp, 0, (amount + 1) * sizeof(int));
    
    dp[0] = 1; // One way to make 0
    
    // Iterate over coins (outer loop) to avoid counting permutations
    for (int i = 0; i < n; i++) {
        for (int a = coins[i]; a <= amount; a++) {
            dp[a] += dp[a - coins[i]];
        }
    }
    
    int result = dp[amount];
    free(dp);
    return result;
}

// 10d: Longest Common Subsequence (LCS)
int lcs(char *s1, char *s2, int m, int n) {
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        memset(dp[i], 0, (n + 1) * sizeof(int));
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
    
    int result = dp[m][n];
    
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return result;
}

// 10e: Longest Increasing Subsequence (LIS)
int lis(int *arr, int n) {
    int *dp = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                dp[i] = (1 + dp[j]) > dp[i] ? (1 + dp[j]) : dp[i];
            }
        }
    }
    
    int max_lis = 0;
    for (int i = 0; i < n; i++) {
        max_lis = dp[i] > max_lis ? dp[i] : max_lis;
    }
    
    free(dp);
    return max_lis;
}

// ============================================================================
// TEST MAIN FUNCTION
// ============================================================================

int main() {
    printf("====================================================================\n");
    printf("           ALGORITHM PROBLEM SET - COMPLETE SOLUTIONS\n");
    printf("====================================================================\n");
    
    // Problem 1: Median
    printf("\n[PROBLEM 1] Median via Selection Sort Invariant\n");
    printf("-------------------------------------------------\n");
    {
        int arr1[] = {7, 2, 10, 9, 1};
        int arr1_copy[] = {7, 2, 10, 9, 1};
        int result = find_median(arr1_copy, 5);
        printf("Input: {7, 2, 10, 9, 1}\nOutput: %d\n", result);
        
        int arr2[] = {4, 1, 8, 3};
        int arr2_copy[] = {4, 1, 8, 3};
        result = find_median(arr2_copy, 4);
        printf("Input: {4, 1, 8, 3}\nOutput: %d\n", result);
    }
    
    // Problem 2: K-th Largest
    printf("\n[PROBLEM 2] K-th Largest via Bubble Sort Invariant\n");
    printf("---------------------------------------------------\n");
    {
        int arr1[] = {3, 1, 7, 4, 9, 2};
        int arr1_copy[] = {3, 1, 7, 4, 9, 2};
        int result = find_kth_largest(arr1_copy, 6, 2);
        printf("Input: {3, 1, 7, 4, 9, 2}, k=2\nOutput: %d\n", result);
        
        int arr2[] = {10, 5, 8, 3};
        int arr2_copy[] = {10, 5, 8, 3};
        result = find_kth_largest(arr2_copy, 4, 4);
        printf("Input: {10, 5, 8, 3}, k=4\nOutput: %d\n", result);
    }
    
    // Problem 3: Merge Two Arrays
    printf("\n[PROBLEM 3] Merge Two Arrays via Insertion Sort Logic\n");
    printf("------------------------------------------------------\n");
    {
        int a[] = {5, 1, 9};
        int b[] = {3, 7, 2, 6};
        int out[7];
        merge_sorted(a, 3, b, 4, out);
        printf("Input A: {5, 1, 9}\nInput B: {3, 7, 2, 6}\nOutput: {");
        for (int i = 0; i < 7; i++) {
            printf("%d%s", out[i], i < 6 ? ", " : "}\n");
        }
    }
    
    // Problem 4: Recursive Problems
    printf("\n[PROBLEM 4] Recursive Problems\n");
    printf("------------------------------\n");
    {
        printf("4.1 Factorial:\n");
        printf("  factorial(0) = %lld\n", factorial(0));
        printf("  factorial(5) = %lld\n", factorial(5));
        printf("  factorial(10) = %lld\n", factorial(10));
        
        printf("\n4.2 Fibonacci:\n");
        printf("  fibonacci(0) = %lld\n", fibonacci(0));
        printf("  fibonacci(7) = %lld\n", fibonacci(7));
        printf("  fibonacci(10) = %lld\n", fibonacci(10));
        
        printf("\n4.3 Count Digits:\n");
        printf("  count_digits(0) = %d\n", count_digits(0));
        printf("  count_digits(100) = %d\n", count_digits(100));
        printf("  count_digits(98765) = %d\n", count_digits(98765));
        
        printf("\n4.4 Power:\n");
        printf("  power(2.0, 0) = %.1f\n", power(2.0, 0));
        printf("  power(3.0, 4) = %.1f\n", power(3.0, 4));
        printf("  power(2.5, 3) = %.3f\n", power(2.5, 3));
        
        printf("\n4.5 Palindrome Check:\n");
        printf("  is_palindrome(\"racecar\", 0, 6) = %d\n", is_palindrome("racecar", 0, 6));
        printf("  is_palindrome(\"hello\", 0, 4) = %d\n", is_palindrome("hello", 0, 4));
        printf("  is_palindrome(\"abba\", 0, 3) = %d\n", is_palindrome("abba", 0, 3));
        
        printf("\n4.6 Array Sum:\n");
        int arr_sum[] = {1, 2, 3, 4, 5};
        printf("  array_sum({1,2,3,4,5}, 5) = %d\n", array_sum(arr_sum, 5));
        
        printf("\n4.7 Array Max:\n");
        int arr_max[] = {3, 1, 9, 2, 7};
        printf("  array_max({3,1,9,2,7}, 5) = %d\n", array_max(arr_max, 5));
        
        printf("\n4.8 Binary Search:\n");
        int arr_bs[] = {1, 3, 5, 7, 9};
        printf("  binary_search({1,3,5,7,9}, 0, 4, 7) = %d\n", binary_search(arr_bs, 0, 4, 7));
        printf("  binary_search({1,3,5,7,9}, 0, 4, 4) = %d\n", binary_search(arr_bs, 0, 4, 4));
    }
    
    // Problem 5: Merge Sort
    printf("\n[PROBLEM 5] Merge Sort\n");
    printf("---------------------\n");
    {
        int arr[] = {38, 27, 43, 3, 9, 82, 10};
        int size = 7;
        printf("Input: {38, 27, 43, 3, 9, 82, 10}\n");
        merge_sort(arr, 0, size - 1);
        printf("Output: {");
        for (int i = 0; i < size; i++) {
            printf("%d%s", arr[i], i < size - 1 ? ", " : "}\n");
        }
    }
    
    // Problem 6: Quick Sort
    printf("\n[PROBLEM 6] Quick Sort\n");
    printf("---------------------\n");
    {
        int arr[] = {10, 7, 8, 9, 1, 5};
        int size = 6;
        printf("Input: {10, 7, 8, 9, 1, 5}\n");
        swap_count = 0;
        quick_sort(arr, 0, size - 1);
        printf("Output: {");
        for (int i = 0; i < size; i++) {
            printf("%d%s", arr[i], i < size - 1 ? ", " : "}\n");
        }
        printf("Total Swaps: %lld\n", swap_count);
    }
    
    // Problem 7: Fractional Knapsack
    printf("\n[PROBLEM 7] Fractional Knapsack\n");
    printf("--------------------------------\n");
    {
        Item items[] = {
            {10, 60, 0, 0},
            {20, 100, 0, 1},
            {30, 120, 0, 2}
        };
        double result = fractional_knapsack(items, 3, 50);
        printf("Input: weights={10,20,30}, values={60,100,120}, capacity=50\n");
        printf("Output: %.2f\n", result);
    }
    
    // Problem 8: Minimum Spanning Tree
    printf("\n[PROBLEM 8] Minimum Spanning Tree\n");
    printf("----------------------------------\n");
    {
        int graph[V][V] = {
            {0, 2, 0, 6, 0},
            {2, 0, 3, 8, 5},
            {0, 3, 0, 7, 0},
            {6, 8, 7, 0, 9},
            {0, 5, 0, 9, 0}
        };
        
        Edge edges[] = {
            {0, 1, 2}, {0, 3, 6}, {1, 2, 3}, {1, 3, 8},
            {1, 4, 5}, {2, 3, 7}, {2, 4, 0}, {3, 4, 9}
        };
        
        prims_mst(graph);
        
        // Reinitialize edges for Kruskal's
        edges[6] = {2, 4, 7}; // Fix the edge we modified
        kruskals_mst(edges, 8);
    }
    
    // Problem 9: Shortest Paths
    printf("\n[PROBLEM 9] Shortest Path Algorithms\n");
    printf("-------------------------------------\n");
    {
        int graph[V][V] = {
            {0, 4, 0, 0, 8},
            {4, 0, 8, 0, 11},
            {0, 8, 0, 7, 0},
            {0, 0, 7, 0, 9},
            {8, 11, 0, 9, 0}
        };
        
        dijkstra(graph, 0);
        
        // Bellman-Ford
        Edge edges[] = {
            {0, 1, 6}, {0, 2, 7}, {1, 2, 8}, {1, 3, 5},
            {1, 4, -4}, {2, 3, -3}, {2, 4, 9}, {3, 1, -2},
            {4, 0, 2}, {4, 3, 7}
        };
        
        bellman_ford(5, 10, edges, 0);
    }
    
    // Problem 10: Dynamic Programming
    printf("\n[PROBLEM 10] Dynamic Programming\n");
    printf("----------------------------------\n");
    {
        printf("10a. 0/1 Knapsack:\n");
        int weights[] = {2, 3, 4, 5};
        int values[] = {3, 4, 5, 6};
        int result = knapsack_01(weights, values, 4, 5);
        printf("  Input: weights={2,3,4,5}, values={3,4,5,6}, W=5\n");
        printf("  Output: %d\n", result);
        
        printf("\n10b. Minimum Coins:\n");
        int coins[] = {1, 5, 6, 9};
        result = min_coins(coins, 4, 11);
        printf("  Input: coins={1,5,6,9}, amount=11\n");
        printf("  Output: %d\n", result);
        
        printf("\n10c. Count Coin Ways:\n");
        int coins2[] = {1, 2, 3};
        result = count_ways(coins2, 3, 4);
        printf("  Input: coins={1,2,3}, amount=4\n");
        printf("  Output: %d (combinations: {1,1,1,1}, {1,1,2}, {1,3}, {2,2})\n", result);
        
        printf("\n10d. Longest Common Subsequence:\n");
        result = lcs("ABCBDAB", "BDCAB", 7, 5);
        printf("  Input: s1=\"ABCBDAB\", s2=\"BDCAB\"\n");
        printf("  Output: %d\n", result);
        
        printf("\n10e. Longest Increasing Subsequence:\n");
        int arr[] = {10, 9, 2, 5, 3, 7, 101, 18};
        result = lis(arr, 8);
        printf("  Input: {10,9,2,5,3,7,101,18}\n");
        printf("  Output: %d\n", result);
    }
    
    printf("\n====================================================================\n");
    printf("                    ALL TESTS COMPLETED\n");
    printf("====================================================================\n");
    
    return 0;
}
