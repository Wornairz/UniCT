// SPDX-License-Identifier: None

pragma solidity ^0.8.0;

import "./exam-2021-07-12-specs.sol";

contract CorporateManagement is CorporateManagementSpecs {
    struct Proposal {
        ProposalCategory category;
        string description;
        address proposer;
        mapping(address => bool) voters;
        uint votersShares;
        bool accepted;
    }
    
    address immutable founder;
    uint immutable minShare;
    mapping(address => bool) public override isAssociated;
    mapping(address => uint) associatesShares;
    uint public totalShares;
    mapping(address => bool) public isCandidated;
    mapping(address => uint) candidatesShares;
    mapping(uint => Proposal) proposals;
    uint proposalCount;
    bool public override isDissoluted;

    constructor(uint minimumAssociatingShare) payable {
        founder = msg.sender;
        minShare = minimumAssociatingShare;
        isAssociated[msg.sender] = true;
        associatesShares[msg.sender] = msg.value;
        totalShares = msg.value;
        isDissoluted = false;
    }

    modifier onlyAssociate() {
        require(isAssociated[msg.sender], "Only associated members can call this function");
        _;
    }
    
    modifier onlyActive() {
        require(isDissoluted == false, "Corporate is dissoluting");
        _;
    }
    
    function depositFunds() external payable onlyActive {
        if(isAssociated[msg.sender]) {
            associatesShares[msg.sender] += msg.value;
            totalShares += msg.value;
        }
        else if(isCandidated[msg.sender]) {
            candidatesShares[msg.sender] += msg.value;
        }
        else {
            require(msg.value > minShare, "The funds of a new associate has to respect the specified minimum");
            isCandidated[msg.sender] = true;
            candidatesShares[msg.sender] = msg.value;
            uint proposalId = proposalCount++;
            emit NewAssociateCandidate(proposalId, msg.sender);
            Proposal storage proposal = proposals[proposalId];
            proposal.category = ProposalCategory.NewAssociationAcceptance;
            proposal.proposer = msg.sender;
            proposal.accepted = false;
        }
    }

    function voteProposal(uint proposalId) external onlyAssociate onlyActive {
        Proposal storage proposal = proposals[proposalId];
        require(proposal.accepted == false, "Proposal has already been accepted");
        require(proposalId < proposalCount, "Proposal doesn't exists");
        if(!proposal.voters[msg.sender]) {
            proposal.voters[msg.sender] = true;
            proposal.votersShares += associatesShares[msg.sender];
        }
        checkProposalApproval(proposal);
    }

    function depositGenericProposal(string calldata description) external onlyAssociate onlyActive {
        uint proposalId = proposalCount++;
        Proposal storage proposal = proposals[proposalId];
        proposal.category = ProposalCategory.Generic;
        proposal.proposer = msg.sender;
        proposal.description = description;
        proposal.voters[msg.sender] = true;
        proposal.votersShares = associatesShares[msg.sender];
        proposal.accepted = false;
        emit NewGenericProposal(proposalId, description);
    }

    function depositDissolutionProposal() external onlyAssociate onlyActive {
        uint proposalId = proposalCount++;
        Proposal storage proposal = proposals[proposalId];
        proposal.category = ProposalCategory.Generic;
        proposal.proposer = msg.sender;
        proposal.voters[msg.sender] = true;
        proposal.votersShares = associatesShares[msg.sender];
        proposal.accepted = false;
        emit NewDissolutionProposal(proposalId);
    }

    function checkProposalApproval(Proposal storage proposal) internal {
        if(proposal.category == ProposalCategory.NewAssociationAcceptance) {
            if(proposal.votersShares > (totalShares/2)+1) {
                proposal.accepted = true;
                isAssociated[proposal.proposer] = true;
                isCandidated[proposal.proposer] = false;
                associatesShares[proposal.proposer] = candidatesShares[proposal.proposer];
                totalShares += candidatesShares[proposal.proposer];
                candidatesShares[proposal.proposer] = 0;
                emit AcceptedAssociate(proposal.proposer);
            }
        }
        else if(proposal.category == ProposalCategory.Generic) {
            if(proposal.votersShares > (totalShares/2)+1) {
                proposal.accepted = true;
                emit AcceptedGenericProposal(proposal.description);
            }
        }
        else if(proposal.category == ProposalCategory.CorporateDissolution) {
            if(proposal.votersShares >= totalShares) {
                proposal.accepted = true;
                isDissoluted = true;
                emit AcceptedCorporateDissolution();
            }
        }
    }

    function requestShareRefunding() external {
        if(isAssociated[msg.sender]) {
            require(isDissoluted, "Company is not dissoluting, you cannot be refunded");
            assert(address(this).balance >= associatesShares[msg.sender]);
            isAssociated[msg.sender] = false;
            uint associateAmount = associatesShares[msg.sender];
            totalShares -= associateAmount;
            associatesShares[msg.sender] = 0;
            payable(msg.sender).transfer(associateAmount);

            if (address(this).balance == 0) {
                selfdestruct(payable(founder));
            }
        }
        else if(isCandidated[msg.sender]) {
            assert(address(this).balance >= candidatesShares[msg.sender]);
            isCandidated[msg.sender] = false;
            uint candidateAmount = candidatesShares[msg.sender];
            candidatesShares[msg.sender] = 0;
            payable(msg.sender).transfer(candidateAmount);
        }
        else {
            revert("You are not associated nor candidated");
        }
    }
}