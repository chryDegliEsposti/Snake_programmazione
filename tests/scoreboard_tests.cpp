#include <cassert>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <type_traits>

#include "scoreBoard/ScoreBoard.hpp"

namespace fs = std::filesystem;

// ---- dimensioni derivate dalla tua classe ----
static constexpr size_t LEVELS =
    std::extent<decltype(scoreBoard::levelScores), 0>::value; // 30
static constexpr size_t TOP =
    std::extent<decltype(scoreBoard::levelScores), 1>::value; // 10

// === Utility comuni ===
static scoreBoard::DataPlayer makePlayer(const char* name, int s) {
    scoreBoard::DataPlayer p{};
    std::strncpy(p.name, name, 3); // 3 char + '\0'
    p.name[3] = '\0';
    p.score = s;
    return p;
}

static void resetLevel(scoreBoard& sb, int level) {
    for (size_t i = 0; i < TOP; ++i) {
        sb.levelScores[level][i] = scoreBoard::DataPlayer{{'\0','\0','\0','\0'}, 0};
    }
}

static bool equalTopN(const scoreBoard::DataPlayer* a,
                      const scoreBoard::DataPlayer* b) {
    for (size_t i = 0; i < TOP; ++i) {
        if (a[i].score != b[i].score) return false;
        if (std::strncmp(a[i].name, b[i].name, 4) != 0) return false;
    }
    return true;
}

// RAII per salvare e ripristinare l'eventuale file "scoreboard"
struct ScoreboardFileGuard {
    const char* path = "scoreboard";
    fs::path backup;

    ScoreboardFileGuard() {
        try {
            if (fs::exists(path)) {
                backup = fs::path(path).concat(".bak");
                fs::copy_file(path, backup, fs::copy_options::overwrite_existing);
            }
        } catch (...) {
            std::cerr << "[WARN] impossibile fare il backup del file 'scoreboard'\n";
        }
    }
    ~ScoreboardFileGuard() {
        try {
            if (!backup.empty() && fs::exists(backup)) {
                fs::copy_file(backup, path, fs::copy_options::overwrite_existing);
                fs::remove(backup);
            } else {
                if (fs::exists(path)) fs::remove(path);
            }
        } catch (...) {
            std::cerr << "[WARN] impossibile ripristinare il file 'scoreboard'\n";
        }
    }
};

// ===================
// Test saveScore (TOP=10)
// ===================
static void testInsertFirst() {
    scoreBoard sb{};
    resetLevel(sb, 0);

    scoreBoard::saveScore(0, makePlayer("AAA", 100), &sb);

    assert(sb.levelScores[0][0].score == 100);
    assert(std::string(sb.levelScores[0][0].name) == "AAA");
}

static void testKeepOrder() {
    scoreBoard sb{};
    resetLevel(sb, 0);

    // inseriamo 4 punteggi in ordine sparso
    scoreBoard::saveScore(0, makePlayer("AAA", 100), &sb);
    scoreBoard::saveScore(0, makePlayer("BBB", 250), &sb);
    scoreBoard::saveScore(0, makePlayer("CCC", 150), &sb);
    scoreBoard::saveScore(0, makePlayer("DDD", 200), &sb);

    // Atteso: BBB(250), DDD(200), CCC(150), AAA(100)
    assert(sb.levelScores[0][0].score == 250);
    assert(std::string(sb.levelScores[0][0].name) == "BBB");
    assert(sb.levelScores[0][1].score == 200);
    assert(std::string(sb.levelScores[0][1].name) == "DDD");
    assert(sb.levelScores[0][2].score == 150);
    assert(std::string(sb.levelScores[0][2].name) == "CCC");
    assert(sb.levelScores[0][3].score == 100);
    assert(std::string(sb.levelScores[0][3].name) == "AAA");
}

static void testOverflowTop10() {
    scoreBoard sb{};
    resetLevel(sb, 0);

    // Riempiamo i 10 slot con punteggi decrescenti
    // Nome "A0".."A9" (max 3 char)
    std::string lastName;
    for (size_t i = 0; i < TOP; ++i) {
        char nm[4] = {'A', char('0' + i), '\0', '\0'};
        lastName = nm; // l'ultimo sarà "A9"
        int sc = int((TOP - i) * 100); // 1000,900,...,100
        scoreBoard::saveScore(0, makePlayer(nm, sc), &sb);
    }

    // Inseriamo un punteggio troppo basso: non deve entrare
    scoreBoard::saveScore(0, makePlayer("ZZZ", 50), &sb);
    for (size_t i = 0; i < TOP; ++i) {
        assert(std::string(sb.levelScores[0][i].name) != "ZZZ");
    }

    // Inseriamo un punteggio altissimo: deve andare in cima
    scoreBoard::saveScore(0, makePlayer("HGH", 9999), &sb);
    assert(sb.levelScores[0][0].score == 9999);
    assert(std::string(sb.levelScores[0][0].name) == "HGH");

    // e l'ultimo precedente ("A9") deve essere uscito
    bool lastStillThere = false;
    for (size_t i = 0; i < TOP; ++i) {
        if (std::string(sb.levelScores[0][i].name) == lastName) lastStillThere = true;
    }
    assert(!lastStillThere);
}

static void testEqualScoresStability() {
    scoreBoard sb{};
    resetLevel(sb, 0);

    // Inseriamo più di 3 uguali, comunque <= TOP
    scoreBoard::saveScore(0, makePlayer("A", 100), &sb);
    scoreBoard::saveScore(0, makePlayer("B", 100), &sb);
    scoreBoard::saveScore(0, makePlayer("C", 100), &sb);
    scoreBoard::saveScore(0, makePlayer("D", 100), &sb);

    // Con punteggi uguali, il nuovo viene dopo (stabilità)
    assert(std::string(sb.levelScores[0][0].name) == "A");
    assert(std::string(sb.levelScores[0][1].name) == "B");
    assert(std::string(sb.levelScores[0][2].name) == "C");
    assert(std::string(sb.levelScores[0][3].name) == "D");
}

// ===================
// Test serialize/deserialize (TOP=10)
// ===================

// Crea una scoreboard di esempio con dati deterministici su tutti i livelli/top
static scoreBoard makeSampleScoreboard() {
    scoreBoard sb{};
    for (size_t lvl = 0; lvl < LEVELS; ++lvl) {
        for (size_t i = 0; i < TOP; ++i) {
            char n[4] = {
                char('A' + (lvl % 26)),
                char('0' + (i % 10)),
                '\0',
                '\0'
            };
            // punteggio distinto e ordinato (decrescente su i crescente)
            int sc = int((lvl + 1) * 1000 + (TOP - i) * 10);
            sb.levelScores[lvl][i] = makePlayer(n, sc);
        }
    }
    return sb;
}

static void testSerializeDeserializeRoundTrip() {
    ScoreboardFileGuard guard; // salva/restore del file reale
    scoreBoard original = makeSampleScoreboard();

    // 1) Serializza
    scoreBoard::serialize(original);

    // 2) Deserializza in un nuovo oggetto e confronta
    scoreBoard loaded{};
    // inizialmente diverso (almeno su un livello)
    assert(!equalTopN(original.levelScores[0], loaded.levelScores[0]));

    scoreBoard::deserialize(&loaded);

    // Confronto su più livelli
    for (int lvl : {0, 1, 5, 10, 29}) {
        assert(equalTopN(original.levelScores[lvl], loaded.levelScores[lvl]));
    }

    // 3) Controllo dimensione file = sizeof(levelScores)
    try {
        if (fs::exists("scoreboard")) {
            auto sz = fs::file_size("scoreboard");
            assert(sz == sizeof(original.levelScores));
        }
    } catch (...) {
        std::cerr << "[WARN] impossibile leggere la dimensione del file 'scoreboard'\n";
    }
}

static void testDeserializeWhenFileMissingKeepsData() {
    ScoreboardFileGuard guard; // ripristina alla fine

    // Assicura che il file non esista
    try {
        if (fs::exists("scoreboard")) fs::remove("scoreboard");
    } catch (...) {
        std::cerr << "[WARN] impossibile rimuovere 'scoreboard' per il test\n";
    }

    scoreBoard sb{};
    // Pre-carica valori per verificare che NON vengano sovrascritti
    sb.levelScores[0][0] = makePlayer("ZZZ", 999);
    sb.levelScores[0][TOP-1] = makePlayer("YYY", 111);

    scoreBoard::deserialize(&sb);

    // Dato che il file manca, i dati preesistenti devono rimanere invariati
    assert(sb.levelScores[0][0].score == 999);
    assert(std::string(sb.levelScores[0][0].name) == "ZZZ");
    assert(sb.levelScores[0][TOP-1].score == 111);
    assert(std::string(sb.levelScores[0][TOP-1].name) == "YYY");
}

// ===================
// MAIN
// ===================
int main() {
    // saveScore
    testInsertFirst();
    testKeepOrder();
    testOverflowTop10();
    testEqualScoresStability();

    // serialize/deserialize
    testSerializeDeserializeRoundTrip();
    testDeserializeWhenFileMissingKeepsData();

    std::cout << "Tutti i test (scoreBoard TOP-10) PASSATI!\n";
    return 0;
}
