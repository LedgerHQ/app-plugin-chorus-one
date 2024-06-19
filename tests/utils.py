import os
import re
from pathlib import Path
from typing import Optional

from web3 import Web3
from ledger_app_clients.ethereum.utils import recover_transaction
from ragger.navigator import NavInsID
from eth_typing import ChainId
from ledger_app_clients.ethereum.client import EthAppClient
from ledger_app_clients.ethereum.utils import get_selector_from_data
import ledger_app_clients.ethereum.response_parser as ResponseParser

DERIVATION_PATH = "m/44'/60'/0'/0/0"
makefile_relative_path = "../Makefile"

ROOT_SCREENSHOT_PATH = Path(__file__).parent


makefile_path = (
    Path(os.path.dirname(os.path.realpath(__file__))) / Path(makefile_relative_path)
).resolve()

pattern = r".*APPNAME.*=.*"
default_strip_parameter = " \t\n\r\x0b\x0c"


def get_appname_from_makefile() -> str:
    """
    Parse the app Makefile to automatically get the APPNAME value
    """
    APPNAME: Optional[str] = None
    with open(makefile_path) as file:
        for line in file:
            if re.search(pattern, line):
                _, var = line.partition("=")[::2]
                APPNAME = var.strip(default_strip_parameter + '"')

    if APPNAME is None:
        raise AssertionError("Unable to find APPNAME in the Makefile")

    return APPNAME


# CONSTANTS
STAKEWISE_ADDRESS = "e6d8d8ac54461b1c5ed15740eee322043f696c08"
EIGENLAYER_ADDRESS = "39053d51b77dc0d36036fc1fcc8cb819df8ef37a"
SYMBIOTIC_ADDRESS = "c329400492c6ff2438472d4651ad17389fcb843a"
PLUGIN_NAME = get_appname_from_makefile()


def get_default_tx_params(contract, data):
    tx_params = {
        "nonce": 1,
        "maxFeePerGas": Web3.to_wei(145, "gwei"),
        "maxPriorityFeePerGas": Web3.to_wei(1.5, "gwei"),
        "gas": 173290,
        "to": contract,
        "value": Web3.to_wei(1, "ether"),
        "chainId": ChainId.ETH,
        "data": data,
    }
    return tx_params


def send_tx_and_compare_snapshots(client, navigator, wallet_addr, test_name, tx_params):
    # send the transaction
    with client.sign(DERIVATION_PATH, tx_params):
        # Validate the on-screen request by performing the navigation appropriate for this device
        navigator.navigate_until_text_and_compare(
            NavInsID.RIGHT_CLICK,
            [NavInsID.BOTH_CLICK],
            "Accept",
            ROOT_SCREENSHOT_PATH,
            test_name,
        )
    # verify signature
    vrs = ResponseParser.signature(client.response().data)
    addr = recover_transaction(tx_params, vrs)
    assert addr == wallet_addr.get()


class LedgerUtils:
    client: EthAppClient
    test_name: str

    def __init__(self, backend, navigator, test_name):
        self.client = EthAppClient(backend)
        self.navigator = navigator
        self.test_name = test_name

    def get(self, path=DERIVATION_PATH) -> bytes:
        with self.client.get_public_addr(display=False, bip32_path=path):
            pass
        return ResponseParser.pk_addr(self.client.response().data)[1]

    def set_external_plugin(self, contract_address, data):
        self.client.set_external_plugin(
            PLUGIN_NAME,
            contract_address,
            # Extract function selector from the encoded data
            get_selector_from_data(data),
        )

    def send_tx_and_compare_snapshots(self, tx_params):
        # send the transaction
        with self.client.sign(DERIVATION_PATH, tx_params):
            # Validate the on-screen request by performing the navigation appropriate for this device
            self.navigator.navigate_until_text_and_compare(
                NavInsID.RIGHT_CLICK,
                [NavInsID.BOTH_CLICK],
                "Accept",
                ROOT_SCREENSHOT_PATH,
                self.test_name,
            )
        # verify signature
        vrs = ResponseParser.signature(self.client.response().data)
        addr = recover_transaction(tx_params, vrs)
        assert addr == self.get()
