#include <iostream>
#include <random>
#include <utility>
#include <bits/stdc++.h>
using namespace std;
const int ChromosomesNumber = 6;
const int SelectedChromosomes = 4;
int Random01()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, 1);
    return distribution(gen);
}
double Random0To1()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(gen);
}
int Random1l(int length)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, length-1);
    return distribution(gen);
}
int Random0l(int length)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, length-1);
    return distribution(gen);
}
float RandomDecimal()
{

    mt19937 rng(random_device{}());
    uniform_real_distribution<float> dist(0.0f, 1.0f);
    float randomFloat = dist(rng);
    return randomFloat;
}
vector<vector<int>> Init_Chromosome(int length)
{
    vector<vector<int>> Chromosome(ChromosomesNumber,vector<int>(length));
    for (int j = 0; j < ChromosomesNumber; j++) {

        for (int i = 0; i < length; ++i) {
            int RandomNumber = Random01();
            Chromosome[j][i] = RandomNumber;
        }
    }
    return Chromosome;
}
void Get_Fitness(vector<vector<int>> &Chromosomes, vector<int> &Weight, vector<int> &Value, int size, vector<pair<int, int>> &Fitness, int num)
{
    int TotalFitness = 0, Totalweight = 0;
    for (int j = 0; j < ChromosomesNumber; j++)
    {
        for (int i = 0; i < num; ++i)
        {
            if (Chromosomes[j][i] == 1)
            {
                TotalFitness += Value[i];
                Totalweight += Weight[i];
            }
        }

            for (int i = 0; i < num; ++i)
            {
                if (Totalweight > size)
                {
                if (Chromosomes[j][i])
                {
                    Chromosomes[j][i] = 0;
                    TotalFitness -= Value[i];
                    Totalweight -= Weight[i];
                }
            }
                else
                {break;}
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
    for (int i = 0; i < SelectedChromosomes; i++)
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
vector<vector<int>> Crossover(vector<int> Selected, vector<vector<int>> Chromosomes, int length)
{
    vector<vector<int>> Children(SelectedChromosomes,vector<int>(length));
    int CrossPoint = Random1l(length);
   for (int i = 0; i < SelectedChromosomes; i++)
    {
        Children[i] = Chromosomes[Selected[i]];
    }

    int index = 0;
    while (index < SelectedChromosomes)
    {

        for (int i = CrossPoint; i < length; i++)
        {
            swap(Children[index][i], Children[index + 1][i]);
        }
        index += 2;
    }
    return Children;
}

vector<vector<int>> BitFlip_Mutation(vector<vector<int>> Children, int length,double MutationFactor)
{

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < length; j++)
        {
            double random=Random0To1();

            if (random < MutationFactor) {

                 Children[i][j] = 1-Children[i][j];
            }

        }
    }
    return Children;
}
vector<vector<int>> Feasability(vector<vector<int>> Children,vector<vector<int>> Chromosomes,int num,vector<int> &Weight, vector<int> &Value, int size) {

    int Totalweight = 0;
    vector<vector<int>> newChromosomes=Chromosomes;
    for (int j = 0; j < SelectedChromosomes; j++) {
        for (int i = 0; i < num; ++i) {
            if (Children[j][i] == 1) {

                Totalweight += Weight[i];

            }
        }

        if (Totalweight <= size)
        {
            newChromosomes.push_back(Children[j]);

        }
         Totalweight = 0;

    }
    return newChromosomes;
}

vector<vector<int>> Elitism_Replacement(vector<vector<int>> population, vector<int> &Weight, vector<int> &Value, int size,int Elite,int num)
{
    vector<pair<int, int>> Fitness;
    Get_Fitness(population, Weight, Value, size, Fitness, num);

    sort(Fitness.begin(), Fitness.end(),greater<pair<int, int>>());
    cout<<"fitness"<<endl;
    for (auto ch: Fitness) {
        cout << ch.first << " "<<ch.second<<endl;
    }
    cout << endl;
    vector<vector<int>> NewGeneration(ChromosomesNumber,vector<int>(num));
    for (int i = 0; i <Elite; ++i) {
        NewGeneration[i]=(population[Fitness[i].second]);
    }
    for (int j = 0; j <Elite ; j++) {
        for (int i = 0; i < num; ++i) {
            cout << NewGeneration[j][i] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = Elite; i <ChromosomesNumber; ++i) {
        int random = Random0l(ChromosomesNumber);
        NewGeneration[i]=(population[Fitness[random].second]);
    }


  return NewGeneration;
}

int main()
{
    ifstream inputFile("C:\\Users\\MBR\\OneDrive\\Desktop\\input.txt");

    if (!inputFile.is_open()) {
        cerr << "Failed to open the input file." << endl;
        return 1;
    }

    int Test, size, num, w, v, x, n;
    inputFile >>Test;
    while (Test--) {
        inputFile >> size;
        inputFile >> num;

        vector<int> Weight;
        vector<int> Value;

        for (int i = 0; i < num; i++) {
            inputFile >> w;
            inputFile >> v;
            Weight.push_back(w);
            Value.push_back(v);
        }


        vector<vector<int>> Chromosomes(6, vector<int>(num));
        Chromosomes = Init_Chromosome(num);

        vector<pair<int, int>> Fitness;
        Get_Fitness(Chromosomes, Weight, Value, size, Fitness, num);
        for (int j = 0; j < 6; j++) {
            for (int i = 0; i < num; ++i) {
                cout << Chromosomes[j][i] << " ";
            }
            cout << endl;
        }
        cout<<"fitness"<<endl;
        for (auto ch: Fitness) {
            cout << ch.first << " "<<ch.second<<endl;
        }
        cout << endl;
        vector<int> Selected;
        cout<<"selected"<<endl;
        Selected=Selection(Fitness, 6);
        for (auto ch: Selected)
            cout << ch << " ";
        cout<<endl;
        cout<<"crossed"<<endl;
        vector<vector<int>> Cross;
        Cross= Crossover(Selected,Chromosomes,num);
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < num; ++i) {
                cout << Cross[j][i] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout<<"Mutated"<<endl;
        vector<vector<int>> mutated;
        mutated= BitFlip_Mutation(Cross,num,0.5);
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < num; ++i) {
                cout << mutated[j][i] << " ";
            }
            cout << endl;
        }
        cout << endl;
        Chromosomes= Feasability(mutated,Chromosomes,num,Weight,Value,size);
        for (int j = 0; j <Chromosomes.size() ; j++) {
            for (int i = 0; i < num; ++i) {
                cout << Chromosomes[j][i] << " ";
            }
            cout << endl;
        }
        cout << endl;
        vector<vector<int>> newPop;
        newPop= Elitism_Replacement(Chromosomes,Weight,Value,size,4,num);
        for (int j = 0; j <6 ; j++) {
            for (int i = 0; i < num; ++i) {
                cout << newPop[j][i] << " ";
            }
            cout << endl;
        }
        cout << endl;

    }
    inputFile.close();
    return 0;
}