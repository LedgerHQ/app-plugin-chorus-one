import { runTest, stakewiseContract } from "./utils.js";

runTest(
    "Deposit 1 Eth",
    async (eth) => {
        const address = await eth.getAddress("44'/60'/0'/0");
        const referrerAddr = "0x010203efdeadbeefdeadbeefdeadbeefde040506";
        const { data } = await stakewiseContract.populateTransaction.deposit(
            address.address,
            referrerAddr
        );
        return [data, [4, 0]];
    },
    "1"
);

runTest(
    "Deposit 1 Eth with different address as receiver",
    async (eth) => {
        const receiverAddr = "0x6050403020100efdeadbeefdeadbeefdea010203";
        const referrerAddr = "0x010203efdeadbeefdeadbeefdeadbeefde040506";
        const { data } = await stakewiseContract.populateTransaction.deposit(
            receiverAddr,
            referrerAddr
        );
        return [data, [5, 0]];
    },
    "1"
);

afterAll(async () => {
    await new Promise((resolve) => setTimeout(() => resolve(), 500)); // avoid jest open handle error
});
