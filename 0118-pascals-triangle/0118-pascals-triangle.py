from typing import List

class Solution:
    def generate(self, numRows: int) -> List[List[int]]:
        # First row
        triangle = [[1]]
        
        # Generate remaining rows
        for i in range(1, numRows):
            prev = triangle[i - 1]
            row = [1]  # first element
            
            # inner elements
            for j in range(1, i):
                row.append(prev[j - 1] + prev[j])
            
            row.append(1)  # last element
            triangle.append(row)
        
        return triangle
