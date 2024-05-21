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

const contract = new ethers.Contract(contractAddr, abi);
const snapshotsDir = "OpusPlugin";

test("Burn OS token", async () => {
    // Create Zemu object. Pass the path to your .elf file
    const sim = new Zemu(NANOS_ETH_PATH, { OpusPlugin: NANOS_PLUGIN_PATH });
    try {
        let eth = await startSimulator(sim);
        // Get address used in Ledger.
        const maxUint128 = BigNumber.from(2).pow(128).sub(1);
        const { data } = await contract.populateTransaction.burnOsToken(
            maxUint128
        );
        console.log("DATA: ", data);

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

        let nav = await sim.navigate(snapshotsDir, "Burn OsToken", [6, 0]);
        await tx;
    } catch (e) {
        console.error(e);
        throw e;
    } finally {
        await sim.close();
    }
});

test("Call liquidate Os Token", async () => {
    // Create Zemu object. Pass the path to your .elf file
    const sim = new Zemu(NANOS_ETH_PATH, { OpusPlugin: NANOS_PLUGIN_PATH });
    try {
        let eth = await startSimulator(sim);
        // Get address used in Ledger.
        const address = await eth.getAddress("44'/60'/0'/0");
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const owner = address.address;
        const receiver = address.address;
        const { data } = await contract.populateTransaction.liquidateOsToken(
            maxUint256,
            owner,
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

        let nav = await sim.navigate(snapshotsDir, "Liquidate OsToken", [9, 0]);
        await tx;
    } catch (e) {
        console.error(e);
        throw e;
    } finally {
        await sim.close();
    }
});

test("Call liquidate Os Token with different address as receiver", async () => {
    // Create Zemu object. Pass the path to your .elf file
    const sim = new Zemu(NANOS_ETH_PATH, { OpusPlugin: NANOS_PLUGIN_PATH });
    try {
        let eth = await startSimulator(sim);
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const owner = "0x6050403020100efdeadbeefdeadbeefdea010203";
        const receiver = "0x010203efdeadbeefdeadbeefdeadbeefde040506";
        const { data } = await contract.populateTransaction.liquidateOsToken(
            maxUint256,
            owner,
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

        let nav = await sim.navigate(
            snapshotsDir,
            "Liquidate OsToken different address",
            [10, 0]
        );
        await tx;
    } catch (e) {
        console.error(e);
        throw e;
    } finally {
        await sim.close();
    }
});

test("Call mint OsToken", async () => {
    // Create Zemu object. Pass the path to your .elf file
    const sim = new Zemu(NANOS_ETH_PATH, { OpusPlugin: NANOS_PLUGIN_PATH });
    try {
        let eth = await startSimulator(sim);
        const address = await eth.getAddress("44'/60'/0'/0");
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const receiver = address.address;
        const referrer = "0x6050403020100efdeadbeefdeadbeefdea010203";
        const { data } = await contract.populateTransaction.mintOsToken(
            receiver,
            maxUint256,
            referrer
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

        let nav = await sim.navigate(snapshotsDir, "Mint OsToken", [8, 0]);
        await tx;
    } catch (e) {
        console.error(e);
        throw e;
    } finally {
        await sim.close();
    }
});

test("Call mint OsToken with different address as receiver", async () => {
    // Create Zemu object. Pass the path to your .elf file
    const sim = new Zemu(NANOS_ETH_PATH, { OpusPlugin: NANOS_PLUGIN_PATH });
    try {
        let eth = await startSimulator(sim);
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const referrer = "0x6050403020100efdeadbeefdeadbeefdea010203";
        const receiver = "0x010203efdeadbeefdeadbeefdeadbeefde040506";
        const { data } = await contract.populateTransaction.mintOsToken(
            receiver,
            maxUint256,
            referrer
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
            "Mint OsToken different address",
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

test("Call redeem Os Token", async () => {
    // Create Zemu object. Pass the path to your .elf file
    const sim = new Zemu(NANOS_ETH_PATH, { OpusPlugin: NANOS_PLUGIN_PATH });
    try {
        let eth = await startSimulator(sim);
        // Get address used in Ledger.
        const address = await eth.getAddress("44'/60'/0'/0");
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const owner = address.address;
        const receiver = address.address;
        const { data } = await contract.populateTransaction.redeemOsToken(
            maxUint256,
            owner,
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

        let nav = await sim.navigate(snapshotsDir, "Redeem OsToken", [9, 0]);
        await tx;
    } catch (e) {
        console.error(e);
        throw e;
    } finally {
        await sim.close();
    }
});

test("Call redeem Os Token with different address as receiver", async () => {
    // Create Zemu object. Pass the path to your .elf file
    const sim = new Zemu(NANOS_ETH_PATH, { OpusPlugin: NANOS_PLUGIN_PATH });
    try {
        let eth = await startSimulator(sim);
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const owner = "0x6050403020100efdeadbeefdeadbeefdea010203";
        const receiver = "0x010203efdeadbeefdeadbeefdeadbeefde040506";
        const { data } = await contract.populateTransaction.redeemOsToken(
            maxUint256,
            owner,
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

        let nav = await sim.navigate(
            snapshotsDir,
            "Redeem OsToken different address",
            [10, 0]
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
