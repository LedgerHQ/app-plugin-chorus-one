function serialize_data(pluginName, contractAddress, selector) {
    const len = Buffer.from([pluginName.length]);
    const name = Buffer.from(pluginName);
    const address = Buffer.from(contractAddress.slice(2), "hex");
    const methodid = Buffer.from(selector.slice(2), "hex");

    // Taking .slice(2) to remove the "0x" prefix
    return Buffer.concat([len, name, address, methodid]);
}

// Function to generate the plugin configuration.
function generate_plugin_config(abis) {
    // Load the b2c.json file
    const b2c = require("../b2c.json");

    let res = {};

    // Place holder signature
    const PLACE_HOLDER_SIGNATURE =
        "3045022100f6e1a922c745e244fa3ed9a865491672808ef93f492ee0410861d748c5de201f0220160d6522499f3a84fa3e744b3b81e49e129e997b28495e58671a1169b16fa777";

    // Iterate through contracts in b2c.json file
    for (let contract of b2c["contracts"]) {
        let methods_info = {};
        const contractAddress = contract["address"];
        for (let [selector, values] of Object.entries(contract["selectors"])) {
            // Gather up the info needed for the end result
            const pluginName = values["plugin"];
            const serializedData = serialize_data(
                pluginName,
                contractAddress,
                selector
            );
            const signature = PLACE_HOLDER_SIGNATURE;

            methods_info[selector] = {
                plugin: pluginName,
                serialized_data: serializedData,
                signature: signature,
            };
        }
        // Add the abi to methods_info
        methods_info["abi"] = abis[contractAddress];
        // Add the methods_info to the end result
        res[contractAddress] = methods_info;
    }
    return res;
}

module.exports = {
    generate_plugin_config,
};
