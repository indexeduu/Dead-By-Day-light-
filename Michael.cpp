struct FShapeConfig {
    float BaseSpeed = 4.6f;
    float AttackSpeed = 1.0f;
    float StalkRange = 20.0f;
    float StalkSlow = 0.65f;
    float StalkSlowWithPerk = 0.75f;
    int   MaxTargets = 5;

    struct FTier {
        float Speed;
        float TerrorRadius;
        int EvilRequired;
        float AttackSpeedBonus;
        float Duration;
    } Tier[3] = {
        {4.2f, 10.f,   0,  0.0f,  0.f},
        {4.4f, 15.f, 100,  0.0f,  0.f},
        {4.6f, 20.f, 200, +0.1f, 60.f}
    };
};

class AKiller_Michael : public AKillerBase {
public:
    FShapeConfig Config;
    int EvilProgress = 0;
    int CurrentTier = 1;
    bool bIsTier3Active = false;
    float AttackSpeed;

    AKiller_Michael() {
        AttackSpeed = Config.BaseSpeed;
    }

    void Stalk(ASurvivor* Target) {
        if (!Target) return;

        float dist = GetDistanceTo(Target);
        if (dist <= Config.StalkRange) {
            Target->ApplySlow(Config.StalkSlow);
            EvilProgress += 10;

            if (EvilProgress >= Config.Tier[1].EvilRequired && CurrentTier < 2) {
                OnTierUp(2);
            }
            if (EvilProgress >= Config.Tier[2].EvilRequired && CurrentTier < 3) {
                OnTierUp(3);
            }
        }
    }

    void OnTierUp(int NewTier) {
        CurrentTier = NewTier;
        SetSpeed(Config.Tier[NewTier-1].Speed);
        SetTerrorRadius(Config.Tier[NewTier-1].TerrorRadius);

        if (NewTier == 3) {
            bIsTier3Active = true;
            AttackSpeed += Config.Tier[2].AttackSpeedBonus;
            StartTimer("Tier3End", Config.Tier[2].Duration);
        }
    }

    void OnTimerEnd(std::string TimerName) {
        if (TimerName == "Tier3End") {
            bIsTier3Active = false;
            CurrentTier = 2;
            EvilProgress = 150;
            AttackSpeed = Config.BaseSpeed;
            SetSpeed(Config.Tier[1].Speed);
            SetTerrorRadius(Config.Tier[1].TerrorRadius);
        }
    }
};
