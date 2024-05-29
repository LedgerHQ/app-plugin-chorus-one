import { runTest, stakewiseContract } from "./utils.js";
import { BigNumber } from "ethers";

runTest("Burn OS token", async (_eth) => {
    const maxUint128 = BigNumber.from(2).pow(128).sub(1);
    const { data } = await stakewiseContract.populateTransaction.burnOsToken(
        maxUint128
    );
    return [data, [6, 0]];
});

runTest("Liquidate Os Token", async (eth) => {
    const address = await eth.getAddress("44'/60'/0'/0");
    const maxUint256 = BigNumber.from(2).pow(256).sub(1);
    const owner = address.address;
    const receiver = address.address;
    const { data } =
        await stakewiseContract.populateTransaction.liquidateOsToken(
            maxUint256,
            owner,
            receiver
        );
    return [data, [9, 0]];
});

runTest(
    "Liquidate Os Token with different address as receiver",
    async (eth) => {
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const owner = "0x6050403020100efdeadbeefdeadbeefdea010203";
        const receiver = "0x010203efdeadbeefdeadbeefdeadbeefde040506";
        const { data } =
            await stakewiseContract.populateTransaction.liquidateOsToken(
                maxUint256,
                owner,
                receiver
            );
        return [data, [10, 0]];
    }
);

runTest("Mint OsToken", async (eth) => {
    const address = await eth.getAddress("44'/60'/0'/0");
    const maxUint256 = BigNumber.from(2).pow(256).sub(1);
    const receiver = address.address;
    const referrer = "0x6050403020100efdeadbeefdeadbeefdea010203";
    const { data } = await stakewiseContract.populateTransaction.mintOsToken(
        receiver,
        maxUint256,
        referrer
    );
    return [data, [8, 0]];
});

runTest("Mint OsToken with different address as receiver", async (eth) => {
    const maxUint256 = BigNumber.from(2).pow(256).sub(1);
    const referrer = "0x6050403020100efdeadbeefdeadbeefdea010203";
    const receiver = "0x010203efdeadbeefdeadbeefdeadbeefde040506";
    const { data } = await stakewiseContract.populateTransaction.mintOsToken(
        receiver,
        maxUint256,
        referrer
    );
    return [data, [9, 0]];
});

runTest("Redeem OsToken", async (eth) => {
    const address = await eth.getAddress("44'/60'/0'/0");
    const maxUint256 = BigNumber.from(2).pow(256).sub(1);
    const owner = address.address;
    const receiver = address.address;
    const { data } = await stakewiseContract.populateTransaction.redeemOsToken(
        maxUint256,
        owner,
        receiver
    );
    return [data, [9, 0]];
});

runTest("Redeem OsToken with different address as receiver", async (eth) => {
    const maxUint256 = BigNumber.from(2).pow(256).sub(1);
    const owner = "0x6050403020100efdeadbeefdeadbeefdea010203";
    const receiver = "0x010203efdeadbeefdeadbeefdeadbeefde040506";
    const { data } = await stakewiseContract.populateTransaction.redeemOsToken(
        maxUint256,
        owner,
        receiver
    );
    return [data, [10, 0]];
});

afterAll(async () => {
    await new Promise((resolve) => setTimeout(() => resolve(), 500)); // avoid jest open handle error
});
