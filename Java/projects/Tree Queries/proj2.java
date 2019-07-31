import java.io.*;
import java.util.*;
/**
 * @filename proj2.java
 * 
 * Recursively builds a Tree given a pre-order and a post-order traversal,
 * answers queries about relationships between Nodes in the Tree, and prints
 * a level-order representation of the tree.
 * 
 * @author Cole Southern
 */
public class proj2 {
    /** Buffer to store pre-order representation of tree. */
    static char[] pretrav = new char[256];
    /** Buffer to store post-order representation of tree. */
    static char[] posttrav = new char[256];
    
    /**
     * Program starting point, takes input of pre and post-order traversal
     * of tree and builds tree, then answers queries, and prints a level-order
     * traversal of tree.
     * @param args Command line arguments
     */
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.print("Enter input file:\n");
        String inputFile = scan.next();
        System.out.print("Enter output file:\n");
        String outputFile = scan.next();
        scan.close();
        
        File input = new File(inputFile);
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
        
        Tree tree = null;
        int size = 0;
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            Scanner scanner = new Scanner(line);
            String first = "";
            size = 0;
            if (scanner.hasNext()) {
                first = scanner.next();
            }
            if (first.equals("<")) {
                int count = 0;
                scanner.useDelimiter(",");
                while (scanner.hasNext()) {
                    pretrav[count] = scanner.next().trim().charAt(0);
                    count++;
                    size++;
                }
            } else if (first.equals(">")) {
                int count = 0;
                scanner.useDelimiter(",");
                while (scanner.hasNext()) {
                    posttrav[count] = scanner.next().trim().charAt(0);
                    count++;
                    size++;
                }
                tree = new Tree();
                tree.setRoot(buildTree(size, 0, 0));
            } else if (first.equals("?")) {
                scanner.useDelimiter(",");
                char arg1 = scanner.next().trim().charAt(0);
                char arg2 = scanner.next().trim().charAt(0);
                Node a = tree.findNode(arg1);
                Node b = tree.findNode(arg2);
                System.out.print(findRelation(a, b));
            }
            scanner.close();
        }
        sc.close();
        System.out.print(levelOrderPrint(tree));
    }

    /**
     * Finds the relationship between two given nodes and prints the
     * relationship.
     * @param a first Node to be analyzed
     * @param b second Node to be analyzed
     */
    private static String findRelation(Node a, Node b) {
        String ret = "";
        a.mark = true;
        Node iterate = a;
        while (iterate.parent != null) {
            iterate.parent.mark = true;
            iterate = iterate.parent;
        }
        iterate = b;
        int bcount = 0;
        while (iterate != null && iterate.mark == false) {
            iterate = iterate.parent;
            bcount++;
        }
        if (iterate != null && iterate.mark == true) {
            iterate.supermark = true;
        }
        int acount = 0;
        iterate = a;
        while (iterate != null && iterate.supermark == false) {
            iterate = iterate.parent;
            acount++;
        }

        if (acount == 0 && bcount == 0) {
            ret = a.value + " is " + b.value + ".";
        } else if (acount == 0 && bcount == 1) {
            ret = a.value + " is " + b.value + "'s parent.";
        } else if (acount == 0 && bcount == 2) {
            ret = a.value + " is " + b.value + "'s grandparent.";
        } else if (acount == 0 && bcount == 3) {
            ret = a.value + " is " + b.value + "'s great-grandparent.";
        } else if (acount == 0 && bcount > 3) {
            ret = a.value + " is " + b.value + "'s (great)^k-2-grandparent.";
        } else if (acount == 1 && bcount == 0) {
            ret = a.value + " is " + b.value + "'s child.";
        } else if (acount == 2 && bcount == 0) {
            ret = a.value + " is " + b.value + "'s grandchild.";
        } else if (acount >= 3 && bcount == 0) {
            ret = a.value + " is " + b.value + "'s (great)^k-2-grandchild.";
        } else if (acount == 1 && bcount == 1) {
            ret = a.value + " is " + b.value + "'s sibling.";
        } else if (acount == 1 && bcount == 2) {
            ret = a.value + " is " + b.value + "'s aunt/uncle";
        } else if (acount == 1 && bcount >= 2) {
            ret = a.value + " is " + b.value + "'s (great)^k-2-aunt/uncle.";
        } else if (acount == 2 && bcount == 1) {
            ret = a.value + " is " + b.value + "'s niece/nephew.";
        } else if (acount >= 2 && bcount == 1) {
            ret = a.value + " is " + b.value + "'s (great)^k-2-niece/nephew.";
        } else if (acount >= 2 && bcount >= 2) {
            ret = a.value + " is " + b.value + "'s " + (Math.min(acount, bcount) - 1) + "th cousin " + (bcount - acount) + " times removed.";
        }
        
        ret += "\n";
        iterate = a;
        while (iterate != null) {
            iterate.mark = false;
            iterate.supermark = false;
            iterate = iterate.parent;
        }
        return ret;
    }

    /**
     * Builds a Tree recursively using the global arrays of pre and post order
     * traversals.
     * @param size Size of current subtree
     * @param prestart Buffer location for start of pre-traversal representation
     * @param poststart Buffer location for start of post-order traversal representation
     * @return Node that is root of subtree
     */
    public static Node buildTree(int size, int prestart, int poststart) {
        if (size == 1) {
            Node p = new Node(pretrav[prestart]);
            return p;
        } else {
            Node node = new Node(pretrav[prestart]);
            int pretemp = prestart + 1;
            int posttemp = poststart;
            int sizetemp = size - 1;
            int count = 0;
            int counter = 0;
            while (counter < sizetemp) {
                count++;
                if (pretrav[pretemp] == posttrav[posttemp]) {
                    ListNode newNode = new ListNode(buildTree(count, pretemp, poststart));
                    newNode.value.parent = node;
                    ListNode iterate = node.children.head;
                    if (iterate == null) {
                        node.children.head = newNode;
                    } else {
                        while (iterate.next != null) {
                            iterate = iterate.next;
                        }
                        iterate.next = newNode;
                    }
                    poststart = posttemp + 1;
                    pretemp += count;
                    prestart += count;
                    count = 0;
                }
                posttemp++;
                counter++;
            }
            return node;
        }
    }
    
    /**
     * Prints the level-order traversal representation of the given tree.
     * @param t Tree to be printed
     */
    public static String levelOrderPrint(Tree t) {
        String ret = "";
        Queue<Node> q = new LinkedList<Node>();
        if (t == null) {
            return ret;
        }
        q.add(t.root);
        while (!q.isEmpty()) {
            Node d = q.remove();
            ret += d.value;
            ListNode iterate = d.children.head;
            while (iterate != null) {
                q.add(iterate.value);
                iterate = iterate.next;
            }
            if (q.isEmpty()) {
                ret += ".\n";
            } else {
                ret += ", ";
            }
        }
        return ret;
    }
    
    /**
     * Tree object, contains a root Node that acts as the root of the
     * tree.
     * @author Cole Southern
     */
    public static class Tree {
        /** Root of Tree. */
        Node root;
        
        /**
         * Tree Constructor
         */
        public Tree() {
            this.root = null;
        }
        
        /**
         * Sets the root of the Tree as the given Node
         * @param root Root of Tree
         */
        public void setRoot(Node root) {
            this.root = root;
        }
        
        /**
         * Finds the Node with the given character as its value.
         * @param c Character of the Node to return
         * @return Node whose value is the character being searched.
         */
        public Node findNode(char c) {
            Node iterate = this.root;
            return find(iterate, c);
        }
        
        /**
         * Recursive implementation of traversing the Tree to find the
         * given Node
         * @param n Node to search
         * @param c Character we are looking for
         * @return Node containing the given character
         */
        public Node find(Node n, char c) {
            if (n.value == c) {
                return n;
            } else {
                ListNode iterate = n.children.head;
                Node p = null;
                while (iterate != null) {
                    p = find(iterate.value, c);
                    if (p != null) {
                        return p;
                    }
                    iterate = iterate.next;
                }
                return p;
            }
        }
    }
    
    /**
     * Node object, represents a Node in a general tree structure with a List as
     * its children.
     * @author Cole Southern
     */
    public static class Node {
        /** Value of the Node */
        char value;
        /** Linked List representing children of Node. */
        List children;
        /** Parent Node of Node. */
        Node parent;
        /** Mark to determine if ancestor of a particular Node. */
        boolean mark;
        /** Mark to determine least common ancestor. */
        boolean supermark;
        
        /**
         * Node Constructor
         * @param val character of Node
         */
        public Node(char val) {
            this.value = val;
            this.children = new List();
            this.parent = null;
            this.mark = false;
            this.supermark = false;
        }
    }
    
    /**
     * List representing the children of a Node.
     * @author Cole Southern
     */
    public static class List {
        /** Head of Linked List representing children of Node. */
        ListNode head;
        
        /**
         * List constructor, sets head to null by default as
         * it is possible for a Node to have no children.
         */
        public List() {
            this.head = null;
        }
    }
    
    /**
     * Node of a List, allows for Linked-list representation 
     * of a Tree Node's children.
     * @author Cole Southern
     */
    public static class ListNode {
        /** Node of Linked ListNode (Node of Tree). */
        Node value;
        /** ListNode next in the List. */
        ListNode next;
        
        /**
         * ListNode constructor
         * @param value The value is the Node of the Tree.
         */
        public ListNode(Node value) {
            this.value = value;
            this.next = null;
        }
    }
}
