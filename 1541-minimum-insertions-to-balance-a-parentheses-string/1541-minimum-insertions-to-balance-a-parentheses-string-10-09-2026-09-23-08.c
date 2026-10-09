int minInsertions(char* s) {
    int n = strlen(s);
    int i = 0;
    int open_needed = 0;   // how many ')' we still need (each '(' needs 2)
    int insertions = 0;

    while (i < n) {
        if (s[i] == '(') {
            open_needed += 2;
        } else { // s[i] == ')'
            // Check for "))"
            if (i + 1 < n && s[i + 1] == ')') {
                i++; // consume both
            } else {
                // single ')', need one more ')'
                insertions++;
            }

            if (open_needed == 0) {
                // no '(' to match, insert '('
                insertions++;
            } else {
                open_needed -= 2;
            }
        }
        i++;
    }

    insertions += open_needed; // remaining needed ')'
    return insertions;
}