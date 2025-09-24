#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

class APlayer {
public:
    std::string Name;
    bool bIsKiller;
    bool bIsReady;

    APlayer(std::string InName, bool InKiller = false, bool InReady = false)
        : Name(InName), bIsKiller(InKiller), bIsReady(InReady) {}
};

class AMatch {
public:
    APlayer* Killer = nullptr;
    std::vector<APlayer*> Survivors;
    std::chrono::steady_clock::time_point StartTime;

    bool IsFull() {
        return Killer != nullptr && Survivors.size() == 4;
    }

    bool AllReady() {
        if (!IsFull()) return false;
        if (Killer && !Killer->bIsReady) return false;
        for (auto* S : Survivors) {
            if (!S->bIsReady) return false;
        }
        return true;
    }

    void StartMatch(bool Forced = false) {
        std::cout << "Match Started! "
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
