#!/usr/bin/env python
from pathlib import Path

import json
from web3 import Web3
from ledger_app_clients.ethereum.client import EthAppClient
from utils import get_appname_from_makefile
from ragger.backend import LedgerCommBackend
from ragger.firmware import Firmware


PLUGIN_NAME = get_appname_from_makefile()
CHORUS_POOL = "e6d8d8ac54461b1c5ed15740eee322043f696c08"

with open("./StakewiseAbi.json") as file:
    contract = Web3().eth.contract(
        abi=json.load(file),
        address=bytes.fromhex(CHORUS_POOL),
    )


backend = LedgerCommBackend(Firmware.NANOX)

with backend as bk:
    cli = EthAppClient(bk)
    deposit_function_hash = bytes.fromhex("f9609f08")
    with cli.set_external_plugin(
        PLUGIN_NAME,
        contract.address,
        deposit_function_hash,
    ):
        pass
