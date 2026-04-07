class Robot {
    private List<int[]> border;
    private List<String> dirAt;
    private int perim;
    private int idx;
    private long totalSteps; // total steps ever taken (before modulo)

    public Robot(int width, int height) {
        border = new ArrayList<>();
        dirAt = new ArrayList<>();

        // 1) Bottom edge: (0,0) -> (width-1,0), facing East
        for (int x = 0; x < width; x++) {
            border.add(new int[]{x, 0});
            dirAt.add("East");
        }

        // 2) Right edge: (width-1,1) -> (width-1,height-1), facing North
        for (int y = 1; y < height; y++) {
            border.add(new int[]{width - 1, y});
            dirAt.add("North");
        }

        // 3) Top edge: (width-2,height-1) -> (0,height-1), facing West
        for (int x = width - 2; x >= 0; x--) {
            border.add(new int[]{x, height - 1});
            dirAt.add("West");
        }

        // 4) Left edge: (0,height-2) -> (0,1), facing South
        for (int y = height - 2; y >= 1; y--) {
            border.add(new int[]{0, y});
            dirAt.add("South");
        }

        perim = border.size();
        idx = 0;
        totalSteps = 0;
    }

    public void step(int num) {
        totalSteps += num;          // record real steps (may exceed perim)
        num %= perim;               // move along cycle
        if (num == 0) return;
        idx = (idx + num) % perim;
    }

    public int[] getPos() {
        return border.get(idx);
    }

    public String getDir() {
        int[] pos = border.get(idx);

        // If we have walked at least one full lap and are at (0,0) -> South
        if (totalSteps > 0 && totalSteps % perim == 0 && pos[0] == 0 && pos[1] == 0) {
            return "South";
        }

        return dirAt.get(idx);
    }
}