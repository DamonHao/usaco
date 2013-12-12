/*
This is a pretty straight-forward dynamic programming problem. The factors that determine whether we can put a song on a CD are:

The length used up on the CD so far
The length of the current song
The last song that we put on the CD (because of the date restriction)
Therefore, we create an matrix called "dp", with dp[a][b][c] being the most number of songs that we can put on the first 'a' CDs, with 'b' minutes already used up on the 'a'th CD, and with 'c' being the last song that we put on CD 'a'. We initialize the matrix to be all zeroes, and then we cycle through it as follows:

We traverse the CDs in ascending order to satisfy the date requirement
We go through the number of minutes used in ascending order, so that we have had a chance to put on a song earlier in the CD before we try to put songs on at a later time
We go through the last song used in ascending order (although this order doesn't really matter)
We go through the new songs in ascending order, making sure to start with songs that were dated after the last song
If the new song that we want to include in the set will fit on the current CD, there is no reason to put it on the next CD, so we check the matrix and see if adding it to the current set of songs will be better than the value already stored in the matrix. Otherwise, we check to see if it would be beneficial to put the song on the next CD. As a time-saver, each time we check a current value in the matrix to see what other songs we can put on the CD, we also check and see if this value is better than the most number of CDs that we have currently been able to fit in the set, so that we don't need to do this at the end. Finally, we output this best number, which will be the most number of CDs that we can fit in the set.
*/
/*
A very strange dp,it is straight-forward,its state transition equation:
If add in current cd: dp[a][b][c] = max{dp[a][b-len[c]][k]}+1; k < c,that is the song before c th song; ;
If add in new cd: dp[a][len[c]][c] = max{dp[a-1][n][k]}+1; n is [1,cd_lenght], k < c;
*/
#include <stdio.h>
#define MAX 25
int dp[MAX][MAX][MAX], length[MAX];

int main (){
    FILE   *in = fopen ("rockers.in", "r");
    FILE   *out = fopen ("rockers.out", "w");
    int     a, b, c, d, best, numsongs, cdlength, numcds;
    fscanf (in, "%d%d%d", &numsongs, &cdlength, &numcds);
    for (a = 1; a <= numsongs; a++)
        fscanf (in, "%d", &length[a]);
    best = 0;
    for (a = 0; a < numcds; a++)/* current cd */
        for (b = 0; b <= cdlength; b++) /* number of minutes used */
            for (c = 0; c <= numsongs; c++) {   /* last song */
                for (d = c + 1; d <= numsongs; d++) {   /* new song */
                    if (b + length[d] <= cdlength) {
                        if (dp[a][b][c] + 1 > dp[a][b + length[d]][d]) //check whether add song d;
                            dp[a][b + length[d]][d] = dp[a][b][c] + 1;
                    }
                    else {
                        if (dp[a][b][c] + 1 > dp[a + 1][length[d]][d])//check whether add song d in new cd;
                            dp[a + 1][length[d]][d] = dp[a][b][c] + 1;
                    }
                }
                if (dp[a][b][c] > best)
                    best = dp[a][b][c];
            }
    fprintf (out, "%d\n", best);
    return 0;
}
