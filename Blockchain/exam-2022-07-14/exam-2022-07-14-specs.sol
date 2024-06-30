
/*
  ##  Corso Blockchain & Cryptocurrencies - Compito di laboratorio del 14/07/2022

  Scrivere un contratto `AuctionManager` che implementi l'interfaccia 
  `AuctionManagerSpecs` usando il linguaggio Solidity per creare un sistema di
  gestione di aste multiple sulla piattaforma Ethereum.

  Il sistema di gestione permettera' a chiunque di creare una nuova asta con
  `createNewAuction` fornendo una descrizione testuale, una eventuale offerta 
  minima e una durata in ore. Ogni asta avra' un proprio `id` univoco e sara' 
  sempre possibile conoscere la lista delle aste attualmente in corso usando
  `idsOfOngoingAuctions`. Chiunque potra' proporre una propria offerta su un'asta
  in corso usando `bidOnAuction` trasferendo gli ETH corrispondenti: tali
  crediti saranno trattenuti dal contratto fino alla conclusione dell'asta. 
  Sara' possibile usare piu' volte `bidOnAuction` per aumentare in modo
  cumulativo la propria offerta attuale.

  Tramite i metodi `auctionDescription`, `auctionMinimumBid`, `auctionExpiration`,
  `auctionBeneficiary`, `auctionState`, `auctionHighestBid`, `auctionHighestBidder`
  sara' sempre possibile richiedere informazioni circa qualunque asta valida
  (conclusa o in corso).

  Una volta scaduta l'asta chiunque potra' finalizzare l'esito tramite 
  `finalizeAuction`: tale metodo trasferira' al beneficiario l'ammontare 
  corrispondente all'offerta piu' alta e restituira' ai rispettivi proprietari i
  crediti delle offerte minori. In caso di offerte massime con lo stesso ammontare
  vincera' sempre l'offerta pervenuta per prima.
  
  Il creatore del contratto manager avra' la facolta' di utilizzare 
  `cancelAuction` per annullare un'asta purche' questa sia ancora in corso e
  non ancora scaduta: in tal caso tutti i crediti relativi a tutte le offerte
  verranno restituite ai relativi offerenti.

  Gli eventi `NewAuction`, `NewHighestBid`, `AuctionEndedWithWinner` e 
  `AuctionExpiredWithoutWinner` dovranno essere opportunamente generati durante
  le varie fasi dell'asta.

  I vari errori previsti dall'interfaccia dovranno essere tutti oppotunamente 
  generati dai metodi interessati.
    
  Infine il contratto dovrà occuparsi di validare gli input ricevuti secondo 
  criteri ovvi di sensatezza.
*/ 

// SPDX-License-Identifier: None

pragma solidity ^0.8.0;

interface AuctionManagerSpecs {
  enum AuctionState {Ongoing, EndedWithWinner, Expired, Canceled}

  function createNewAuction(string memory description, uint minimumBid, uint expirationInHours) external returns (uint id);
  function bidOnAuction(uint id) external payable returns (bool isHighest);
  function idsOfOngoingAuctions() external returns (uint[] memory ids);
  function auctionDescription(uint id) external view returns (string memory);
  function auctionMinimumBid(uint id) external view returns (uint amount);
  function auctionExpiration(uint id) external view returns (uint timestamp);
  function auctionBeneficiary(uint id) external view returns (address beneficiary);
  function auctionState(uint id) external returns (AuctionState);
  function auctionHighestBid(uint id) external view returns (uint amount);
  function auctionHighestBidder(uint id) external view returns (address bidder);
  function finalizeAuction(uint id) external;
  function cancelAuction(uint id) external;
  
  event NewAuction(string description, uint minimumBid, uint expiration);
  event NewHighestBid(uint auctionId, address bidder, uint amount);
  event AuctionEndedWithWinner(uint auctionId, address winner, uint amount);
  event AuctionExpiredWithoutWinner(uint auctionId);

  error AuctionNotExisting();
  error BidNotAboveMinimum(uint minimumBid);
  error AuctionAlreadyEnded(AuctionState state);
  error AuctionToFinalizeNotYetEnded(uint expiration);
  error AuctionToFinalizeAlreadyFinalized();
}
