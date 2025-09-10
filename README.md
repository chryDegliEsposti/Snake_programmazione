# Snake Game in C++

Questo è un progetto universitario di programmazione per un gioco Snake sviluppato in C++ utilizzando la libreria `ncurses`. Il progetto è stato realizzato da un team di tre persone, rispettando i vincoli e le specifiche fornite dai tutor del corso.

## Membri del Team

*   Cristian Di Nicola
*   Matteo Lombardo
*   Christian Degli Esposti

## Descrizione

Il gioco è una versione del classico Snake, implementato con un'interfaccia a riga di comando grazie alla libreria `ncurses`. L'obiettivo è guidare il serpente per mangiare il cibo che appare sullo schermo. Il gioco termina se il serpente si scontra con se stesso o se il tempo a disposizione scade.

## Funzionalità

*   **Menu Principale Interattivo**: Un menu di avvio per iniziare a giocare, visualizzare i punteggi o selezionare il livello.
*   **Livelli Multipli**: Il gioco include 20 livelli pre-configurati con difficoltà crescente (aumento della velocità e della lunghezza iniziale del serpente).
*   **Selezione del Livello**: Un'interfaccia grafica per scorrere e selezionare il livello da cui iniziare.
*   **Scoreboard**: Una classifica dei punteggi migliori per ogni livello, con salvataggio persistente su file (`scoreboard`).
*   **Gameplay a Tempo**: Ogni partita ha una durata massima di 5 minuti.
*   **Pausa**: È possibile mettere in pausa il gioco in qualsiasi momento.
*   **Grafica testuale**: Utilizzo di `ncurses` per creare un'esperienza di gioco visivamente piacevole nel terminale.

## Requisiti

*   Un compilatore C++ (come g++)
*   La libreria `ncurses`

## Come Compilare ed Eseguire

1.  **Installare le dipendenze**:
    Assicurarsi di avere `g++` e `ncurses` installati. Su sistemi basati su Debian/Ubuntu, è possibile installarli con:
    ```bash
    sudo apt-get update
    sudo apt-get install build-essential libncurses5-dev libncursesw5-dev
    ```

2.  **Compilare il progetto**:
    Navigare nella directory principale del progetto ed eseguire il seguente comando per compilare tutti i file sorgente e creare l'eseguibile:
    ```bash
    make
    ```

3.  **Eseguire il gioco**:
    Dopo la compilazione, avviare il gioco con:
    ```bash
    ./app
    ```

## Struttura del Progetto

```
.
├── run/
├── scoreboard
├── src/
│   ├── main.cpp
│   ├── debug/
│   │   └── print.hpp
│   ├── game/
│   │   ├── Game.cpp
│   │   ├── Game.hpp
│   │   ├── Snake.cpp
│   │   └── Snake.hpp
│   ├── Levels/
│   │   ├── levels.cpp
│   │   └── levels.hpp
│   ├── scoreBoard/
│   │   ├── ScoreBoard.cpp
│   │   └── ScoreBoard.hpp
│   └── view/
│       ├── graphicFuncs.cpp
│       ├── graphicFuncs.hpp
│       ├── levelGraphics.cpp
│       ├── levelGraphics.hpp
│       ├── mainMenu.cpp
│       └── mainMenu.hpp
└── tests/
    └── scoreboard_tests.cpp
```

### Descrizione delle Directory

*   `src/game`: Contiene la logica principale del gioco, inclusa la gestione del serpente e il game loop.
*   `src/Levels`: Gestisce la creazione e la navigazione tra i diversi livelli di gioco.
*   `src/scoreBoard`: Implementa la funzionalità di salvataggio, caricamento e visualizzazione dei punteggi.
*   `src/view`: Contiene tutto il codice relativo all'interfaccia utente e alla grafica `ncurses` (menu, schermate, ecc.).
*   `src/debug`: Utility per il debug.
*   `scoreboard`: File binario dove vengono salvati i punteggi.
*   `tests`: Contiene test unitari (attualmente per lo scoreboard).
