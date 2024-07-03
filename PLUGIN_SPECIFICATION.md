# Technical Specification

## About

This documentation describes the smart contracts and functions supported by the Chorus plugin.

## Smart Contracts

Smart contracts covered by the plugin shall be described here:

|  Network | Smart Contract      | Address |
|   ----   |      ----           |   ---   |
| Ethereum | Stakewise           | `0xe6d8d8aC54461b1C5eD15740EEe322043F696C08` |
| Ethereum | Eigenlayer          | `0x39053D51B77DC0d36036Fc1fCc8Cb819df8Ef37A` |
| Ethereum | Symbiotic (wstETH)  | `0xc329400492c6ff2438472d4651ad17389fcb843a` |
| Ethereum | Symbiotic (cbETH)   | `0xb26ff591f44b04e78de18f43b46f8b70c6676984` |
| Ethereum | Symbiotic (wBETH)   | `0x422f5accc812c396600010f224b320a743695f85` |
| Ethereum | Symbiotic (rETH)    | `0x03bf48b8a1b37fbead1ecabcf15b98b924ffa5ac` |
| Ethereum | Symbiotic (mETH)    | `0x475d3eb031d250070b63fa145f0fcfc5d97c304a` |
| Ethereum | Symbiotic (swETH)   | `0x38b86004842d3fa4596f0b7a0b53de90745ab654` |
| Ethereum | Symbiotic (sfrxETH) | `0x5198cb44d7b2e993ebdda9cad3b9a0eaa32769d2` |
| Ethereum | Symbiotic (ETHx)    | `0xbdea8e677f9f7c294a4556005c640ee505be6925` |

## Functions

For the smart contracts implemented, the functions covered by the plugin shall be described here:

|Contract |    Function   | Selector  | Displayed Parameters |
|   ---   |    ---        | ---       | --- |
|Stakewise  | burnOsToken | `0x066055e0`| <table><tbody> <tr><td><code>uint128 osTokenShares</code></td></tr> </tbody></table> |
|Stakewise  | claimExitedAssets | `0x8697d2c2`| <table><tbody> <tr><td><code>uint256 positionTicket</code></td></tr> <tr><td><code>uint256 timestamp</code></td></tr> <tr><td><code>uint256 exitQueueIndex</code></td></tr></tbody></table> |
|Stakewise  | deposit | `0xf9609f08`| <table><tbody> <tr><td><code>address receiver</code></td></tr> <tr><td><code>address referrer</code></td></tr> </tbody></table> |
|Stakewise  | enterExitQueue | `0x8ceab9aa`| <table><tbody> <tr><td><code>uint256 shares</code></td></tr> <tr><td><code>address receiver</code></td></tr> </tbody></table> |
|Stakewise  | mintOsToken | `0x201b9eb5`| <table><tbody> <tr><td><code>address receiver</code></td></tr> <tr><td><code>uint256 osTokenShares</code></td></tr> <tr><td><code>address referrer</code></td></tr> </tbody></table> |
|Stakewise  | redeem | `0x7bde82f2`| <table><tbody> <tr><td><code>uint256 shares</code></td></tr> <tr><td><code>address receiver</code></td></tr> </tbody></table> |
|Stakewise  | redeemOsToken | `0x43e82a79`| <table><tbody> <tr><td><code>uint256 osTokenShares</code></td></tr> <tr><td><code>address owner</code></td></tr> <tr><td><code>address receiver</code></td></tr></tbody></table> |
|||||
|Eigenlayer  | delegateTo | `0xeea9064b`| <table><tbody> <tr><td><code>address operator</code></td></tr> <tr><td><code>SignatureWithExpiry approverSignatureAndExpiry</code></td></tr> <tr><td><code>bytes32 approverSalt</code></td></tr> </tbody></table> |
|Eigenlayer  | increaseDelegatedShares | `0x28a573ae`| <table><tbody> <tr><td><code>address staker</code></td></tr> <tr><td><code>address strategy</code></td></tr> <tr><td><code>uint256 shares</code></td></tr> </tbody></table> |
|Eigenlayer  | decreaseDelegatedShares | `0x132d4967`| <table><tbody> <tr><td><code>address staker</code></td></tr> <tr><td><code>address strategy</code></td></tr> <tr><td><code>uint256 shares</code></td></tr> </tbody></table> |
|Eigenlayer  | completeQueuedWithdrawal | `0x60d7faed`| <table><tbody> <tr><td><code>Withdrawal withdrawal</code></td></tr> <tr><td><code>IERC20[] tokens</code></td></tr> <tr><td><code>uint256 middlewareTimesIndex</code></td></tr> <tr><td><code>bool receiveAsTokens</code></td></tr> </tbody></table> |
|Eigenlayer  | queueWithdrawals           | `0x0dd8dd02`| <table><tbody> <tr><td><code>QueuedWithdrawalParams[] queuedWithdrawalParams</code></td></tr> </tbody></table> |
|Eigenlayer  | undelegate | `0xda8be864`| <table><tbody> <tr><td><code>address staker</code></td></tr> </tbody></table> |
|||||
|Symbiotic  | deposit | `0x47e7ef24`| <table><tbody> <tr><td><code>address recipient</code></td></tr> <tr><td><code>uint256 amount</code></td></tr> </tbody></table> |
|Symbiotic  | deposit | `0xc5758489`| <table><tbody> <tr><td><code>address recipient</code></td></tr> <tr><td><code>uint256 amount</code></td></tr> <tr><td><code>uint256 deadline</code></td></tr> <tr><td><code>bytes32 v</code></td></tr> <tr><td><code>bytes32 r</code></td></tr> <tr><td><code>bytes32 s</code></td></tr></tbody></table> |
|Symbiotic  | issueDebt | `0x7715be0b`| <table><tbody> <tr><td><code>address recipient</code></td></tr> <tr><td><code>uint256 amount</code></td></tr> </tbody></table> |
|Symbiotic  | withdraw | `0xf3fef3a3`| <table><tbody> <tr><td><code>address recipient</code></td></tr> <tr><td><code>uint256 amount</code></td></tr> </tbody></table> |

## Structs

```solidity
struct SignatureWithExpiry {
        // the signature itself, formatted as a single bytes object
        bytes signature;
        // the expiration timestamp (UTC) of the signature
        uint256 expiry;
    }
```

```solidity
struct Withdrawal {
        // The address that originated the Withdrawal
        address staker;
        // The address that the staker was delegated to at the time that the Withdrawal was created
        address delegatedTo;
        // The address that can complete the Withdrawal + will receive funds when completing the withdrawal
        address withdrawer;
        // Nonce used to guarantee that otherwise identical withdrawals have unique hashes
        uint256 nonce;
        // Block number when the Withdrawal was created
        uint32 startBlock;
        // Array of strategies that the Withdrawal contains
        IStrategy[] strategies;
        // Array containing the amount of shares in each Strategy in the `strategies` array
        uint256[] shares;
    }
```

```solidity
struct QueuedWithdrawalParams {
        // Array of strategies that the QueuedWithdrawal contains
        IStrategy[] strategies;
        // Array containing the amount of shares in each Strategy in the `strategies` array
        uint256[] shares;
        // The address of the withdrawer
        address withdrawer;
    }
```
