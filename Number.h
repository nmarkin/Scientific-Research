//
// Created by nmark on 28.04.2019.
//

#ifndef UNTITLED_NUMBER_H
#define UNTITLED_NUMBER_H

class Number {
public:
    std::string num;
    int ptr = num.length();

    Number()
    {
        num = "";
    }

    Number (std::string a)
    {
        num = a;
        ptr = num.length();
    }

    Number (size_t a)
    {
        num = std::to_string(a);
        ptr = num.length();
    }

    int getd()
    {
        ptr--;
        if(ptr == -1)
            ptr = num.length()-1;
        return num[ptr] - 48; // from char to int
    }

    Number operator + (const Number& a)
    {
        Number number;
        int j = a.num.length() - 1;
        int i = this->num.length()-1;
        int tmp2 = 0;
        while(i >= 0 && j >= 0)
        {
            int tmp = this->num[i] - '0' + a.num[j] - '0' + tmp2;
            if(tmp > 9)
            {
                tmp -= 10;
                tmp2 = 1;
            } else
                tmp2 = 0;
            number.num += (tmp + '0');
            j--;
            i--;
        }
        if(i >= 0)
            while(i >= 0)
            {
                int tmp = int(this->num[i] - '0') + tmp2;
                if(tmp > 9)
                {
                    tmp -= 10;
                    tmp2 = 1;
                } else
                    tmp2 = 0;
                number.num += (tmp + '0');
                i--;
            }
        else if (j >= 0)
            while(j >= 0)
            {
                int tmp = int(a.num[j] - '0') + tmp2;
                if(tmp > 9)
                {
                    tmp -= 10;
                    tmp2 = 1;
                } else
                    tmp2 = 0;
                number.num += (tmp + '0');
                j--;
            }
        if(tmp2)
            number.num +=(tmp2 +'0');
        reverse(number.num.begin(), number.num.end());
        return number;
    }

    Number operator - (const Number& a)
    {
        Number number;
        int j = a.num.length() - 1;
        int i = this->num.length()-1;
        int tmp2 = 0;
        while(i >= 0 && j >= 0)
        {
            int tmp = this->num[i] - a.num[j] - tmp2;
            if(tmp < 0)
            {
                tmp += 10;
                tmp2 = 1;
            } else
                tmp2 = 0;
            number.num += (tmp + '0');
            j--;
            i--;
        }
        if(i >= 0)
            while(i >= 0)
            {
                int tmp = int(this->num[i] - '0') - tmp2;
                if(tmp < 0)
                {
                    tmp += 10;
                    tmp2 = 1;
                } else
                    tmp2 = 0;
                number.num += (tmp + '0');
                i--;
            }
        else if (j >= 0)
            while(j >= 0)
            {
                int tmp = int(a.num[j] - '0') - tmp2;
                if(tmp < 0)
                {
                    tmp += 10;
                    tmp2 = 1;
                } else
                    tmp2 = 0;
                number.num += (tmp + '0');
                j--;
            }
        for(int n = number.num.length()-1; n > 0 ; n--)
        {
            if(number.num[n] == '0')
                number.num.pop_back();
            else
                break;
        }
        reverse(number.num.begin(), number.num.end());
        return number;
    }

    Number operator += (const Number& a)
    {
        *this = *this + a;
        return *this;
    }

    Number splitLeft()
    {
        int len = this->num.length();
        if(len == 1)
            return Number("0");
        std::string str = this->num.substr(0, len/2);
        if(str.empty())
            return Number("0");
        else
            return Number(str);
    }

    Number splitRight()
    {
        int len = this->num.length();
        if(len == 1)
            return *this;
        std::string str = this->num.substr(len/2, len - 1);
        if(str.empty())
            return Number("0");
        else
            return Number(str);
    }
};


#endif //UNTITLED_NUMBER_H
