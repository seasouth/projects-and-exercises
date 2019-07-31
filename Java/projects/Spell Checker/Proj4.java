import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Scanner;

/**
 * @file Proj4.java
 *
 * Implements the coalesced chaining with a cellar technique to build a hash table
 * of roughly 25,000 common English words to use as a spell-checker for an input file.
 */
public class Proj4 {
    static int m, words, dictLength, misspelled,
    lookUps, numProbes = 0;
    /** Golden ratio for compression. */
    static double golden = (1 + Math.sqrt(5)) / 2;

    /**
     * Program starting point, prompts the user for dictionary, input, and output file
     * names, constructs a hash table from the dictionary and spell-checks the input
     * file, printing out unrecognized words to the output file, as well as a report
     * of the number of words in the dictionary and input file, the number of misspelled
     * words, and statistics on the average numbers of probes required for spell-checking.
     * @param args Command line arguments
     */
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.print("Enter name of dictionary file: ");
        String dictionaryFile = scan.next();
        System.out.print("Enter name of input file: ");
        String inputFile = scan.next();
        System.out.print("Enter name of output file: ");
        String outputFile = scan.next();
        scan.close();
        
        File dictionary = new File(dictionaryFile);
        Scanner dict = null;
        try {
            dict = new Scanner(dictionary);
        } catch (FileNotFoundException e) {
            System.out.println("Invalid dictionary file.");
            e.printStackTrace();
        }
        
        File input = new File(inputFile);
        Scanner in = null;
        try {
            in = new Scanner(input);
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

        m = 29243;
        int cellarSize = (m * 14) / 100;
        m -= cellarSize;

        HashTable table = new HashTable(m, cellarSize);

        constructHashTable(table, dict);
        dict.close();
        spellCheck(table, in);
        in.close();
        report();
    }
    
    /**
     * Constructs a HashTable object from the given dictionary file.
     * @param table HashTable object representing dictionary
     * @param scan Scanner to scan dictionary file
     */
    public static void constructHashTable(HashTable table, Scanner scan) {
        while (scan.hasNextLine()) {
            String line = scan.nextLine();
            Scanner scanner = new Scanner(line);
            while (scanner.hasNext()) {
                table.insert(scanner.next());
                dictLength++;
            }
            scanner.close();
        }
    }
    
    /**
     * Spell-checks the input file using the HashTable constructed from
     * the dictionary
     * @param table HashTable representing dictionary
     * @param input Scanner to scan input file
     */
    public static void spellCheck(HashTable table, Scanner input) {
        while (input.hasNextLine()) {
            String line = input.nextLine();
            Scanner scan = new Scanner(line);
            while (scan.hasNext()) {
                int returned = 0;
                String word = scan.next();
                if (word.contains("-") && !word.equals("-")) {
                    Scanner wordScanner = new Scanner(word);
                    wordScanner.useDelimiter("-");
                    while (wordScanner.hasNext()) {
                        String splitWord = wordScanner.next();
                        word = word.replaceAll("[^a-zA-Z']", "");
                        splitWord = splitWord.replaceAll("[^a-zA-Z']", "");
                        returned = table.lookUp(splitWord);
                    }
                    wordScanner.close();
                } else {
                    word = word.replaceAll("[^a-zA-Z']", "");
                    returned = table.lookUp(word);
                }
                if (returned == 0 && !word.isEmpty()) {
                    System.out.println(word);
                    misspelled++;
                }
                words++;
            }
            scan.close();
        }
    }
    
    /**
     * Cyclic-shift hash code, adapted from Table 10.1 on p. 414 ed. 6 of Data
     * Structures and Algorithms. Chose 5 as the shift number as it results in
     * the fewest collisions when applied to a list of 230,000 English words.
     * @param input string to hash
     * @return compressed hash code
     */
    public static int hashFunction(String input) {
        int hash = 0;
        for (int i = 0; i < input.length(); i++) {
            hash = (hash << 5) | (hash >>> 27);
            hash += (int) input.charAt(i);
        }
        
        return compress(hash);
    }
    
    /**
     * Compresses the hash value of the String to place as an index into the HashTable.
     * Uses the Golden Ratio method, as this method is great for providing a uniform
     * distribution of hashed values.
     * @param num hash value
     * @return compressed hash value
     */
    public static int compress(int num) {
        return (int) Math.floor(m * ((num * (1 / golden) - Math.floor(num * (1 / golden)))));
    }
    
    /**
     * Reports to the output file the number of words in the dictionary, number of words
     * in the input file, number of misspelled words, and the average number of probes
     * needed per words and per call to lookUp.
     */
    public static void report() {
        System.out.println();
        System.out.println("Number of words in dictionary: " + dictLength);
        System.out.println("Number of words in input file: " + words);
        System.out.println("Number of misspelled words: " + misspelled);
        System.out.println("Total number of probes: " + numProbes);
        double avePerWord = (double) numProbes / (double) words;
        System.out.println("Average number of probes per word: " + avePerWord);
        double avePerLookUp = (double) numProbes / (double) lookUps;
        System.out.println("Average number of probes per lookup: " + avePerLookUp);
    }
    
    /**
     * Class representing the HashTable. Includes an array of Nodes which hold the String
     * and index of the next Node in the chain. Uses coalesced chaining with a cellar.
     * @author Cole Southern
     *
     */
    static class HashTable {
        Node[] table;
        int cellarSize;
        
        /**
         * Constructor for HashTable, takes the size of the table as a whole and the size of
         * the cellar.
         * @param tableSize size of table
         * @param cellarSize size of cellar
         */
        public HashTable(int tableSize, int cellarSize) {
            this.table = new Node[tableSize + cellarSize];
            this.cellarSize = cellarSize;
        }
        
        /**
         * Class representing a Node, which acts as the elements in the array provided by the
         * HashTable. Holds a String and the index of the next Node in the chain. If there is
         * no next Node in the chain, the next value will be -1.
         * @author Cole Southern
         *
         */
        class Node {
            String key;
            int next;
            
            /**
             * Node Constructor, takes in a String as its key and initializes next to -1;
             * @param key
             */
            public Node(String key) {
                this.key = key;
                this.next = -1;
            }
        }
        
        /**
         * Inserts a word into the HashTable.
         * @param word String to be inserted
         */
        public void insert(String word) {
            int hashCode = hashFunction(word);
            if (this.table[hashCode + cellarSize] == null) {
                this.table[hashCode + cellarSize] = new Node(word);
            } else {
                Node iterator = this.table[hashCode + cellarSize];
                while (iterator.next != -1) {
                    iterator = this.table[iterator.next];
                }

                int firstAvailable = 0;
                Node iter = this.table[0];
                while (iter != null) {
                    iter = this.table[++firstAvailable];
                }
                iterator.next = firstAvailable;
                this.table[firstAvailable] = new Node(word);
            }
        }
        
        /**
         * Looks up the String in the HashTable, and counts the number of lookups
         * as well as the number of probes.
         * @param target String to search for
         * @return number of probes after lookup, 0 if not found
         */
        public int lookUp(String target) {
            lookUps++;
            int targetIndex = hashFunction(target);
            Node iterator = this.table[targetIndex + cellarSize];
            while (iterator != null && iterator.next != -1) {
                if (iterator.key.equals(target)) {
                    numProbes++;
                    return numProbes;
                }
                numProbes++;
                iterator = this.table[iterator.next];
            }

            if (iterator != null) {
                numProbes++;
                if (iterator.key.equals(target)) {
                    return numProbes;
                }
            }

            if (!target.isEmpty() && Character.isUpperCase(target.charAt(0))) {
                return lookUp(target.toLowerCase());
            } else if (target.endsWith("'s")) {
                int ret = lookUp(target.substring(0, target.length() - 2));
                if (ret > 0) {
                    return ret;
                }
            } else if (target.endsWith("s")) {
                int ret = lookUp(target.substring(0, target.length() - 1));
                if (ret > 0) {
                    return ret;
                }
                if (target.endsWith("es")) {
                    ret = lookUp(target.substring(0, target.length() - 2));
                    if (ret > 0) {
                        return ret;
                    }
                }
            } else if (target.endsWith("d")) {
                if (target.endsWith("ed")) {
                    int ret = lookUp(target.substring(0, target.length() - 2));
                    if (ret > 0) {
                        return ret;
                    }
                }
                int ret = lookUp(target.substring(0, target.length() - 1));
                if (ret > 0) {
                    return ret;
                }
            } else if (target.endsWith("r")) {
                if (target.endsWith("er")) {
                    int ret = lookUp(target.substring(0, target.length() - 2));
                    if (ret > 0) {
                        return ret;
                    }
                }
                int ret = lookUp(target.substring(0, target.length() - 2));
                if (ret > 0) {
                    return ret;
                }
            } else if (target.endsWith("ing")) {
                int ret = lookUp(target.substring(0, target.length() - 3));
                if (ret > 0) {
                    return ret;
                } else {
                    target = target.substring(0, target.length() - 3);
                    target = target + "e";
                    return lookUp(target);
                }
            } else if (target.endsWith("ly")) {
                int ret = lookUp(target.substring(0, target.length() - 2));
                if (ret > 0) {
                    return ret;
                }
            }
            
            return 0;
        }
    }
}
