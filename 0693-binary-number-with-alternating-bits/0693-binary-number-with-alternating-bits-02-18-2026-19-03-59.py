class Solution:
    def hasAlternatingBits(self, n: int) -> bool:
        n ^= (n >> 1)
        return (n & (n + 1)) == 0

# Test
sol = Solution()
print(sol.hasAlternatingBits(5))  # True
print(sol.hasAlternatingBits(7))  # False
print(sol.hasAlternatingBits(11)) # False
