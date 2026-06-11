#include "VainSabersRuntime.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Time.hpp"

DEFINE_TYPE(VainSabers, VainSabersRuntime);

namespace VainSabers {

    void VainSabersRuntime::Awake() {
        // Initialisation par défaut si nécessaire
        this->blurCount = 4;
        this->blurSoftness = 0.5f;
        this->saberColor = UnityEngine::Color(1.0f, 1.0f, 1.0f, 1.0f);
    }

    void VainSabersRuntime::Initialize(GlobalNamespace::Saber* saber, int blurCount, float softness, UnityEngine::Color color) {
        this->targetSaber = saber;
        this->blurCount = blurCount;
        this->blurSoftness = softness;
        this->saberColor = color;

        if (saber) {
            // Récupération des points d'ancrage natifs du sabre (Pointe et Base)
            this->tipTransform = saber->get_saberBladeTipTransform();
            this->baseTransform = saber->get_saberBladeBaseTransform();
        }
    }

    void VainSabersRuntime::Update() {
        if (!tipTransform || !baseTransform) return;

        // 1. Enregistrement de la frame actuelle (Position de la pointe et de la base)
        SaberFrameData currentFrame;
        currentFrame.tipPos = tipTransform->get_position();
        currentFrame.basePos = baseTransform->get_position();

        history.insert(history.begin(), currentFrame);

        // On garde uniquement le nombre de frames nécessaires pour le flou (blurCount)
        if ((int)history.size() > blurCount) {
            history.pop_back();
        }

        // 2. Application de la logique d'effet visuel
        ApplyMotionBlur();
    }

    void VainSabersRuntime::ApplyMotionBlur() {
        if (history.size() < 2) return;

        // Logique de rendu du flou (Motion Blur / Trails) :
        // Sur Quest, au lieu d'instancier de lourds GameObjects PC pour chaque segment,
        // on interpole dynamiquement la position des textures/matériaux ou on étire le mesh.
        
        for (size_t i = 0; i < history.size(); i++) {
            float alpha = 1.0f - ((float)i / (float)history.size());
            // Exemple : On applique l'atténuation (softness) sur la couleur selon l'historique
            UnityEngine::Color segmentColor = saberColor;
            segmentColor.a *= (alpha * blurSoftness);

            // TODO: Injecter cette couleur modifiée dans le renderer ou le générateur de trail customisé
        }
    }
}