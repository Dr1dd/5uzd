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
int main(){
    std::multimap<std::string, int> tekstas;
    std::map<std::string, int> zodziai;
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
    
    auto iterator = numeris.begin();
    int y = 0;
    for(auto it = zodziai.cbegin(); it != zodziai.cend(); ++it){
        fr << "Zodis: "  << std::left <<std::setw(15) <<it->first << std::setw(10) << " pasikartojo " << it->second << " kartus, ";
               for(auto j = 0; j !=numeris[y].eilNr.size(); j++)
                   fr << numeris[y].eilNr[j]  <<" ";
        y++;
            fr<<"eilutese \n";
    }
    fr << "\nRasti URL linkai: \n";

    for(auto it = URL.begin(); it != URL.end(); ++it){
        fr << it->first << ", eiluteje: " << it->second << endl;
    }
    
    fr.close();
    return 0;
}