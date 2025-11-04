#include <stdio.h>
#include <string.h>
#include <math.h>

#define d 256             // Number of possible characters (ASCII)
#define q 101             // A prime number (modulus for hashing)

// Rabin–Karp string search function
void rabinKarp(char text[], char pattern[]) {
    int n = strlen(text);       // Length of text
    int m = strlen(pattern);    // Length of pattern
    int i, j;
    int p = 0;  // Hash value for pattern
    int t = 0;  // Hash value for current window of text
    int h = 1;

    // h = pow(d, m-1) % q  → used to remove the leading character
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Calculate initial hash for pattern and first window of text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= n - m; i++) {
        // If the hash values match, check the actual characters
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            if (j == m)
                printf("Pattern found at index %d\n", i);
        }

        // Compute hash for next window:
        // Remove leading char, add trailing char
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            // Make sure hash is positive
            if (t < 0)
                t = (t + q);
        }
    }
}

int main() {
    char text[] = "abedabcabcababc";
    char pattern[] = "abc";

    rabinKarp(text, pattern);

    return 0;
}
