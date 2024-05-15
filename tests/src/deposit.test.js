import { genericTx, abi, startSimulator } from "./utils.js";
import { parseEther } from "ethers/lib/utils";
import { ethers } from "ethers";
import Zemu from "@zondax/zemu";
import { resolve } from "path";

jest.setTimeout(20000);

const NANOS_ETH_PATH = resolve("elfs/ethereum_nanos.elf");
const NANOX_ETH_PATH = resolve("elfs/ethereum_nanox.elf");

const NANOS_PLUGIN_PATH = resolve("elfs/plugin_nanos.elf");
const NANOX_PLUGIN_PATH = resolve("elfs/plugin_nanox.elf");

const transactionUploadDelay = 60000;

const contractAddr = "0x393216dfc16b9115936ffb78c87888817e63f291";
const receiverAddr = "0x010203efdeadbeefdeadbeefdeadbeefde040506";
const referrerAddr = "0xdeadbeefdeadbeefdeadbeefdeadbeefdeadbeef";

const contract = new ethers.Contract(contractAddr, abi);
const snapshotsDir = "OpusPlugin";

test("Deposit Eth with same address as receiver", async () => {
    // Create Zemu object. Pass the path to your .elf file
    const sim = new Zemu(NANOS_ETH_PATH, { OpusPlugin: NANOS_PLUGIN_PATH });
    try {
        let eth = await startSimulator(sim);
        // Get address used in Ledger.
        const address = await eth.getAddress("44'/60'/0'/0");
        const { data } = await contract.populateTransaction.deposit(
            address.address,
            referrerAddr
        );

        let unsignedTx = genericTx;
        unsignedTx.to = contractAddr;
        unsignedTx.data = data;
        unsignedTx.value = parseEther("1");

        const serializedTx = ethers.utils
            .serializeTransaction(unsignedTx)
            .slice(2);

        const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

        await sim.waitUntilScreenIsNot(
            sim.getMainMenuSnapshot(),
            transactionUploadDelay
        );

        let nav = await sim.navigate(snapshotsDir, "Deposit Eth", [4, 0]);
        await tx;
    } catch (e) {
        console.error(e);
        throw e;
    } finally {
        await sim.close();
    }
});

test("Deposit Eth with different address as receiver", async () => {
    // Create Zemu object. Pass the path to your .elf file
    const sim = new Zemu(NANOS_ETH_PATH, { OpusPlugin: NANOS_PLUGIN_PATH });
    try {
        let eth = await startSimulator(sim);
        const { data } = await contract.populateTransaction.deposit(
            receiverAddr,
            referrerAddr
        );

        let unsignedTx = genericTx;
        unsignedTx.to = contractAddr;
        unsignedTx.data = data;
        unsignedTx.value = parseEther("1");

        const serializedTx = ethers.utils
            .serializeTransaction(unsignedTx)
            .slice(2);

        const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

        await sim.waitUntilScreenIsNot(
            sim.getMainMenuSnapshot(),
            transactionUploadDelay
        );

        let nav = await sim.navigate(
            snapshotsDir,
            "Deposit Eth different address",
            [5, 0]
        );
        await tx;
    } catch (e) {
        console.error(e);
        throw e;
    } finally {
        await sim.close();
    }
});

afterAll(async () => {
    await new Promise((resolve) => setTimeout(() => resolve(), 500)); // avoid jest open handle error
});
