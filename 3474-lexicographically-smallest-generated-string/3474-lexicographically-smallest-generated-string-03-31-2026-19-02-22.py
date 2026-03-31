class Solution(object):
    def generateString(self, str1, str2):
        n, m = len(str1), len(str2)
        L = n + m - 1

        word = ['?'] * L
        forced = ['#'] * L   # char forced by some T, or '#'

        # 1) Apply all T-constraints
        for i in range(n):
            if str1[i] == 'T':
                for k in range(m):
                    p = i + k
                    need = str2[k]
                    if forced[p] == '#':
                        forced[p] = need
                        word[p] = need
                    elif forced[p] != need:
                        return ""

        # 2) Fill remaining '?' with 'a'
        for p in range(L):
            if word[p] == '?':
                word[p] = 'a'

        # 3) Fix all F-constraints
        for i in range(n):
            if str1[i] == 'F':
                s = i
                e = i + m - 1

                # already has mismatch?
                has_mismatch = False
                for j in range(s, e + 1):
                    pc = str2[j - i]
                    if word[j] != pc:
                        has_mismatch = True
                        break
                if has_mismatch:
                    continue

                # need to break this window
                fixed = False
                for j in range(e, s - 1, -1):
                    if forced[j] != '#':
                        continue
                    pc = str2[j - i]
                    for code in range(ord('a'), ord('z') + 1):
                        c = chr(code)
                        if c != pc:
                            word[j] = c
                            fixed = True
                            break
                    if fixed:
                        break

                if not fixed:
                    return ""

        return "".join(word)
