# Opus plugin for Stakewise vaults and Eigenlayer contracts

This repository contains code for the Opus plugin for stakewise and Eigenlayer
contracts.

## Implemented functions

- burnOsToken(uint128 osTokenShares)
- claimExitedTokens(uint256 positionTicket, uint256 timestamp, uint256 exitQueueIndex)
- deposit(address receiver, address referer)
- enterExitQueue(uint256 shares, address receiver)
- liquidateOsToken(uint256 osTokenShares, address owner, address receiver)
- mintOsToken(address receiver, uint256 osTokenShares, address referrer)
- redeem(uint256 shares, address receiver)
- redeemOsToken(uint256 osTokenShares, address owner, address receiver)
