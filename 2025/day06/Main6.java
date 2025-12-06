import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

// I LOVE ADVENT OF PARSING
// I LOVE ADVENT OF PARSING
// I LOVE ADVENT OF PARSING
// I LOVE ADVENT OF PARSING
// I LOVE ADVENT OF PARSING
// I LOVE ADVENT OF PARSING
// I LOVE ADVENT OF PARSING
// I LOVE ADVENT OF PARSING
// I LOVE ADVENT OF PARSING
// I LOVE ADVENT OF PARSING

public class Main6 {
    private static ArrayList<ArrayList<String>> PARSEINPUTFROMHELL(String filename) {
        File f = new File(filename);

        // get lenghts of operators
        ArrayList<Integer> oplen = new ArrayList<>();
        try (Scanner scan = new Scanner(f)) {
            Pattern HEHAUNTSME = Pattern.compile("([+*])\\s+");
            while (scan.hasNextLine()) {
                String data = scan.nextLine();
                if (!scan.hasNextLine()) {
                    Matcher RELEASEME = HEHAUNTSME.matcher(data);
                    while(RELEASEME.find()) {
                        oplen.add(RELEASEME.group().length());
                    }
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println("ERROR ON OPERATOR SCAN");
            e.printStackTrace();
        }

        // now get the real data, without having to align anything
        ArrayList<ArrayList<String>> result = new ArrayList<>(); // this isnt what gets returned by the way.
        try (Scanner scan = new Scanner(f)) {
            while (scan.hasNextLine()) {
                int offset = 0;
                int oplenIterator = 0;
                ArrayList<String> whatever = new ArrayList<>();

                String data = scan.nextLine();

                while (offset < data.length()) {
                    int newlen = oplen.get(oplenIterator);
                    String sub = data.substring(offset, offset+newlen);
                    oplenIterator++;
                    offset += newlen;
                    whatever.add(sub);
                }

                result.add(whatever);
            }
        } catch (FileNotFoundException e) {
            System.out.println("ERROR ON DATA READ");
            e.printStackTrace();
        }

        // nuke delimiters. nuking only for all but the last subarray.
        for(int i = 0; i < result.size(); i++) {
            for(int j = 0; j < result.getFirst().size()-1; j++) {
                result.get(i).set(j, result.get(i).get(j).substring(0, result.get(i).get(j).length()-1));
            }
        }

        // make it so that each sublist is the column, not the row
        // this isnt really necessary, but its sane.
        ArrayList<ArrayList<String>> columns = new ArrayList<>();
        for(int i = 0; i < result.getFirst().size(); i++) {
            ArrayList<String> bawooga = new ArrayList<>();

            for(int j = 0; j < result.size(); j++) {
                bawooga.add(result.get(j).get(i));
            }

            columns.add(bawooga);
        }

        return columns;
    }

    private static long solve1(ArrayList<ArrayList<String>> data) {
        long result = 0;

        for(int i = 0; i < data.size(); i++) {
            ArrayList<Integer> numbers = new ArrayList<>();

            for(int j = 0; j < data.get(i).size()-1; j++) {
                numbers.add(Integer.parseInt(data.get(i).get(j).strip()));
            }

            String operator = data.get(i).getLast().strip();
            switch(operator) {
                case "+" -> {
                    long sum = 0;
                    for (Integer number : numbers)
                        sum += number;
                    result += sum;
                }
                case "*" -> {
                    long sum = 1;
                    for (Integer number : numbers)
                        sum *= number;
                    result += sum;
                }
            }
        }
        return result;
    }

    private static long powof10(int n) {
        if(n == 0)
            return 1;

        long ret = 10;
        for(int i = 1; i < n; i++) {
            ret *= 10;
        }

        return ret;
    }

    private static long solve2(ArrayList<ArrayList<String>> data) {
        long result = 0;
        final int numbersInColumn = data.getFirst().size()-1;

        for(int i = data.size()-1; i >=0; i--) {
            // g  t  c  n
            // e  h  e  u
            // t  e  p  m
            //       h  b
            //       a  e
            //       l  r
            //       o  s
            //       d
            final int digits = data.get(i).getLast().length();
            ArrayList<Integer> cephalopodMath = new ArrayList<>();
            for(int j = 0; j < digits; j++) {
                int number = 0;
                int power = 0;
                for(int k = numbersInColumn; k > 0; k--) {
                    char c = data.get(i).get(k-1).charAt(j);
                    if(c == ' ') {
                        continue;
                    }
                    number += (int) (Integer.parseInt(String.valueOf(c)) * powof10(power));
                    power++;
                }
                cephalopodMath.add(number);
            }

            // do the math
            String operator = data.get(i).getLast().strip();
            switch(operator) {
                case "+" -> {
                    long sum = 0;
                    for(int number : cephalopodMath) {
                        sum += number;
                    }
                    result += sum;
                }
                case "*" -> {
                    long sum = 1;
                    for(int number : cephalopodMath) {
                        sum *= number;
                    }
                    result += sum;
                }
            }
        }
        // cry.
        return result;
    }

    public static void main(String[] args) {
        final String filename = "in.txt";
        ArrayList<ArrayList<String>> data = PARSEINPUTFROMHELL(filename); // im so fed up with you...
        System.out.println("silver: " + solve1(data));
        System.out.println("gold: " + solve2(data));
    }
}
