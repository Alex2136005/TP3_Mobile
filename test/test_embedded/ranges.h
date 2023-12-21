#ifndef RANGES_H
#define RANGES_H

class ranges
{
    private:
    public:
       static constexpr  const char* json =
        R"({
            "ranges": [
                {
                "min": 0,
                "max": 50,
                "label": "Bon",
                "color": "009982",
                "health_effect": "La qualité de l’air est considérée comme satisfaisante et la pollution de l’air pose peu ou pas de risque.",
                "note": "Aucune."
                },
                {
                "min": 51,
                "max": 100,
                "label": "Modéré",
                "color": "ecde2b",
                "health_effect": "La qualité de l’air est acceptable; cependant, pour certains polluants, il peut y avoir un problème de santé modéré pour un très petit nombre de personnes qui sont inhabituellement sensibles à la pollution atmosphérique.",
                "note": "Les enfants et les adultes actifs, ainsi que les personnes souffrant de maladies respiratoires, telles que l’asthme, devraient limiter les efforts prolongés à l’extérieur."
                },
                {
                "min": 101,
                "max": 150,
                "label": "Mauvais pour les groupes sensibles",
                "color": "ff991e",
                "health_effect": "Les membres de groupes sensibles peuvent subir des effets sur la santé. Le grand public ne sera probablement pas affecté.",
                "note": "Les enfants et les adultes actifs, ainsi que les personnes souffrant de maladies respiratoires, telles que l’asthme, devraient limiter les efforts prolongés à l’extérieur."
                },
                {
                "min": 151,
                "max": 200,
                "label": "Mauvais pour la santé",
                "color": "b00085",
                "health_effect": "Tout le monde peut commencer à ressentir des effets sur la santé; les membres de groupes sensibles peuvent subir des effets plus graves sur la santé.",
                "note": "Les enfants et les adultes actifs, ainsi que les personnes souffrant de maladies respiratoires, telles que l’asthme, devraient éviter les efforts prolongés à l’extérieur; tout le monde, en particulier les enfants, devrait limiter les efforts prolongés à l’extérieur."
                },
                {
                "min": 201,
                "max": 300,
                "label": "Très mauvais pour la santé",
                "color": "ff000b",
                "health_effect": "Avertissements sanitaires des conditions d’urgence. La population entière est plus susceptible d’être touchée.",
                "note": "Les enfants et les adultes actifs, ainsi que les personnes souffrant de maladies respiratoires, comme l’asthme, devraient éviter tout effort extérieur; tout le monde, en particulier les enfants, devrait limiter les efforts à l’extérieur."
                },
                {
                "min": 300,
                "max": 10000,
                "label": "Dangereux",
                "color": "ff000b",
                "health_effect": "Alerte santé: tout le monde peut subir des effets sanitaires plus graves.",
                "note": "Tout le monde devrait éviter tout effort extérieur."
                }
            ]
        })";
};

#endif

