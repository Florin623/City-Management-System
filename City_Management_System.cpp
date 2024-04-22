#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <set>

class Person {

public:
    std::string mName;
    uint16_t mAge;
    double mSalary;

    Person(): mAge(0), mSalary(0) {}

    Person(std::string mName, const uint16_t& mAge, const double& mSalary): mName(std::move(mName)), mAge(mAge), mSalary(mSalary) {}

    bool operator==(const Person& other) const {
        return mName == other.mName && mAge == other.mAge && mSalary == other.mSalary;
    }

    bool operator!=(const Person& other) const {
        return mName != other.mName || mAge != other.mAge || mSalary != other.mSalary;
    }

    bool operator<(const Person& other) const {
        return mName < other.mName;
    }
};

class Building {

protected:
    std::string mBuildingName;
    std::string mType;
    Person mCoordinator;
    std::vector<Person> mEmployees;
    std::vector<Person> mCitizens;

public:
    Building(std::string mBuildingName, std::string  mType): mBuildingName(std::move(mBuildingName)), mType(std::move(mType)) {}

    virtual void add(const Person& other) = 0;
    virtual void remove(const Person& other) = 0;

    virtual Building* operator+(const Person& other) {
        return this;
    }

    virtual Building* operator-() /*unar*/ {
        return nullptr;
    }

    virtual Building* operator-(const Person& other) /*binar*/ {
        return nullptr;
    }

    [[nodiscard]] std::string getBuildingName() const {
        return mBuildingName;
    }

    [[nodiscard]] std::string getType() const {
        return mType;
    }

    [[nodiscard]] uint16_t getEmployeesSize() const {
        return mEmployees.size();
    }

    [[nodiscard]] uint16_t getCitizensSize() const {
        return mCitizens.size();
    }

    [[nodiscard]] Person getEmployee(uint16_t i) const {
        return mEmployees[i];
    }

    [[nodiscard]] Person getCitizen(uint16_t i) const {
        return mCitizens[i];
    }

    [[nodiscard]] Person getCoordinator() const {
        return mCoordinator;
    }
};

class CityHall : public Building {

public:
    explicit CityHall(std::string CityHallName): Building(std::move(CityHallName), "CityHall") {
        mCitizens.clear();
    }

    Building* operator+(const Person& other) override {
        if (mCoordinator == Person())
            mCoordinator = other;

        return this;
    }

    Building* operator-() override {
        mCoordinator = Person();
        return this;
    }

    Building* operator-(const Person& other) override {
        mCoordinator = Person();
        return this;
    }

    void add(const Person& other) override {
        mCitizens.emplace_back(other);
    }

    void remove(const Person& other) override {
        mCitizens.erase(std::remove(mCitizens.begin(), mCitizens.end(), other), mCitizens.end());
    }
};

class Hospital : public Building {

public:
    explicit Hospital(std::string HospitalName): Building(std::move(HospitalName), "Hospital") {
        mCitizens.clear();
        mEmployees.clear();
    }

    Building* operator+(const Person& other) override {
        mEmployees.emplace_back(other);
        return this;
    }

    Building* operator-() override {
        mCoordinator = Person();
        return this;
    }

    Building* operator-(const Person& other) override {
        mEmployees.erase(std::remove(mEmployees.begin(), mEmployees.end(), other), mEmployees.end());
        return this;
    }

    void add(const Person& other) override {
        mCitizens.emplace_back(other);
    }

    void remove(const Person& other) override {
        mCitizens.erase(std::remove(mCitizens.begin(), mCitizens.end(), other), mCitizens.end());
    }
};

class PoliceStation : public Building {

public:
    explicit PoliceStation(std::string PoliceStationName): Building(std::move(PoliceStationName), "PoliceStation") {
        mCitizens.clear();
        mEmployees.clear();
    }

    Building* operator+(const Person& other) override {
        mEmployees.emplace_back(other);
        return this;
    }

    Building* operator-() override {
        mCoordinator = Person();
        return this;
    }

    Building* operator-(const Person& other) override {
        mEmployees.erase(std::remove(mEmployees.begin(), mEmployees.end(), other), mEmployees.end());
        return this;
    }

    void add(const Person& other) override {
        mCitizens.emplace_back(other);
    }

    void remove(const Person& other) override {
        mCitizens.erase(std::remove(mCitizens.begin(), mCitizens.end(), other), mCitizens.end());
    }
};

class House : public Building {

    uint16_t mMaxNumber;

public:
    House(std::string HouseName, const uint16_t& MaxNumber): Building(std::move(HouseName), "House") {
        mMaxNumber = MaxNumber;
        mCitizens.clear();
    }

    Building* operator+(const Person& other) override {
        if (mCoordinator == Person()) {
            mCoordinator = other;
            mCitizens.emplace_back(mCoordinator);
        }
        return this;
    }

    Building* operator-() override {
        mCitizens.erase(std::remove(mCitizens.begin(), mCitizens.end(), mCoordinator), mCitizens.end());
        return this;
    }

    Building* operator-(const Person& other) override {
        mCitizens.erase(std::remove(mCitizens.begin(), mCitizens.end(), mCoordinator), mCitizens.end());
        return this;
    }

    void add(const Person& other) override {
        if (mCitizens.size() < mMaxNumber)
            mCitizens.emplace_back(other);
    }

    void remove(const Person& other) override {
        if (other.mAge >= 18)
            mCitizens.erase(std::remove(mCitizens.begin(), mCitizens.end(), other), mCitizens.end());
    }
};

class Block : public Building {

    uint16_t mMaxNumberPerFloor;
    uint16_t mnr_etaje;

public:
    Block(std::string BlockName, const uint16_t& nr_etaje, const uint16_t& MaxNumberPerFloor): Building(std::move(BlockName), "Block") {
        mnr_etaje = nr_etaje;
        mMaxNumberPerFloor = MaxNumberPerFloor;
        mCitizens.clear();
    }

    Building* operator+(const Person& other) override {
        if (mCoordinator == Person())
            mCoordinator = other;
        return this;
    }

    Building* operator-() override {
        mCoordinator = Person();
        return this;
    }

    Building* operator-(const Person& other) override {
        mCoordinator = Person();
        return this;
    }

    void add(const Person& other) override {
        if (mCitizens.size() < mnr_etaje * mMaxNumberPerFloor)
            mCitizens.emplace_back(other);
    }

    void remove(const Person& other) override {
        if (other.mAge >= 18) {
            for (auto & mCitizen : mCitizens)
                if (mCitizen == other) {
                    mCitizen = Person();
                    break;
                }
        }
    }
};

int main() {
    std::string comanda;
    std::string entitate;
    std::string nume_entitate;
    std::string nume_cladire;
    uint16_t nr_CityHall = 0;
    uint16_t nr_Hospital = 0;
    uint16_t nr_PoliceStation = 0;
    uint16_t nr_House = 0;
    uint16_t nr_Block = 0;
    std::vector<Building*> cladiri;

    while (std::cin >> comanda) {
        if (comanda == "add") {
            std::cin >> entitate;
            if (entitate == "CityHall") {
                std::cin >> nume_entitate;
                cladiri.emplace_back(new CityHall(nume_entitate));
            }
            else if (entitate == "Hospital") {
                std::cin >> nume_entitate;
                cladiri.emplace_back(new Hospital(nume_entitate));
            }
            else if (entitate == "PoliceStation") {
                std::cin >> nume_entitate;
                cladiri.emplace_back(new PoliceStation(nume_entitate));
            }
            else if (entitate == "House") {
                uint16_t nr_persoane;
                std::cin >> nume_entitate >> nr_persoane;
                cladiri.emplace_back(new House(nume_entitate, nr_persoane));
            }
            else if (entitate == "Block") {
                uint16_t nr_etaje;
                uint16_t MaxNumberPerFloor;
                std::cin >> nume_entitate >> nr_etaje >> MaxNumberPerFloor;
                cladiri.emplace_back(new Block(nume_entitate, nr_etaje, MaxNumberPerFloor));
            }
            else if (entitate == "coordinator") {
                uint16_t age;
                double salary;
                std::cin >> nume_entitate >> age >> salary >> nume_cladire;
                for (const auto& it : cladiri)
                    if (nume_cladire == it->getBuildingName()) {
                        replace(cladiri.begin(), cladiri.end(), it, it->operator+(Person(nume_entitate, age, salary)));
                        break;
                    }
            }
            else if (entitate == "employee") {
                uint16_t age;
                double salary;
                std::cin >> nume_entitate >> age >> salary >> nume_cladire;
                for (const auto& it : cladiri)
                    if (nume_cladire == it->getBuildingName()) {
                        replace(cladiri.begin(), cladiri.end(), it, it->operator+(Person(nume_entitate, age, salary)));
                        break;
                    }
            }
            else if (entitate == "citizen") {
                uint16_t age;
                double salary;
                std::cin >> nume_entitate >> age >> salary >> nume_cladire;
                for (const auto& it : cladiri)
                    if (nume_cladire == it->getBuildingName()) {
                        it->add(Person(nume_entitate, age, salary));
                        break;
                    }
            }
        }
        else if (comanda == "remove") {
            std::cin >> entitate;
            if (entitate == "citizen") {
                std::cin >> nume_entitate >> nume_cladire;
                for (const auto& it : cladiri)
                    if (nume_cladire == it->getBuildingName())
                        for (uint16_t i = 0; i < it->getCitizensSize(); ++i)
                            if (nume_entitate == it->getCitizen(i).mName) {
                                it->remove(it->getCitizen(i));
                                break;
                            }
            }
            else if (entitate == "employee") {
                std::cin >> nume_entitate >> nume_cladire;
                for (const auto& it : cladiri)
                    if (nume_cladire == it->getBuildingName())
                        for (uint16_t i = 0; i < it->getEmployeesSize(); ++i)
                            if (nume_entitate == it->getEmployee(i).mName) {
                                replace(cladiri.begin(), cladiri.end(), it, it->operator-(it->getEmployee(i)));
                                break;
                            }
            }
            else if (entitate == "coordinator") {
                std::cin >> nume_entitate >> nume_cladire;
                for (const auto& it : cladiri)
                    if (nume_cladire == it->getBuildingName())
                        if (nume_entitate == it->getCoordinator().mName) {
                            replace(cladiri.begin(), cladiri.end(), it, it->operator-());
                            break;
                        }
            }
        }
    }

    for (const auto& it : cladiri) {
        if (it->getType() == "CityHall")
            ++nr_CityHall;
        else if (it->getType() == "Hospital")
            ++nr_Hospital;
        else if (it->getType() == "PoliceStation")
            ++nr_PoliceStation;
        else if (it->getType() == "House")
            ++nr_House;
        else if (it->getType() == "Block")
            ++nr_Block;
    }

    if (nr_CityHall >= 3 && nr_Hospital >= 2 && nr_PoliceStation >= 3 && nr_House >= 8 && nr_Block >= 4)
        std::cout << "Type: Capital\n";
    else
    if (nr_CityHall >= 2 && nr_Hospital >= 1 && nr_PoliceStation >= 2 && nr_House >= 4 && nr_Block >= 1)
        std::cout << "Type: Town\n";
    else
        std::cout << "Type: Village\n";

    uint16_t nr_pacienti = 0;

    for (const auto& it : cladiri)
        if (it->getType() == "Hospital")
            nr_pacienti += it->getCitizensSize();

    std::cout << "Number of patients in hospitals: " << nr_pacienti << "\n";

    uint16_t doctori = 0;
    uint16_t politai = 0;
    uint16_t primari = 0;
    uint16_t acoliti = 0;
    uint16_t puscariasi = 0;
    uint16_t varste_puscariasi = 0;
    double doc_salariu = 0;
    double pol_salariu = 0;
    double prim_salariu = 0;
    double acol_salariu = 0;

    for (const auto& it : cladiri) {
        if (it->getEmployeesSize() != 0)
            if (it->getType() == "Hospital")
                for (uint16_t i = 0; i < it->getEmployeesSize(); ++i) {
                    ++doctori;
                    doc_salariu += it->getEmployee(i).mSalary;
                }
            else if (it->getType() == "PoliceStation")
                for (uint16_t i = 0; i < it->getEmployeesSize(); ++i) {
                    ++politai;
                    pol_salariu += it->getEmployee(i).mSalary;
                }
    }

    if (doctori == 0)
        std::cout << "Average salary for doctors: " << doctori << "\n";
    else
        std::cout << "Average salary for doctors: " << doc_salariu/doctori << "\n";

    if (politai == 0)
        std::cout << "Average salary for cops: " << politai << "\n";
    else
        std::cout << "Average salary for cops: " << pol_salariu/politai << "\n";

    for (const auto& it : cladiri)
        if (it->getType() == "CityHall")
            if (it->getCoordinator().mSalary != 0) {
                ++primari;
                prim_salariu += it->getCoordinator().mSalary;
            }

    if (primari == 0)
        std::cout << "Average salary for mayors: " << primari << "\n";
    else
        std::cout << "Average salary for mayors: " << prim_salariu/primari << "\n";

    for (const auto& it : cladiri)
        if (it->getType() == "CityHall")
            for (uint16_t i = 0; i < it->getCitizensSize(); ++i) {
                ++acoliti;
                acol_salariu += it->getCitizen(i).mSalary;
            }

    if (acoliti == 0)
        std::cout << "Average salary for city hall employees: " << acoliti << "\n";
    else
        std::cout << "Average salary for city hall employees: " << acol_salariu/acoliti << "\n";

    for (const auto& it : cladiri)
        if (it->getType() == "PoliceStation")
            for (uint16_t i = 0; i < it->getCitizensSize(); ++i) {
                ++puscariasi;
                varste_puscariasi += it->getCitizen(i).mAge;
            }

    if (puscariasi == 0)
        std::cout << "Average age of busted in police stations: " << puscariasi << "\n";
    else
        std::cout << "Average age of busted in police stations: " << (double) varste_puscariasi/puscariasi << "\n";

    for (const auto& it : cladiri)
        if (it->getType() == "House")
            std::cout << "Number of people in House " << it->getBuildingName() << ": " << it->getCitizensSize() << "\n";
        else if (it->getType() == "Block") {
            uint16_t blocari = 0;
            for (uint16_t i = 0; i < it->getCitizensSize(); ++i)
                if (it->getCitizen(i) != Person())
                    ++blocari;
            if (it->getCoordinator() != Person())
                std::cout << "Number of people in Block " << it->getBuildingName() << ": " << blocari + 1 << "\n";
            else
                std::cout << "Number of people in Block " << it->getBuildingName() << ": " << blocari << "\n";
        }

    std::set<std::string> nume_admin_case;
    std::set<std::string> nume_admin_blocuri;
    std::set<std::string> admin_ambele;

    uint8_t nr_admin = 0;

    for (const auto& it : cladiri)
        if (it->getCoordinator() != Person()) {
            ++nr_admin;
            if (it->getType() == "House")
                nume_admin_case.insert(it->getCoordinator().mName);
            else if (it->getType() == "Block")
                nume_admin_blocuri.insert(it->getCoordinator().mName);
        }

    for (const auto& it : nume_admin_case)
        for (const auto& it1 : nume_admin_blocuri)
            if (it1 == it) {
                ++nr_admin;
                admin_ambele.insert(it1);
            }

    if (nr_admin == 0 || nume_admin_case.empty() || nume_admin_blocuri.empty())
        std::cout << "Administrators of house and block: Nobody\n";
    else {
        std::cout << "Administrators of house and block: ";
        for (const auto& it : admin_ambele)
            std::cout << it << " ";
    }

    return 0;
}