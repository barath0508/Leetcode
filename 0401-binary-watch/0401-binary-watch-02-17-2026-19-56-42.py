from typing import List

class Solution:
    def readBinaryWatch(self, turnedOn: int) -> List[str]:
        ans = []
        for h in range(12):          # hours: 0–11
            for m in range(60):      # minutes: 0–59
                if (bin(h).count('1') + bin(m).count('1')) == turnedOn:
                    time_str = f"{h}:{m:02d}"  # minute always 2 digits
                    ans.append(time_str)
        return ans
