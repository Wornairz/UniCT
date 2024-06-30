pragma solidity ^0.8.0;

import "./exam-2022-07-14-specs.sol";

contract AuctionManager is AuctionManagerSpecs {
    struct Auction {
        address payable beneficiary;
        string description;
        uint256 minimumBid;
        uint256 expiration;
        AuctionState state;
        address[] bidders;
        mapping(address => uint256) bids;
        uint256 highestBid;
        address highestBidder;
    }

    Auction[] auctions;
    uint256 auctionsCounter = 0;
    uint256 ongoingAuctionsCounter = 0;

    modifier auctionExists(uint256 id) {
        if(id >= auctionsCounter) {
            revert AuctionNotExisting();
        }
        _;
    }

    function createNewAuction(
        string memory description,
        uint256 minimumBid,
        uint256 expirationInHours
    ) external returns (uint256 id) {
        Auction storage auction = auctions.push();
        auction.beneficiary = payable(msg.sender);
        auction.description = description;
        auction.minimumBid = minimumBid;
        auction.expiration = block.timestamp + (expirationInHours * 3600);
        auction.state = AuctionState.Ongoing;
        auction.highestBid = 0;
        auction.highestBidder = address(0);
        /*Auction memory auction = Auction({
            beneficiary: payable(msg.sender),
            description: description,
            minimumBid: minimumBid,
            expiration: block.timestamp + (expirationInHours * 3600),
            state: AuctionState.Ongoing,
            highestBid: 0,
            highestBidder: address(0)
        });*/
        emit NewAuction(description, minimumBid, auction.expiration);
        ongoingAuctionsCounter++;
        return auctionsCounter++;
    }

    function bidOnAuction(uint256 id)
        external
        payable
        auctionExists(id)
        returns (bool isHighest)
    {
        Auction storage auction = auctions[id];
        require(msg.sender != auction.beneficiary, "you cannot make an offer to your own auction");
        if(auction.state != AuctionState.Ongoing) {
            revert AuctionAlreadyEnded(auction.state);
        }
        if(msg.value < auction.minimumBid) {
            revert BidNotAboveMinimum(auction.minimumBid);
        }
        if(auction.bids[msg.sender] == 0) {
            auction.bidders.push(msg.sender);
        }
        auction.bids[msg.sender] += msg.value;
        if (auction.bids[msg.sender] > auction.highestBid) {
            auction.highestBid = auction.bids[msg.sender];
            auction.highestBidder = msg.sender;
            emit NewHighestBid(id, auction.highestBidder, auction.highestBid);
            return true;
        }
        return false;
    }

    function idsOfOngoingAuctions()
        external
        view
        returns (uint256[] memory ids)
    {
        ids = new uint256[](ongoingAuctionsCounter);

        uint256 index = 0;
        for (uint256 i = 0; i < auctions.length; i++) {
            if (auctions[i].state == AuctionState.Ongoing) {
                ids[index] = i;
                index++;
            }
        }
    }

    function auctionDescription(uint256 id)
        external
        view
        auctionExists(id)
        returns (string memory)
    {
        Auction storage auction = auctions[id];
        return auction.description;
    }

    function auctionMinimumBid(uint256 id)
        external
        view
        auctionExists(id)
        returns (uint256 amount)
    {
        Auction storage auction = auctions[id];
        return auction.minimumBid;
    }

    function auctionExpiration(uint256 id)
        external
        view
        auctionExists(id)
        returns (uint256 timestamp)
    {
        Auction storage auction = auctions[id];
        return auction.expiration;
    }

    function auctionBeneficiary(uint256 id)
        external
        view
        auctionExists(id)
        returns (address beneficiary)
    {
        Auction storage auction = auctions[id];
        return auction.beneficiary;
    }

    function auctionState(uint256 id)
        external
        view
        auctionExists(id)
        returns (AuctionState)
    {
        Auction storage auction = auctions[id];
        return auction.state;
    }

    function auctionHighestBid(uint256 id)
        external
        view
        auctionExists(id)
        returns (uint256 amount)
    {
        Auction storage auction = auctions[id];
        return auction.highestBid;
    }

    function auctionHighestBidder(uint256 id)
        external
        view
        auctionExists(id)
        returns (address bidder)
    {
        Auction storage auction = auctions[id];
        return auction.highestBidder;
    }

    function finalizeAuction(uint256 id) external auctionExists(id) {
        Auction storage auction = auctions[id];
        if(auction.state != AuctionState.Ongoing) {
            revert AuctionToFinalizeAlreadyFinalized();
        }
        if(block.timestamp < auction.expiration) {
            revert AuctionToFinalizeNotYetEnded(auction.expiration);
        }
        ongoingAuctionsCounter--;
        if(auction.highestBid == 0) {
            auction.state = AuctionState.Expired;
            emit AuctionExpiredWithoutWinner(id);
            return;
        }
        auction.state = AuctionState.EndedWithWinner;
        for(uint i=0; i<auction.bidders.length; i++) {
            address bidderAddr = auction.bidders[i];
            uint256 bidderAmount = auction.bids[bidderAddr];
            auction.bids[bidderAddr] = 0;
            if(bidderAddr != auction.highestBidder) {
                payable(bidderAddr).transfer(bidderAmount);
            }
        }
        auction.beneficiary.transfer(auction.highestBid);
        emit AuctionEndedWithWinner(id, auction.highestBidder, auction.highestBid);
    }

    function cancelAuction(uint256 id) external auctionExists(id) {
        Auction storage auction = auctions[id];
        require(msg.sender == auction.beneficiary, "Only the creator can cancel an auction");
        require(auction.state == AuctionState.Ongoing, "You can cancel only ongoing auction");
        require(auction.expiration > block.timestamp, "You can cancel only not expired auction");
        auction.state = AuctionState.Canceled;
        ongoingAuctionsCounter--;
        for(uint i=0; i<auction.bidders.length; i++) {
            address bidderAddr = auction.bidders[i];
            uint256 bidderAmount = auction.bids[bidderAddr];
            auction.bids[bidderAddr] = 0;
            payable(bidderAddr).transfer(bidderAmount);
        }
    }
}
