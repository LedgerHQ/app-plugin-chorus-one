import { parseEther, parseUnits } from "ethers/lib/utils";
import { resolve } from "path";
import Eth from "@ledgerhq/hw-app-eth";
import { generate_plugin_config } from "./generate_plugin_config";

const zeroAddr = "0x0000000000000000000000000000000000000000";

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

const abiPath = resolve("../utils/StakewiseAbi.json");
const abi = require(abiPath);

let genericTx = {
    nonce: Number(0),
    gasLimit: Number(21000),
    gasPrice: parseUnits("1", "gwei"),
    value: parseEther("0"),
    chainId: 1,
    to: zeroAddr,
    data: null,
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

    eth.setLoadConfig({
        baseURL: null,
        extraPlugins: generate_plugin_config(abi),
    });
    return eth;
};

module.exports = {
    genericTx,
    writePng,
    startSimulator,
    abi,
};
