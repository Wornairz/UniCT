pragma solidity ^0.8.0;

import "./exam-2022-06-24-specs.sol";

contract MafiaToken is ERC20, MafiosoTokenSpecs {
    address public immutable godfather;
    address[] picciottiList;
    mapping(address => uint256) picciottoChildren;
    uint256 public override totalSupply;
    mapping(address => uint256) public override balanceOf;
    mapping(address => mapping(address => uint256)) public override allowance;
    uint8 public override pizzoRate = 0;
    uint public override picciottiSalary = 100;
    uint lastSalaryEmitted;

    constructor(uint256 initialSupply) {
        godfather = msg.sender;
        balanceOf[godfather] = initialSupply;
        totalSupply = initialSupply;
        lastSalaryEmitted = block.timestamp;
    }

    function transfer(address recipient, uint256 amount)
        external
        validAddress(recipient)
        returns (bool)
    {
        moveAmount(msg.sender, recipient, amount);
        return true;
    }

    function approve(address delegate, uint256 amount) external returns (bool) {
        allowance[msg.sender][delegate] = amount;
        return true;
    }

    function transferFrom(
        address sender,
        address recipient,
        uint256 amount
    ) external returns (bool) {
        require(
            allowance[sender][msg.sender] >= amount,
            "no permission for this amount"
        );
        moveAmount(sender, recipient, amount);
        return true;
    }

    function moveAmount(address sender, address recipient, uint256 amount) validAddress(sender) validAddress(recipient) internal {
        require(balanceOf[sender] >= amount, "insufficient tokens");
        balanceOf[sender] -= amount;
        balanceOf[recipient] += amount;
        emit Transfer(sender, recipient, amount);
    }

    function calculatePizzo(uint256 amount) internal view returns (uint256) {
        if(pizzoRate > 0)
            return (amount * pizzoRate)/100;
        else 
            return 0;        
    }

    modifier godfatherOnly() {
        require(msg.sender == godfather);
        _;
    }

    modifier mafiaOnly() {
        require(msg.sender == godfather || isPicciotto(msg.sender));
        _;
    }

    modifier validAddress(address id) {
        require(id != address(0), "The passed address is not valid.");
        _;
    }
    
    function isPicciotto(address addr) internal view returns (bool) {
        bool flag = false;
        for(uint i=0; i<picciottiList.length; i++) {
            if(picciottiList[i] == addr) {
                flag = true;
                break;
            }
        }
        return flag;
    } 

    function picciotti() external view returns (address[] memory) {
        return picciottiList;
    }

    function addPicciotto(address id, uint8 children) external godfatherOnly {
        require(!isPicciotto(id));
        picciottiList.push(id);
        picciottoChildren[id] = children;
    }

    function removePicciotto(address id) external godfatherOnly {
        require(isPicciotto(id));
        for(uint i=0; i<picciottiList.length; i++) {
            if(picciottiList[i] == id) {
                picciottiList[i] = picciottiList[picciottiList.length - 1];
                delete picciottoChildren[id];
                picciottiList.pop;
                break;
            }
        }
    }

    function forgeNewTokens(uint256 additionalSupply) external godfatherOnly {
        balanceOf[godfather] += additionalSupply;
        totalSupply += additionalSupply;
    }

    function stealTokens(address robbed, uint256 amount) external mafiaOnly {
        require(robbed != godfather, "il padrino t'ammazza");
        moveAmount(robbed, msg.sender, amount);
    }

    function setPizzoRate(uint8 rate) external godfatherOnly {
        require(rate <= 100, "Rate has to be an integer between 0 and 100.");
        pizzoRate = rate;
    }

    function setPicciottiPerChildSalary(uint256 amount) external godfatherOnly {
        require(amount > 1);
        picciottiSalary = amount;
    }

    function triggerMonthlyPicciottiSalary() external {
        uint256 monthsToPay = (block.timestamp - lastSalaryEmitted) / (30 days);
        for(uint i=0; i<picciottiList.length; i++) {
            address picciotto = picciottiList[i];
            uint numOfChildren = picciottoChildren[picciotto];
            uint picciottoSalary = picciottiSalary * (1+numOfChildren) * monthsToPay;
            require(balanceOf[godfather] >= picciottoSalary);
            moveAmount(godfather, picciotto, picciottiSalary);
        }
        lastSalaryEmitted = block.timestamp;
    }
}
