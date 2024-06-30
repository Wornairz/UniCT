/*
    Corso Blockchain & Cryptocurrencies - Compito di laboratorio del 24/06/2022

    Scrivere un contratto `MafiaToken` che implementi sia l'interfaccia standard `ERC20`, vista a lezione, che 
    quella addizionale `MafiosoTokenSpecs` che realizzi, usando il linguaggio Solidity, un 
    "particolare token" sulla piattaforma Ethereum.

    I metodi standard dell'interfaccia `ERC20` hanno i seguenti compiti:
    - `totalSupply`: fornisce il totale dei token in circolazione;
    - `balanceOf`: fornisce l'ammontare di token associati ad uno specifico indirizzo;
    - `transfer`: trasferisce all'indirizzo `recipient` l'ammontare specificato attingendo dal conto del 
      chiamante;
    - `approve`: autorizza l'indirizzo `delegate` a spendere al piu' l'ammontare specificato attingendo dal
      conto del chiamante;
    - `transferFrom`: trasferisce all'indirizzo `recipient` l'ammontare specificato (purche' pre-autorizzato
      tramite `approve`) attingendo dal conto dell'indirizzo `spender`;
    - `allowance`: riporta l'ammontare pre-autorizzato per delega (vedi `approve`) da `owner` a favore di 
      `delegate`.

    Passando all'interfaccia `MafiosoTokensSpecs`: questa prevede di identificare come "padrino" (godfather)
    il proprietario/creatore del contratto e dal riservargli alcune azioni previste tra cui: `addPicciotto`, 
    `removePicciotto`, `setPizzoRate`, `setPicciottiPerChildSalary` e `forgeNewTokens`. 
    Viene anche gestito un gruppo di utenti speciali detti "picciotti" che unicamente il padrino puo' gestire.
    A tale gruppo sono permesse alcune azioni e ricevono uno "stipendio" mensile dal padrino. Lo stipendio
    mensile di un picciotto e' pari "(n + 1) x 'PerChildSalary'", dove 'PerChildSalary' e' il valore 
    impostato dal metodo `setPicciottiPerChildSalary`.

    In particolare:
    - `forgeNewTokens`, utilizzabile solo dal padrino, creano nuovi token e li accredita allo stesso;
    - `stealTokens`, utilizzabile dal padrino e dai picciotti, puo' essere usato per "rubare" token 
      all'indirizzo `robbed` specificato; non si puo' rubare al padrino stesso;
    - tramite `pizzoRate` e `setPizzoRate` e' possibile consultare e impostare, quest'ultimo solo da 
      parte del padrino, la percentuale che lo stesso trattiene ad ogni trasferimento effettuato tramite 
      i metodi standard `transfer` e `transferFrom`; la percentuale e' espressa come un intero tra 0 e 100;
    - tramite `picciottiSalary` e `setPicciottiPerChildSalary` e' possibile consultare e impostare, 
      quest'ultimo solo da parte del padrino, l'ammontare in token che lo stesso paghera' mensilmente agli 
      stessi; il metodo `triggerMonthlyPicciottiSalary`, invocabile da chiunque e in qualunque momento, 
      effettuera' il pagamento a tutti gli attuali picciotti, con periodicita' di 30 giorni, usando come 
      data di riferimento quella di creazione del contratto. 
      Il salario  mensile per figlio predefinito alla creazione del contratto e' di 100 token più una base di
      altri 100 token.

    L'evento standard `Approve` dovra' essere emesso in occasione di una pre-autorizzazione al transferimento e
    quello `Transfer` ogni qualvolta si configuri un trasferimento di proprieta' di token: anche per i metodi
    dell'interfaccia `MafiosoTokenSpecs`.
    
    Il contratto dovrà occuparsi di validare gli input ricevuti secondo criteri ovvi di sensatezza.

    Declaration: we don't like Mafia, we are just making fun of it!
    
*/

// SPDX-License-Identifier: None

pragma solidity ^0.8.0;

/* https://eips.ethereum.org/EIPS/eip-20 */
interface ERC20 {
    function totalSupply() external view returns (uint256);
    function balanceOf(address account) external view returns (uint256);
    function transfer(address recipient, uint256 amount) external returns (bool);
    function allowance(address owner, address delegate) external view returns (uint256);
    function approve(address delegate, uint256 amount) external returns (bool);
    function transferFrom(address sender, address recipient, uint256 amount) external returns (bool);

    event Transfer(address indexed from, address indexed to, uint256 value);
    event Approval(address indexed owner, address indexed delegate, uint256 value);
}

interface MafiosoTokenSpecs {
  /* constructor(uint initialSupply) */

  function godfather() external view returns (address);
  function picciotti() external view returns (address[] memory);
  function addPicciotto(address id, uint8 children) external;
  function removePicciotto(address id) external;
  function forgeNewTokens(uint additionalSupply) external;
  function stealTokens(address robbed, uint amount) external;
  function pizzoRate() external view returns (uint8);
  function setPizzoRate(uint8 rate) external;
  function picciottiSalary() external view returns (uint);
  function setPicciottiPerChildSalary(uint amount) external;
  function triggerMonthlyPicciottiSalary() external;
}
