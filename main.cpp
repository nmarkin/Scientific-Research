#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <ctime>
#include <fstream>
#include "Number.h"

class Multiplicator{
public:

    static Number schoolGradeMultiplication(Number &a, Number &b)
    {
        Number res = Number("0");
        std::string mainZeros;
        for(int i = 0; i < a.num.length(); i ++)
        {
            int num = a.getd();
            std::string zeros = mainZeros;
            for(int j = 0; j < b.num.length(); j ++)
            {
                res += Number(std::to_string(b.getd() * num) + zeros);
                zeros += "0";
            }
            mainZeros += "0";
        }
        if(res.num[0] == '0') // multiplication by 0 case
            res.num = "0";
        return res;
    }

    static Number divideAndConquer (Number a, Number b)
    {
        if(a.num.length() != b.num.length())  // equalizing length
        {
            std::string zeros;
            if (a.num.length() > b.num.length())
            {
                int dif = a.num.length() - b.num.length();
                for(int i = 0; i < dif; i++)
                    zeros += '0';
                b.num = zeros + b.num;
            } else
            {
                int dif = b.num.length() - a.num.length();
                for(int i = 0; i < dif; i++)
                    zeros += '0';
                a.num = zeros + a.num;
            }
        }
        if(a.num.length() == 1 && b.num.length() == 1)
        {
            int res = a.getd() * b.getd();
            return Number(std::to_string(res));
        } else
        {
            Number z1 = a.splitLeft();
            Number z2 = b.splitLeft();
            Number q1 = a.splitRight();
            Number q2 = b.splitRight();
            std::string zeros;
            for(int i = 0; i < q1.num.length(); i++)
                zeros += '0';
            Number x = divideAndConquer(z1, z2);
            Number z = divideAndConquer(q1, q2);
            Number y = divideAndConquer(z1 + q1, z2 + q2) - x - z;
            x.num += zeros + zeros;
            y.num += zeros;
            Number res = x + y + z;
            for(int i = 0; i < res.num.length() - 1; i++)  // getting rid of zeros before numbers
            {
                if (res.num[0] == '0')
                    res.num.erase(0,1);
                else
                    break;
            }
            return res;
        }
    }

    static Number randomNumberTime(int k)
    {
        std::string num;
        std::random_device rd;
        std::mt19937 gen(clock());
//        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 9);
        std::uniform_int_distribution<> dis1(1, 9);
        num += dis1(gen) + '0';
        for(int i = 0; i < k - 1; i++)
            num += dis(gen) + '0';
        return Number(num);
    }

    static Number randomNumber(int k)
    {
        std::string num;
        std::random_device rd;
//        std::mt19937 gen(clock());
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 9);
        std::uniform_int_distribution<> dis1(1, 9);
        num += dis1(gen) + '0';
        for(int i = 0; i < k - 1; i++)
            num += dis(gen) + '0';
        return Number(num);
    }

    static std::vector<std::pair<double, double>> conductResearch(int k)
    {
        std::vector<std::pair<double, double>> experiment;
        for(int i = 1; i <= k; i++)
        {
            double schoolTime = 0, smartTime = 0;
            for(int j = 0; j < 3; j++)
            {
                Number a = randomNumber(i);         // having 2 different constructors allows
                Number b = randomNumberTime(i);     // to get 2 dif numbers for each multiplication
                const clock_t begin_time1 = clock();
                schoolGradeMultiplication(a,b);
                schoolTime += double(clock () - begin_time1);
                const clock_t begin_time2 = clock();
                divideAndConquer(a,b);
                smartTime += double(clock () - begin_time2);
            }
            experiment.emplace_back(std::make_pair(schoolTime/3, smartTime/3));
            std::cout << i <<'\t' << schoolTime << '\t' << smartTime << '\n';
        }
//        for( int i = 0; i < k - 1; i++)
//            std::cout << experiment[i].first << '\t' << experiment[i].second << '\n';
        return experiment;
    }

    static void CSV(std::vector<std::pair<double, double>> res)
    {
        std::ofstream file;
        file.open ("Data.csv");
        for (int i = 0; i < res.size(); i++)
            file << i + 1 << ";" << res[i].first << ";" << res[i].second << "\n";
        file.close();
    }
};

int main() {
//    Number a = Number("123456789");
//    Number b = Number("1");
//    Number s = Multiplicator::randomNumber(3);
//    std::cout<<s.num<<std::endl;
//    Number f = Multiplicator::randomNumber(3);
//    std::cout<<f.num<<std::endl;
    Multiplicator::CSV(Multiplicator::conductResearch(400));
//    std::cout<<s.splitLeft().num<<std::endl;
//    std::cout<<s.splitRight().num<<std::endl;
}