import json
import os

from web3 import Web3

from utils import (
    get_default_tx_params,
    EIGENLAYER_ADDRESS,
)

ABIS_FOLDER = "%s/abis" % (os.path.dirname(__file__))

with open("%s/EigenlayerAbi.json" % (ABIS_FOLDER)) as file:
    contract = Web3().eth.contract(
        abi=json.load(file),
        # Get address from filename
        address=bytes.fromhex(EIGENLAYER_ADDRESS),
    )


def test_eigenlayer_delegate_to(ledger_utils):
    operator = bytes.fromhex("0102030000000000000000000000000000030201")
    signature_expiry = (
        "0x0102032222222222222222222222222222222222222222222222222222222222223333333333333333333333333333333333333333333333333333333333040506",
        123456789,
    )
    approver_salt = "0xfffefdfffffffffffffffffffffffffffffffffffffffffffffffffffffcfbfa"

    data = contract.encode_abi(
        "delegateTo", [operator, signature_expiry, approver_salt]
    )

    ledger_utils.set_external_plugin(
        contract.address,
        data,
    )
    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_eigenlayer_increase_delegated_shares_wallet_address(ledger_utils):
    receiver = ledger_utils.get()
    strategy = bytes.fromhex("0405060000000000000000000000000000070809")
    shares = 2**256 - 1

    data = contract.encode_abi("increaseDelegatedShares", [receiver, strategy, shares])

    ledger_utils.set_external_plugin(
        contract.address,
        data,
    )
    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_eigenlayer_increase_delegated_shares(ledger_utils):
    receiver = bytes.fromhex("0102030000000000000000000000000000030201")
    strategy = bytes.fromhex("0405060000000000000000000000000000070809")
    shares = 2**256 - 1

    data = contract.encode_abi("increaseDelegatedShares", [receiver, strategy, shares])

    ledger_utils.set_external_plugin(
        contract.address,
        data,
    )
    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_eigenlayer_decrease_delegated_shares_wallet_address(ledger_utils):
    receiver = ledger_utils.get()
    strategy = bytes.fromhex("0405060000000000000000000000000000070809")
    shares = 2**256 - 1

    data = contract.encode_abi("decreaseDelegatedShares", [receiver, strategy, shares])

    ledger_utils.set_external_plugin(
        contract.address,
        data,
    )
    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_eigenlayer_decrease_delegated_shares(ledger_utils):
    receiver = bytes.fromhex("0102030000000000000000000000000000030201")
    strategy = bytes.fromhex("0405060000000000000000000000000000070809")
    shares = 2**256 - 1

    data = contract.encode_abi("decreaseDelegatedShares", [receiver, strategy, shares])

    ledger_utils.set_external_plugin(
        contract.address,
        data,
    )
    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_eigenlayer_complete_queued_withdrawal(ledger_utils):
    withdrawal = (
        bytes.fromhex("0102030000000000000000000000000000040506"),
        bytes.fromhex("07080900000000000000000000000000000a0b0c"),
        bytes.fromhex("0d0e0f0000000000000000000000000000101112"),
        19,
        99,
        [bytes.fromhex("13141500000000000000000000000000001c1d1e")],
        [10],
    )
    tokens = [bytes.fromhex("1f20210000000000000000000000000000222324")]
    middleware_times_index = 255
    receive_as_tokens = False

    data = contract.encode_abi(
        "completeQueuedWithdrawal",
        [withdrawal, tokens, middleware_times_index, receive_as_tokens],
    )

    ledger_utils.set_external_plugin(
        contract.address,
        data,
    )
    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_eigenlayer_queue_withdrawal(ledger_utils):
    withdrawal = [
        (
            [bytes.fromhex("0102030000000000000000000000000000040506")],
            [255],
            bytes.fromhex("07080900000000000000000000000000000a0b0c"),
        )
    ]

    data = contract.encode_abi("queueWithdrawals", [withdrawal])

    ledger_utils.set_external_plugin(
        contract.address,
        data,
    )
    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_eigenlayer_undelegate(ledger_utils):
    staker = bytes.fromhex("07080900000000000000000000000000000a0b0c")

    data = contract.encode_abi("undelegate", [staker])

    ledger_utils.set_external_plugin(
        contract.address,
        data,
    )
    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)