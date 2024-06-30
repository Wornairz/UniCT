pragma solidity ^0.8.0;

import "./exam-2022-09-02-specs.sol";

contract UnblindElection is UnblindElectionSpecs {
    address immutable president;
    uint8 immutable quorumPercentual;
    uint256 immutable votingExpiration;
    uint256 immutable candidationExpiration;

    address[] voters;
    mapping(address => bool) isVoter;
    address[] candidates;
    mapping(address => bool) isCandidate;
    address[] acceptedCandidates;
    mapping(address => bool) isAcceptedCandidate;

    mapping(address => bool) hasVoted;
    mapping(address => uint256) candidatesVotes;
    uint256 validVotes = 0;

    constructor(
        uint256 candidationDays,
        uint256 votingDays,
        uint8 quorumPercent
    ) {
        president = msg.sender;
        quorumPercentual = quorumPercent;
        candidationExpiration =
            block.timestamp +
            (candidationDays * 24 * 60 * 60);
        votingExpiration = candidationExpiration + (votingDays * 24 * 60 * 60);
        addVoter(president);
    }

    modifier presidentOnly() {
        if (msg.sender != president) {
            revert PresidentReservedAction();
        }
        _;
    }

    modifier checkCandidation(address voter) {
        if (!isVoter[voter]) {
            revert CandidateHasToBeAVoter();
        }
        if (block.timestamp > candidationExpiration) {
            revert CandidationPhaseAlreadyClosed();
        }
        _;
    }

    function addVoter(address voter) public presidentOnly {
        require(!isVoter[voter], "already a voter");
        voters.push(voter);
        isVoter[voter] = true;
    }

    function addVoters(address[] calldata votersInput) external presidentOnly {
        for (uint256 i = 0; i < votersInput.length; i++) {
            addVoter(votersInput[i]);
        }
    }

    function candidateMySelf() external checkCandidation(msg.sender) {
        candidates.push(msg.sender);
        isCandidate[msg.sender] = true;
    }

    function candidateSomeoneElse(address candidate)
        external
        checkCandidation(candidate)
    {
        candidates.push(candidate);
        isCandidate[msg.sender] = true;
    }

    function acceptCandidation(address candidate) public presidentOnly {
        if (!isCandidate[candidate]) {
            revert ItIsNotACandidate();
        }
        delete isCandidate[candidate];
        isAcceptedCandidate[candidate] = true;
        emit AcceptedCandidation(candidate);
    }

    function acceptCandidations(address[] calldata candidatesInput)
        external
        presidentOnly
    {
        for (uint256 i = 0; i < candidatesInput.length; i++) {
            acceptCandidation(candidatesInput[i]);
        }
    }

    function getAcceptedCandidates()
        external
        view
        returns (address[] memory candidatesInput)
    {
        return acceptedCandidates;
    }

    function vote(address candidate) external {
        if (block.timestamp < candidationExpiration) {
            revert VotingPhaseNotYetOpen();
        }
        if (block.timestamp > votingExpiration) {
            revert VotingPhaseAlreadyClosed();
        }
        if (!isVoter[msg.sender]) {
            revert OnlyKnownVotersCanVote();
        }
        if (!isAcceptedCandidate[candidate]) {
            revert OnlyAcceptedCandidatesCanBeVoted();
        }
        if (hasVoted[msg.sender]) {
            revert OnlyOneVotePerVoter();
        }
        hasVoted[msg.sender] = true;
        candidatesVotes[candidate]++;
        validVotes++;
    }

    function closeElection() external presidentOnly returns (bool valid) {
        if (
            voters.length == 0 ||
            acceptedCandidates.length == 0 ||
            validVotes == 0
        ) {
            revert ElectionClosedWithAnInvalidResult();
        }
        if (((validVotes * 100) / voters.length) < quorumPercentual) {
            revert ElectionClosedWithoutQuorum();
        }

        address winner;
        uint256 firstVotes;
        uint256 secondVotes;
        for (uint256 i = 0; i < acceptedCandidates.length; i++) {
            address candidate = acceptedCandidates[i];
            if (candidatesVotes[candidate] > firstVotes) {
                winner = candidate;
                firstVotes = candidatesVotes[candidate];
            }
            if (candidatesVotes[candidate] > secondVotes) {
                secondVotes = candidatesVotes[candidate];
            }
        }
        if (firstVotes > secondVotes) {
            emit ElectionRegularlyClosed(winner);
            return true;
        }
        return false;
    }
}
