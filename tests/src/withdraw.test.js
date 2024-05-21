import { runTest, contract } from "./utils.js";
import { BigNumber } from "ethers";

runTest("enterExitQueue", "0", async (eth) => {
    const address = await eth.getAddress("44'/60'/0'/0");
    const maxUint256 = BigNumber.from(2).pow(256).sub(1);
    const { data } = await contract.populateTransaction.enterExitQueue(
        maxUint256,
        address.address
    );
    return [data, [8, 0]];
});

runTest(
    "enterExitQueue with different address as receiver",
    "0",
    async (eth) => {
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const receiverAddr = "0x6050403020100efdeadbeefdeadbeefdea010203";
        const { data } = await contract.populateTransaction.enterExitQueue(
            maxUint256,
            receiverAddr
        );
        return [data, [9, 0]];
    }
);

runTest("claimExitedAssets", "0", async (eth) => {
    const positionTicket = 157489234;
    const timestamp = 1716235414;
    const exitQueueIndex = 655;
    const { data } = await contract.populateTransaction.claimExitedAssets(
        positionTicket,
        timestamp,
        exitQueueIndex
    );
    return [data, [6, 0]];
});

runTest("redeem", "0", async (eth) => {
    const address = await eth.getAddress("44'/60'/0'/0");
    const receiver = address.address;
    const maxUint256 = BigNumber.from(2).pow(256).sub(1);
    const { data } = await contract.populateTransaction.redeem(
        maxUint256,
        receiver
    );
    return [data, [8, 0]];
});

runTest("redeem with different address as receiver", "0", async (eth) => {
    const maxUint256 = BigNumber.from(2).pow(256).sub(1);
    const receiverAddr = "0x6050403020100efdeadbeefdeadbeefdea010203";
    const { data } = await contract.populateTransaction.redeem(
        maxUint256,
        receiverAddr
    );
    return [data, [9, 0]];
});

afterAll(async () => {
    await new Promise((resolve) => setTimeout(() => resolve(), 500)); // avoid jest open handle error
});
