import { parseEther, parseUnits } from "ethers/lib/utils";
import { ethers } from "ethers";
import { resolve } from "path";
import Eth from "@ledgerhq/hw-app-eth";
import { generate_plugin_config } from "./generate_plugin_config";
import Zemu from "@zondax/zemu";

const snapshotsDir = "ChorusPlugin";
const transactionUploadDelay = 60000;

const NANOS_ETH_PATH = resolve("elfs/ethereum_nanos.elf");
const NANOX_ETH_PATH = resolve("elfs/ethereum_nanox.elf");

const NANOS_PLUGIN_PATH = resolve("elfs/plugin_nanos.elf");
const NANOX_PLUGIN_PATH = resolve("elfs/plugin_nanox.elf");

const STAKEWISE_CONTRACT_ADDRESS = "0xe6d8d8ac54461b1c5ed15740eee322043f696c08";
const EIGENLAYER_CONTRACT_ADDRESS =
    "0x39053d51b77dc0d36036fc1fcc8cb819df8ef37a";
const SYMBIOTIC_CONTRACT_ADDRESS = "0xc329400492c6ff2438472d4651ad17389fcb843a";

const STAKEWISE_ABI_PATH = resolve("../utils/StakewiseAbi.json");
const EIGENLAYER_ABI_PATH = resolve("../utils/EigenlayerAbi.json");
const SYMBIOTIC_ABI_PATH = resolve("../utils/SymbioticAbi.json");

const stakewiseAbi = require(STAKEWISE_ABI_PATH);
const eigenlayerAbi = require(EIGENLAYER_ABI_PATH);
const symbioticAbi = require(SYMBIOTIC_ABI_PATH);

const stakewiseContract = new ethers.Contract(
    STAKEWISE_CONTRACT_ADDRESS,
    stakewiseAbi
);

const eigenlayerContract = new ethers.Contract(
    EIGENLAYER_CONTRACT_ADDRESS,
    eigenlayerAbi
);

const symbioticContract = new ethers.Contract(
    SYMBIOTIC_CONTRACT_ADDRESS,
    symbioticAbi
);

jest.setTimeout(20000);

const writePng = async (path, data) => {
    return new Promise((resolve, reject) => {
        _fs.promises.writeFile(path, data, (err) => {
            if (err) {
                reject(err);
            } else {
                resolve();
            }
        });
    });
};

const zemu_options = {
    X11: true,
    logging: true,
    startDelay: 5000,
    startText: "is ready",
    model: "nanos",
};

const startSimulator = async (sim) => {
    // Create Zemu object. Pass the path to your .elf file
    await sim.start(zemu_options);
    const transport = await sim.getTransport();
    const eth = new Eth(transport);

    let abis = {
        [STAKEWISE_CONTRACT_ADDRESS]: stakewiseAbi,
        [EIGENLAYER_CONTRACT_ADDRESS]: eigenlayerAbi,
        [SYMBIOTIC_CONTRACT_ADDRESS]: symbioticAbi,
    };
    eth.setLoadConfig({
        baseURL: null,
        extraPlugins: generate_plugin_config(abis),
    });
    return eth;
};

/*
 * Run a test with a given name, value in Eth, and a function that returns the contract data
 * and instructions to navigate the simulator to the correct screen.
 * @param {String} testName - The name of the test
 * @param {String} valueEth - The value in Eth to send in the transaction
 * @param {String} contract - The contract to interact with: can be either "stakewise" or "eigenlayer"
 * @param {Function} getContractData - A function that returns the contract data and navigation instructions
 */
const runTest = async (
    testName,
    getContractData,
    valueEth = "0",
    contract = "stakewise"
) => {
    test(testName, async () => {
        const sim = new Zemu(NANOS_ETH_PATH, {
            ChorusPlugin: NANOS_PLUGIN_PATH,
        });
        try {
            let eth = await startSimulator(sim);
            const [data, nav] = await getContractData(eth);

            let contractAddr;
            if (contract === "stakewise") {
                contractAddr = STAKEWISE_CONTRACT_ADDRESS;
            } else if (contract === "eigenlayer") {
                contractAddr = EIGENLAYER_CONTRACT_ADDRESS;
            } else if (contract == "symbiotic") {
                contractAddr = SYMBIOTIC_CONTRACT_ADDRESS;
            } else {
                throw new Error(
                    "Invalid contract specified. Must be 'stakewise', 'eigenlayer' or 'symbiotic'"
                );
            }
            let unsignedTx = {
                nonce: Number(0),
                gasLimit: Number(21000),
                gasPrice: parseUnits("1", "gwei"),
                value: parseEther(valueEth),
                chainId: 1,
                to: contractAddr,
                data: data,
            };

            const serializedTx = ethers.utils
                .serializeTransaction(unsignedTx)
                .slice(2);

            const tx = eth.signTransaction("44'/60'/0'/0", serializedTx);

            await sim.waitUntilScreenIsNot(
                sim.getMainMenuSnapshot(),
                transactionUploadDelay
            );

            await sim.navigateAndCompareSnapshots(snapshotsDir, testName, nav);
            await tx;
        } catch (e) {
            console.error(e);
            throw e;
        } finally {
            await sim.close();
        }
    });
};

module.exports = {
    stakewiseContract,
    eigenlayerContract,
    symbioticContract,
    runTest,
};
