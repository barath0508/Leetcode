class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions,
                                      vector<int>& healths,
                                      string directions) {
        int n = positions.size();
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);

        // Sort robots by position
        sort(idx.begin(), idx.end(),
             [&](int a, int b) { return positions[a] < positions[b]; });

        vector<int> st;  // stack of indices (original indices)

        for (int k = 0; k < n; ++k) {
            int i = idx[k];

            // Only 'L' can collide with previous 'R' robots
            if (directions[i] == 'L') {
                // While there is a possible 'R' robot to collide with
                while (!st.empty() && directions[st.back()] == 'R' && healths[i] > 0) {
                    int j = st.back();  // last 'R' robot

                    if (healths[j] == healths[i]) {
                        // Both destroyed
                        healths[j] = -1;
                        healths[i] = -1;
                        st.pop_back();
                        break;
                    } else if (healths[j] < healths[i]) {
                        // Right robot dies, left loses 1, continue checking previous 'R'
                        healths[j] = -1;
                        st.pop_back();
                        healths[i]--;
                    } else {
                        // Left robot dies, right loses 1
                        healths[i] = -1;
                        healths[j]--;
                        break;
                    }
                }

                // If still alive and no more collisions, push this 'L' robot
                if (healths[i] > 0) {
                    st.push_back(i);
                }
            } else {
                // 'R' robot, just push to stack
                st.push_back(i);
            }
        }

        // Collect surviving healths in original order
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (healths[i] > 0) ans.push_back(healths[i]);
        }
        return ans;
    }
};