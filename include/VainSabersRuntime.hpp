#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Color.hpp"
#include "GlobalNamespace/Saber.hpp"
#include <vector>

// Déclaration de la classe personnalisée qui sera enregistrée dans l'IL2CPP de Unity
DECLARE_CLASS_CODEGEN(VainSabers, VainSabersRuntime, UnityEngine::MonoBehaviour,
    
    // Attributs internes de la classe
    DECLARE_INSTANCE_FIELD(GlobalNamespace::Saber*, targetSaber);
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, tipTransform);
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, baseTransform);
    
    // Paramètres de configuration du mod (équivalents aux propriétés PC)
    DECLARE_INSTANCE_FIELD(int, blurCount);
    DECLARE_INSTANCE_FIELD(float, blurSoftness);
    DECLARE_INSTANCE_FIELD(UnityEngine::Color, saberColor);

    // Méthodes Unity standard
    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, Update);

    public:
        // Méthode d'initialisation personnalisée appelée lors du Hook
        void Initialize(GlobalNamespace::Saber* saber, int blurCount, float softness, UnityEngine::Color color);
        
    private:
        // Structure pour stocker l'historique des positions pour le calcul du flou cinétique
        struct SaberFrameData {
            UnityEngine::Vector3 tipPos;
            UnityEngine::Vector3 basePos;
        };
        std::vector<SaberFrameData> history;
        void ApplyMotionBlur();
)