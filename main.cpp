#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <locale>
#include <regex>

using std::cout;
using std::endl;
class zdz{
private:
    public:
        std::vector<int> eilNr;

};
struct comp {
    bool operator() (const std::string& lhs, const std::string& rhs) const {
        return stricmp(lhs.c_str(), rhs.c_str()) < 0;
    }
};

int main(){
    std::multimap<std::string, int, comp> tekstas;
    std::map<std::string, int, comp> zodziai;
    std::map<std::string, int> URL;

    std::string zodis;
    std::string eilute;
    std::string zodisRez;

    std::vector<zdz> numeris;
    zdz number;


    std::ifstream fd("tekstas.txt");
    if(fd.fail()) {
    cout << "Sis failas neegzistuoja" << endl;
    }
    int lnsk =0;
    while(getline(fd, eilute)){
        lnsk++;
        std::stringstream ss(eilute);
        while(ss >> zodis){
            if(zodis[zodis.size()-1] == ',' || zodis[zodis.size()-1] == '.') zodis = zodis.substr(0, zodis.size()-1);
            if(std::regex_match(zodis, std::regex("[(http(s)?):\\/\\/(www\\.)?a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)") )){
                URL.insert(std::pair<std::string,int>(zodis,lnsk));
            }
            zodis.erase (std::remove_if(zodis.begin(), zodis.end(), ::ispunct), zodis.end());
            tekstas.insert(std::pair<std::string,int>(zodis,lnsk));
        }
    }
    fd.close();

    int count;
    std::multimap<std::string, int>::iterator itlow, itup;
    for(auto it =  tekstas.cbegin(); it != tekstas.cend(); ++it){
        number.eilNr.clear();
        if(tekstas.count(it->first) > 1) {
            count = tekstas.count(it->first);
            zodziai.insert(std::pair<std::string, int>(it->first,count));
            itlow = tekstas.lower_bound(it->first);
            itup = tekstas.upper_bound(it->first);
            while(itlow != itup){
                if (std::find(number.eilNr.begin(), number.eilNr.end(), itlow->second) == number.eilNr.end()) {
                    number.eilNr.push_back(itlow->second);
                }
            itlow++;
            it++;
            }
            numeris.push_back(number);
        }
        }

    std::ofstream fr("rezultatai.txt");
    int max = 0;
    for(auto it = zodziai.cbegin(); it != zodziai.cend(); ++it){ // ieskomas max rastu zodziu skaicius
        if (it->second > max) {
            max = it->second;
        }
    }
    
    auto iterator = numeris.begin();
    int y = 0;
    int start = 2; // pradzia
    int zodziuSkaicius =0;
    while(start <= max) {
        y= 0;
        zodziuSkaicius = 0;
        fr << "Žodžiai, kurie tekste pasikartoja " << start << " kartus:" << endl;
        fr << endl;
        for (auto it = zodziai.cbegin(); it != zodziai.cend(); ++it) {
            if(it->second == start){
                zodziuSkaicius++;
                fr << "Žodis: " << std::left << std::setw(15) << it->first << std::setw(10) << " pasikartojo " << it->second
                   << " kartus, ";
                for (auto j = 0; j != numeris[y].eilNr.size(); j++)
                    fr << numeris[y].eilNr[j] << " ";
                fr << "eilutėse \n";
            }
            y++;
        }
        start++;
        if(zodziuSkaicius == 0) fr << "--------------------Tokių žodžių nėra, kurie pasikartoja " << start << " kartus-----------------" << endl;
        fr << endl;
    }
    fr << "\nRasti URL linkai: \n";

    for(auto it = URL.begin(); it != URL.end(); ++it){
        fr << it->first << ", eilutėje: " << it->second << endl;
    }
    
    fr.close();
    std::string word;
    std::ofstream fr1("rezultatai2.txt");
    fr1 << "Žodžiai, kurie tekste pasikartoja daugiau nei 1 kartą:" << endl;
    fr1<<endl;
    std::string previous;
    int linesLeft = 1;
    int linesRight = lnsk/2;
    int linesRightConst =lnsk/2;
    int eilIlgis;
    while (linesLeft <= linesRightConst && linesLeft <= lnsk) {
            fr1 << linesLeft << " eilutėje esantys žodžiai: ";
            for (auto it = tekstas.cbegin(); it != tekstas.cend(); ++it) {
                if (tekstas.count(it->first) > 1) {
                    if (it->second == linesLeft) {
                        word = it->first;
                        if (previous != word) {
                            eilIlgis += word.length()+2;
                            fr1 << word << ", ";
                        }
                        previous = word;
                    }
                }
            }

            fr1 << std::right << std::setw(240-eilIlgis);
                fr1 <<  linesRight << " eilutėje esantys žodžiai: ";
            for (auto it = tekstas.cbegin(); it != tekstas.cend(); ++it) {
                if (tekstas.count(it->first) > 1) {
                    if (it->second == linesRight) {
                        word = it->first;
                        if (previous != word) fr1 << word << ", ";
                        previous = word;
                    }
                }
            }

            linesLeft++;
            linesRight++;
            eilIlgis = 0;
            fr1 << endl;
        }

    fr1.close();
    return 0;
}