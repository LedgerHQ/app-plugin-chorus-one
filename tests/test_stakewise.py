import json
import os

from web3 import Web3

from utils import (
    get_default_tx_params,
    STAKEWISE_ADDRESS,
)


ABIS_FOLDER = "%s/abis" % (os.path.dirname(__file__))

with open("%s/StakewiseAbi.json" % (ABIS_FOLDER)) as file:
    contract = Web3().eth.contract(
        abi=json.load(file),
        # Get address from filename
        address=bytes.fromhex(STAKEWISE_ADDRESS),
    )


# Deposit with the same wallet address
def test_stakewise_deposit_wallet_address(ledger_utils):
    receiverAddr = ledger_utils.get()
    referrerAddr = bytes.fromhex("010203efdeadbeefdeadbeefdeadbeefde040506")
    data = contract.encode_abi("deposit", [receiverAddr, referrerAddr])

    ledger_utils.set_external_plugin(
        contract.address,
        data,
    )
    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


# Deposit with different wallet address
def test_stakewise_deposit(ledger_utils):
    receiverAddr = bytes.fromhex("6050403020100efdeadbeefdeadbeefdea010203")
    referrerAddr = bytes.fromhex("010203efdeadbeefdeadbeefdeadbeefde040506")
    data = contract.encode_abi("deposit", [receiverAddr, referrerAddr])

    ledger_utils.set_external_plugin(
        contract.address,
        data,
    )

    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_stakewise_burn_os_token(ledger_utils):
    data = contract.encode_abi("burnOsToken", [2**128 - 1])
    ledger_utils.set_external_plugin(
        contract.address,
        # Extract function selector from the encoded data
        data,
    )

    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_stakewise_liquidate_os_token(ledger_utils):
    maxUint256 = 2**256 - 1
    owner = bytes.fromhex("6050403020100efdeadbeefdeadbeefdea010203")
    receiver = bytes.fromhex("010203efdeadbeefdeadbeefdeadbeefde040506")

    data = contract.encode_abi("liquidateOsToken", [maxUint256, owner, receiver])
    ledger_utils.set_external_plugin(
        contract.address,
        # Extract function selector from the encoded data
        data,
    )

    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_stakewise_liquidate_os_token_wallet_address(ledger_utils):
    maxUint256 = 2**256 - 1
    owner = bytes.fromhex("6050403020100efdeadbeefdeadbeefdea010203")
    receiver = ledger_utils.get()

    data = contract.encode_abi("liquidateOsToken", [maxUint256, owner, receiver])
    ledger_utils.set_external_plugin(
        contract.address,
        # Extract function selector from the encoded data
        data,
    )

    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_stakewise_mint_os_token(ledger_utils):
    receiver = bytes.fromhex("010203efdeadbeefdeadbeefdeadbeefde040506")
    maxUint256 = 2**256 - 1
    referrer = bytes.fromhex("6050403020100efdeadbeefdeadbeefdea010203")

    data = contract.encode_abi("mintOsToken", [receiver, maxUint256, referrer])
    ledger_utils.set_external_plugin(
        contract.address,
        # Extract function selector from the encoded data
        data,
    )

    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_stakewise_mint_os_token_wallet_address(ledger_utils):
    receiver = ledger_utils.get()
    maxUint256 = 2**256 - 1
    referrer = bytes.fromhex("6050403020100efdeadbeefdeadbeefdea010203")

    data = contract.encode_abi("mintOsToken", [receiver, maxUint256, referrer])
    ledger_utils.set_external_plugin(
        contract.address,
        # Extract function selector from the encoded data
        data,
    )

    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_stakewise_redeem_os_token(ledger_utils):
    maxUint256 = 2**256 - 1
    owner = bytes.fromhex("010203efdeadbeefdeadbeefdeadbeefde040506")
    receiver = bytes.fromhex("6050403020100efdeadbeefdeadbeefdea010203")

    data = contract.encode_abi("redeemOsToken", [maxUint256, owner, receiver])
    ledger_utils.set_external_plugin(
        contract.address,
        # Extract function selector from the encoded data
        data,
    )

    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)


def test_stakewise_redeem_os_token_wallet_address(ledger_utils):
    maxUint256 = 2**256 - 1
    owner = bytes.fromhex("6050403020100efdeadbeefdeadbeefdea010203")
    receiver = ledger_utils.get()

    data = contract.encode_abi("redeemOsToken", [maxUint256, owner, receiver])
    ledger_utils.set_external_plugin(
        contract.address,
        # Extract function selector from the encoded data
        data,
    )

    tx_params = get_default_tx_params(contract.address, data)
    ledger_utils.send_tx_and_compare_snapshots(tx_params)
