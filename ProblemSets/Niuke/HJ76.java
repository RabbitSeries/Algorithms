package Niuke;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

public class HJ76 {
    long generateSum(long start, long n) {
        long sum = 0;
        for (long i = 0; i < n; i++) {
            sum += (start + 2 * i);
        }
        return sum;
    }

    long powl(long n, int times) {
        return times == 0 ? 1 : n * powl(n, times - 1);
    }

    void Solution1() throws IOException {
        long num = 0;
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        num = Long.parseLong(input.readLine().trim());
        long target = powl(num, 3);
        long left = 1, right = target;
        while (left <= right) {
            long mid = left + (right - left) / 2;
            long sum = generateSum(mid, num);
            if (sum > target) {
                right = mid - 1;
            } else if (sum < target) {
                left = mid + 1;
            } else {
                List<Long> res = new ArrayList<>();
                for (int i = 0; i < num; i++) {
                    res.add(mid + 2 * i);
                }
                System.out.println(res.stream().map(l -> l.toString()).collect(Collectors.joining("+")));
                break;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        HJ76 Solution = new HJ76();
        Solution.Solution1();
    }
}
