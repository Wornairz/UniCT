// SPDX-License-Identifier: None

pragma solidity ^0.8.0;

import "./exam-2023-06-30-specs.sol";

contract BingoGame is BingoGameSpecs {

    GameState gameState;
    address[] players;
    mapping(address => Card[]) cards;
    uint256 immutable cardCost;
    uint256 immutable bookingPeriodExpiration;
    uint numberOfPlayers = 0;
    uint numberOfCards = 0;
    mapping (uint8 => bool) extracted;
    bool fiveInARowWon = false;
    address[] fiveInARowWinners;
    bool bingoWon = false;
    address[] bingoWinners;

    constructor(uint256 bookingPeriodInHours, uint256 cardUnitCost) {
        gameState = GameState.Booking;
        cardCost = cardUnitCost;
        bookingPeriodExpiration = block.timestamp + (bookingPeriodInHours * 60 * 60);
    }

    modifier onlyActiveGame {
        if(gameState == GameState.Ended) {
            revert GameAlreadyEnded();
        }
        _;
    }

    function buyCards() external payable onlyActiveGame {
        if(gameState != GameState.Booking) {
            revert BookingPeriodAlreadyExpired();
        }
        if(msg.value < cardCost) {
            revert InsufficientFundsToBuyEvenACard(msg.value, cardCost);
        }

        uint cardsToBuy = msg.value / cardCost;
        if(cards[msg.sender].length == 0) {
            players.push(msg.sender);
            numberOfPlayers++;
        }
        numberOfCards+=cardsToBuy;

        uint8[] memory cardsNumbers;
        for(uint i = 0; i<cardsToBuy; i++) {
            cardsNumbers = new uint8[](15);
            for(uint j = 0; j<15; j++) {
                bool isUnique = true;
                uint8 number;
                do {
                    number = uint8(uint256(keccak256(abi.encodePacked(block.timestamp, block.difficulty, j, i))) % 75);
                    for(uint k=0; k<j; k++) {
                        if(cardsNumbers[k] == number) {
                            isUnique = false;
                        }
                    }                
                } while(!isUnique);
                cardsNumbers[j] = number;
            }
            Card storage card = cards[msg.sender].push();
            for (uint l = 0; l < 15; l++) {
                uint row = l % 3;
                uint col = l / 3;
                card.cells[row][col] = cardsNumbers[l];
            }
        }
        emit PurchaseOfCards(msg.sender, cardsToBuy);
    }

    function extractNextNumber() external onlyActiveGame returns (uint8 number) {
        require(gameState == GameState.Extraction, "Not extraction phase");
        bool isUnique = true;
        uint i = 0;
        do {
            number = uint8(uint256(keccak256(abi.encodePacked(block.timestamp, block.difficulty, i++))) % 75);
            for(uint k=0; k<i; k++) {
                if(extracted[number]) {
                    isUnique = false;
                }
            }                
        } while(!isUnique);
        extracted[number] = true;

        uint matchingCards = 0;

        for (i = 0; i<players.length; i++) {
            address player = players[i];
            for(uint j = 0; j<cards[player].length; j++) {
                Card storage card = cards[player][j];
                uint8[] memory extractedForEachLine = new uint8[](3); 
                for(uint l = 0; l < 3; l++) {
                    for(uint k = 0; k<5; k++) {
                        if(extracted[card.cells[l][k]]) {
                            extractedForEachLine[l]++;
                            if(card.cells[l][k] == number) {
                                matchingCards++;
                            }
                        }
                    }
                }
                if(!fiveInARowWon && (extractedForEachLine[0] == 5 || extractedForEachLine[1] == 5 || extractedForEachLine[2] == 5)) {
                    fiveInARowWinners.push(player);
                }
                if(!bingoWon && extractedForEachLine[0] == 5 && extractedForEachLine[1] == 5 && extractedForEachLine[2] == 5) {
                    bingoWinners.push(player);
                }
            }
        }
        emit NumberExtraction(number, matchingCards);
        
        if(!fiveInARowWon && fiveInARowWinners.length > 0) {
            uint totalAmount = address(this).balance / 100 * 30;
            emit FiveInARowHasBeenWon(totalAmount, fiveInARowWinners.length);
            uint amountPerPlayer = totalAmount / fiveInARowWinners.length;
            for(i = 0; i<fiveInARowWinners.length; i++) {
                address winner = fiveInARowWinners[i];
                payable(winner).transfer(amountPerPlayer);
                emit PrizePayed(amountPerPlayer, winner);
            }
        }
        if(!bingoWon && bingoWinners.length > 0) {
            uint totalAmount = address(this).balance;
            emit BingoHasBeenWon(totalAmount, fiveInARowWinners.length);
            uint amountPerPlayer = totalAmount / fiveInARowWinners.length;
            for(i = 0; i<fiveInARowWinners.length; i++) {
                address winner = fiveInARowWinners[i];
                payable(winner).transfer(amountPerPlayer);
                emit PrizePayed(amountPerPlayer, winner);
            }
        }

    }

    function getCardCost() external view returns (uint256 cost) {
        return cardCost;
    }

    function getGameState() external view returns (GameState state) {
        return gameState;
    }

    function getNumberOfPlayers() external view returns (uint256 playersNumber) {
        return numberOfPlayers;
    }

    function getNumberOfCards() external view returns (uint256 cardsNumber) {
        return numberOfCards;
    }

    function getMyCards() external view returns (Card[] memory myCards) {
        if(cards[msg.sender].length == 0) {
            revert EnquirerIsNotAGamer();
        }
        return cards[msg.sender];
    }

    function isItExtracted(uint8 number) external view returns (bool) {
        if(gameState == GameState.Booking) {
            revert ExtractionPhaseNotYetStarted(bookingPeriodExpiration - block.timestamp);
        }
        return extracted[number];
    }

}
