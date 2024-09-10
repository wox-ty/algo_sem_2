#include "iostream"
#include "regex"


int main(){
    int N;
    std::cin >> N;

    std::cin.ignore();
    std::string data;
    for (int i = 0; i < N; ++i) {
        std::getline(std::cin, data);
//        std::regex full_name("[A-Z][a-z]+ [A-Z][a-z]+ [A-Z][a-z]+");

//        std::regex age(R"(\d{2})");

//        std::regex phone_num(R"((\+7|7|8)\(?\d{3}\)?\-?\d{3}\-?\d{2}\-?\d{2})");

//        std::regex city(R"(\g\.[A-Z]{3})");
//        std::regex street(R"(ul\.[A-Z][a-z]+)");
//        std::regex flat_num(R"(d\.\d\d+)");

//        std::regex full_address(R"(g\.[A-Z]{3}, ul\.[A-Z][a-z]+, d\.\d{2,})");

        std::regex full_data(R"([A-Z][a-z]+ [A-Z][a-z]+ [A-Z][a-z]+ \d{2} (\+7|7|8)\(?\d{3}\)?\-?\d{3}\-?\d{2}\-?\d{2} g\.[A-Z]{3}, ul\.[A-Z][a-z]+, d\.\d{2,})");

        bool found = std::regex_match(data.begin(), data.end(), full_data);
        if (found) {
            std::cout << "YES\n";
        }
        else{
            std::cout << "NO\n";
        }
    }

    return 0;
}
/*
[+]?[7|8][(]?[0-9]{3}[)]?[-]?[0-9]{3}[-]?[0-9]{2}[-]?[0-9]{2}
(+7|7|8)\(?\d{3}\)?\-?\d{3}\-?\d{2}\-?\d{2}

1
Bak Ve Qd 67 +84717214117 g.MWN, ul.Mhowfwnyepb, d.87
1
Ew Ob Ad 47 71778163784 g.SRB, ul.Uzmeuxmxm, d.618
*/