#include <vector>
#include "iostream"

bool Cap_Start_Word(std::string &s) {
    if (!s.empty() && isupper(s[0])) {
        for (auto i = 1; i < s.length(); ++i) {
            if (!islower(s[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool City(std::string &s) {
    if (s.length() == 3) {
        for (char c: s) {
            if (!isupper(c)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Apart_num(std::string &s) {
    if (s.length() > 1) {
        for (auto c: s) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Street(std::string &s) {
    if (!s.empty() && isupper(s[0])) {
        for (auto i = 1; i < s.length(); ++i) {
            if (!islower(s[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool FULL_NAME(std::string &s, int s1p, int s2p) {
    std::string name = s.substr(0, s1p);
    std::string surname = s.substr(s1p + 1, s2p - s1p - 1);
    std::string otchestvo = s.substr(s2p + 1);

    if (Cap_Start_Word(name) && Cap_Start_Word(surname) && Cap_Start_Word(otchestvo)) {
        return true;
    }

    return false;
}

bool AGE(std::string &s) {
    if (s.length() == 2 && isdigit(s[0]) && isdigit(s[1])) {
        return true;
    }
    return false;
}

bool PHONE_NUM(std::string &s) {
    // +7XXXXXXXXXX
    if (s.length() == 12 && s[0] == '+' && s[1] == '7' &&
        isdigit(s[2]) && isdigit(s[3]) && isdigit(s[4]) &&
        isdigit(s[5]) && isdigit(s[6]) && isdigit(s[7]) &&
        isdigit(s[8]) && isdigit(s[9]) && isdigit(s[10]) &&
        isdigit(s[11])) {
        return true;
    }
        // 7XXXXXXXXXX или 8XXXXXXXXXX
    if (s.length() == 11 && (s[0] == '7' || s[0] == '8') &&
             isdigit(s[1]) && isdigit(s[2]) && isdigit(s[3]) &&
             isdigit(s[4]) && isdigit(s[5]) && isdigit(s[6]) &&
             isdigit(s[7]) && isdigit(s[8]) && isdigit(s[9]) &&
             isdigit(s[10])) {
        return true;
    }
        // +7(XXX)-XXX-XX-XX
    if (s.length() == 17 && s[0] == '+' && s[1] == '7' && s[2] == '(' &&
             isdigit(s[3]) && isdigit(s[4]) && isdigit(s[5]) && s[6] == ')' &&
             s[7] == '-' && isdigit(s[8]) && isdigit(s[9]) && isdigit(s[10]) &&
             s[11] == '-' && isdigit(s[12]) && isdigit(s[13]) && s[14] == '-' &&
             isdigit(s[15]) && isdigit(s[16])) {
        return true;
    }
        // +7(XXX)XXX-XXXX
    if (s.length() == 15 && s[0] == '+' && s[1] == '7' && s[2] == '(' &&
             isdigit(s[3]) && isdigit(s[4]) && isdigit(s[5]) && s[6] == ')' &&
             isdigit(s[7]) && isdigit(s[8]) && isdigit(s[9]) && s[10] == '-' &&
             isdigit(s[11]) && isdigit(s[12]) && isdigit(s[13]) && isdigit(s[14])) {
        return true;
    }
    return false;
}

bool ADDRESS(std::string &s, int s1p, int s2p) {
    int gp = s.find("g.");
    int ulp = s.find(", ul");
    int dp = s.find(", d");

    if (gp == std::string::npos || ulp == std::string::npos || dp == std::string::npos) {
        return false;
    }

    std::string city = s.substr(gp + 2, s1p - gp - 2 - 1);
    std::string street = s.substr(ulp + 5, s2p - s1p + 3 - 1);
    std::string apart_num = s.substr(dp + 4);

    if (City(city) && Street(street) && Apart_num(apart_num)) {
        return true;
    }
    return false;
}

int main() {
    int N;
    std::cin >> N;

    std::cin.ignore();
    std::string data;
    for (int i = 0; i < N; ++i) {
        std::getline(std::cin, data);

        int s1p = data.find(' ', 0);
        int s2p = data.find(' ', s1p + 1);
        int s3p = data.find(' ', s2p + 1);
        if (s1p == std::string::npos || s2p == std::string::npos || s3p == std::string::npos) {
            std::cout << "NO\n";
            continue;
        }
        std::string full_name = data.substr(0, s3p);

        int s4p = data.find(' ', s3p + 1);
        if (s4p == std::string::npos) {
            std::cout << "NO\n";
            continue;
        }
        std::string age = data.substr(s3p + 1, s4p - s3p - 1);

        int s5p = data.find(' ', s4p + 1);
        if (s5p == std::string::npos) {
            std::cout << "NO\n";
            continue;
        }
        std::string phone_num = data.substr(s4p + 1, s5p - s4p - 1);

        int s6p = data.find(' ', s5p + 1);
        int s7p = data.find(' ', s6p + 1);
        if (s6p == std::string::npos || s7p == std::string::npos) {
            std::cout << "NO\n";
            continue;
        }
        std::string address = data.substr(s5p + 1);

        if (!FULL_NAME(full_name, s1p, s2p)) {
            std::cout << "NO\n";
            continue;
        }
        if (!AGE(age)) {
            std::cout << "NO\n";
            continue;
        }
        if (!PHONE_NUM(phone_num)) {
            std::cout << "NO\n";
            continue;
        }
        if (!ADDRESS(address, s6p - s5p - 1, s7p - s6p - 1)) {
            std::cout << "NO\n";
            continue;
        }

        std::cout << "YES\n";
    }

    return 0;
}
/*
1
Ew ObAd 47 71778163784 g.SRB, ul.Uzmeuxmxm, d.618


1
Ew Ob Ad 47 71778163784 g.SRB, ul.uzmeuxmxm, d.618


1
Ew Ob Ad 47 71778163784 g.BOB, ul.Loxy, d.6969


4
Ew Ob Ad 47 71778163784 g.BOB, ul.Loxy, d.6969
Ew ObAd 47 71778163784 g.SRB, ul.Uzmeuxmxm, d.618
Bak Ve Qd 67 +84717214117 g.MWN, ul.Mhowfwnyepb, d.87
Ew Ob Ad 47 71778163784 g.SRB, ul.Uzmeuxmxm, d.618

4
Anna Ivanova Petrova 25 +7(912)345-6789 g.MSK, ul.Lenina, d.12
John Doe Smith 99 89991234567 g.NYC, ul.Broadway, d.123
Ivan Petrov Sidorov 18 +7(000)000-00-00 g.SPB, ul.Nevsky, d.1
Maria Zhukova Kuznetsova 30 70000000000 g.EKB, ul.Malysheva, d.50


3
Alexey Smirnov kuznetsov 34 +7(123)456-7890 g.KZN, ul.Sibirskaya, d.8
Maria Ivanova Orlova 27 81234567890 g.VLD, ul.Amurskaya, d.77
Nikolay Petrov Ivanov 45 +7(987)654-3210 g.NVS, ul.Taiginskaya, d.156
*/