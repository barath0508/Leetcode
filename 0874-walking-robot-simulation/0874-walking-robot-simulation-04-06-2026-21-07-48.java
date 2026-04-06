class Solution {
    public int robotSim(int[] commands, int[][] obstacles) {
        // 1) Put all obstacles into a hash set for O(1) lookup
        // Encode each (x, y) as "x#y"
        HashSet<String> blocked = new HashSet<>();
        for (int[] ob : obstacles) {
            blocked.add(ob[0] + "#" + ob[1]);
        }

        // 2) Direction vectors: 0=N,1=E,2=S,3=W
        int[][] dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        int dir = 0;          // start facing north
        int x = 0, y = 0;     // start at origin
        int maxDist2 = 0;     // maximum squared distance

        // 3) Process each command
        for (int cmd : commands) {
            if (cmd == -1) {
                // turn right: +1 (mod 4)
                dir = (dir + 1) % 4;
            } else if (cmd == -2) {
                // turn left: -1 (mod 4) → +3 (mod 4)
                dir = (dir + 3) % 4;
            } else {
                // move forward cmd steps, but one step at a time
                int dx = dirs[dir][0];
                int dy = dirs[dir][1];

                for (int step = 0; step < cmd; step++) {
                    int nx = x + dx;
                    int ny = y + dy;

                    // check if next cell is an obstacle
                    if (blocked.contains(nx + "#" + ny)) {
                        // stop moving for this command
                        break;
                    }

                    // otherwise move into the cell
                    x = nx;
                    y = ny;

                    // update max distance squared
                    int dist2 = x * x + y * y;
                    if (dist2 > maxDist2) {
                        maxDist2 = dist2;
                    }
                }
            }
        }
        return maxDist2;
    }
}