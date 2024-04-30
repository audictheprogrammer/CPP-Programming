#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include <cmath>
#include <unordered_set>


struct PersonInfo {
    std::string name;
    std::string city;
    int age;
    double time;
};

struct Answers {
    int lyonnaisCount;
    double lyonnaisAndUnder30Count;
    bool existToulousainAndNameStartsWithA;
    int minAge, maxAge;
    std::string minAgeName, maxAgeName;
    double meanAge;
    double standardDeviationAge;
    bool parisBetterThanMarseille;
    double covarianceAgeAndTime;
    std::unordered_set<std::string> cityList;
};

struct Answers analysis(std::vector<PersonInfo> P) {
    /* Using the algorithm library to answer.
    The goal here is to not use a single loop. */
    struct Answers A;

    // Lyonnais: Count.
    auto isFromLyon = [] (PersonInfo p) {
        return p.city == "Lyon";
    };
    A.lyonnaisCount = std::count_if(P.begin(), P.end(), isFromLyon);

    // Lyonnais and age under 30: Count.
    auto isFromLyonAndAgeUnder30 = [] (PersonInfo p) {
        return p.city == "Lyon" && p.age < 30;
    };
    A.lyonnaisAndUnder30Count = std::count_if(P.begin(), P.end(), isFromLyonAndAgeUnder30);

    // Toulousain and name starts with A: bool.
    auto isToulousainAndNameStartsWithA = [] (PersonInfo p) {
        return p.city == "Toulouse" && p.name[0] == 'A';
    };
    A.existToulousainAndNameStartsWithA = std::any_of(P.begin(), P.end(), isToulousainAndNameStartsWithA);

    // Youngest and oldest: Age and Names.
    auto ageCompare = [] (PersonInfo p1, PersonInfo p2) {
        return p1.age < p2.age;
    };
    auto minAndMaxIterators = std::minmax_element(P.begin(), P.end(), ageCompare);
    PersonInfo minPerson = *(minAndMaxIterators.first);
    PersonInfo maxPerson = *(minAndMaxIterators.second);
    A.minAge = minPerson.age;
    A.maxAge = maxPerson.age;
    A.minAgeName = minPerson.name;
    A.maxAgeName = maxPerson.name;

    // Mean age.
    auto sumAge = [] (double acc, PersonInfo p) {
        return acc + p.age;
    };
    A.meanAge = std::accumulate(P.begin(), P.end(), 0., sumAge) / P.size();

    // Standard Deviation = Sqrt(Variance)
    double meanAge = A.meanAge;
    auto sumAgeDiff = [meanAge] (double acc, PersonInfo p) {
        return acc + (p.age - meanAge) * (p.age - meanAge);
    };
    A.standardDeviationAge = std::sqrt( std::accumulate(P.begin(), P.end(), 0., sumAgeDiff) / P.size() );

    // Paris better than Marseille: Bool
    auto sumParisTime = [] (double acc, PersonInfo p) {
        if (p.city == "Paris") {
            return acc + p.time;
        }
        return acc;
    };
    auto sumMarseilleTime = [] (double acc, PersonInfo p) {
        if (p.city == "Marseille") {
            return acc + p.time;
        }
        return acc;
    };
    auto isFromParis = [] (PersonInfo p) {
        return p.city == "Paris";
    };
    auto isFromMarseille = [] (PersonInfo p) {
        return p.city == "Marseille";
    };

    double meanParisTime = std::accumulate(P.begin(), P.end(), 0, sumParisTime) / std::count_if(P.begin(), P.end(), isFromParis);
    double meanMarseilleTime = std::accumulate(P.begin(), P.end(), 0, sumMarseilleTime) / std::count_if(P.begin(), P.end(), isFromMarseille);
    A.parisBetterThanMarseille = meanParisTime > meanMarseilleTime;

    // Covariance between Age and Time.
    auto sumTime = [] (double acc, PersonInfo p) {
        return acc + p.time;
    };
    double meanTime = std::accumulate(P.begin(), P.end(), 0., sumTime) / P.size();

    auto sumProductDiff = [meanAge, meanTime] (double acc, PersonInfo p) {
        return acc + (p.age - meanAge) * (p.time - meanTime);
    };
    A.covarianceAgeAndTime = std::accumulate(P.begin(), P.end(), 0.0, sumProductDiff) / P.size();

    std::unordered_set<std::string> E;
    auto insertCity = [&E] (PersonInfo p) {
        E.insert(p.city);
    };
    std::for_each(P.begin(), P.end(), insertCity);
    A.cityList = E;

    return A;
}

void writeAnswers(Answers A, const std::string filename) {
    std::ofstream file(filename);
    file << "lyonnaisCount = " << A.lyonnaisCount << std::endl;
    file << "lyonnaisAndUnder30Count = " << A.lyonnaisAndUnder30Count << std::endl;
    file << "existToulousainAndNameStartsWithA = " << A.existToulousainAndNameStartsWithA << std::endl;
    file << "minAge = " << A.minAge << " and minAgeName = " << A.minAgeName << std::endl;
    file << "maxAge = " << A.maxAge << " and maxAgeName = " << A.maxAgeName << std::endl;
    file << "meanAge = " << A.meanAge <<std::endl;
    file << "standardDeviationAge = " << A.standardDeviationAge << std::endl;
    file << "parisBetterThanMarseille = " << A.parisBetterThanMarseille << std::endl;
    file << "covarianceAgeAndTime = " << A.covarianceAgeAndTime << std::endl;

    file << std::endl << "cityList: " << std::endl;
    for (std::string city: A.cityList) {
        file << city << std::endl;
    }

    file.close();
    return ;
}

int main() {
    std::vector<PersonInfo> personsInfo;
    std::ifstream file("smalldata.txt");

    std::string name;
    std::string city;
    int age;
    double time;
    while (file >> name >> city >> age >> time) {
        PersonInfo p = {name, city, age, time};
        personsInfo.push_back(p);
    }
    file.close();

    Answers A = analysis(personsInfo);
    writeAnswers(A, "Analysis.txt");

    return 0;
}
