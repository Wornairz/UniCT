// SPDX-License-Identifier: None

pragma solidity ^0.8.0;

import "./exam-2023-07-14-specs.sol";

contract CryptoPigeon is CryptoPigeonSpecs, SimplifiedERC721 {
    address immutable manager;
    mapping(uint256 => Pigeon) pigeons;
    mapping(address => uint256) public balanceOf;
    mapping(uint256 => address) public ownerOf;
    uint256 public totalSupply = 0;
    uint256 public birthFee;
    uint256 public renamingFee;
    uint256 pubertyBlockPeriodInSecs;
    uint256 cooldownBlockPeriodInSecs;

    constructor(
        uint16 _initialPigeons,
        uint256 _initialPigeonsFixedScore,
        uint256 _birthFee,
        uint256 _renamingFee,
        uint256 _pubertyBlockPeriodInSecs,
        uint256 _cooldownBlockPeriodInSecs
    ) {
        require(_initialPigeons >= 2, "You must provide at least 2 initial pigeons");
        manager = msg.sender;
        birthFee = _birthFee;
        renamingFee = _renamingFee;
        pubertyBlockPeriodInSecs = _pubertyBlockPeriodInSecs;
        cooldownBlockPeriodInSecs = _cooldownBlockPeriodInSecs;
        for (uint256 i = 0; i < _initialPigeons; i++) {
            uint256 _id = totalSupply++;
            Pigeon storage pigeon = pigeons[_id];
            pigeon.name = "Initial Pigeon";
            pigeon.generation = 0;
            pigeon.geneticScore = _initialPigeonsFixedScore;
            pigeon.birthTime = block.timestamp;
            ownerOf[_id] = manager;
            balanceOf[manager]++;
        }
    }

    modifier validId(uint256 _id) {
        if (_id >= totalSupply) {
            revert PigeonIdentifierUnknown();
        }
        _;
    }

    modifier onlyOwner(uint256 _id) {
        if (msg.sender != ownerOf[_id]) {
            revert PigeonOwnerReservedAction();
        }
        _;
    }

    modifier onlyManager() {
        if (msg.sender != manager) {
            revert ManagerReservedAction();
        }
        _;
    }

    function transfer(address _to, uint256 _tokenId)
        external
        onlyOwner(_tokenId)
        validId(_tokenId)
    {
        ownerOf[_tokenId] = _to;
        balanceOf[msg.sender]--;
        balanceOf[_to]++;
    }

    function pigeonBirth(
        uint256 firstParent,
        uint256 secondParent,
        string calldata name
    )
        external
        payable
        onlyOwner(firstParent)
        onlyOwner(secondParent)
        validId(firstParent)
        validId(secondParent)
        returns (uint256 _id)
    {
        if (msg.value < birthFee) {
            revert InsufficientSentAmount(birthFee);
        }
        if (firstParent == secondParent) {
            revert ParentsCannotBeEqual();
        }
        Pigeon storage firstParentPigeon = pigeons[firstParent];
        Pigeon storage secondParentPigeon = pigeons[secondParent];
        parentsChecks(firstParent, firstParentPigeon, secondParent, secondParentPigeon);
        _id = totalSupply++;
        Pigeon storage pigeon = pigeons[_id];
        pigeon.name = name;
        pigeon.firstParent = firstParent;
        pigeon.secondParent = secondParent;
        pigeon.generation = firstParentPigeon.generation >
            secondParentPigeon.generation
            ? firstParentPigeon.generation + 1
            : secondParentPigeon.generation + 1;
        pigeon.geneticScore = calculateGeneticScore(firstParentPigeon, secondParentPigeon);
        pigeon.birthTime = block.timestamp;
        ownerOf[_id] = msg.sender;
        balanceOf[msg.sender]++;
        emit Birth(_id, name, firstParent, secondParent, pigeon.generation);
        firstParentPigeon.cooldownEndBlockTime =
            block.timestamp +
            cooldownBlockPeriodInSecs;
        secondParentPigeon.cooldownEndBlockTime =
            block.timestamp +
            cooldownBlockPeriodInSecs;
    }

    function parentsChecks(uint256 firstParent, Pigeon memory firstParentPigeon, uint256 secondParent, Pigeon memory secondParentPigeon)
        internal view
    {
        if (block.timestamp < firstParentPigeon.cooldownEndBlockTime) {
            revert ParentStillInCooldownPeriod(
                firstParent,
                firstParentPigeon.cooldownEndBlockTime - block.timestamp
            );
        } else if (block.timestamp < secondParentPigeon.cooldownEndBlockTime) {
            revert ParentStillInCooldownPeriod(
                secondParent,
                secondParentPigeon.cooldownEndBlockTime - block.timestamp
            );
        }
        if (
            block.timestamp <
            firstParentPigeon.birthTime + pubertyBlockPeriodInSecs
        ) {
            revert ParentStillInPubertyPeriod(
                firstParent,
                firstParentPigeon.cooldownEndBlockTime - block.timestamp
            );
        } else if (
            block.timestamp <
            secondParentPigeon.birthTime + pubertyBlockPeriodInSecs
        ) {
            revert ParentStillInPubertyPeriod(
                secondParent,
                secondParentPigeon.cooldownEndBlockTime - block.timestamp
            );
        }
    }

    function calculateGeneticScore(Pigeon memory firstParentPigeon, Pigeon memory secondParentPigeon) internal view returns (uint256 geneticScore) {
        uint256 parentGeneticScoreMean = ((firstParentPigeon.geneticScore +
            secondParentPigeon.geneticScore) / 2);
        int256 randomGeneticScorePercent = int256(
            (uint256(keccak256(abi.encode(block.timestamp, block.difficulty))) %
                60) - 20
        );
        if (randomGeneticScorePercent < 0) {
            geneticScore =
                parentGeneticScoreMean -
                ((parentGeneticScoreMean * 100) /
                    uint256(randomGeneticScorePercent));
        } else if (randomGeneticScorePercent > 0){
            geneticScore =
                parentGeneticScoreMean +
                ((parentGeneticScoreMean * 100) /
                    uint256(randomGeneticScorePercent));
        }
    } 

    function getPigeonData(uint256 _id)
        external
        view
        validId(_id)
        returns (Pigeon memory)
    {
        return pigeons[_id];
    }

    function renamePigeon(uint256 _id, string calldata _newName)
        external
        payable
        validId(_id)
        onlyOwner(_id)
    {
        if (msg.value < renamingFee) {
            revert InsufficientSentAmount(renamingFee);
        }
        Pigeon storage pigeon = pigeons[_id];
        pigeon.name = _newName;
    }

    function changeBirthFee(uint256 _newFee) external onlyManager {
        birthFee = _newFee;
    }

    function changeRenamingFee(uint256 _newFee) external onlyManager {
        renamingFee = _newFee;
    }

    function withdrawProfits(uint256 _amount) external onlyManager {
        require(
            address(this).balance >= _amount,
            "Contract doesn't have that much money"
        );
        payable(manager).transfer(_amount);
    }
}
