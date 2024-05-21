import { runTest, contract } from "./utils.js";

runTest("Deposit 1 Eth", "1", async (eth) => {
    const address = await eth.getAddress("44'/60'/0'/0");
    const referrerAddr = "0x010203efdeadbeefdeadbeefdeadbeefde040506";
    const { data } = await contract.populateTransaction.deposit(
        address.address,
        referrerAddr
    );
    return [data, [4, 0]];
});

runTest(
    "Deposit 1 Eth with different address as receiver",
    "1",
    async (eth) => {
        const receiverAddr = "0x6050403020100efdeadbeefdeadbeefdea010203";
        const referrerAddr = "0x010203efdeadbeefdeadbeefdeadbeefde040506";
        const { data } = await contract.populateTransaction.deposit(
            receiverAddr,
            referrerAddr
        );
        return [data, [5, 0]];
    }
);

afterAll(async () => {
    await new Promise((resolve) => setTimeout(() => resolve(), 500)); // avoid jest open handle error
});
