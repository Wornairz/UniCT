
/*
  ## Corso Blockchain & Cryptocurrencies - Compito di laboratorio del 02/09/2022

  ##############################################################################

  Scrivere un contratto `UnblindElection` che implementi l'interfaccia 
  `UnblindElectionSpecs` usando il linguaggio Solidity per creare un sistema 
  di elezioni con un singolo vincitore sulla piattaforma Ethereum.

  Una elezione prevede un insieme di elettori (`Voters`) che possono esprimere 
  il proprio voto; in una prima fase qualunque elettore può candidarsi e, 
  ricevuta l'accettazione, ricevere voti nella fase successiva di voto.

  Il creatore del contratto (`President`) deciderà quanti giorni dureranno,
  rispettivamente, le fasi di candidatura e di voto. Stabilirà anche un 
  quorum minimo percentuale (un intero tra 0 e 99) che una elezione valida 
  dovrà raggiungere.
  Solo il presidente potrà registrare gli elettori tramite i metodi `addVoter` e
  `addVoters`, riportando eventualmente l'errore `PresidentReservedAction`.

  Nella fase di candidatura chiunque può candidarsi o essere candidato tramite i 
  metodi `candidateMySelf` e `candidateSomeoneElse`. Questi potrebbero generare
  i seguenti errori: `CandidationPhaseAlreadyClosed` o `CandidateHasToBeAVoter`.
  Solo il presidente, in tutte le fasi, può accettare una candidatura tramite
  i metodi `acceptCandidation` e `acceptCandidations`; questi metodi genereranno
  l'evento `AcceptedCandidation` o un dei seguenti errori: `ItIsNotACandidate` o
  `PresidentReservedAction`.
  Chiunque può ottenere la lista dei candidati attualmente accettati tramite il
  metodo `getAcceptedCandidates`.

  Nella fase successiva di voto qualunque votante noto può usare il metodo
  `vote` per esercitare il proprio diritto di voto: solo un candidato accettato
  potrà essere votato e si potrà esprimere solo un voto per l'intera elezione.
  Il metodo potrebbe generare i seguenti errori: `VotingPhaseNotYetOpen`, 
  `VotingPhaseAlreadyClosed`, `OnlyKnownVotersCanVote`, 
  `OnlyAcceptedCandidatesCanBeVoted` o `OnlyOneVotePerVoter`.

  Quando la fase di voto sarà chiusa il presidente potrà usare metodo 
  `closeElection` per emanare il risultato: affinché una elezione sia ritenuta
  valida dovranno sussistere tutte le seguenti condizioni:
  - ci dovrà essere almeno un votante noto introdotto dal presidente;
  - ci dovrà essere stato almeno un candidato accettato dal presidente;
  - si dovrà essere registrato almeno un voto valido;
  - il vincitore dovrà avere almeno un voto di scarto rispetto all'eventuale
    secondo (non ci possono essere ex aequo).
  Il metodo generare l'evento `ElectionRegularlyClosed` o uno dei seguenti
  errori: `ElectionClosedWithoutQuorum` o `ElectionClosedWithAnInvalidResult`.

  Infine il contratto dovrà occuparsi di validare gli input ricevuti secondo
  criteri ovvi di sensatezza.
*/ 

// SPDX-License-Identifier: None

pragma solidity ^0.8.0;

interface UnblindElectionSpecs {
  /* constructor(uint candidationDays, uint votingDays, uint8 quorumPercent); */

  function addVoter(address voter) external;
  function addVoters(address[] calldata voters) external;
  function candidateMySelf() external;
  function candidateSomeoneElse(address candidate) external;
  function acceptCandidation(address candidate) external;
  function acceptCandidations(address[] calldata candidates) external;
  function getAcceptedCandidates() external view returns (address[] memory candidates);
  function vote(address candidate) external;
  function closeElection() external returns (bool valid);

  error PresidentReservedAction();
  error CandidationPhaseAlreadyClosed();
  error CandidateHasToBeAVoter();
  error ItIsNotACandidate();
  error VotingPhaseNotYetOpen();
  error VotingPhaseAlreadyClosed();
  error VotingPhaseNotYetClosed();
  error OnlyKnownVotersCanVote();
  error OnlyAcceptedCandidatesCanBeVoted();
  error OnlyOneVotePerVoter();
  error ElectionClosedWithoutQuorum();
  error ElectionClosedWithAnInvalidResult();

  event AcceptedCandidation(address candidate);
  event ElectionRegularlyClosed(address winner);
}
