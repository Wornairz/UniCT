pragma solidity ^0.8.0;

import './exam-2021-06-22-specs.sol';

contract TrustworthyRockPaperScissorsTournament is TrustworthyRockPaperScissorsTournamentSpecs {
    address payable immutable owner;
    enum Move { ROCK, PAPER, SCISSOR }
    enum TournamentStatus { IN_PROGRESS, CLOSED }
    struct PlayerInfo {
        address payable playerAddress;
        uint256 wins;
        Move[] moves;
    }
    uint8 requiredWins;
    uint256 immutable singleMatchFee;
    mapping (Player => PlayerInfo) players;
    uint8 public override disputedMatches;
    TournamentStatus tournamentStatus;

    constructor(
        address payable firstPlayer,
        address payable secondPlayer,
        uint8 targetWins,
        uint256 matchFee
    ) {
        owner = payable(msg.sender);
        requiredWins = targetWins;
        singleMatchFee = matchFee;
        players[Player.First] = PlayerInfo({
            playerAddress: firstPlayer,
            wins: 0,
            moves: new Move[](0)
        });
        players[Player.Second] = PlayerInfo({
            playerAddress: secondPlayer,
            wins: 0,
            moves: new Move[](0)
        });
        disputedMatches = 0;
        tournamentStatus = TournamentStatus.IN_PROGRESS;
    }

    modifier checks {
        require(msg.value >= singleMatchFee, "The request requires the payment of at least the minimum price");
        assert(tournamentStatus == TournamentStatus.IN_PROGRESS);
        _;
    }

    function moveRock() external payable checks {
        moveAndCheck(Move.ROCK);
    }
    function movePaper() external payable checks {
        moveAndCheck(Move.PAPER);
    }
    function moveScissor() external payable checks {
        moveAndCheck(Move.SCISSOR);
    }

    function moveAndCheck(Move m) internal {
        move(m);
        checkMatches();
        checkTournamentStatus();
    }

    function move(Move move) internal {
        Player p;
        if(msg.sender == players[Player.First].playerAddress) {
            p = Player.First;
        }
        else if (msg.sender == players[Player.Second].playerAddress) {
            p = Player.Second;
        }
        else {
            revert("invalid player address");
        }
        players[p].moves.push(move);
    }

    function checkMatches() internal {
        uint8 finishedMatches;
        if(players[Player.First].moves.length < players[Player.Second].moves.length) {
            finishedMatches = uint8(players[Player.First].moves.length);
        } 
        else {
            finishedMatches = uint8(players[Player.Second].moves.length);
        }
        for(uint8 i = disputedMatches; i < finishedMatches; i++) {
            Move p1Move = players[Player.First].moves[i];
            Move p2Move = players[Player.Second].moves[i];
            uint wins = 0;
            
            if ((p1Move == Move.ROCK && p2Move == Move.SCISSOR) ||
                    (p1Move == Move.PAPER && p2Move == Move.ROCK) ||
                    (p1Move == Move.SCISSOR && p2Move == Move.PAPER)) {
                wins = ++players[Player.First].wins;
                emit MatchWonBy(Player.First, i);
            }
            else {
                wins = ++players[Player.Second].wins;
                emit MatchWonBy(Player.Second, i);
            }
        }
        disputedMatches = finishedMatches;
    }

    function checkTournamentStatus() internal {
        address payable winner;
        if(players[Player.First].wins >= requiredWins) {
            winner = players[Player.First].playerAddress;
            emit TournamentWonBy(Player.First);
        }
        else if(players[Player.Second].wins >= requiredWins) {
            winner = players[Player.Second].playerAddress;
            emit TournamentWonBy(Player.Second);
        }
        if(winner != address(0)) {
            tournamentStatus = TournamentStatus.CLOSED;
            if (address(this).balance > 0) {
                winner.transfer(address(this).balance);
            }

            selfdestruct(owner);
        }
    }

}