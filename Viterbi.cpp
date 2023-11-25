#include <iostream>

using namespace std;

// 定义 HMM 参数
const int num_states = 3;       // 状态数量
const int num_observations = 7; // 观测数量

double initial_prob[] = {0.2, 0.2, 0.6};                                                                                                                    // 初始状态概率
double transition_prob[][num_states] = {{0.3, 0.3, 0.4}, {0.2, 0.5, 0.3}, {0.2, 0.2, 0.6}};                                                                 // 状态转移概率
double emission_prob[][num_observations] = {{0.1, 0.7, 0.1, 0.0, 0.1, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.2, 0.0, 0.7, 0.1}, {0.2, 0.2, 0.1, 0.1, 0.1, 0.1, 0.2}}; // 观测概率

// 定义观测序列
int observations[] = {3, 5, 6, 4}; // 观测序列 You hate green bananas

// Viterbi 算法
void viterbi_algorithm()
{
    int T = sizeof(observations) / sizeof(observations[0]);
    double dp[T][num_states];
    int backpointer[T][num_states];

    // 初始化
    for (int i = 0; i < num_states; ++i)
    {
        dp[0][i] = initial_prob[i] * emission_prob[i][observations[0]];
    }

    // 递推
    for (int t = 1; t < T; ++t)
    {
        for (int j = 0; j < num_states; ++j)
        {
            double max_prob = -1.0;
            int argmax = -1;
            for (int i = 0; i < num_states; ++i)
            {
                double prob = dp[t - 1][i] * transition_prob[i][j] * emission_prob[j][observations[t]];
                if (prob > max_prob)
                {
                    max_prob = prob;
                    argmax = i;
                }
            }
            dp[t][j] = max_prob;
            backpointer[t][j] = argmax;
        }
    }

    // 回溯
    double max_prob = -1.0;
    int argmax = -1;
    for (int i = 0; i < num_states; ++i)
    {
        if (dp[T - 1][i] > max_prob)
        {
            max_prob = dp[T - 1][i];
            argmax = i;
        }
    }

    // 构造最优路径
    int best_path[T];
    best_path[T - 1] = argmax;
    for (int t = T - 2; t >= 0; --t)
    {
        best_path[t] = backpointer[t + 1][best_path[t + 1]];
    }

    // 输出最优状态序列
    cout << "最优状态序列：";
    for (int t = 0; t < T; ++t)
    {
        cout << best_path[t] << " ";
    }
    cout << endl;
}

int main()
{
    viterbi_algorithm();

    return 0;
}
