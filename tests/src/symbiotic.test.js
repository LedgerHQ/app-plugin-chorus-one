import { BigNumber } from "ethers";
import { runTest, symbioticContract } from "./utils.js";

runTest(
    "Symbiotic deposit",
    async (_eth) => {
        const recipient = "0x0102030000000000000000000000000000030201";
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);

        const { data } = await symbioticContract.populateTransaction[
            "deposit(address,uint256)"
        ](recipient, maxUint256);
        return [data, [9, 0]];
    },
    "0",
    "symbiotic"
);

runTest(
    "Symbiotic issue debt",
    async (_eth) => {
        const recipient = "0x0102030000000000000000000000000000030201";
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);

        const { data } = await symbioticContract.populateTransaction.issueDebt(
            recipient,
            maxUint256
        );
        return [data, [9, 0]];
    },
    "0",
    "symbiotic"
);

runTest(
    "Symbiotic withdraw",
    async (_eth) => {
        const recipient = "0x0102030000000000000000000000000000030201";
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);

        const { data } = await symbioticContract.populateTransaction.withdraw(
            recipient,
            maxUint256
        );
        return [data, [9, 0]];
    },
    "0",
    "symbiotic"
);

runTest(
    "Symbiotic deposit with signature",
    async (_eth) => {
        const recipient = "0x0102030000000000000000000000000000030201";
        const maxUint256 = BigNumber.from(2).pow(256).sub(1);
        const v = 27;
        const r =
            "0x0102030000000000000000000000000000000000000000000000000000040506";
        const s =
            "0x07080900000000000000000000000000000000000000000000000000000a0b0c";

        console.log(symbioticContract.populateTransaction);
        const { data } = await symbioticContract.populateTransaction[
            "deposit(address,uint256,uint256,uint8,bytes32,bytes32)"
        ](recipient, maxUint256, 0, v, r, s);
        return [data, [14, 0]];
    },
    "0",
    "symbiotic"
);
