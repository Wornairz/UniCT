/*
    Corso Blockchain e Cryptocurrencies - Compito di laboratorio del 12/07/2021

    Scrivere un contratto `CorporateManagement` che implementi l'interfaccia `CorporateManagementSpecs`
    per la gestione delle decisioni di una società sulla piattaforma Ethereum usando il linguaggio Solidity.

    All'interno della società ci possono essere una serie di soci (associates): il primo è il fondatore che
    crea il contratto stesso con relativa quota (share). Gli altri soci si possono auto-candidare depositando
    una quota sufficiente: tale candidatura viene considerata accettata solo se accettata a maggioranza dai
    soci attuali. Ogni socio può depositare una generica proposta, consistente in una semplice descrizione
    testuale: essa sarà considerata accettata se votata a maggioranza dai soci. Il voto per maggioranza (50% + 1)
    tiene conto del peso della quota in ETH depositata da ogni socio.
    La società, su proposta di qualche socio, può essere anche sciolta purché la risoluzione venga votata 
    all'unanimità.

    Di seguito alcuni dettagli sui singoli elementi obbligatori dell'interfaccia:
    - tutti i casi illustrati sopra vengono considerti come proposte da accettare: le tipologie di proposte 
      corrispondono all'enumerazione `ProposalCategory`;
    - il primo socio (fondatore) crea il contratto specificando la quota minima e versando, contestualmente, la
      propria di quota sufficiente;
    - il metodo `depositFunds` può essere usato da chiunque per auto-candidarsi a socio, versando la relativa
      sufficiente quota; il metodo può essere usato sia dai soci che da candidati-soci per aumentare la propria 
      quota;
    - il metodo `voteProposal`, utilizzabile solo dai soci effettivi, può essere usato per aderire, con la propria
      quota, all'accettazione della proposta tramite l'apposito identificativo; ovviamente un socio può votare una
      sola volta per ogni singola proposta, tale metodo dovrà anche verificare se la proposta ha raggiunto i voti 
      necessari e far scaturire i relativi effetti;
    - i metodi `depositGenericProposal` e `depositDissolutionProposal` permettono, unicamente ai soci, di depositare,
      rispettivamente, una generica proposta con descrizione testuale o una proposta di scioglimento;
    - nel caso in cui una proposta di scioglimento venga accettata all'unanimità la società va in liquidazione e pertanto
      nessuna funzionalità avrà più effetti ad eccezione del metodo `requestShareRefunding` che permette al singolo
      socio di riscuotere la propria quota;
    - i predicati `isAssociated` e `isDissoluted` permettono, rispettivamente, di verificare se un indirizzo specificato
      corrisponde ad un socio effettivo o se la società è in scioglimento;
    - gli eventi di tipo `New...` dovranno essere generati quando una proposta viene creata a seguito di un'azione 
      esterna; depositare dei fondi sufficienti da parte di un non-socio rappresenta una proposta di candidatura;
    - gli eventi di tipo `Accepted....` dovranno essere generati ogniqualvolta una relativa proposta viene accettata;
      notare che all'atto della creazione della società il socio fondatore è implicitamente accettato.
    
    Il contratto dovrà occuparsi di validare gli input ricevuti secondo criteri ovvi di sensatezza.

*/

// SPDX-License-Identifier: None

pragma solidity ^0.8.0;

interface CorporateManagementSpecs {
    enum ProposalCategory {
        NewAssociationAcceptance,
        Generic,
        CorporateDissolution
    }

    /* constructor(uint minimumAssociatingShare) payable */

    function depositFunds() external payable;
    function voteProposal(uint proposalId) external;
    function depositGenericProposal(string calldata description) external;
    function depositDissolutionProposal() external;
    function requestShareRefunding() external;
    function isAssociated(address id) external returns (bool);
    function isDissoluted() external returns (bool);

    event NewAssociateCandidate(uint proposalId, address id);
    event NewGenericProposal(uint proposalId, string description);
    event NewDissolutionProposal(uint proposalId);
    event AcceptedAssociate(address id);
    event AcceptedGenericProposal(string description);
    event AcceptedCorporateDissolution();
}
