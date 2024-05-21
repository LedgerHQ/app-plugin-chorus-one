import { abi, runTest, CONTRACT_ADDRESS } from "./utils.js";
import { ethers, BigNumber } from "ethers";

jest.setTimeout(20000);

const contract = new ethers.Contract(CONTRACT_ADDRESS, abi);

runTest("Burn OS token", "0", async (_eth) => {
    const maxUint128 = BigNumber.from(2).pow(128).sub(1);
    const { data } = await contract.populateTransaction.burnOsToken(maxUint128);
    return [data, [6, 0]];
});

runTest("Liquidate Os Token", "0", async (eth) => {
    const address = await eth.getAddress("44'/60'/0'/0");
    const maxUint256 = BigNumber.from(2).pow(256).sub(1);
    const owner = address.address;
    const receiver = address.address;
    const { data } = await contract.populateTransaction.liquidateOsToken(
        maxUint256,
        owner,
        receiver
    );
    return [data, [9, 0]];
});

runTest(
    "Liquidate Os Token with different address as receiver",
    "0",
    async (eth) => {
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const owner = "0x6050403020100efdeadbeefdeadbeefdea010203";
        const receiver = "0x010203efdeadbeefdeadbeefdeadbeefde040506";
        const { data } = await contract.populateTransaction.liquidateOsToken(
            maxUint256,
            owner,
            receiver
        );
        return [data, [10, 0]];
    }
);

runTest("Mint OsToken", "0", async (eth) => {
    const address = await eth.getAddress("44'/60'/0'/0");
    const maxUint256 = BigNumber.from(2).pow(256).sub(1);
    const receiver = address.address;
    const referrer = "0x6050403020100efdeadbeefdeadbeefdea010203";
    const { data } = await contract.populateTransaction.mintOsToken(
        receiver,
        maxUint256,
        referrer
    );
    return [data, [8, 0]];
});

runTest("Mint OsToken with different address as receiver", "0", async (eth) => {
    const maxUint256 = BigNumber.from(2).pow(256).sub(1);
    const referrer = "0x6050403020100efdeadbeefdeadbeefdea010203";
    const receiver = "0x010203efdeadbeefdeadbeefdeadbeefde040506";
    const { data } = await contract.populateTransaction.mintOsToken(
        receiver,
        maxUint256,
        referrer
    );
    return [data, [9, 0]];
});

runTest("Redeem OsToken", "0", async (eth) => {
    const address = await eth.getAddress("44'/60'/0'/0");
    const maxUint256 = BigNumber.from(2).pow(256).sub(1);
    const owner = address.address;
    const receiver = address.address;
    const { data } = await contract.populateTransaction.redeemOsToken(
        maxUint256,
        owner,
        receiver
    );
    return [data, [9, 0]];
});

runTest(
    "Redeem OsToken with different address as receiver",
    "0",
    async (eth) => {
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const owner = "0x6050403020100efdeadbeefdeadbeefdea010203";
        const receiver = "0x010203efdeadbeefdeadbeefdeadbeefde040506";
        const { data } = await contract.populateTransaction.redeemOsToken(
            maxUint256,
            owner,
            receiver
        );
        return [data, [10, 0]];
    }
);

afterAll(async () => {
    await new Promise((resolve) => setTimeout(() => resolve(), 500)); // avoid jest open handle error
});
