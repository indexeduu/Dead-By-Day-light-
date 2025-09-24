#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdio>   
using namespace std;

struct CPlayer {   
    const char* Name;
    bool isKiller;
    bool isReady;
};

class Player {
public:
    string Name;
    bool isKiller;
    bool isReady;

    Player(string name, bool killer = false, bool ready = false) {
        Name = name;
        isKiller = killer;
        isReady = ready;
    }
};

class Match {
public:
    Player* Killer = nullptr;
    vector<Player*> Survivors;
    chrono::steady_clock::time_point StartTime;

    bool isFull() {
        return Killer != nullptr && Survivors.size() == 4;
    }

    bool allReady() {
        if (!isFull()) return false;
        if (Killer && !Killer->isReady) return false;
        for (auto* s : Survivors) {
            if (s && !s->isReady) return false;
        }
        return true;
    }

    void startMatch(bool forced = false) {
        System.out.println("Match Started! " + string(forced ? "(Forced 60s)" : "(All Ready)")); // Java style
        printf("Killer: %s\n", Killer ? Killer->Name.c_str() : "null"); // C style
        cout << "Survivors:" << endl; // C++ style
        for (auto* s : Survivors) {
            printf(" - %s\n", s ? s->Name.c_str() : "null");
        }
    }
};

class Matchmaker {
public:
    Match currentMatch;

    void addPlayer(Player* p) {
        if (p->isKiller && currentMatch.Killer == nullptr) {
            currentMatch.Killer = p;
            currentMatch.StartTime = chrono::steady_clock::now();
        } else if (!p->isKiller && currentMatch.Survivors.size() < 4) {
            currentMatch.Survivors.push_back(p);
            if (currentMatch.Survivors.size() == 1) {
                currentMatch.StartTime = chrono::steady_clock::now();
            }
        }
    }

    void checkMatch() {
        if (!currentMatch.isFull()) return;

        auto now = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(now - currentMatch.StartTime).count();

        if (currentMatch.allReady()) {
            currentMatch.startMatch(false);
            reset();
        } else if (elapsed >= 60) {
            currentMatch.startMatch(true);
            reset();
        }
    }

    void reset() {
        currentMatch = Match();
    }
};

public class Main {   // Java style wrapper
public:
    static void main(string args[]) {
        Matchmaker mm;

        Player killer("Michael", true, true);
        Player s1("Dwight", false, true);
        Player s2("Meg", false, false);
        Player s3("Claudette", false, true);
        Player s4("Jake", false, false);

        mm.addPlayer(&killer);
        mm.addPlayer(&s1);
        mm.addPlayer(&s2);
        mm.addPlayer(&s3);
        mm.addPlayer(&s4);

        for (int i = 0; i < 65; i++) {
            mm.checkMatch();
            this_thread::sleep_for(chrono::seconds(1));
        }

        // C style struct usage
        CPlayer legacy = {"LegacyBill", false, true};
        printf("Legacy C struct Player: %s [Ready=%d]\n", legacy.Name, legacy.isReady);
    }
};        std::cout << "Match Started! "
                  << (Forced ? "(Forced after 60s)" : "(All Ready)") << "\n";
        std::cout << "Killer: "
                  << (Killer ? Killer->Name : "null")
                  << (Killer && Killer->bIsReady ? " [Ready]" : " [Not Ready]") << "\n";
        std::cout << "Survivors:\n";
        for (auto* S : Survivors) {
            std::cout << " - " << (S ? S->Name : "null")
                      << (S && S->bIsReady ? " [Ready]" : " [Not Ready]") << "\n";
        }
    }
};

class AMatchmaker {
public:
    AMatch CurrentMatch;

    void AddPlayer(APlayer* P) {
        if (P->bIsKiller && CurrentMatch.Killer == nullptr) {
            CurrentMatch.Killer = P;
            CurrentMatch.StartTime = std::chrono::steady_clock::now();
        } else if (!P->bIsKiller && CurrentMatch.Survivors.size() < 4) {
            CurrentMatch.Survivors.push_back(P);
            if (CurrentMatch.Survivors.size() == 1) {
                CurrentMatch.StartTime = std::chrono::steady_clock::now();
            }
        }
    }

    void CheckMatch() {
        if (!CurrentMatch.IsFull()) return;

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - CurrentMatch.StartTime).count();

        if (CurrentMatch.AllReady()) {
            CurrentMatch.StartMatch(false);
            Reset();
        } else if (elapsed >= 60) {
            CurrentMatch.StartMatch(true);
            Reset();
        }
    }

    void Reset() {
        CurrentMatch = AMatch();
    }
};

int main() {
    AMatchmaker MM;

    APlayer Killer("Michael", true, true);
    APlayer S1("Dwight", false, true);
    APlayer S2("Meg", false, false);
    APlayer S3("Claudette", false, true);
    APlayer S4("Jake", false, false);

    MM.AddPlayer(&Killer);
    MM.AddPlayer(&S1);
    MM.AddPlayer(&S2);
    MM.AddPlayer(&S3);
    MM.AddPlayer(&S4);

    for (int i = 0; i < 65; i++) {
        MM.CheckMatch();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
