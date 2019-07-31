import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Scanner;

/**
 * @file Proj3.java
 *
 * Implements Kruskal's Minimum Spanning Tree algorithm which utilizes up-trees,
 * heaps, and, in this case, linked lists.
 */
public class Proj3 {
    static int numVertices = 0;
    
    /**
     * Accepts arguments from the console for input and output file names,
     * creates heaps, up-trees, and linked lists to implement Kruskal's
     * algorithm for MSTs
     * @param args command line arguments
     */
    public static void main(String args[]) {
        Scanner scan = new Scanner(System.in);
        System.out.print("Input filename: ");
        String inputFile = scan.next();
        System.out.print("Output filename: ");
        String outputFile = scan.next();
        scan.close();
        
        File input =  new File(inputFile);
        Scanner sc = null;
        try {
            sc = new Scanner(input);
        } catch (FileNotFoundException e) {
            System.out.println("Invalid input file.");
            e.printStackTrace();
        }

        PrintStream output = null;
        try {
            output = new PrintStream(new FileOutputStream(outputFile));
            System.setOut(output);
        } catch (IOException e) {
            System.out.println("Invalid output file.");
            e.printStackTrace();
        }

        EdgeList[] adjList = new EdgeList[1000];
        Heap h = new Heap();
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            Scanner scanner = new Scanner(line);
            int v1 = scanner.nextInt();
            if (v1 == -1) {
                break;
            }
            if (v1 > numVertices) {
                numVertices = v1;
            }
            int v2 = scanner.nextInt();
            if (v2 > numVertices) {
                numVertices = v2;
            }
            double w = scanner.nextDouble();
            Edge one = new Edge(v1, v2, w, null);
            Edge two = new Edge(v2, v1, w, null);
            if (adjList[v1] == null) {
                adjList[v1] = new EdgeList();
            }
            adjList[v1].addEdge(one);
            if (adjList[v2] == null) {
                adjList[v2] = new EdgeList();
            }
            adjList[v2].addEdge(two);
            h.insert(one);
            scanner.close();
        }
        numVertices++;
        sc.close();
        
        h.print();
        EdgeList list = kruskalsAlgorithm(h);
        while (list.size > 0) {
            Edge e = removeLeastEdge(list);
            if (e == null) {
                break;
            }
            if (e.vertex1 <= e.vertex2) {
                System.out.printf("%4d %4d\n", e.vertex1, e.vertex2);
            } else {
                System.out.printf("%4d %4d\n", e.vertex2, e.vertex1);
            }
        }

        for (int i = 0; i < numVertices; i++) {
            while (adjList[i].size > 1) {
                Edge e = removeLeastEdge(adjList[i]);
                System.out.printf("%4d ", e.vertex2);
            }
            Edge e = removeLeastEdge(adjList[i]);
            System.out.printf("%4d\n", e.vertex2);
        }
    }
    /**
     * Adapted directly from pseudocode, except for creating the heap, which I decided to do
     * while reading in input.
     * @param h Heap to construct MST from
     * @return EdgeList representing MST
     */
    public static EdgeList kruskalsAlgorithm(Heap h) {
        EdgeList list = new EdgeList(); //Minimum Spanning Tree structure (Linked List of Edges)

        int components = numVertices;
        
        UpTree tree = new UpTree(components);
        for (int i = 0; i < components; i++) {
            tree.tree[i] = -1;
        }
        
        while (components > 1) {
            Edge e = deleteMin(h);
            int u = tree.find(e.vertex1);
            int v = tree.find(e.vertex2);
            if (u != v) {
                tree.union(u, v);
                list.addEdge(new Edge(e.vertex1, e.vertex2, e.weight, null));
                components--;
            }
        }

        return list;
    }
    /**
     * Given a heap, removes the root node of the heap and reorders
     * structure so heap qualities remain.
     * @param h Heap to delete root node from
     * @return Edge root node of Heap
     */
    public static Edge deleteMin(Heap h) {
        Edge e = h.buffer[0];
        h.size--;
        h.buffer[0] = h.buffer[h.size - 1];
        h.downHeap(0);
        return e;
    }
    
    /**
     * Removes the least-valued edge, considering both vertices.
     * @param list EdgeList to find, remove and return least value from
     * @return Edge least value in EdgeList
     */
    public static Edge removeLeastEdge(EdgeList list) {
        int least = 1001;
        Edge leastEdge = null;
        Edge iter = list.head;
        if (iter == null) {
            return null;
        }
        while (iter != null) {
            if (iter.vertex1 < least || iter.vertex2 < least) {
                leastEdge = iter;
                if (iter.vertex1 <= iter.vertex2) {
                    least = iter.vertex1;
                } else {
                    least = iter.vertex2;
                }
            } else if (iter.vertex1 == least) {
                if (iter.vertex2 < leastEdge.vertex2) {
                    leastEdge = iter;
                }
                if (iter.vertex2 < leastEdge.vertex1) {
                    leastEdge = iter;
                }
            } else if (iter.vertex2 == least) {
                if (iter.vertex1 < leastEdge.vertex1) {
                    leastEdge = iter;
                }
                if (iter.vertex1 < leastEdge.vertex2) {
                    leastEdge = iter;
                }
            }
            iter = iter.next;
        }

        iter = list.head;
        Edge previous = null;
        while (iter != null) {
            if (iter.vertex1 == leastEdge.vertex1 && iter.vertex2 == leastEdge.vertex2) {
                if (previous != null) {
                    previous.next = iter.next;
                } else {
                    list.head = list.head.next;
                }
            }
            previous = iter;
            iter = iter.next;
        }
        list.size--;
        return leastEdge;
    }
    
    /**
     * Linked List of Edges.
     */
    static class EdgeList {
        public Edge head;
        public int size;
        
        /**
         * Constructor, initializes empty list.
         */
        public EdgeList() {
            this.head = null;
        }
        
        /**
         * Returns the size of the EdgeList
         * @return size of EdgeList
         */
        public int size() {
            int size = 0;
            Edge e = head;
            while (e != null) {
                size++;
                e = e.next;
            }
            return size;
        }
        
        /**
         * Adds an Edge to the EdgeList
         * @param e Edge to add to the EdgeList
         */
        public void addEdge(Edge e) {
            Edge iter = this.head;
            if (iter == null) {
                this.head = e;
                size++;
                return;
            }
            while (iter.next != null) {
                iter = iter.next;
            }
            iter.next = e;
            size++;
        }
    }
    
    /**
     * Edge structure, constructs an Edge with given information.
     */
    static class Edge {
        public int vertex1;
        public int vertex2;
        public double weight;
        public Edge next;
        
        /** 
         * Edge constructor, takes four parameters.
         * @param v1 vertex 1 in the Edge
         * @param v2 vertex 2 in the Edge
         * @param weight weight of Edge
         * @param next allows for Linked structure of Edges
         */
        
        public Edge(int v1, int v2, double weight, Edge next) {
            this.vertex1 = v1;
            this.vertex2 = v2;
            this.weight = weight;
            this.next = next;
        }
    }
    
    /**
     * Heap structure, helps with implementing Kruskal's algorithm.
     */
    static class Heap {
        public Edge[] buffer;
        public int size;
        
        /**
         * Heap constructor, initializes empty heap.
         */
        public Heap() {
            this.buffer = new Edge[5000];
            this.size = 0;
        }
        
        /**
         * Reorganizes Heap to maintain heap qualities.
         * @param i index of Edge
         */
        public void upHeap(int i) {
            if (i > 0) {
                if (this.buffer[(i - 1) / 2].weight > this.buffer[i].weight) {
                    Edge temp = this.buffer[(i - 1) / 2];
                    this.buffer[(i - 1) / 2] = this.buffer[i];
                    this.buffer[i] = temp;
                    upHeap((i - 1) / 2);
                }
            }
        }
        
        /**
         * Reorganizes Heap to maintain heal qualities.
         * @param m index of Edge
         */
        public void downHeap(int m) {
            int i = 0;
            if (((2 * m) + 2) < this.size) {
                if (this.buffer[((2 * m) + 2)].weight < this.buffer[((2 * m) + 1)].weight) {
                    i = (2 * m) + 2;
                } else {
                    i = (2 * m) + 1;
                }
            } else if (((2 * m) + 2) < this.size) {
                i = (2 * m) + 1;
            }
            if (i > 0 && this.buffer[m].weight > this.buffer[i].weight) {
                Edge temp = this.buffer[i];
                this.buffer[i] = this.buffer[m];
                this.buffer[m] = temp;
                downHeap(i);
            }
        }
        
        /**
         * Inserts an Edge into the Heap
         * @param e Edge to insert
         */
        public void insert(Edge e) {
            this.buffer[size] = e;
            this.size++;
            upHeap(size - 1);
        }
        
        /**
         * Prints Heap in level order.
         */
        public void print() {
            for (int i = 0; i < this.size; i++) {
                int u = this.buffer[i].vertex1;
                int v = this.buffer[i].vertex2;
                
                if (u >= v) {
                    System.out.printf("%4d %4d\n", v, u);
                } else {
                    System.out.printf("%4d %4d\n", u, v);
                }
            }
        }
    }
    
    /**
     * Up-Tree structure to help implement Kruskal's algorithm.
     */
    static class UpTree {
        public int[] tree;
        
        /**
         * UpTree constructor, initializes empty UpTree.
         * @param numNodes initializes array to store up to
         * numNodes integers
         */
        public UpTree(int numNodes) {
            this.tree = new int[numNodes];
        }
        
        /**
         * Finds the root of the subtree of the given item.
         * @param item to find root of
         * @return returns item's root
         */
        public int find(int item) {
            while (this.tree[item] >= 0) {
                item = tree[item];
            }
            return item;
        }
        
        /**
         * Performs a union of 2 nodes, resulting in a union of
         * 2 sets.
         * @param s root of set to perform union on
         * @param t root of set to perform union on
         * @return Returns root of new set
         */
        public int union(int s, int t) {
            if ((tree[s] * -1) >= tree[t] * -1) {
                tree[s] = tree[s] + tree[t];
                tree[t] = s;
                return s;
            } else {
                tree[t] = tree[s] + tree[t];
                tree[s] = t;
                return t;
            }
        }
    }
}
