#include <iostream>
#include <iomanip>
using namespace std;

// 定义 HMM 参数
const int num_states = 3;       // 状态数量
const int num_observations = 7; // 观测数量

double initial_prob[] = {0.2, 0.2, 0.6};                                                                                                                    // 初始状态概率
double transition_prob[][num_states] = {{0.3, 0.3, 0.4}, {0.2, 0.5, 0.3}, {0.2, 0.2, 0.6}};                                                                 // 状态转移概率
double emission_prob[][num_observations] = {{0.1, 0.7, 0.1, 0.0, 0.1, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.2, 0.0, 0.7, 0.1}, {0.2, 0.2, 0.1, 0.1, 0.1, 0.1, 0.2}}; // 观测概率

// 定义观测序列
int observations[] = {3, 5, 6, 4}; // 观测序列 You hate green bananas

// 函数：计算前向算法得到的联合概率
double forwardAlgorithm()
{
    int T = num_observations;

    // 初始化前向概率矩阵
    double alpha[T + 1][num_states];

    // 初始化步骤
    for (int j = 0; j < num_states; ++j)
    {
        alpha[1][j] = initial_prob[j] * emission_prob[j][observations[0]];
    }

    // 递推步骤
    for (int t = 2; t <= T; ++t)
    {
        for (int j = 0; j < num_states; ++j)
        {
            double sum = 0.0;
            for (int i = 0; i < num_states; ++i)
            {
                sum += alpha[t - 1][i] * transition_prob[i][j];
            }
            alpha[t][j] = sum * emission_prob[j][observations[t - 1]];
        }
    }

    // 终止步骤
    double joint_probability = 0.0;
    for (int i = 0; i < num_states; ++i)
    {
        joint_probability += alpha[T][i];
    }

    return joint_probability;
}

int main()
{

    // 使用前向算法计算联合概率
    double result = forwardAlgorithm();

    // 打印结果
    cout << fixed << setprecision(10) << result << endl;

    return 0;
}