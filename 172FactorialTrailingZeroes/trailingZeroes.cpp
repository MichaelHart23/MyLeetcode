
/**
 * 20260904:
 * 我依旧不能给出一个完美的数学证明, 不过依据我的观察, 一个数能分解出几个5相乘, 就能提供几个零
 * 其余的数则不能提供0
 * 
 * 不得不说, 我的洞察还是比较敏锐的
 * 尾0的数量取决于 10, 而10的质因数是 2 和 5
 * 所以就看最终的数字能分解出几个 2, 几个 5, 而 2 的数量远多于 5, 所以最终答案取决于5 
 */
class Solution {
public:
    int trailingZeroes(int n) {
        int res = 0;
        for (int i = 5; i <= n; i += 5) {
            int num = i;
            while (num % 5 == 0) {
                res++;
                num /= 5;
            }
        }
        return res;
    }
};