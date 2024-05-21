import { genericTx, abi, startSimulator } from "./utils.js";
import { ethers, BigNumber } from "ethers";
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

const contract = new ethers.Contract(contractAddr, abi);
const snapshotsDir = "OpusPlugin";

test("Call enterExitQueue with same address as receiver", async () => {
    // Create Zemu object. Pass the path to your .elf file
    const sim = new Zemu(NANOS_ETH_PATH, { OpusPlugin: NANOS_PLUGIN_PATH });
    try {
        let eth = await startSimulator(sim);
        // Get address used in Ledger.
        const address = await eth.getAddress("44'/60'/0'/0");
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const { data } = await contract.populateTransaction.enterExitQueue(
            maxUint256,
            address.address
        );

        let unsignedTx = genericTx;
        unsignedTx.to = contractAddr;
        unsignedTx.data = data;

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
            "Withdraw enterExitQueue",
            [8, 0]
        );
        await tx;
    } catch (e) {
        console.error(e);
        throw e;
    } finally {
        await sim.close();
    }
});

test("Call enterExitQueue with different address as receiver", async () => {
    // Create Zemu object. Pass the path to your .elf file
    const sim = new Zemu(NANOS_ETH_PATH, { OpusPlugin: NANOS_PLUGIN_PATH });
    try {
        let eth = await startSimulator(sim);
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const { data } = await contract.populateTransaction.enterExitQueue(
            maxUint256,
            receiverAddr
        );

        let unsignedTx = genericTx;
        unsignedTx.to = contractAddr;
        unsignedTx.data = data;

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
            "Withdraw enterExitQueue different address",
            [9, 0]
        );
        await tx;
    } catch (e) {
        console.error(e);
        throw e;
    } finally {
        await sim.close();
    }
});

test("Call claimExitedAssets", async () => {
    // Create Zemu object. Pass the path to your .elf file
    const sim = new Zemu(NANOS_ETH_PATH, { OpusPlugin: NANOS_PLUGIN_PATH });
    try {
        let eth = await startSimulator(sim);
        const positionTicket = 157489234;
        const timestamp = 1716235414;
        const exitQueueIndex = 655;
        const { data } = await contract.populateTransaction.claimExitedAssets(
            positionTicket,
            timestamp,
            exitQueueIndex
        );

        let unsignedTx = genericTx;
        unsignedTx.to = contractAddr;
        unsignedTx.data = data;

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
            "Claim exited assets",
            [6, 0]
        );
        await tx;
    } catch (e) {
        console.error(e);
        throw e;
    } finally {
        await sim.close();
    }
});

test("Call redeem", async () => {
    // Create Zemu object. Pass the path to your .elf file
    const sim = new Zemu(NANOS_ETH_PATH, { OpusPlugin: NANOS_PLUGIN_PATH });
    try {
        let eth = await startSimulator(sim);
        // Get address used in Ledger.
        const address = await eth.getAddress("44'/60'/0'/0");
        const receiver = address.address;
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const { data } = await contract.populateTransaction.redeem(
            maxUint256,
            receiver
        );

        let unsignedTx = genericTx;
        unsignedTx.to = contractAddr;
        unsignedTx.data = data;

        const serializedTx = ethers.utils
            .serializeTransaction(unsignedTx)
            .slice(2);

        const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

        await sim.waitUntilScreenIsNot(
            sim.getMainMenuSnapshot(),
            transactionUploadDelay
        );

        let nav = await sim.navigate(snapshotsDir, "Redeem", [8, 0]);
        await tx;
    } catch (e) {
        console.error(e);
        throw e;
    } finally {
        await sim.close();
    }
});

test("Call redeem with different address as receiver", async () => {
    // Create Zemu object. Pass the path to your .elf file
    const sim = new Zemu(NANOS_ETH_PATH, { OpusPlugin: NANOS_PLUGIN_PATH });
    try {
        let eth = await startSimulator(sim);
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const { data } = await contract.populateTransaction.redeem(
            maxUint256,
            receiverAddr
        );

        let unsignedTx = genericTx;
        unsignedTx.to = contractAddr;
        unsignedTx.data = data;

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
            "Redeem different address",
            [9, 0]
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
