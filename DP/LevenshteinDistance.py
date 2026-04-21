
def lev(a, b):
    m, n = len(a), len(b)
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    # initialize
    for i in range(1, m + 1):
        dp[i][0] = i
    for j in range(1, n + 1):
        dp[0][j] = j

    # dynamic programming
    # 这个写法才是顺畅的，符合推理的的写法，很多版本都是“错的”，即使可以弯弯绕的证明是对的，但不符合从头
    # 开始一步一步的推理
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if a[i-1] == b[j-1]:
                cost = 0
            else:
                cost = 1
            dp[i][j] = min(dp[i-1][j] + 1,      # 删除
                           dp[i][j-1] + 1,      # 插入
                           dp[i-1][j-1] + cost) # 替换

    return dp[m][n]