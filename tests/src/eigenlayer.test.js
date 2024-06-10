import { BigNumber } from "ethers";
import { runTest, eigenlayerContract } from "./utils.js";

runTest(
    "Eigenlayer delegateTo",
    async (_eth) => {
        const operator = "0x0102030000000000000000000000000000030201";
        const signatureExpiry = {
            signature:
                "0x0102032222222222222222222222222222222222222222222222222222222222223333333333333333333333333333333333333333333333333333333333040506",
            expiry: "123456789",
        };
        const approverSalt =
            "0xfffefdfffffffffffffffffffffffffffffffffffffffffffffffffffffcfbfa";

        const { data } =
            await eigenlayerContract.populateTransaction.delegateTo(
                operator,
                signatureExpiry,
                approverSalt
            );
        return [data, [7, 0]];
    },
    "0",
    "eigenlayer"
);

runTest(
    "Eigenlayer increase delegated shares",
    async (eth) => {
        const receiver = await eth.getAddress("44'/60'/0'/0");
        const strategy = "0x0405060000000000000000000000000000070809";
        const shares = BigNumber.from(2).pow(256).sub(1);

        const { data } =
            await eigenlayerContract.populateTransaction.increaseDelegatedShares(
                receiver.address,
                strategy,
                shares
            );
        return [data, [10, 0]];
    },
    "0",
    "eigenlayer"
);

runTest(
    "Eigenlayer increase delegated shares with different receiver",
    async (_eth) => {
        const receiver = "0x0102030000000000000000000000000000030201";
        const strategy = "0x0405060000000000000000000000000000070809";
        const shares = BigNumber.from(2).pow(256).sub(1);

        const { data } =
            await eigenlayerContract.populateTransaction.increaseDelegatedShares(
                receiver,
                strategy,
                shares
            );
        return [data, [11, 0]];
    },
    "0",
    "eigenlayer"
);

runTest(
    "Eigenlayer decrease delegated shares",
    async (eth) => {
        const receiver = await eth.getAddress("44'/60'/0'/0");
        const strategy = "0x0405060000000000000000000000000000070809";
        const shares = BigNumber.from(2).pow(256).sub(1);

        const { data } =
            await eigenlayerContract.populateTransaction.decreaseDelegatedShares(
                receiver.address,
                strategy,
                shares
            );
        return [data, [10, 0]];
    },
    "0",
    "eigenlayer"
);

runTest(
    "Eigenlayer decrease delegated shares with different receiver",
    async (_eth) => {
        const receiver = "0x0102030000000000000000000000000000030201";
        const strategy = "0x0405060000000000000000000000000000070809";
        const shares = BigNumber.from(2).pow(256).sub(1);

        const { data } =
            await eigenlayerContract.populateTransaction.decreaseDelegatedShares(
                receiver,
                strategy,
                shares
            );
        return [data, [11, 0]];
    },
    "0",
    "eigenlayer"
);
