/*
  ## Blockchain & Cryptocurrencies -  Compito di laboratorio del 30/06/2023

  ##############################################################################

  Scrivere un contratto `BingoGame` che implementi l'interfaccia `BingoGameSpecs`
  utilizzando il linguaggio Solidity per una partita di Bingo sulla piattaforma 
  Ethereum.

  In una partita di Bingo c'è una fase preliminare di prenotazione durante la 
  quale chiunque può acquistare alcune schede pagando in crediti Ether. Nella 
  successiva "fase estrattiva", ad ogni estrazione di numeri, tutte le schede
  vengono verificate cercando i vincitori dei due unici premi previsti:
  - premio "fila di cinque" corrispondente al 30% del montepremi in Ether
    incassato attraverso la vendita delle schede;
  - premio finale "Bingo" corrispondente al 70%.
  Sulla stessa estrazione più di un giocatore potrebbe raggiungere lo stesso 
  obiettivo (ex-aequo): in tal caso il sistema suddividerà in parti uguali 
  l'importo del premio da assegnare. Una scheda è composta da 3 file di 5 numeri
  senza duplicati sull'intera scheda. I numeri estratti appartengono 
  all'intervallo 1-75 (standard Americano).

  Il proprietario del contratto determina la durata del periodo di prenotazione
  e il costo di una singola scheda (un importo strettamente positivo in Wei).

  Nella fase di `Booking` chiunque può utilizzare il metodo `buyCards` per
  ottenerne un certo numero di schede: il numero esatto è determinato,
  arrotondando per difetto, dalla quantità di crediti trasferiti (ad esempio,
  trasferendo 900 Wei si ottengono 4 schede se il costo per la scheda è di 200).
  Il metodo può essere utilizzato più volte dallo stesso giocatore purché
  la fase preliminare non sia già conclusa. Le schede assegnate sono generate
  casuale rispettando le specifiche (3x5 numeri senza duplicati).
  Il metodo `buyCards` attiva l'evento `PurchaseOfCards` o uno dei seguenti
  errori: `BookingPeriodAlreadyExpired`, `GameAlreadyEnded` o
  `InsufficientFundsToBuyEvenACard`.

  Nella successiva fase di `Extraction` chiunque può attivare l'estrazione di
  del numero successivo utilizzando il metodo pubblico `extractNextNumber`.
  Il numero, compreso tra 1 e 75 e diverso dai precedenti, viene estratto a caso
  e tutte le schede vengono controllate alla ricerca delle condizioni per 
  assegnare uno dei due premi (se ancora disponibile). L'evento 
  `NumberExtraction` viene sempre attivato riportando anche il numero di
  schede corrispondenti. Se uno dei due premi viene vinto (da un singolo o da un
  gruppo di giocatori) viene lanciato l'evento corrispondente
  (`FiveInARowHasBeenWon` o `BingoHasBeenWon`). In quest'ultimo caso il gioco è
  considerato `Ended`, l'importo del premio (o il suo frazionamento in caso
  di ex-aequo) viene corrisposto al vincitore con il trasferimento dei
  corrispondenti Ether sulla piattaforma Ethereum e l'evento `PrizePayed` viene
  attivato. Il metodo `extractNextNumber` potrebbe anche attivare uno dei
  seguenti errori: `ExtractionPhaseNotYetStarted` o `GameAlreadyEnded`.

  Il contratto deve implementare anche le seguenti funzioni ausiliaria in sola
  lettura:
  - `getCardCost`, `getGameState`, `getNumberOfPlayers` e `getNumberOfCards` con
     i loro ovvi significati;
  - `getMyCards` che riporta un elenco delle schede possedute dal chiamante o
    o attiva l'errore `EnquirerIsNotAGamer`;
  - `isItExtracted` che consente di verificare se un numero specifico è stato
    già estratto o che genera l'errore `ExtractionPhaseNotYetStarted`.

  Infine il contratto dovrà occuparsi di convalidare i pochi input ricevuti
  secondo ovvi criteri di sensatezza.

  Suggerimento: per generare un numero casuale (non del tutto imprevedibile) si
  può usare qualcosa come:
  `uint256(keccak256(abi.encode(block.timestamp, block.difficulty)))`
*/ 

// SPDX-License-Identifier: None

pragma solidity ^0.8.0;

interface BingoGameSpecs {
  /* constructor(uint bookingPeriodInHours, uint cardCost); */

  struct Card {
      uint8 [5][3] cells; /* 3 righe di 5 colonne */
  }
  enum GameState {Booking, Extraction, Ended}
  
  function buyCards() payable external;
  function extractNextNumber() external returns (uint8 number);

  function getCardCost() external view returns (uint cost);
  function getGameState() external view returns (GameState state);
  function getNumberOfPlayers() external view returns (uint players);
  function getNumberOfCards() external view returns (uint cards);
  function getMyCards() external view returns (Card[] memory cards);
  function isItExtracted(uint8 number) external view returns (bool);
 
  event PurchaseOfCards(address buyer, uint numberOfCards);
  event NumberExtraction(uint8 number, uint matchingCards);
  event FiveInARowHasBeenWon(uint prizeAmount, uint numberOfWinners);
  event BingoHasBeenWon(uint prizeAmount, uint numberOfWinners);
  event PrizePayed(uint prizeAmount, address winner);

  error BookingPeriodAlreadyExpired();
  error ExtractionPhaseNotYetStarted(uint secondsToGo);
  error GameAlreadyEnded();
  error InsufficientFundsToBuyEvenACard(uint providedFunds, uint cardCost);
  error EnquirerIsNotAGamer();
}
