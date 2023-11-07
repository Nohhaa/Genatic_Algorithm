#include <iostream>
#include <random>
#include <bits/stdc++.h>
using namespace std;

int Random01()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, 1);
    return distribution(gen);
}
float RandomDecimal()
{

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    float randomFloat = dist(rng);
    return randomFloat;
}
vector<int> Init_Chromosome(int length)
{
    vector<int> Chromosome;
    for (int i = 0; i < length; ++i)
    {
        int RandomNumber = Random01();
        Chromosome[i] = RandomNumber;
    }
    return Chromosome;
}
void Get_Fitness(vector<vector<int>> &Chromosomes, vector<int> &Weight, vector<int> &Value, int size, vector<pair<int, int>> Fitness, int num)
{
    int TotalFitness = 0, Totalweight = 0;
    for (int j = 0; j < 6; j++)
    {
        for (int i = 0; i < num; ++i)
        {
            if (Chromosomes[j][i] == 1)
            {
                TotalFitness += Value[i];
                Totalweight += Weight[i];
            }
        }
        while (Totalweight > size)
        {
            for (int i = 0; i < num; ++i)
            {
                if (Chromosomes[j][i] == 1)
                {
                    TotalFitness -= Value[i];
                    Totalweight -= Weight[i];
                }
            }
        }
        Fitness.push_back({TotalFitness, j});
        TotalFitness = 0;
        Totalweight = 0;
    }
}
vector<int> Selection(vector<pair<int, int>> &Fitness, int NumberOfChromosomes)
{
    vector<int> Selected;
    sort(Fitness.begin(), Fitness.end());
    vector<float> Normalization(NumberOfChromosomes);
    vector<float> CumulativeSum(NumberOfChromosomes);
    float Sum = NumberOfChromosomes * (NumberOfChromosomes + 1) / 2 * 1.0;
    for (int i = 0; i < NumberOfChromosomes; i++)
    {
        Normalization[Fitness[i].second] = (i + 1) * 1.0 / Sum * 1.0;
    }
    CumulativeSum[0] = Normalization[0];
    for (int i = 1; i < NumberOfChromosomes; i++)
    {
        CumulativeSum[i] = Normalization[i] + CumulativeSum[i - 1];
    }
    for (int i = 0; i < 4; i++)
    {
        float RandomNum = RandomDecimal();
        for (int i = 0; i < CumulativeSum.size(); i++)
        {
            if (RandomNum < CumulativeSum[i])
            {

                Selected.push_back(i);
                break;
            }
        }
    }
    return Selected;
}
int main()
{

    int Test, size, num, w, v, x, n;
    cin >> Test;
    while (Test--)
    {
        cin >> size;
        cin >> num;

        vector<int> Weight;
        vector<int> Value;

        for (int i = 0; i < num; i++)
        {
            cin >> w;
            cin >> v;
            Weight.push_back(w);
            Value.push_back(v);
        }
    }
    /* vector<vector<int>> Chromosomes(6, vector<int>(n));
     Init_Chromosome(Chromosomes, num);
     vector<pair<int, int>> Fitness;
     Get_Fitness(Chromosomes, Weight, Value, size, Fitness, num);
     for (int j = 0; j < 6; j++)
     {
         for (int i = 0; i < num; ++i)
         {
             cout << Chromosomes[j][i] << " ";
         }
         cout << endl;
     }
     for (auto ch : Fitness)
     {
         cout << ch.first << " ";
     }
     cout << endl;
     vector<int> Selected;
     Selection(Fitness, Selected, 6);
     for (auto ch : Selected)
         cout << ch << " ";
 }*/

    return 0;
}