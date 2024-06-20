import json
import os

from web3 import Web3

from utils import (
    get_default_tx_params,
    SYMBIOTIC_ADDRESS,
)

ABIS_FOLDER = "%s/abis" % (os.path.dirname(__file__))

with open("%s/SymbioticAbi.json" % (ABIS_FOLDER)) as file:
    contract = Web3().eth.contract(
        abi=json.load(file),
        # Get address from filename
        address=bytes.fromhex(SYMBIOTIC_ADDRESS),
    )


def test_symbiotic_deposit(ledger_utils):
    recipient = bytes.fromhex("0102030000000000000000000000000000030201")
    maxUint256 = 2**252

    data = contract.encode_abi("deposit", [recipient, maxUint256])

    ledger_utils.set_external_plugin(
        contract.address,
        data,
    )
    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_symbiotic_deposit_with_signature(ledger_utils):
    recipient = bytes.fromhex("0102030000000000000000000000000000030201")
    maxUint256 = 2**252
    deadline = 0
    v = 27
    r = bytes.fromhex(
        "0102030000000000000000000000000000000000000000000000000000040506"
    )
    s = bytes.fromhex(
        "07080900000000000000000000000000000000000000000000000000000a0b0c"
    )

    data = contract.encode_abi("deposit", [recipient, maxUint256, deadline, v, r, s])

    ledger_utils.set_external_plugin(
        contract.address,
        data,
    )
    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_symbiotic_issue_debt(ledger_utils):
    recipient = bytes.fromhex("0102030000000000000000000000000000030201")
    maxUint256 = 2**252

    data = contract.encode_abi("issueDebt", [recipient, maxUint256])

    ledger_utils.set_external_plugin(
        contract.address,
        data,
    )
    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_symbiotic_withdraw(ledger_utils):
    recipient = bytes.fromhex("0102030000000000000000000000000000030201")
    maxUint256 = 2**252

    data = contract.encode_abi("withdraw", [recipient, maxUint256])

    ledger_utils.set_external_plugin(
        contract.address,
        data,
    )
    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)
