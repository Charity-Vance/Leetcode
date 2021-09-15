import java.util.HashMap;
import java.util.Map;

class Solution {
    public int numberOfBoomerangs(int[][] points) {
        int ans = 0, n = points.length;
        for(int i=0;i<n;i++){
            Map<Integer,Integer> cnts = new HashMap<>();
            for(int j=0;j<n;j++){
                int d = distance(points[i][0], points[j][0], points[i][1],points[j][1]);
                int v = cnts.getOrDefault(d, 0);
                cnts.put(d, v+1);
            }
            for(int val: cnts.values())
                ans += val * (val - 1);
        }
        return ans;
    }

    public int distance(int x1, int x2, int y1, int y2){
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    }
}
