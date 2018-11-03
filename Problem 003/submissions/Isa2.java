// Solution to Isa/Hasa (Floyd-Warshall version)

import java.util.*;

public class Isa2 {
  public static Scanner in;
  public static int n, // number of relationships
                    m; // number of queries
  public static int count; // number of distinct names
  public static boolean isa[][], hasa[][]; // the relations
  public static HashMap<String,Integer> names; // for fast lookup of names
  public static String[] nms; //  names in order of appearance
  public static int nmsc, relsc;
  public static String[] rels; // inputs after names have been processed

  public static void main(String[] args) {
    in = new Scanner(System.in);
    n = in.nextInt();
    m = in.nextInt();
    names = new HashMap<String,Integer>();
    nms = new String[500];
    nmsc = 0;
    rels = new String[10000];
    relsc = 0;
    count = 0;

    isa = new boolean[500][500];
    for (int i = 0; i < 500; i++) {
      isa[i] = new boolean[500];
      Arrays.fill(isa[i],false);
      isa[i][i] = true;
    }
    hasa = new boolean[500][500];
    for (int i = 0; i < 500; i++) {
      hasa[i] = new boolean[500];
      Arrays.fill(hasa[i],false);
    }

    for (int i = 0; i < n; i++) {
      String x = in.next();
      String rel = in.next();
      String y = in.next();
      int xk, yk;
      if (names.containsKey(x)) {
        xk = names.get(x);
      }
      else {
        xk = count++;
        names.put(x,xk);
        nms[nmsc++]=x;
 //System.out.println("Adding name " + x + " in position " + xk);
      }
      if (names.containsKey(y)) {
        yk = names.get(y);
      }
      else {
        yk = count++;
        names.put(y,yk);
        nms[nmsc++]=y;
 //System.out.println("Adding name " + y + " in position " + yk);
      }
      rels[relsc++]=""+xk+" "+rel+" "+yk;
      if (rel.equals("is-a")) {
        isa[xk][yk] = true;
      }
      else {
        hasa[xk][yk] = true;
      }
    }

/*
    for (int i = 0; i < n; i++) {
      Scanner in2 = new Scanner(rels.get(i));
      int xk = in2.nextInt();
      String rel = in2.next();
      int yk = in2.nextInt();

      if (rel.equals("is-a")) {
        isa[xk][yk] = true;
//System.out.println("Processing line " + i + ": "+nms[xk]+" isa "+nms[yk]);
      } else if (rel.equals("has-a")) {
        hasa[xk][yk] = true;
//System.out.println("Processing line " + i + ": "+nms[xk]+" hasa "+nms[yk]);
      }
    //  else System.out.println("ERROR IN INPUT");
    }
*/

    closeIsa();
    closeHasa();

    for (int i = 0; i < m; i++) {
      String x = in.next();
      String rel = in.next();
      String y = in.next();
      int xk = -1, yk = -1;
      if (names.containsKey(x)) {
        xk = names.get(x);
      }
      else {
        System.out.println("Error--no such class "+x);
      }
      if (names.containsKey(y)) {
        yk = names.get(y);
      }
      else {
        System.out.println("Error--no such class "+y);
      }
      System.out.print ("Query "+(i+1)+": ");
      if (rel.equals("is-a")) {
        System.out.println(isa[xk][yk]);
      } else {
        System.out.println(hasa[xk][yk]);
      }
    }
  }

  public static void closeIsa() {
    for (int k = 0; k < count; k++) {
      for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
          isa[i][j] = isa[i][j] || (isa[i][k] && isa[k][j]);
        }
      }
    }
  }

  public static void closeHasa() {
    for (int k = 0; k < count; k++) {
      for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
          hasa[i][j] = hasa[i][j] || (hasa[i][k] && hasa[k][j]);
          hasa[i][j] = hasa[i][j] || (isa[i][k] && hasa[k][j]);
          hasa[i][j] = hasa[i][j] || (hasa[i][k] && isa[k][j]);
        }
      }
    }
  }

/* For debugging: */
  public static void displayHasa() {
    System.out.println("Has-A:");
    for (int i = 0; i < count; i++) {
      for (int j = 0; j < count; j++) {
        if (hasa[i][j]) {
          System.out.println(nms[i]+" has-a "+nms[j]);
        }
      }
    }
  }

  public static void displayIsa() {
    System.out.println("Is-A:");
    for (int i = 0; i < count; i++) {
      for (int j = 0; j < count; j++) {
        if (isa[i][j]) {
          System.out.println(nms[i]+" is-a "+nms[j]);
        }
      }
    }
  }
}
